#include "../../head.h"


class SolutionTLE {
public:
    long long countSubarrays(std::vector<int> const & nums, long long k) {
        if (nums.empty()) {
            return 0;
        }
        std::vector<int> preSums(nums.size() + 1, 0);
        for (int idx = 0; idx < nums.size(); idx++) {
            preSums[idx + 1] = preSums[idx] + nums[idx];
        }
        long long ans = 0;
        for (int len = 1; len <= nums.size(); len++) {
            for (int idx = len; idx <= nums.size(); idx++) {
                long long mul = (long long) (preSums[idx] - preSums[idx - len]) * len;
                if (mul < k) {
                    ans++;
                }
            }
        }
        return ans;
    }
};