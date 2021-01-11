#include "../../head.h"


#define DEBUG
#define TEST
#define TEST_OUTPUT_TO_SCREEN
class SolutionDp {
public:
    std::vector<int> maxSumOfSubSequence(std::vector<int> const & nums) {
        int const numsSize = nums.size();
        if (JUST_RETURN >= numsSize) {
            return nums;
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

        return std::vector<int>(nums.begin() + maxStart, nums.begin() + maxEnd);
    }
private:
    static int const JUST_RETURN = 1;
    static int const INIT_MIN = INT_MIN;
};

class Solution {
public:
    std::vector<int> maxSumOfSubSequence(std::vector<int> const & nums) {
        int const numsSize = nums.size();
        if (JUST_RETURN >= numsSize) {
            return nums;
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
        return std::vector<int>(nums.begin() + maxStart, nums.begin() + maxEnd);
    }
private:
    static int const JUST_RETURN = 1;
    static int const INIT_MIN = INT_MIN;
};

class SolutionMaxSum {
public:
    int maxSumOfSubSequence(std::vector<int> const & nums) {
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

#ifdef TEST
int main() {
    // Solution obj;
    SolutionDp obj;
    SolutionMaxSum maxSumObj;
    std::vector<int> nums{{-1, 1, 3, -1, 2, -1, -3, 0, 1, 9}};
    std::vector<int> ans = obj.maxSumOfSubSequence(nums);
    int maxSum = maxSumObj.maxSumOfSubSequence(nums);
#ifdef TEST_OUTPUT_TO_SCREEN
    std::cout << "TEST OUTPUT\n";
    std::cout << "maxSum: " << maxSum << "\n";
    int sum = 0;
    for (auto const num : ans) {
        sum += num;
        std::cout << num << "\t";
    }
    std::cout << '\n';
    assert(maxSum == sum);
#endif
    assert(maxSum == std::accumulate(ans.begin(), ans.end(), 0));
    return 0;
}
#endif
