#include "../../head.h"


class SolutionSort {
public:
    int maximumGap(std::vector<int> nums) {
        if (JUST_TWO > nums.size()) {
            return 0;
        }
        std::sort(nums.begin(), nums.end());
        int diff = nums[1] - nums[0];
        for (int idx = 2; idx < nums.size(); idx++) {
            int curDelta = nums[idx] - nums[idx - 1];
            if (diff < curDelta) {
                diff = curDelta;
            }
        }
        return diff;
        
        
    }
private:
    static int const JUST_TWO = 2;
};

// #define DEBUG
// #define USING_CEIL_FUNC
class Solution {
public:
    int maximumGap(std::vector<int> const & nums) {
        // plagiarizing idea from https://leetcode.com/problems/maximum-gap/discuss/50643/bucket-sort-JAVA-solution-with-explanation-O(N)-time-and-space
        if (JUST_TWO > nums.size()) {
            return 0;
        }
        int const numsSize = nums.size();
        int const minusSize = numsSize - 1;
        int minNum = INIT_MAX;
        int maxNum = INIT_MIN;
        for (int const num : nums) {
            minNum = std::min(minNum, num);
            maxNum = std::max(maxNum, num);
        }

        #ifdef DEBUG
        std::cout << "max, min: " << maxNum << ",\t" << minNum << "\t";
        #endif

#ifdef USING_CEIL_FUNC
        int minGap = (int)std::ceil((maxNum - minNum) * 1.0 / minusSize);
#else
        int minGap = (maxNum - minNum + minusSize - 1) / minusSize;
#endif
        #ifdef DEBUG
        std::cout << "minGap: " << minGap << "\n";
        #endif
        std::vector<int> bucketsMin(minusSize, INIT_MAX);
        std::vector<int> bucketsMax(minusSize, INIT_MIN);
        for (int const num : nums) {
            if (num == minNum || num == maxNum) {
                continue;
            }
            int idx = (num - minNum) / minGap;
            bucketsMin[idx] = std::min(bucketsMin[idx], num);
            bucketsMax[idx] = std::max(bucketsMax[idx], num);

            #ifdef DEBUG
            std::cout << "bucker max, min: " << bucketsMax[idx] << ",\t" << bucketsMin[idx]  << "\t";
            #endif
        }

        #ifdef DEBUG
        std::cout << "\n";
        #endif
        int maxGap = minGap;
        int preBucketMax = minNum;
        for (int idx = 0; idx < bucketsMin.size(); idx++) {
            if (INIT_MAX == bucketsMin[idx]) {
                // the bucket is empty
                continue;
            }
            maxGap = std::max(maxGap,  bucketsMin[idx] - preBucketMax);
            preBucketMax = bucketsMax[idx];
            #ifdef DEBUG
            std::cout << "maxGap, preBuckerMax: " << maxGap << ",\t" << preBucketMax  << "\t";
            #endif
        }
        maxGap = std::max(maxGap, maxNum - preBucketMax);

        #ifdef DEBUG
        std::cout << "\n";
        #endif
        return maxGap;
    }

    private:
    static int const JUST_TWO = 2;
    int const INIT_MAX = INT_MAX;
    int const INIT_MIN = INT_MIN;
};
