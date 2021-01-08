#include "../../head.h"


class Solution {
public:
    int lengthOfLIS(std::vector<int> const & nums) {
        int const numsSize = nums.size();
        if (JUST_RETURN >= numsSize) {
            return numsSize;
        }

        int const MAX_INIT = INT_MAX;
        std::vector<int> incSeq(numsSize, MAX_INIT);
        int maxLen = 0;
        for (auto const num : nums) {
            auto it = std::lower_bound(incSeq.begin(), incSeq.end(), num);
            *it = num;
            maxLen = std::max(maxLen, static_cast<int>(std::distance(incSeq.begin(), it)) + 1);
        }
        while (!incSeq.empty() && MAX_INIT == incSeq.back()) {
            incSeq.pop_back();
        }
        return maxLen;
        
    }
private:
    static int const JUST_RETURN = 1;
};
