#include "../../head.h"


class Solution {
public:
    bool exist(std::vector<std::vector<char>> board, std::string const & word) {
        if (word.empty()) {
            return true;
        }
        int const rowSize = board.size();
        if (0 == rowSize) {
            return false;
        }
        int const colSize = board[0].size();
        if (0 == colSize) {
            return false;
        }
        for (int row = 0; row < rowSize; row++) {
            for (int col = 0; col < colSize; col++) {
                if (find(board, word, row, col, 0)) {
                    return true;
                }
            }
        }
        return false;
    }
    bool find(std::vector<std::vector<char>> & board, std::string const & word,
            int rowStart, int colStart, int index) {
        if (index >= word.size()) {
            return true;
        }
        if (!check(board, word, rowStart, colStart, index)) {
            return false;
        }
        board[rowStart][colStart] += 'a' - 'A';
        for (int indexDirec = 0; indexDirec < DIRECTION_SIZE; indexDirec++) {
            if (find(board, word, rowStart + directions[indexDirec], colStart + directions[indexDirec + 1], index + 1)) {
                return true;
            }
        }
        board[rowStart][colStart] -= 'a' - 'A';
        return false;

    }
    bool check(std::vector<std::vector<char>> const & board, std::string const & word,
            int rowStart, int colStart, int index) {
        if (rowStart >= 0 && rowStart < board.size() &&
                colStart >= 0 && colStart < board[rowStart].size() &&
                board[rowStart][colStart] == word[index]) {
            return true;
        }
        return false;
    }
private:
    static int const DIRECTION_ARRAY_SIZE = 5;
    static int const DIRECTION_SIZE = DIRECTION_ARRAY_SIZE - 1;
    static std::array<int, DIRECTION_ARRAY_SIZE> directions;
};

std::array<int, Solution::DIRECTION_ARRAY_SIZE> Solution::directions = {0, 1, 0, -1, 0};

class SolutionBetteRunTime {
public:
    int nRows;
    int nCols;
    bool solve(std::vector<std::vector<char>> & board, int i, int j, int w, const std::string & word) {
        char ch = board[i][j];
        if(ch == '$' || ch != word[w])
            return false;
        board[i][j] = '$';

        ++w;

        if (w == word.length()) {
            return true;
        }

        bool solved = false;
        //Left
        if (j > 0)
            solved = solve(board, i, j - 1, w, word);
        //Right
        if (!solved && j < nCols - 1)
            solved = solve(board, i, j + 1, w, word);
        //Up
        if (!solved && i > 0)
            solved = solve(board, i - 1, j, w, word);
        //Down
        if (!solved && i < nRows - 1)
            solved = solve(board, i + 1, j, w, word);

        board[i][j] = ch;

        return solved;
    }
    bool exist(std::vector<std::vector<char>> board, std::string const & word) {
        nRows = board.size();
        nCols = board[0].size();

        for (int i = 0; i < nRows; ++i) {
            for (int j = 0; j < nCols; ++j) {
                if(solve(board, i, j, 0, word)) {
                    return true;
                }
            }
        }
        return false;
    }
};
