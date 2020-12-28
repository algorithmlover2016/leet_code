#include "../../head.h"


class Solution {
public:
    std::vector<std::vector<int>> candyCrush(std::vector<std::vector<int>> & board) {
        // plagiarizing from https://www.youtube.com/watch?v=IcyOjlzySXI
        if (board.empty() || board[0].empty()) {
            return board;
        }
        int const boardRowSize = board.size();
        int const boardColSize = board[0].size();

        bool needCrush = false;

        // vertically mark
        for (int row = 0; row < boardRowSize - 2; row++) {
            for (int col = 0; col < boardColSize; col++) {
                int const curVal = abs(board[row][col]);
                if (0 != curVal &&
                        curVal == abs(board[row + 1][col]) &&
                        curVal == abs(board[row + 2][col])) {
                    board[row][col] = board[row + 1][col] = board[row + 2][col] = -curVal;
                    needCrush = true;
                }
            }
        }


        // horizontally mark
        for (int row = 0; row < boardRowSize; row++) {
            for (int col = 0; col < boardColSize - 2; col++) {
                int const curVal = abs(board[row][col]);
                if (0 != curVal &&
                        curVal == abs(board[row][col + 1]) &&
                        curVal == abs(board[row][col + 2])) {
                    board[row][col] = board[row][col + 1] = board[row][col + 2] = -curVal;
                    needCrush = true;
                }
            }
        }
        if (!needCrush) {
            return board;
        }

        // crush
        for (int col = 0; col < boardColSize; col++) {
            int crushRow = boardRowSize - 1;
            for (int row = boardRowSize - 1; row > -1; row--) {
                if (board[row][col] > 0) {
                    board[crushRow--][col] = board[row][col];
                }
            }
            crushRow++;
            for (int row = 0; row < crushRow; row++) {
                board[row][col] = 0;
            }
        }
        return candyCrush(board);
    }
};

int main() {
    std::vector<std::vector<int>> board = 
        {{110,   5, 112, 113, 114},
         {210, 211,   5, 213, 214},
         {310, 311,   3, 313, 314},
         {410, 411, 412,   5, 414},
         {  5,   1, 512,   3,   3},
         {610,   4,   1, 613, 614},
         {710,   1,   2, 713, 714},
         {810,   1,   2,   1,   1},
         {  1,   1,   2,   2,   2},
         {  4,   1,   4,   4, 1014}
        };
    std::vector<std::vector<int>> boardOutput = 
        {{  0,   0,   0,   0,   0},
         {  0,   0,   0,   0,   0},
         {  0,   0,   0,   0,   0},
         {110,   0,   0,   0, 114},
         {210,   0,   0,   0, 214},
         {310,   0,   0, 113, 314},
         {410,   0,   0, 213, 414},
         {610, 211, 112, 313, 614},
         {710, 311, 412, 613, 714},
         {810, 411, 512, 713, 1014}
        }
        ;
    Solution test;
    test.candyCrush(board);
    assert(board == boardOutput);

    std::cout << "{";
    for (int row = 0; row < board.size(); row++) {
        std::cout << "{";
        for (int col = 0; col < board[row].size(); col++) {
            std::cout << (0 == col ? "" : ",\t") << board[row][col];
        }
        std::cout << "},\n";
    }

    return 0;

}
