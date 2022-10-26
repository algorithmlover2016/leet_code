#include "../../head.h"


class Solution {
public:
    long long minCost(std::vector<int> const & nums, std::vector<int> const & cost) {
        // plagiarizing from https://leetcode.com/problems/minimum-cost-to-make-array-equal/solutions/2734162/java-c-python-binary-search/
        int left = *std::min_element(std::begin(nums), std::end(nums));
        int right = *std::max_element(std::begin(nums), std::end(nums));
        long long ans = 0;
        while (left < right) {
            int mid = (left + right) / 2;
            long long curAnsLeft = compute(nums, mid, cost), curAnsRight = compute(nums, mid + 1, cost);
            ans = std::min(curAnsLeft, curAnsRight);
            if (curAnsLeft < curAnsRight) {
                right = mid;
            } else {
                left = mid + 1;
            }
            /*
            if (curAnsLeft > curAnsRight) {
                left = mid + 1;
            } else {
                right = mid;
            }
            */
        }
        return ans;
    }
private:
    long long compute(std::vector<int> const & nums, int average, std::vector<int> const & cost) {
        assert(nums.size() == cost.size());
        long long ans = 0;
        for (int idx = 0; idx < nums.size(); idx++) {
            ans += std::abs(((long long)(nums[idx]) - average)) * cost[idx];
        }
        return ans;
    }

};