#include "../../head.h"


// #define DEBUG
class Solution {
public:
    long long countSubarrays(std::vector<int> const & nums, int minK, int maxK) {
        long long ans = 0;
        int left = 0, minKIdx = 0, maxKIdx = 0;
        int twoMeet = 0;
        for (int idx = 0; idx < nums.size(); idx++) {
            if (nums[idx] == minK) {
                minKIdx = idx;
                twoMeet |= 0x01;
                #ifdef DEBUG
                std::cout << "encounter minK at " << idx << ", twoMeet is " << twoMeet << "\n";
                #endif
            }
            if (nums[idx] == maxK) {
                maxKIdx = idx;
                twoMeet |= 0x02;
                #ifdef DEBUG
                std::cout << "encounter maxK at " << idx << ", twoMeet is " << twoMeet << "\n";
                #endif
            }
            if (nums[idx] > maxK || nums[idx] < minK) {
                minKIdx = maxKIdx = left = idx + 1;
                twoMeet = 0;
                #ifdef DEBUG
                std::cout << "need reset at " << idx << ", twoMeet is " << twoMeet << "\n";
                #endif
            }
            ans += (twoMeet == 3 ? std::min(minKIdx, maxKIdx) - left + 1 : 0);
            #ifdef DEBUG
            std::cout << "at " << idx << ", sum is " << ans << "\n";
            #endif
        }
        return ans;
    }
};

class Solution {
public:
    long long countSubarrays(std::vector<int> const & nums, int minK, int maxK) {
        // plagiarizing from https://leetcode.com/problems/count-subarrays-with-fixed-bounds/solutions/2708099/java-c-python-sliding-window-with-explanation/
        long long ans = 0, left = -1, minKIdx = -1, maxKIdx = -1;
        for (int idx = 0; idx < nums.size(); idx++) {
            if (nums[idx] > maxK || nums[idx] < minK) {
                left = minKIdx = maxKIdx = idx;
            }
            if (nums[idx] == maxK) {
                maxKIdx = idx;
            }
            if (nums[idx] == minK) {
                minKIdx = idx;
            }
            ans += std::min(maxKIdx, minKIdx) - left;
        }
        return ans;
    }
};