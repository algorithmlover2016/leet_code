#include "../../head.h"


class Solution {
public:
    int countSquares(std::vector<std::vector<int>> const & mat) {
        // plagiarizing from https://leetcode.com/problems/count-square-submatrices-with-all-ones/discuss/441306/JavaC%2B%2BPython-DP-solution and https://leetcode.com/problems/count-square-submatrices-with-all-ones/discuss/643429/Python-DP-Solution-%2B-Thinking-Process-Diagrams-(O(mn)-runtime-O(1)-space)
        if (mat.empty() || mat[0].empty()) {
            return 0;
        }
        int const matRowSize = mat.size();
        int const matColSize = mat[0].size();
        int ans = 0;
        std::vector<std::vector<int>> dpMemo(mat);
        for (int row = 0; row < matRowSize; row++) {
            for (int col = 0; col < matColSize; col++) {
                // row > 0 && col > 0 && mat[row][col] > 0
                if (row * col * mat[row][col] > 0) {
                    dpMemo[row][col] += std::min(dpMemo[row - 1][col - 1],
                            std::min(dpMemo[row][col - 1], dpMemo[row - 1][col]));
                }
                ans += dpMemo[row][col];
            }
        }
        return ans;
    }
};
