#include "../../head.h"


class Solution {
public:
    int maximumAND(std::vector<int>& nums, int k, int m) {
        // becase of the constraints that 1 <= nums[i] <= 10^9 < 2^30
        const int MAX_BIT = 30;
        int currAns = 0;
        for (int bit = MAX_BIT; bit >= 0; bit--) {
            int t = currAns | (1LL << bit); // based on currAns to set the bit to 1
            std::vector<int> steps;
            for (int num : nums) {
                steps.push_back(helper(num, t, MAX_BIT));
            }
            std::sort(steps.begin(), steps.end());
            int sumSteps = 0;
            for (int i = 0; i < m; i++) {
                sumSteps += steps[i];
                if (sumSteps > k) {
                    break;
                }
            }
            if (sumSteps <= k) {
                currAns |= (1LL << bit);
            }
        }
        return currAns;
    }
private:
    int helper(int num, int target, const int MAX_BIT) {
        if ((num & target) == target) {
            return 0;
        }
        int currAns = 0;
        for (int bit = MAX_BIT; bit >= 0; bit--) {
            int tBit = (target >> bit) & 1;
            int nBit = (num >> bit) & 1;
            if (tBit == 1 && nBit == 0) {
                currAns |= (1LL << bit);
                currAns |= (target & ((1LL << bit) - 1));
                return currAns - num;
            }
            if (nBit) {
                currAns |= (1LL << bit);
            }
        }
        return currAns - num;
    }
};

/*
class Solution1 {
public:
    int maximumAND(vector<int>& nums, int k, int m) {
        vector<int> ops(nums.size()); // Number of operations for each number
        int ans = 0;
        int max_width = bit_width((uint32_t) ranges::max(nums) + k / m);
        for (int bit = max_width - 1; bit >= 0; bit--) {
            int target = ans | (1 << bit); // Note: target includes the bits already set in ans
            for (int i = 0; i < nums.size(); i++) {
                int x = nums[i];
                int j = bit_width((uint32_t) target & ~x);
                // j-1 is the highest bit where target is 1 and x is 0
                int mask = j < 31 ? (1 << j) - 1 : INT_MAX;
                ops[i] = (target & mask) - (x & mask);
            }

            // Greedy: pick the smallest m operation counts
            // ranges::sort(ops);
            ranges::nth_element(ops, ops.begin() + m);
            if (reduce(ops.begin(), ops.begin() + m, 0LL) <= k) {
                ans = target; // This bit of the answer can be set to 1
            }
        }
        return ans;
    }
};
*/