#include "../../head.h"


// #define DEBUG
class Solution {
public:
    int jump(std::vector<int> const & nums) {
        int const numsSize = nums.size();
        if (JUST_RETURN_ZERO >= numsSize) {
            return 0;
        }

        int jump = 0;
        int maxIdx = 0;
        int pos = 0;
        int const TARGET = numsSize - 1;
        for (int idx = 0; idx < numsSize; idx++) {
            if (maxIdx < idx) {
                return -1;
            }

            if (TARGET <= pos) {
                break;
            }

            maxIdx = std::max(maxIdx, idx + nums[idx]);
            #ifdef DEBUG
            std::cout << "idx, maxIdx: " << idx << ",\t" << maxIdx << '\n';
            #endif
            if (idx == pos) {
                jump++;
                pos = maxIdx;
            }
        }
        return jump;
    }
private:
    static int const JUST_RETURN_ZERO = 1;
};
