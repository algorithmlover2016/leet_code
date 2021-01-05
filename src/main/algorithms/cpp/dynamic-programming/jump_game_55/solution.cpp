#include "../../head.h"


class Solution {
public:
    bool canJump(std::vector<int> const & nums) {
        int const numsSize = nums.size();
        if (JUST_RETURN_TRUE >= numsSize) {
            return true;
        }
        int jump = 0;
        int pos = 0;
        int const TARGET = numsSize - 1;
        int nextMaxFar = pos;
        for (int idx = 0; idx < numsSize; idx++) {
            if (pos < idx) {
                return false;
            }
            if (TARGET <= pos) {
                return true;
            }
            nextMaxFar = std::max(nextMaxFar, idx + nums[idx]);
            if (idx == pos) {
                jump++;
                pos = nextMaxFar;
            }
        }
        return false;
    }
private:
    static int const JUST_RETURN_TRUE = 1;

};
