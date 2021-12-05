#include "../../head.h"



// #define DEBUG
class Solution {
public:
    int latestDayToCross(int row, int col, std::vector<std::vector<int>> const & cells) {
        // plagiarizing from https://leetcode.com/problems/last-day-where-you-can-still-cross/discuss/1403907/C%2B%2BJavaPython-Binary-Search-and-BFS-Clean-and-Concise
        int const cellsSize = cells.size();
        if (0 == cellsSize) {
            return row * col;
        }
        int left = 1, right = cellsSize;
        int ans = 0;
        while (left <= right) {
            int mid = (left + right + 1) / 2;
            #ifdef DEBUG
            std::cout << "left, right, mid: " << left << ", " << right << ", " << mid << "\n";
            #endif
            
            if (canThrough(cells, row, col, mid)) {
                ans = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return ans;
    }
private:
    bool canThrough(std::vector<std::vector<int>> const & cells, int const row, int const col, int mid) {
        int const cellsSize = cells.size();
        std::vector<std::vector<bool>> grids(row, std::vector<bool>(col, GRID_INIT_STATUS));
        for (int idx = 0; idx < mid; idx++) {
            auto const & cell = cells[idx];
            assert(CELL_SIZE == cell.size());
            grids[cell[CELL_FIRST_IDX] - 1][cell[CELL_SECOND_IDX] - 1] = GRID_BLOCK_STATUS;
        }
        std::queue<std::pair<int, int>> bfsQue;
        for (int idx = 0; idx < col; idx++) {
            if (GRID_INIT_STATUS == grids[FIRST_ROW][idx]) {
                bfsQue.emplace(std::make_pair(FIRST_ROW, idx));
                grids[FIRST_ROW][idx] = GRID_BLOCK_STATUS;
            }
        }
        while (!bfsQue.empty()) {
            auto [curRow, curCol] = bfsQue.front(); bfsQue.pop();
            if (row - 1 == curRow) {
                return true;
            }
            for (int direcIdx = 0; direcIdx < DIRECTION_SIZE; direcIdx++) {
                int nextRow = curRow + directions[direcIdx];
                int nextCol = curCol + directions[direcIdx + 1];
                if (nextRow < 0 || nextRow == row ||
                    nextCol < 0 || nextCol == col ||
                    GRID_BLOCK_STATUS == grids[nextRow][nextCol]) {
                        continue;
                    }
                grids[nextRow][nextCol] = GRID_BLOCK_STATUS;
                bfsQue.push({nextRow, nextCol});
            }
        }
        return false;
    }
private:
    static int const FIRST_ROW = 0;
    bool const GRID_INIT_STATUS = true;
    bool const GRID_BLOCK_STATUS = false;
    static int const CELL_SIZE = 2;
    static int const CELL_FIRST_IDX = 0;
    static int const CELL_SECOND_IDX = 1;
    static int const DIRECTION_SIZE = 4;
    static std::array<int, DIRECTION_SIZE + 1> directions;
};
std::array<int, Solution::DIRECTION_SIZE + 1> Solution::directions = {0, 1, 0, -1, 0};