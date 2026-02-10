#include "../../head.h"


class Solution {
public:
    std::vector<long long> countStableSubarrays(std::vector<int>& nums, std::vector<std::vector<int>>& queries) {
        // https://leetcode.com/problems/count-stable-subarrays/solutions/7351402/on-simple-and-efficient-no-binary-search-oung/
        std::vector<long long> ans;
        if (nums.empty() || queries.empty()) {
            return ans;
        }
        const int n = nums.size();
        ans.reserve(queries.size());
        std::vector<long long> prefix(n, 0);
        prefix[0] = 1;
        
        int nonDecreasingInterval = 1;
        for (int i = 1; i < n; i++) {
            if (nums[i] < nums[i - 1]) {
                nonDecreasingInterval = 1;
            } else {
                nonDecreasingInterval++;
            }
            prefix[i] = prefix[i - 1] + nonDecreasingInterval;
        }

        std::vector<long long> invertVally(n, 0);
        invertVally[n - 1] = n; // index start from 1
        for (int i = n - 2; i >= 0; i--) {
            if (nums[i] > nums[i + 1]) {
                invertVally[i] = i + 1;
            } else {
                invertVally[i] = invertVally[i + 1];
            }
        }

        for (auto & query : queries) {
            int left = query[0], right = query[1];
            long long count = 0;
            if (invertVally[left] > right) { // invertVally start from 1 and left, right start from 0, so no equal
                // it means [left, right] is non-decreasing array
                long long len = right - left + 1;
                count = len * (len + 1) / 2;
            } else {
                int firstPeakFromLeft = invertVally[left];
                long long lenLeftToPeak = firstPeakFromLeft - left;
                count = (lenLeftToPeak * (lenLeftToPeak + 1)) / 2;

                count += prefix[right] - prefix[firstPeakFromLeft - 1]; // start from firstPeakFromLeft to right
            }
            ans.emplace_back(count);
        }
        return ans;
        
    }
};