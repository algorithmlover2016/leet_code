#include "../../head.h"

#define GET_MAX_CHOSED
class Solution {
public:

    int combinationSumCntWithK(std::vector<int> nums, int target, int k) {
        // if the elements of nums is random order, then we should do the follow operation
        // std::sort(std::begin(nums), std::end(nums));
        // each element should be used only once
        int const numsSize = nums.size();
        std::vector<std::vector<std::vector<int>>> dpMemo(numsSize + 1,
                std::vector<std::vector<int>>(k + 1, std::vector<int>(target + 1, 0)));
        for (int idx = 0; idx < dpMemo.size(); idx++) {
            dpMemo[idx][0][0] = 1;
        }

        // the outer and inner for loop order determine the using times of elements in nums
        // this condition make sure each element is used only once;
        for (int idx = 1; idx <= numsSize; idx++) {
#ifdef GET_MAX_CHOSED
            int maxChosed = std::min(idx, k);
            for (int chosed = 1; chosed <= maxChosed; chosed++) {
                for (int t = 1; t <= target; t++) {
                    // we choose chosed number from idx - 1 elements;
                    // skip the cur idx;
                    dpMemo[idx][chosed][t] = dpMemo[idx - 1][chosed][t];
                    if (nums[idx - 1] <= t) {
                        // if the val of cur idx is not larger than t, we can choose it;
                        dpMemo[idx][chosed][t] += dpMemo[idx - 1][chosed - 1][t - nums[idx - 1]];
                    }
                }
            }
#else
            for (int chosed = 1; chosed <= k; chosed++) {
                for (int t = 1; t <= target; t++) {
                    // we choose chosed number from idx - 1 elements;
                    // skip the cur idx;
                    if (chosed > idx) {
                        dpMemo[idx][chosed][t] = 0;
                    } else {
                        dpMemo[idx][chosed][t] = dpMemo[idx - 1][chosed][t];
                    }
                    if (nums[idx - 1] <= t) {
                        // if chosed > idx, which means there is no solution, which means 0, then
                        // the solution of chose  chosed - 1 elements from idx - 1 elements is also be 0;
                        // so we can move this if block code into the upper else case condition.
                        // if the val of cur idx is not larger than t, we can choose it;
                        dpMemo[idx][chosed][t] += dpMemo[idx - 1][chosed - 1][t - nums[idx - 1]];
                    }
                }
            }
#endif
        }
        return dpMemo[numsSize][k][target];
    }

    std::vector<std::vector<int>> combinationSumSeqWithK(std::vector<int> nums, int target, int k) {
        // if the elements of nums is random order, then we should do the follow operation
        // std::sort(std::begin(nums), std::end(nums));
        kkkkkkkk
    }
};
