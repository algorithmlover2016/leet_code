#include "../../head.h"


class SolutionDP {
public:
    int maxSubArray(std::vector<int> const & nums) {
        // plagiarizing idea from https://blog.csdn.net/sgbfblog/article/details/8032464
        int const numsSize = nums.size();
        if (JUST_RETURN > numsSize) {
            return INIT_MIN;
        }
        if (JUST_RETURN == numsSize) {
            return nums.back();
        }

        int start = 0, end = start + 1;
        int maxStart = start, maxEnd = end;
        int maxSum = INIT_MIN;
        std::vector<int> dpMemo(numsSize + 1, 0);
        for (int idx = 0; idx < numsSize; idx++) {
            if (dpMemo[idx] > 0) {
                dpMemo[idx + 1] = dpMemo[idx] + nums[idx];
                end = idx + 1;
            } else {
                dpMemo[idx + 1] = nums[idx];
                start = idx;
            }
            if (dpMemo[idx + 1] > maxSum) {
                maxSum = dpMemo[idx + 1];
                maxStart = start;
                maxEnd = end;
            }
        }

        return maxSum;
    }
private:
    static int const JUST_RETURN = 1;
    static int const INIT_MIN = INT_MIN;
};

class SolutionSlidingWindow {
public:
    int maxSubArray (std::vector<int> const & nums) {
        // plagiarizing idea from https://blog.csdn.net/sgbfblog/article/details/8032464
        int const numsSize = nums.size();
        if (JUST_RETURN > numsSize) {
            return INIT_MIN;
        }
        if (JUST_RETURN == numsSize) {
            return nums.back();
        }

        int start = 0, end = start + 1;
        int intervalSum = 0;
        int maxStart = start, maxEnd = end;
        int maxSum = INIT_MIN;
        for (int idx = 0; idx < numsSize; idx++) {
            if (intervalSum > 0) {
                intervalSum += nums[idx];
                end = idx + 1;
            } else {
                intervalSum = nums[idx];
                start = idx;
            }

            if (intervalSum > maxSum) {
                maxSum = intervalSum;
                maxStart = start;
                maxEnd = end;
            }

        }
        return maxSum;
    }
private:
    static int const JUST_RETURN = 1;
    static int const INIT_MIN = INT_MIN;
};

class SolutionBinarySplit {
public:
    int maxSubArray(std::vector<int> const & nums) {
        // plagiarizing idea from https://blog.csdn.net/sgbfblog/article/details/8032464
        int const numsSize = nums.size();
        if (JUST_RETURN > numsSize) {
            return 0;
        }
        return maxSumOfSubSequence(nums, 0, numsSize - 1);
    }
private:
    int maxSumOfSubSequence(std::vector<int> const & nums, int begin, int end) {
        if (begin > end || begin >= nums.size() || begin < 0 || end < 0) {
            return INIT_MIN;
        }
        if (begin == end) {
            return nums[begin];
        }
        int mid = (begin + end) / 2;

        int leftSumMax = nums[mid];
        int leftSum = 0;
        for (int left = mid; left >= begin; left--) {
            leftSum += nums[left];
            if (leftSum > leftSumMax) { 
                leftSumMax = leftSum;
            }
        }

        int rightSumMax = nums[mid + 1];
        int rightSum = 0;
        for (int right = mid + 1; right <= end; right++) {
            rightSum += nums[right];
            if (rightSum > rightSumMax) { 
                rightSumMax = rightSum;
            }
        }
#ifdef DEBUG
        std::cout << "mid, leftSumMax, rightSumMax: " << mid << ",\t" << leftSumMax << ",\t" << rightSumMax << "\n";
#endif
        return std::max(leftSumMax + rightSumMax, std::max(maxSumOfSubSequence(nums, begin, mid),
                    maxSumOfSubSequence(nums, mid + 1, end)));
    }
private:
    static int const JUST_RETURN = 1;
    static int const INIT_MIN = INT_MIN;
};
