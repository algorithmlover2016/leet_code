#include "../../head.h"


// #define DEBUG
#define DUMMY_COL_WITH_MEMORY_OPTMIZATION
// #define DUMMY_ROW_AND_COL
class Solution {
public:
    int calculateMinimumHP(std::vector<std::vector<int>> const & dungeon) {
        // plagiarizing idea from https://leetcode.com/problems/dungeon-game/discuss/52774/C%2B%2B-DP-solution
        if (dungeon.empty() || dungeon[0].empty()) {
            return 0;
        }
        int const rowSize = dungeon.size();
        int const colSize = dungeon[0].size();

        #ifndef DUMMY_COL_WITH_MEMORY_OPTMIZATION
        #ifndef DUMMY_ROW_AND_COL
        std::vector<std::vector<int>> dpMemo(rowSize, std::vector<int>(colSize, 0));
        for (int row = rowSize - 1; row > EXCLUDE_MOST_LEFT_IDX; row--) {
            for (int col = colSize - 1; col > EXCLUDE_MOST_LEFT_IDX; col--) {
                #ifdef DEBUG
                std::cout << row << ", " << col << "\n";
                #endif
                if (row == rowSize - 1 && col == colSize - 1) {
                    dpMemo[row][col] = 1 - dungeon[row][col];
                } else if (row == rowSize - 1) {
                    dpMemo[row][col] = dpMemo[row][col + 1] - dungeon[row][col];
                } else if (col == colSize - 1) {
                    dpMemo[row][col] = dpMemo[row + 1][col] - dungeon[row][col];
                } else {
                    dpMemo[row][col] = std::min(dpMemo[row + 1][col], dpMemo[row][col + 1]) - dungeon[row][col];
                }
                dpMemo[row][col] = std::max(dpMemo[row][col], 1);
            }
        }
        #else
        std::vector<std::vector<int>> dpMemo(rowSize + 1, std::vector<int>(colSize + 1, INIT_MAX));
        // we start from rowSize - 1 and colSize - 1, and it can be from (rowSize, colSize -1) or (rowSize - 1, colSize)
        // when we are at row = rowSize - 1, it can only go to left, however, we initialize the rowSize row with INIT_MAX
        // so it will make sure we can only go to left. Same theory to the right most, namely, colSize
        dpMemo[rowSize - 1][colSize] = 1;
        dpMemo[rowSize][colSize - 1] = 1;
        for (int row = rowSize - 1; row > EXCLUDE_MOST_LEFT_IDX; row--) {
            for (int col = colSize - 1; col > EXCLUDE_MOST_LEFT_IDX; col--) {
                dpMemo[row][col] = std::min(dpMemo[row + 1][col], dpMemo[row][col + 1])
                    - dungeon[row][col];
                // if dpMemo[rowSize][colSize] <= 0, which means we don't need add more blood to knight, however,
                // we should initialize with 1 to make knight live at this position
                dpMemo[row][col] = std::max(dpMemo[row][col], 1);
            }
        }
        #endif
        return dpMemo[0][0];

        #else
        std::vector<int> dpMemo(colSize + 1, INIT_MAX);
        // at the king position, we first need make knight live, which means we should initialize it to 1
        dpMemo[colSize - 1] = 1;
        for (int row = rowSize - 1; row > EXCLUDE_MOST_LEFT_IDX; row--) {
            for (int col = colSize - 1; col > EXCLUDE_MOST_LEFT_IDX; col--) {
                dpMemo[col] = std::min(dpMemo[col], dpMemo[col + 1]) - dungeon[row][col];
                dpMemo[col] = std::max(dpMemo[col], 1);
                #ifdef DEBUG
                std::cout << row << ", " << col << ":\t" << dpMemo[col] << "\n";
                #endif
            }
        }
        return dpMemo[0];
        #endif

    }
private:
    int const INIT_MAX = INT_MAX;
    static int const EXCLUDE_MOST_LEFT_IDX = -1;
};
