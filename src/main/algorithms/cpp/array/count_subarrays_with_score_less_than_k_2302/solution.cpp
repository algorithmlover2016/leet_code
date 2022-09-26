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

class Solution {
public:
    long long countSubarrays(std::vector<int> const & nums, long long k) {

        // plagiarizing from https://leetcode.com/problems/count-subarrays-with-score-less-than-k/discuss/2138778/Sliding-Window
        /*
        we find all the subarray ending with the current index
        */
        long long ans = 0, sum = 0;
        for (int idx = 0, leftIdx = 0; idx < nums.size(); idx++) {
            sum += nums[idx];
            while (sum * (idx - leftIdx + 1) >= k) {
                sum -= nums[leftIdx++];
            }
            ans += idx - leftIdx + 1;
        }
        return ans;
    }
};