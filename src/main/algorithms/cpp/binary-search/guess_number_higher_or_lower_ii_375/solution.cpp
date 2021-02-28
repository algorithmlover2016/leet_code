#include "../../head.h"


class Solution {
public:
    int getMoneyAmount(int n) {
        // at first, I think it's to construct a binary tree with some future
        // plagiarizing idea from https://leetcode.com/problems/guess-number-higher-or-lower-ii/discuss/84764/Simple-DP-solution-with-explanation~~
        std::vector<std::vector<int>> dpMemo(n + 1, std::vector<int>(n + 1, INIT_FLAG));
        return dfs(dpMemo, 1, n);
    }

    int dfs(std::vector<std::vector<int>> & dpMemo, int start, int end) {
        if (start >= end) {
            return 0;
        }
        if (INIT_FLAG != dpMemo[start][end]) {
            return dpMemo[start][end];
        }
        // we have to take each probility
        int ans = INIT_MAX;
        for (int split = start; split <= end; split++) {
            int curSplitAns = split + std::max(dfs(dpMemo, start, split - 1), dfs(dpMemo, split + 1, end));
            ans = std::min(ans, curSplitAns);
        }
        return dpMemo[start][end] = ans;
    }
private:
    int const INIT_FLAG = 0; // because we need use dpMemo[0][*] = 0;
    int const INIT_MAX = INT_MAX;
};

class Solution {
public:
    int getMoneyAmount(int n) {
        // plagiairizing from https://leetcode.com/problems/guess-number-higher-or-lower-ii/discuss/84764/Simple-DP-solution-with-explanation~~
        std::vector<std::vector<int>> dpMemo(n + 1, std::vector<int>(n + 1, INIT_FLAG));
        for (int len = 2; len <= n; len++) {
            for (int left = 1; left + len - 1 <= n; left++) {
                int right = left + len - 1;
                int ans = INIT_MAX;
                for (int split = left + 1; split < right; split++) {
                    int curAns = split + std::max(dpMemo[left][split - 1], dpMemo[split + 1][right]);
                    ans = std::min(ans, curAns);

                }
                dpMemo[left][right] = (left + 1 == right ? left : ans);
            }
        }
        return dpMemo[1][n];
    }

private:
    int const INIT_FLAG = 0; // because we need use dpMemo[0][*] = 0;
    int const INIT_MAX = INT_MAX;
};
