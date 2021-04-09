#include "../../head.h"


#define OPTIMIZATION_MEMRY
class Solution {
public:
    int maximalSquare(std::vector<std::vector<char>> const & matrix) {
        // plagiarizing idea from https://leetcode.com/problems/maximal-square/discuss/61803/C%2B%2B-space-optimized-DP
        // and https://leetcode.com/problems/maximal-square/discuss/61935/6-lines-Visual-Explanation-O(mn)
        if (matrix.empty() || matrix[0].empty()) {
            return 0;
        }
        int const rowSize = matrix.size();
        int const colSize = matrix[0].size();
        int ans = 0;
#ifdef OPTIMIZATION_MEMRY
        std::vector<int> dpMemo(colSize, 0);
        int diagonal = 0;
        for (int row = 0; row < rowSize; row++) {
            for (int col = 0; col < colSize; col++) {
                int nextDiagonal = dpMemo[col];
                if (0 == (row * col * (matrix[row][col] - OFFSET))) {
                    dpMemo[col] = matrix[row][col] - OFFSET;
                } else {
                    dpMemo[col] = std::min(diagonal, std::min(dpMemo[col - 1] /*left*/, dpMemo[col] /*upper*/)) + 1;
                }
                diagonal = nextDiagonal;
                ans = std::max(ans, dpMemo[col]);
            }
        }
#else
        std::vector<std::vector<int>> dpMemo(rowSize, std::vector<int>(colSize, 0));
        for (int row = 0; row < rowSize; row++) {
            for (int col = 0; col < colSize; col++) {
                if (0 == (row * col * (matrix[row][col] - OFFSET))) {
                    dpMemo[row][col] = matrix[row][col] - OFFSET;
                } else {
                    dpMemo[row][col] = std::min(dpMemo[row - 1][col] /*upper squre*/,
                            std::min(dpMemo[row - 1][col - 1] /*above left(diagonal square)*/,
                                dpMemo[row][col - 1] /*left square*/)) + 1;

                }
                ans = std::max(ans, dpMemo[row][col]);
            }
        }
#endif
        return  ans * ans;
    }
private:
    static char const OFFSET = '0';
};

class Solution {
public:
    int maximalSquare(std::vector<std::vector<char>> const & matrix) {
        // plagiarizing idea from https://leetcode.com/problems/maximal-square/discuss/61803/C%2B%2B-space-optimized-DP
        // and https://leetcode.com/problems/maximal-square/discuss/61935/6-lines-Visual-Explanation-O(mn)
        if (matrix.empty() || matrix[0].empty()) {
            return 0;
        }
        int const rowSize = matrix.size();
        int const colSize = matrix[0].size();
        int ans = 0;

        std::vector<std::vector<int>> dpMemo(rowSize + 1, std::vector<int>(colSize + 1, 0));
        for (int row = 1; row < dpMemo.size(); row++) {
            for (int col = 1; col < dpMemo[row].size(); col++) {
                if (ONE_LETTER == matrix[row - 1][col - 1]) {
                    dpMemo[row][col] = std::min(dpMemo[row - 1][col] /*upper squre*/,
                            std::min(dpMemo[row - 1][col - 1] /*above left(diagonal square)*/,
                                dpMemo[row][col - 1] /*left square*/)) + 1;

                }
                ans = std::max(ans, dpMemo[row][col]);
            }
        }
        return  ans * ans;
    }
private:
    static char const ONE_LETTER = '1';
};
