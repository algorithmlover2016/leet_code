#include "../../head.h"


// #define DEBUG
class Solution {
public:
    bool canMouseWin(std::vector<std::string> const & grid,
            int catJump, int mouseJump) {
        // plagiarizing from https://gist.github.com/GeminiCCCC/0ea1c2e740d083aaa10aa0e767a19b97
        if (grid.empty() || grid[0].empty()) {
            return false;
        }
        int const rowSize = grid.size();
        int const colSize = grid[0].size();

        // get the position of cat, mouse, food
        int catPos = 0, mousePos = 0, foodPos = 0;
        for (int row = 0; row < rowSize; row++) {
            for (int col = 0; col < colSize; col++) {
                switch(grid[row][col]) {
                    case CAT_FLAG:
                        catPos = ((row & POS_RESET) << POS_SHIFT_BITS) | (col & POS_RESET);
                        break;
                    case MOUSE_FLAG:
                        mousePos = ((row & POS_RESET) << POS_SHIFT_BITS) | (col & POS_RESET);
                        break;
                    case FOOD_FLAG:
                        foodPos = ((row & POS_RESET) << POS_SHIFT_BITS) | (col & POS_RESET);
                        break;
                    default: ;
                }
            }
        }

        #ifdef DEBUG
        std::cout << "set the cat, mouse, food position\n";
        #endif

        std::unordered_map<int, int> codedAns;
        return dfs(grid, codedAns, catPos, mousePos, 1, foodPos, catJump, mouseJump);
    }
private:
    bool dfs(std::vector<std::string> const & grid,
            std::unordered_map<int, int> & codedAns,
            int catPos, int mousePos, int moves, int foodPos,
            int const catJump, int const mouseJump) {

        int const rowSize = grid.size();
        int const colSize = grid[0].size();

        if (catPos == mousePos || catPos == foodPos) {
            return false;
        }
        if (mousePos == foodPos) {
            return true;
        }

        if (moves >= rowSize * colSize * 2) {
            return false;
        }

        int statusCode = ((catPos & STATUS_RESET) << CAT_SHIFT_BITS) |
            ((mousePos & STATUS_RESET) << MOUSE_SHIFT_BITS) | (moves & STATUS_RESET);

        if (codedAns.find(statusCode) != codedAns.end()) {
            return codedAns[statusCode];
        }

        /*
        #ifdef DEBUG
        std::cout << "\nneed computation\n";
        #endif
        */

        int catRow = (catPos >> POS_SHIFT_BITS) & POS_RESET;
        int catCol = catPos & POS_RESET;
        int mouseRow = (mousePos >> POS_SHIFT_BITS) & POS_RESET;
        int mouseCol = mousePos & POS_RESET;
        #ifdef DEBUG
        std::cout << "cat: " << catRow << ", " << catCol << " mouse: " << mouseRow << ", " << mouseCol
            << ",\t" << moves << "\n";
        #endif

        if (MOUSE_STEP & moves)  {
            for (int idx = 0; idx < DIRECTION_SIZE; idx++) {
                // jump start from 0 means can stay in the same position
                for (int jump = 0; jump <= mouseJump; jump++) {

                    int nextRow = mouseRow + directions[idx] * jump;
                    int nextCol = mouseCol + directions[idx + 1] * jump;
                    int nextEncoded = ((nextRow & POS_RESET) << POS_SHIFT_BITS) |
                                        (nextCol & POS_RESET);
                    if (nextRow >= 0 && nextRow < rowSize &&
                            nextCol >= 0 && nextCol < colSize &&
                            WALL_FLAG != grid[nextRow][nextCol]) {

                        if (dfs(grid, codedAns, catPos, nextEncoded, moves + 1, foodPos, catJump, mouseJump)) {
                            return codedAns[statusCode] = true;
                        }
                    } else {
                        // if not, nextRow and nextCol will become bigger at the same direction
                        break;
                    }
                }
            }
            return codedAns[statusCode] = false;
        } else {
            for (int idx = 0; idx < DIRECTION_SIZE; idx++) {
                // jump start from 0 means can stay in the same position
                for (int jump = 0; jump <= catJump; jump++) {
                    int nextRow = catRow + directions[idx] * jump;
                    int nextCol = catCol + directions[idx + 1] * jump;
                    int nextEncoded = ((nextRow & POS_RESET) << POS_SHIFT_BITS) |
                                        (nextCol & POS_RESET);
                    if (nextRow >= 0 && nextRow < rowSize &&
                            nextCol >= 0 && nextCol < colSize &&
                            WALL_FLAG != grid[nextRow][nextCol]) {

                        if (!dfs(grid, codedAns, nextEncoded, mousePos, moves + 1, foodPos, catJump, mouseJump)) {
                            return codedAns[statusCode] = false;
                        }
                    } else {
                        // if not, nextRow and nextCol will become bigger at the same direction
                        break;
                    }
                }
            }
            return codedAns[statusCode] = true;
        }
    }


private:
    static int const DIRECTION_ARRAY_SIZE = 5;
    static int const DIRECTION_SIZE = DIRECTION_ARRAY_SIZE - 1;
    static std::array<int, DIRECTION_ARRAY_SIZE> directions;

    static int const CAT_SHIFT_BITS = 16;
    static int const MOUSE_SHIFT_BITS = 8;
    static int const POS_SHIFT_BITS = 4;
    static int const POS_RESET = 0x0F;
    static int const STATUS_RESET = 0xFF;

    static char const CAT_FLAG = 'C';
    static char const MOUSE_FLAG = 'M';
    static char const FOOD_FLAG = 'F';
    static char const WALL_FLAG = '#';

    static int const MOUSE_STEP = 0x01;
};
std::array<int, Solution::DIRECTION_ARRAY_SIZE> Solution::directions = {1, 0, -1, 0, 1};
