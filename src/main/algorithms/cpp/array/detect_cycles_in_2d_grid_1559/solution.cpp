#include "../../head.h"


class Solution {
public:
    bool containsCycle(std::vector<std::vector<char>> const & grid) {
        // plagiarizing from https://leetcode.com/problems/detect-cycles-in-2d-grid/discuss/805677/DFS-or-Simple-Explanation
        if (grid.empty() || grid[0].empty()) {
            return false;
        }

        int const rowSize = grid.size();
        int const colSize = grid[0].size();

        std::vector<std::vector<bool>> used(rowSize, std::vector<bool>(colSize, false));

        for (int row = 0; row < rowSize; row++) {
            for (int col = 0; col < colSize; col++) {
                if (!used[row][col]) {
                    if (dfs(grid, used, row, col, -1, -1)) {
                        return true;
                    }

                }
            }
        }
        return false;
    }

private:
    bool dfs(std::vector<std::vector<char>> const & grid,
             std::vector<std::vector<bool>> & used,
             int curX, int curY,
             int preX, int preY) {
        int const rowSize = grid.size();
        int const colSize = grid[curX].size();
        char const preChar = grid[curX][curY];
        used[curX][curY] = true;
        for (int idx = 0; idx < DIRECTION_SIZE; idx++) {
            int nextX = curX + directions[idx];
            int nextY = curY + directions[idx + 1];
            if (nextX < rowSize && nextX > MIN_EX_IDX &&
                nextY < colSize && nextY > MIN_EX_IDX) {
                if ((nextX != preX || nextY != preY) && preChar == grid[nextX][nextY]) {
                    if (used[nextX][nextY]) {
                        return true;
                    } else if (dfs(grid, used, nextX, nextY, curX, curY)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
private:
    static int const MIN_EX_IDX = -1;
    static int const DIRECTION_SIZE = 4;
    static int const DIRECTION_ARRAY_SIZE = DIRECTION_SIZE + 1;
    static std::array<int, DIRECTION_ARRAY_SIZE> directions;
};
std::array<int, Solution::DIRECTION_ARRAY_SIZE> Solution::directions{{0, 1, 0, -1, 0}};


class SolutionGreatIdea {
public:
    bool containsCycle(std::vector<std::vector<char>> const & grid) {
        // plagiarizing from https://leetcode.com/problems/detect-cycles-in-2d-grid/discuss/805673/C%2B%2B-BFS
        if (grid.empty() || grid[0].empty()) {
            return false;
        }

        int const rowSize = grid.size();
        int const colSize = grid[0].size();

        std::vector<std::vector<bool>> used(rowSize, std::vector<bool>(colSize, false));

        // bfs
        for (int row = 0; row < rowSize; row++) {
            for (int col = 0; col < colSize; col++) {
                if (!used[row][col]) {
                    std::vector<std::pair<int, int>> layer{{row, col}};
                    char const curChar = grid[row][col];
                    while (!layer.empty()) {
                        std::vector<std::pair<int, int>> nextLayer;
                        for (auto & [curRow, curCol] : layer) {
                            if (used[curRow][curCol]) {
                                return true;
                            }
                            used[curRow][curCol] = true;
                            for (int idx = 0; idx < DIRECTION_SIZE; idx++) {
                                int nextRow = curRow + directions[idx];
                                int nextCol = curCol + directions[idx + 1];
                                if (MIN_EX_IDX < nextRow && nextRow < rowSize &&
                                        MIN_EX_IDX < nextCol && nextCol < colSize &&
                                    !used[nextRow][nextCol] && curChar == grid[nextRow][nextCol]) {
                                    nextLayer.emplace_back(std::make_pair(nextRow, nextCol));
                                }
                            }

                        }
                        std::swap(layer, nextLayer);
                    }
                }
            }
        }
        return false;
    }

private:
    static int const MIN_EX_IDX = -1;
    static int const DIRECTION_SIZE = 4;
    static int const DIRECTION_ARRAY_SIZE = DIRECTION_SIZE + 1;
    static std::array<int, DIRECTION_ARRAY_SIZE> directions;
};
std::array<int, Solution::DIRECTION_ARRAY_SIZE> Solution::directions{{0, 1, 0, -1, 0}};
