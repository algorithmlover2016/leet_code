#include "../../head.h"


class Solution {
public:
    int largestSubmatrix(std::vector<std::vector<int>> const & matrix) {
        // plagiarizing idea from https://leetcode.com/problems/largest-submatrix-with-rearrangements/discuss/1020710/C%2B%2B-Clean-and-Clear-With-Intuitive-Pictures-O(m-*-n-*-logn)
        if (matrix.empty() || matrix[0].empty()) {
            return 0;
        }

        int const matrixRowSize = matrix.size();
        int const matrixColSize = matrix[0].size();

        std::vector<int> height(matrixColSize, 0);
        int const heightSize = height.size();
        int area = 0;
        for (int row = 0; row < matrixRowSize; row++) {
            for (int col = 0; col < matrixColSize; col++) {
                if (TARGET_FLAG == matrix[row][col]) {
                    height[col] += 1;
                } else {
                    height[col] = 0;
                }
            }
            std::vector<int> sortedCurLayerHeight(height);
            std::sort(sortedCurLayerHeight.begin(), sortedCurLayerHeight.end());
            for (int idx = 0; idx < heightSize; idx++) {
                area = std::max(area, sortedCurLayerHeight[idx] * (heightSize - idx));
            }
        }
        return area;
    }
private:
    static int const TARGET_FLAG = 1;
};
