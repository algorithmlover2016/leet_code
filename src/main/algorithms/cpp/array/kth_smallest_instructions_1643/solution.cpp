#include "../../head.h"


class Solution {
public:
    std::string kthSmallestPath(std::vector<int> const & destination, int k) {
        // plagiarizing from https://leetcode.com/problems/kth-smallest-instructions/discuss/918436/Java-O(r*c)-very-easy-to-understand
        if (JUST_TWO > destination.size()) {
            return "";
        }
        int const hCnts = destination[HORIZONTAL_IDX];
        int const vCnts = destination[VERTICAL_IDX];
        std::vector<std::vector<int>> dpMemo(vCnts + 1, std::vector<int>(hCnts + 1, 0));
        for (int row = vCnts; row > EXCLUDE_MOST_LEFT_IDX; row--) {
            for (int col = hCnts; col >EXCLUDE_MOST_LEFT_IDX; col--) {
                if (row == vCnts && col == hCnts) {
                    // start from the buttom-right corner;
                    dpMemo[row][col] = 1;
                } else if (row == vCnts) {
                    // if we reach at vCnts(the buttom), we can only go left, which means
                    // we we want to arrive at this postion, the previous step must be its right position
                    dpMemo[row][col] = dpMemo[row][col + 1];
                } else if (col == hCnts) {
                    // if we reach at the hCnts(the right border), we can only go to up row.
                    // which means if we want to arrive at this postion, we can only go from bellow row
                    dpMemo[row][col] = dpMemo[row + 1][col];
                } else {
                    // because this problem only allow us move to right or down. So we can get this position
                    // from right or down if we start from right-buttom
                    dpMemo[row][col] = dpMemo[row + 1][col] + dpMemo[row][col + 1];
                }
            }
        }
        std::string ans;
        dfsHelper(dpMemo, 0, 0, k, ans);
        return ans;
    }
    void dfsHelper(std::vector<std::vector<int>> const & dpMemo, int row, int col, int leftSeqs, std::string & ans) {
        int const rowSize = dpMemo.size();
        int const colSize = dpMemo[row].size();
        if (row == rowSize - 1) {
            // we arrive at the buttom, we can only go to right;
            ans.append(colSize - 1 - col, 'H');
            return;
        }
        if (col == colSize - 1) {
            // we arrive the right most border, we can only go down
            ans.append(rowSize - 1 - row, 'V');
            return;
        }
        // because go to right, we append H which is smaller than V if we go down
        // so if the next Horizontal direction meets we can go to the target position, we first choose it
        if (dpMemo[row][col + 1] >= leftSeqs) {
            ans.append(1, 'H');
            dfsHelper(dpMemo, row, col + 1, leftSeqs, ans);
        } else {
            ans.append(1, 'V');
            dfsHelper(dpMemo, row + 1, col, leftSeqs - dpMemo[row][col + 1], ans);
        }
    }

private:
    static int const JUST_TWO = 2;
    static int const HORIZONTAL_IDX = 1;
    static int const VERTICAL_IDX = 0;
    static int const EXCLUDE_MOST_LEFT_IDX = -1;
};

class Solution {
public:
    std::string kthSmallestPath(std::vector<int> const & destination, int k) {
        int m = destination[0] + 1, n = destination[1] + 1;
        std::vector<std::vector<int>> dp(m, std::vector<int>(n, 1));
        for (int i = 1; i < m; i++) {
            for(int j = 1; j < n; j++) {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }

        std::string result;
        int x = m - 1, y = n - 1;
        for (int i = 0; i < m + n - 2; i++) {
            if (y >= 1 && k<= dp[x][y - 1]) {
                result.push_back('H');
                y--;
            } else {
                result.push_back('V');
                if (y >= 1) {
                    k-= dp[x][y-1];
                }
                x--;
            }
        }
        return result;
    }
};
