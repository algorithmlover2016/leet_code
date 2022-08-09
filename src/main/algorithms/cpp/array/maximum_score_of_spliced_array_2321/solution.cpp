#include "../../head.h"


class SolutionTLE_ON2 {
public:
    int maximumsSplicedArray(std::vector<int> const & nums1, std::vector<int> const & nums2) {
        int nums1Size = nums1.size();
        int nums2Size = nums2.size();
        if (nums1Size != nums2Size) {
            return INVALID;
        }
        int numSize = std::min(nums1Size, nums2Size);

        std::vector<int> preSum1(numSize + 1, 0);
        std::vector<int> preSum2(numSize + 1, 0);
        for (int idx = 0; idx < numSize; idx++) {
            preSum1[idx + 1] = preSum1[idx] + nums1[idx];
            preSum2[idx + 1] = preSum2[idx] + nums2[idx];
        }
        int nums1Sum = preSum1[numSize];
        int nums2Sum = preSum2[numSize];
        int ans = 0;
        for (int left = 0; left < numSize; left++) {
            for (int right = left; right < numSize; right++) {
                int subSum1 = preSum1[right + 1] - preSum1[left];
                int subSum2 = preSum2[right + 1] - preSum2[left];
                if (subSum1 >= subSum2) {
                    ans = std::max(ans, nums2Sum - subSum2 + subSum1);
                } else {
                    ans = std::max(ans, nums1Sum - subSum1 + subSum2);
                }
            }
        }
        return ans;
        
    }
private:
    static int const INVALID = -1;
};

// #define DEBUG
class Solution {
public:
    int maximumsSplicedArray(std::vector<int> const & nums1, std::vector<int> const & nums2) {
        int nums1Size = nums1.size();
        int nums2Size = nums2.size();
        if (nums1Size != nums2Size) {
            return INVALID;
        }
        int numSize = std::min(nums1Size, nums2Size);
        // plagiarizing from https://leetcode.com/problems/maximum-score-of-spliced-array/discuss/2198135/Double-Kadane
        // and https://leetcode.com/problems/maximum-score-of-spliced-array/discuss/2198138/Kadane

        int nums1Sum = 0;
        int nums2Sum = 0;
        int windowSum1 = 0;
        int windowSum2 = 0;
        int subSum1 = 0, subSum2 = 0;
        for (int idx = 0; idx < numSize; idx++) {
            int curIdxDiff = nums2[idx] - nums1[idx];
            windowSum1 = std::max(curIdxDiff, windowSum1 + curIdxDiff);
            windowSum2 = std::max(-curIdxDiff, windowSum2 - curIdxDiff);
            subSum1 = std::max(subSum1, windowSum1);
            subSum2 = std::max(subSum2, windowSum2);
            
            #ifdef DEBUG
            std::cout << "curDiff: " << curIdxDiff << ", " << windowSum1 << ", " << windowSum2 << "\n";
            #endif
            nums1Sum += nums1[idx];
            nums2Sum += nums2[idx];
        }
        #ifdef DEBUG
        std::cout << "diff: " << windowSum1 << ", " << windowSum2 << "\n";
        #endif
        
        return std::max(nums1Sum + subSum1, nums2Sum + subSum2);
    }
private:
    static int const INVALID = -1;
};