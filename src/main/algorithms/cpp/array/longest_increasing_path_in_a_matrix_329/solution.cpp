#include "../../head.h"


// #define DEBUG
// #define NO_REVERSE_JUDGEMENT
class Solution {
public:
    int longestIncreasingPath(std::vector<std::vector<int>> const & matrix) {
        // plagiarizing from https://youtu.be/goHVFsq8nts
        if (matrix.empty() || matrix[0].empty()) {
            return 0;
        }
        int const rowSize = matrix.size();
        int const colSize = matrix[0].size();
        std::vector<std::vector<int>> dpMemo(rowSize, std::vector<int>(colSize, 0));
        int ans = 0;
        std::function<int(int, int)> dfs = [&](int row, int col) -> int {
            if (row < 0 || col < 0 || row >= rowSize || col >= colSize) {
                return 0;
            }
            if (0 != dpMemo[row][col]) {
                return dpMemo[row][col];
            }
            int ans = 1;
            for (int dIdx = 0; dIdx < DIRECTIONI_SIZE; dIdx++) {
                int nextRow = row + directions[dIdx];
                int nextCol = col + directions[dIdx + 1];
                #ifdef NO_REVERSE_JUDGEMENT
                if (0 <= nextRow && nextRow < rowSize &&
                   0 <= nextCol && nextCol < colSize &&
                    matrix[nextRow][nextCol] > matrix[row][col]) {
                    ans = std::max(ans, 1 + dfs(nextRow, nextCol));
                }
                #else
                if (nextRow < 0 || nextRow >= rowSize ||
                    nextCol < 0 || nextCol >= colSize ||
                    matrix[nextRow][nextCol] <= matrix[row][col]) {
                    continue;
                }
                #ifdef DEBUG
                std::cout << "next: " << nextRow << ", " << nextCol << "\t;";
                #endif
                ans = std::max(ans, 1 + dfs(nextRow, nextCol));
                #endif
            }
            return dpMemo[row][col] = ans;
        };

        for (int row = 0; row < rowSize; row++) {
            for (int col = 0; col < matrix[row].size(); col++) {
                #ifdef DEBUG
                std::cout << "\ntest " << row << ", " << col << ": ";
                #endif
                ans = std::max(ans, dfs(row, col));
            }
        }

        return ans;

    }
private:
    static int const DIRECTION_ARRAY_SIZE = 5;
    static int const DIRECTIONI_SIZE = DIRECTION_ARRAY_SIZE - 1;
    static std::array<int, DIRECTION_ARRAY_SIZE> directions;
};
std::array<int, Solution::DIRECTION_ARRAY_SIZE> Solution::directions{{1, 0, -1, 0, 1}};
