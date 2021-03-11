#include "../../head.h"


class Solution {
public:
    int removeDuplicates(std::vector<int> & nums) {
        int const numsSize = nums.size();
        if (JUST_TWO >= numsSize) {
            return numsSize;
        }
        int start = 2;
        int pre = nums[0];
        for (int idx = 2; idx < numsSize; idx++) {
            if (nums[idx] != pre) {
                pre = nums[idx - 1];
                nums[start++] = nums[idx];
            }
        }
        return start;
    }
    private:
    static int const JUST_TWO = 2;
};
