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

class SolutionDP {
public:
    long long minCost(std::vector<int> const & nums, std::vector<int> const & cost) {
        std::vector<long long> idxes(nums.size()), preCost(nums.size());
        std::iota(std::begin(idxes), std::end(idxes), 0);

        // sorted nums by index to keep nums and cost unchanged when indexed by index
        std::sort(std::begin(idxes), std::end(idxes), [&](int left, int right) {return nums[left] < nums[right];});

        for (long long idx = 0, preSum = 0; idx < idxes.size() - 1; idx++) {
            preSum += cost[idxes[idx]]; // we compute the cost from most left to cur index if we just modify once.
            preCost[idx + 1] = preCost[idx] + preSum * (nums[idxes[idx + 1]] - nums[idxes[idx]]);
            // we compute the costs if we set the idxes[idx + 1] as target val,
            // it need the idx costs and all the former value change to the nums[idxes[idx + 1]],
            // however, at the moment, all the former values have been added to nums[idxes[idx]],
            // so we just need the diff from nums[idxes[idx]] to nums[idxes[idx + 1]], but each has different cost
        }

        long long ans = preCost.back(), rCost = 0; // it means setting the most right as target value. which means all the others are added to the largest
        for (long long idx = idxes.size() - 1, preSum = 0; idx > 0; idx--) {
            preSum += cost[idxes[idx]];
            rCost +=  preSum * (nums[idxes[idx]] - nums[idxes[idx - 1]]);
            ans = std::min(ans, preCost[idx - 1] + rCost);
        }
        return ans;
    }
};


// #define BINARY_SEARCH
class Solution {
public:
    long long minCost(std::vector<int> const & nums, std::vector<int> const & cost) {
        // plagiarizing from https://leetcode.com/problems/minimum-cost-to-make-array-equal/solutions/2734091/dp-vs-w-median-vs-binary-search/
        long long totalCost = std::accumulate(std::begin(cost), std::end(cost), 0LL);
        long long ans = 0;
        #ifndef BINARY_SEARCH
        std::vector<long long> idxes(nums.size());
        std::iota(std::begin(idxes), std::end(idxes), 0LL);
        std::sort(std::begin(idxes), std::end(idxes), [&](int left, int right) {return nums[left] < nums[right];});
        long long targetIdx = 0;
        for (long long curCost = 0; curCost + cost[idxes[targetIdx]] <= totalCost / 2; targetIdx++) {
            curCost += cost[idxes[targetIdx]];
        }
        for (long long idx = 0; idx < nums.size(); idx++) {
            ans += (long long)cost[idx] * std::abs(nums[idx] - nums[idxes[targetIdx]]);
        }
        #else
        long long target = 0, right = 1e6;
        while (target < right) {
            long long mid = (right + target) / 2;
            long long sum = 0;
            // setting the target as mid + 1
            for(long long idx = 0; idx < nums.size(); idx++) {
                sum += (nums[idx] <= mid) ? cost[idx] : 0;
            }
            if (sum <= totalCost / 2) {
                target = mid + 1;
            } else {
                right = mid;
            }
        }
        for (int idx = 0; idx < nums.size(); idx++) {
            ans += std::abs(nums[idx] - target) * cost[idx];
        }
        #endif
        return ans;
        
    }
};