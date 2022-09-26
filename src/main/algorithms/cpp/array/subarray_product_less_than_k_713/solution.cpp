#include "../../head.h"


class Solution {
public:
    int numSubarrayProductLessThanK(std::vector<int> const & nums, int k) {
        long long mul = 1, ans = 0;
        for (int idx = 0, leftIdx = 0; idx < nums.size(); idx++) {
            mul *= nums[idx];
            while (mul >= k && leftIdx <= idx) {
                mul /= nums[leftIdx++];
            }
            ans += idx - leftIdx + 1;
        }
        return ans;
    }
};