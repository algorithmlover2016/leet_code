#include "../../head.h"


// #define DEBUG
class Solution {
public:
    void gameOfLife(std::vector<std::vector<int>> & board) {
        // plagiarizing idea from https://www.youtube.com/watch?v=jcKUfzrLtuk
        if (board.empty() || board[0].empty()) {
            return;
        }


        int const boardRowSize = board.size();
        for (int row = 0; row < boardRowSize; row++) {
            int const boardColSize = board[row].size();
            for (int col = 0; col < boardColSize; col++) {
                int liveNei = 0;
                for (int idx = 0; idx < DIRECTION_SIZE; idx++) {
                    int nextRow = row + directions[idx];
                    int nextCol = col + directions[idx + 1];
                    if (nextRow >= 0 && nextRow < boardRowSize &&
                            nextCol >= 0 && nextCol < boardColSize) {

                        #ifdef DEBUG
                        std::cout << "nextRow, nextCol: " << nextRow << ",\t" << nextCol << "\t"
                            << board[nextRow][nextCol] << "\t";
                        #endif

                        if (LIVE_FLAG == std::abs(board[nextRow][nextCol])) {
                            liveNei++;
                        }
                    }
                }
                #ifdef DEBUG
                std::cout << "row, col: " << row << ",\t" << col << ",\tliveNei: " << liveNei << "\t";
                #endif
                // live to death
                if (LIVE_FLAG == board[row][col] &&
                    (liveNei < 2 || liveNei > 3)) {
                    board[row][col] = -LIVE_FLAG;
                    #ifdef DEBUG
                    std::cout << "-LIVE_FLAG: " << -LIVE_FLAG << '\t'
                        << board[row][col] << '\t' << std::abs(board[row][col]) << '\t';
                    #endif
                }
                // death to live
                if (DEATH_FLAG == board[row][col] &&
                    DEATH_TO_LIVE_FLAG == liveNei) {
                    board[row][col] = DEATH_TO_LIVE_FLAG;
                }
                #ifdef DEBUG
                std::cout << "\n";
                #endif
            }
        }

        for (int row = 0; row < boardRowSize; row++) {
            int const boardColSize = board[row].size();
            for (int col = 0; col < boardColSize; col++) {
                if (DEATH_FLAG < board[row][col]) {
                    board[row][col] = LIVE_FLAG;
                } else if (DEATH_FLAG > board[row][col]) {
                    board[row][col] = DEATH_FLAG;
                }
            }
        }
    }
    private:
    static int const DEATH_FLAG = 0;
    static int const LIVE_FLAG = 1;
    static int const DEATH_TO_LIVE_FLAG = 3;
    static int const DIRECTION_SIZE = 8;
    static int const DIRECTION_ARRAY_SIZE = DIRECTION_SIZE + 1;
    static std::array<int, DIRECTION_ARRAY_SIZE> directions;
};
std::array<int, Solution::DIRECTION_ARRAY_SIZE> Solution::directions{{0, 1, 1, 0, -1, -1, 1, -1, 0}};
