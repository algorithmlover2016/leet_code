#include "../../head.h"\n\n\n

class SolutionTLE {
public:
    int countRangeSum(std::vector<int> const & nums, int lower, int upper) {
        int const RowSize = nums.size();
        if (RowSize == 0) {
            return 0;
        }
        std::vector<std::vector<long>> dpMemo(RowSize, std::vector<long>(RowSize, INT_MIN));
        for (int row = 0; row < RowSize; row++) {
            dpMemo[row][row] = nums[row];
            for (int col = row + 1; col < RowSize; col++) {
                dpMemo[row][col] = dpMemo[row][col - 1] + nums[col];
            }
        }
        int ans = 0;
        for (int row = 0; row < RowSize; row++) {
            for (int col = row; col < RowSize; col++) {
                if (dpMemo[row][col] >= lower && dpMemo[row][col] <= upper)  {
                    ans++;
                }
            }
        }
        return ans;
    }
};
