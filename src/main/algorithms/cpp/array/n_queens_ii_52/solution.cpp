#include "../../head.h"


class Solution {
public:
    int totalNQueens(int n) {
        // plagiarizing from https://leetcode.com/problems/n-queens/discuss/19808/Accepted-4ms-c%2B%2B-solution-use-backtracking-and-bitmask-easy-understand.
        // (row, col) and row range from 0 to n(not include)
        std::vector<int> notUse(n, 0);

        // (row, col) the slope is y = x + b. b is from -(n - 1) to n - 1.
        // because the index >= 0. so we add an offset n-1. so b range from 0 to 2n - 2; total 2n - 1 numbers
        // the index can be represent by n - 1 + x - y which is b because b is the line
        std::vector<int> lineSlope45(2 * n - 1, 0);

        // (row, col) the slope is y = -x + b. b is from 0 to 2n -2, total 2n - 1 numbers
        // the index can be represent by x + y
        std::vector<int> lineSlope135(2 * n - 1, 0);

        int ans = 0;
        backTracking(0, n, notUse, lineSlope45, lineSlope135, ans);
        return ans;
    }
    void backTracking(int row,
            int n,
            std::vector<int> & notUse,
            std::vector<int> & lineSlope45,
            std::vector<int> & lineSlope135,
            int & ans) {
        if (row == n) {
            ans++;
            return;
        }
        for (int col = 0; col < n; col++) {
            if (notUse[col] ||
                    lineSlope45[n - 1 + col - row] ||
                    lineSlope135[row + col]) {
                continue;
            }
            notUse[col] = lineSlope45[n - 1 + col - row] = lineSlope135[row + col] = 1;
            backTracking(row + 1, n, notUse, lineSlope45, lineSlope135, ans);
            notUse[col] = lineSlope45[n - 1 + col - row] = lineSlope135[row + col] = 0;
        }
    }
};
