#include "../../head.h"


class Solution {
public:
    std::vector<std::vector<int>> colorBorder(std::vector<std::vector<int>> grid,
                                              int r0, int c0,
                                              int color) {

        if (grid.empty() || grid[0].empty()) {
            return {};
        }

        int const gridRowSize = grid.size();
        int const gridColSize = grid[0].size();
        std::vector<std::vector<int>> ans;
        std::queue<std::vector<int>> bfsQue;
        bfsQue.push({r0, c0});
        std::vector<std::vector<bool>> used(gridRowSize,
                std::vector<bool>(gridColSize, false));

        std::vector<std::vector<bool>> addBoarder(gridRowSize,
                std::vector<bool>(gridColSize, false));
        // bfsQue.emplace(r0, c0);
        while (!bfsQue.empty()) {
            auto & pos = bfsQue.front();
            if (POS_IDX_LEN > pos.size()) {
                continue;
            }
            int row = pos[X_IDX], col = pos[Y_IDX];
            bfsQue.pop();

            if (used[row][col]) {
                continue;
            }

            used[row][col] = true;

            for (int idx = 0; idx < DIRECTIONS_SIZE; idx++) {
                int nextRow = row + directions[idx];
                int nextCol = col + directions[idx + 1];
                if (nextRow > MIN_IDX && nextRow < gridRowSize &&
                        nextCol > MIN_IDX && nextCol < gridColSize &&
                        grid[nextRow][nextCol] == grid[row][col]) {
                    bfsQue.push({nextRow, nextCol});
                } else {
                    if (!addBoarder[row][col]) {
                        ans.push_back({row, col});
                        addBoarder[row][col] = true;
                    }
                }
            }
        }
        for (auto & pos : ans) {
            if (POS_IDX_LEN > pos.size()) {
                continue;
            }
            int row = pos[X_IDX], col = pos[Y_IDX];
            grid[row][col] = color;
        }
        return grid;


    }
private:
    static int const DIRECTIONS_ARRAY_SIZE = 5;
    static int const DIRECTIONS_SIZE = 4;
    static std::array<int, DIRECTIONS_ARRAY_SIZE> directions;
    static int const X_IDX = 0;
    static int const Y_IDX = 1;
    static int const POS_IDX_LEN = 2;
    static int const MIN_IDX = -1;
};
std::array<int, Solution::DIRECTIONS_ARRAY_SIZE> Solution::directions{{0, 1, 0, -1, 0}};
