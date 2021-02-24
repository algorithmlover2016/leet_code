#include "../../head.h"


class Solution {
public:
    bool searchMatrix(std::vector<std::vector<int>> const & matrix, int target) {
        int rowSize = matrix.size();
        if (JUST_ZERO == rowSize) {
            return false;
        }
        
        int colSize = matrix[0].size();
        if (JUST_ZERO == colSize) {
            return false;
        }

        for (int row = 0, col = colSize - 1; row < rowSize; row++) {
            while (MOST_LEFT_IDX_EXCLUDE < col && matrix[row][col] > target) {
                col--;
            }
            if (MOST_LEFT_IDX_EXCLUDE < col && target == matrix[row][col]) {
                return true;
            }
        }

        return false;
    }
private:
    static int const JUST_ZERO = 0;
    static int const MOST_LEFT_IDX_EXCLUDE = -1;
};
