#include "../../head.h"


class Solution {
public:
    int maxProductPath(std::vector<std::vector<int>> const & grid) {
        // plagiarizing idea from https://leetcode.com/problems/maximum-non-negative-product-in-a-matrix/discuss/855082/C%2B%2B-Dynamic-Programming-With-Comments
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }
        int const rowSize = grid.size();
        int const colSize = grid[0].size();
        std::vector<std::vector<std::vector<long>>> dpMemo(rowSize,
                std::vector<std::vector<long>>(colSize, std::vector<long>(2)));
        // dpMemo[row][col][0] means the max product at cur position (row, col)
        // dpMemo[row][col][1] means the min product at cur position (row, col)
        dpMemo[0][0][0] = dpMemo[0][0][1] = grid[0][0];
        for (int row = 1; row < rowSize; row++) {
            dpMemo[row][0][0] = dpMemo[row][0][1] = dpMemo[row - 1][0][0] * grid[row][0];
        }
        for (int col = 1; col < colSize; col++) {
            dpMemo[0][col][0] = dpMemo[0][col][1] = dpMemo[0][col - 1][0] * grid[0][col];
        }
        for (int row = 1; row < rowSize; row++) {
            for (int col = 1; col < colSize; col++) {
                if (0 < grid[row][col]) {
                    // the max
                    dpMemo[row][col][0] = std::max(dpMemo[row - 1][col][0], dpMemo[row][col - 1][0]) * grid[row][col];

                    // the min
                    dpMemo[row][col][1] = std::min(dpMemo[row - 1][col][1], dpMemo[row][col - 1][1]) * grid[row][col];
                } else {
                    // the max
                    dpMemo[row][col][0] = std::min(dpMemo[row - 1][col][1], dpMemo[row][col - 1][1]) * grid[row][col];

                    // the min
                    dpMemo[row][col][1] = std::max(dpMemo[row - 1][col][0], dpMemo[row][col - 1][0]) * grid[row][col];
                }
            }
        }

        return dpMemo[rowSize -1][colSize - 1][0] >= 0 ? dpMemo[rowSize -1][colSize - 1][0] % MOD : -1;
    }

private:
    static int const MOD = 1e9 + 7;
};
