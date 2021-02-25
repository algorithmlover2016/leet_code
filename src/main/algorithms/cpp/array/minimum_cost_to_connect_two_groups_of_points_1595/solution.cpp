#include "../../head.h"


class Solution {
public:
    int connectTwoGroups(std::vector<std::vector<int>> const & cost) {
        // plagiarizing idea from https://youtu.be/hq0IVf1Falk
        if (cost.empty() || cost[0].empty()) {
            return 0;
        }

        int const rowSize = cost.size();
        int const colSize = cost[0].size();

        std::vector<int> minRow(rowSize, INIT_MAX);
        for (int row = 0; row < rowSize; row++) {
            minRow[row] = *std::min_element(cost[row].begin(), cost[row].end());
        }

        std::unordered_map<int, int> status2Val;
        return dp(0, 0, cost, minRow, status2Val);
    }
    int dp(int col, int mask,
            std::vector<std::vector<int>> const & cost,
            std::vector<int> const & minRow,
            std::unordered_map<int, int> & status2Val) {
        int const rowSize = cost.size();
        int const colSize = cost[0].size();

        int coded = encode(col, mask);

        if (status2Val.find(coded) != status2Val.end()) {
            return status2Val[coded];
        }

        if (col == colSize) {
            int ans = 0;
            for (int row = 0; row < rowSize; row++) {
                if (0 == (mask & (1 << row))) {
                    // the row has not been connected with any column
                    // connected this row with the min cost col
                    ans += minRow[row];
                }
            }
            return status2Val[coded] = ans;
        }
        int ans = INIT_MAX;
        for (int row = 0; row < rowSize; row++) {
            ans = std::min(ans,
                    dp(col + 1, mask | (1 << row), cost, minRow, status2Val) + cost[row][col]);
        }
        return status2Val[coded] = ans;
    }


private:
    void decode(int coded, int & row, int & mask) {
        mask = coded & POS_RESET;
        row = (coded >> POS_SHIFT_BITS) & POS_RESET;
    }

    int encode(int pos, int mask) {
        return ((pos & POS_RESET) << POS_SHIFT_BITS) | (mask & POS_RESET);
    }
private:
    static int const POS_SHIFT_BITS = 16;
    static int const POS_RESET = 0xFFFF;
    int const INIT_MAX = INT_MAX;
};

class Solution {
public:
    int dp[13][4096] = {};

    int dfs(std::vector<std::vector<int>>& cost, std::vector<int> & min_sz2, int i, int mask) {

        if (dp[i][mask])
            return dp[i][mask] - 1;

        int res = i >= cost.size() ? 0 : INT_MAX;

        if (i >= cost.size()) {
            for (auto j = 0; j < cost[0].size(); ++j) {
                res += min_sz2[j] * ((mask & (1 << j)) == 0);
            }
        } else {
            for (auto j = 0; j < cost[0].size(); ++j) {
                res = std::min(res, cost[i][j] + dfs(cost, min_sz2, i + 1, mask | (1 << j)));
            }
        }

        return dp[i][mask] = res + 1;
    }

    int connectTwoGroups(std::vector<std::vector<int>> const & cost) {

        std::vector<int> min_sz2(cost[0].size(), INT_MAX);

        for (int j = 0; j < min_sz2.size(); ++j) {
            for (int i = 0; i < cost.size(); ++i) {
                min_sz2[j] = std::min(min_sz2[j], cost[i][j]);
            }
        }
        return dfs(cost, min_sz2, 0, 0);
    }
};

class Solution {
public:
    int link[13], visx[13], visy[13], lx[13], ly[13];
    int n, m;
    std::vector<std::vector<int>> w;

    Solution() : w(std::vector<std::vector<int>>(13, std::vector<int> (13))) {
    }

    int can(int t) {
        visx[t] = 1;
        for(int i = 1; i <= m; i++){
            //这里“lx[t]+ly[i]==w[t][i]”决定了这是在相等子图中找增广路的前提，非常重要
            if(!visy[i] && lx[t] + ly[i] == w[t][i]){
                visy[i] = 1;
                if(link[i] == -1 || can(link[i])){
                    link[i] = t;
                    return 1;
                }
            }
        }
        return 0;
    }

    int km(){
        int sum = 0; memset(ly, 0, sizeof(ly));
        for(int i = 1; i <= n; i++){//把各个lx的值都设为当前w[i][j]的最大值
        lx[i] = INT_MIN;
        for(int j = 1; j <= n; j++){
            if(lx[i] < w[i][j])
                lx[i] = w[i][j];
            }
        }
        memset(link, -1, sizeof(link));
        for(int i = 1; i <= n; i++){
            while(1){
                memset(visx, 0, sizeof(visx));
                memset(visy, 0, sizeof(visy));
                if(can(i))//如果它能够形成一条增广路径，那么就break
                    break;
                int d = INT_MAX;//否则，后面应该加入新的边,这里应该先计算d值
                //对于搜索过的路径上的XY点，设该路径上的X顶点集为S，Y顶点集为T，对所有在S中的点xi及不在T中的点yj
                for(int j = 1; j <= n; j++)
                    if(visx[j])
                    for(int k = 1; k <= m; k++)
                       if(!visy[k])
                            d = min(d, lx[j] + ly[k] - w[j][k]);
                if(d == INT_MAX)
                    return -1;//找不到可以加入的边，返回失败（即找不到完美匹配）
                for (int j = 1; j <= n; j++)
                    if (visx[j])
                        lx[j] -= d;
                for(int j = 1; j <= m; j++)
                    if(visy[j])
                        ly[j] += d;
                }
        }
        for(int i = 1; i <= m; i++)
            if(link[i] > -1)
                sum += w[link[i]][i];
        return sum;
    }
    int connectTwoGroups(std::vector<std::vector<int>> & cost) {
        n = cost.size();
        m = cost[0].size();
        int tn = n, tm = m;
        n = std::max(n, m);
        m = n;  //转换成方阵才能过
        std::vector<int> lmin(tn + 1, INT_MAX), rmin(tm + 1, INT_MAX);
        for (int i = 1; i <= tn; ++i) {
            for (int j = 1; j <= tm; ++j) {
                lmin[i] = std::min(lmin[i], cost[i - 1][j - 1]);
                rmin[j] = std::min(rmin[j], cost[i - 1][j - 1]);
            }
        }
        int ans = std::accumulate(lmin.begin() + 1, lmin.end(), 0) +
            std::accumulate(rmin.begin() + 1, rmin.end(), 0);
        for (int i = 1; i <= tn; ++i) {
            for (int j = 1; j <= tm; ++j) {
                w[i][j] = max(0 , lmin[i] + rmin[j] - cost[i - 1][j - 1]);
            }
        }
        return ans - km();
    }
};
