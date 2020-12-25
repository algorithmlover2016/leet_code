#include "../../head.h"


class Solution {
public:
    int cherryPickup(std::vector<std::vector<int>> const & grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }
        int const gridRowSize = grid.size();
        int const gridColSize = grid[gridRowSize - 1].size();

        std::vector<std::vector<std::vector<int>>> dpMemo(gridRowSize,
                std::vector<std::vector<int>>(gridColSize,
                    std::vector<int>(gridRowSize, INT_MIN)));
        return std::max(0, recur(grid, 0, 0, 0, dpMemo));
    }
    int recur(std::vector<std::vector<int>> const & grid,
            int row1, int col1, int row2,
            std::vector<std::vector<std::vector<int>>> & dpMemo) {
        int col2 = row1 + col1 - row2;
        int const rowSize = grid.size();
        int const colSize = grid[row1].size();
        if (row1 < 0 || row1 >= rowSize || // there is no need to judge row1, col1, row2, col2 < 0
                col1 < 0 || col1 >= colSize ||
                row2 < 0 || row2 >= rowSize||
                col2 < 0 || col2 >= colSize ||
                row1 > row2 || // set an order to decrease complexity
                BLOCK == grid[row1][col1] ||
                BLOCK == grid[row2][col2]) {
            return INT_MIN;
        }
        if (rowSize - 1 == row1 && colSize - 1 == col1) {
            // at this time, row1 == row2 and col1 == col2
            return grid[row1][col1];
        }
        if (INT_MIN != dpMemo[row1][col1][row2]) {
            // have visit the status
            return dpMemo[row1][col1][row2];
        }
        int curAns = std::max(
                std::max(recur(grid, row1 + 1, col1, row2, dpMemo), // the first go down, and the second go right
                    recur(grid, row1 + 1, col1, row2 + 1, dpMemo)), // the first and the second all go down
                std::max(recur(grid, row1, col1 + 1, row2 + 1, dpMemo), // the first go right, and the second go down
                    recur(grid, row1, col1 + 1, row2, dpMemo))); // the first and the second all go down
        return dpMemo[row1][col1][row2] = curAns + grid[row1][col1] + (row1 == row2 ? 0 : grid[row2][col2]);
    }
private:
    static int const BLOCK = -1;
};

class SolutionOptimize {
public:
    int cherryPickup(std::vector<std::vector<int>> const & grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }
        int const gridRowSize = grid.size();
        int const gridColSize = grid[gridRowSize - 1].size();

        std::vector<std::vector<std::vector<int>>> dpMemo(gridRowSize,
                std::vector<std::vector<int>>(gridColSize,
                    std::vector<int>(gridRowSize, INT_MIN)));
        return std::max(0, recur(grid, 0, 0, 0, dpMemo));
    }
    int recur(std::vector<std::vector<int>> const & grid,
            int row1, int col1, int row2,
            std::vector<std::vector<std::vector<int>>> & dpMemo) {
        int col2 = row1 + col1 - row2;
        int const rowSize = grid.size();
        int const colSize = grid[row1].size();
        if (row1 >= rowSize || // there is no need to judge row1, col1, row2, col2 < 0
                col1 >= colSize ||
                row2 >= rowSize||
                row1 > row2 || // set an order to decrease complexity
                BLOCK == grid[row1][col1] ||
                BLOCK == grid[row2][col2]) {
            return INT_MIN;
        }
        if (rowSize - 1 == row1 && colSize - 1 == col1) {
            // at this time, row1 == row2 and col1 == col2
            return grid[row1][col1];
        }
        if (INT_MIN != dpMemo[row1][col1][row2]) {
            // have visit the status
            return dpMemo[row1][col1][row2];
        }
        int curAns = std::max(
                std::max(recur(grid, row1 + 1, col1, row2, dpMemo), // the first go down, and the second go right
                    recur(grid, row1 + 1, col1, row2 + 1, dpMemo)), // the first and the second all go down
                std::max(recur(grid, row1, col1 + 1, row2 + 1, dpMemo), // the first go right, and the second go down
                    recur(grid, row1, col1 + 1, row2, dpMemo))); // the first and the second all go down
        return dpMemo[row1][col1][row2] = curAns + grid[row1][col1] + (row1 == row2 ? 0 : grid[row2][col2]);
    }
private:
    static int const BLOCK = -1;
};

class Solution {
public:
    int cherryPickup(std::vector<std::vector<int>> const & grid) {
        // plagiarizing from https://leetcode.com/problems/cherry-pickup/discuss/165218/Java-O(N3)-DP-solution-w-specific-explanation
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }
        // using traversal instead of recursive
        int const gridRowSize = grid.size();
        int const gridColSize = grid[0].size();
        std::vector<std::vector<std::vector<int>>> dpMemo(gridRowSize + 1,
                std::vector<std::vector<int>>(gridColSize + 1,
                    std::vector<int>(gridRowSize + 1, INT_MIN)));
        dpMemo[1][1][1] = grid[0][0];
        for (int row1 = 1; row1 <= gridRowSize; row1++) {
            for (int col1 = 1; col1 <= gridColSize; col1++) {
                for (int row2 = 1; row2 <= gridRowSize; row2++) {
                    int col2 = row1 + col1 - row2;
                    if (1 > col2 ||
                            gridColSize < col2 ||
                            row2 > row1 ||
                            0 < dpMemo[row1][col1][row2] || // already updated
                            BLOCK == grid[row1 - 1][col1 - 1] ||
                            BLOCK == grid[row2 - 1][col2 - 1]) {
                        continue;
                    }
                    int curAns = std::max(
                            std::max(dpMemo[row1 - 1][col1][row2 - 1], dpMemo[row1 - 1][col1][row2]),
                            std::max(dpMemo[row1][col1 - 1][row2 -1], dpMemo[row1][col1 - 1][row2])) ;
                    if (0 > curAns) {
                        continue;
                    }
                    dpMemo[row1][col1][row2] = curAns + grid[row1 - 1][col1 - 1] +
                                                (row1 == row2 ? 0 : grid[row2 - 1][col2 - 1]);
                }
            }
        }
        #ifdef DEBUG
        std::cout << dpMemo[gridRowSize][gridColSize][gridRowSize];
        #endif
        return std::max(0, dpMemo[gridRowSize][gridColSize][gridRowSize]);
    }
private:
    static int const BLOCK = -1;
};

class Solution {
public:
    int cherryPickup(std::vector<std::vector<int>> const & grid) {
        // plagiarizing from https://leetcode.com/problems/cherry-pickup/discuss/109903/Step-by-step-guidance-of-the-O(N3)-time-and-O(N2)-space-solution
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }
        int const gridRowSize = grid.size();
        int const gridColSize = grid[0].size();
        int const MStep = gridRowSize + gridColSize - 1;

        std::vector<std::vector<int>> dpMemo(gridRowSize + 1, std::vector<int>(gridRowSize + 1, INT_MIN));
        dpMemo[1][1] = grid[0][0];
        for (int step = 1; step < MStep; step++) {
            for (int row1 = gridRowSize; row1 > 0; row1--) {
                for (int row2 = gridRowSize; row2 > 0; row2--) {
                    int col1 = step + OFFSET - row1;
                    int col2 = step + OFFSET - row2;
                    if (1 > col1 || col1 > gridColSize ||
                            1 > col2 || col2 > gridColSize ||
                            row2 > row1 ||
                            BLOCK == grid[row1 - 1][col1 - 1] ||
                            BLOCK == grid[row2 - 1][col2 - 1]) {
                        dpMemo[row1][row2] = INT_MIN;
                        continue;
                    }
                    int curAns = std::max(std::max(dpMemo[row1][row2 - 1], dpMemo[row1 - 1][row2]),
                            std::max(dpMemo[row1 - 1][row2 - 1], dpMemo[row1][row2]));
                    if (0 > curAns) {
                        continue;
                    }
                    dpMemo[row1][row2] = curAns + grid[row1 - 1][col1 - 1] +
                        (row1 == row2 ? 0 : grid[row2 - 1][col2 - 1]);
                }
            }
        }
        return std::max(0, dpMemo[gridRowSize][gridRowSize]);
    }
private:
    static int const BLOCK = -1;
    static int const OFFSET = 2;
};
