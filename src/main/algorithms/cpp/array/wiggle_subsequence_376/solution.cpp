#include "../../head.h"


// #define NO_TWO_LAYER_LOOP_AVOID_TLE
class Solution {
public:
    int wiggleMaxLength(std::vector<int> const & nums) {
        // plagiarizing from https://youtu.be/IpWoZvKzpug
        int const numsSize = nums.size();
        // we record the two dpMemo at index idx. pos[idx] and neg[idx]
        // at each index idx, we update the max result
        std::vector<int> pos(numsSize, 1);
        std::vector<int> neg(numsSize, 1);
#ifndef NO_TWO_LAYER_LOOP_AVOID_TLE
        for (int rIdx = 1; rIdx < numsSize; rIdx++) {
            for (int lIdx = 0; lIdx < rIdx; lIdx++) {
                if (nums[rIdx] > nums[lIdx]) {
                    pos[rIdx] = std::max(pos[rIdx], neg[lIdx] + 1);
                } else if (nums[rIdx] < nums[lIdx]) {
                    neg[rIdx] = std::max(neg[rIdx], pos[lIdx] + 1);
                }
            }
        }
#else
        for (int idx = 1; idx < numsSize; idx++) {
            // we assume the cur nums[idx] won't be appended to the result subsequence
            pos[idx] = pos[idx - 1];
            neg[idx] = neg[idx - 1];
            if (nums[idx] > nums[idx - 1]) {
                pos[idx] = std::max(pos[idx], neg[idx - 1] + 1);
            } else if (nums[idx] < nums[idx - 1]) {
                neg[idx] = std::max(neg[idx], pos[idx - 1] + 1);
            }
        }
#endif
        return std::max(pos.back(), neg.back());
    }
};
