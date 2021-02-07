#include "../../head.h"


class SolutionTLE {
public:
    int smallestDistancePair(std::vector<int> const & nums, int k) {
        int const numsSize = nums.size();
        int const diffSize = numsSize * (numsSize - 1) / 2;
        std::vector<int> numsDiff(diffSize, 0);
        for (int idx = 0, diffIdx = 0; idx < numsSize; idx++) {
            for (int nIdx = idx + 1; nIdx < numsSize; nIdx++) {
                numsDiff[diffIdx++] = std::abs(nums[idx] - nums[nIdx]);
            }
        }
        auto it = numsDiff.begin() + k - 1;
        std::nth_element(std::begin(numsDiff), it, std::end(numsDiff));
        return *it;
    }
};

// #define DEBUG
class Solution {
public:
    int smallestDistancePair(std::vector<int> nums, int k) {
        // plagiarizing idea from https://leetcode.com/problems/find-k-th-smallest-pair-distance/discuss/109082/Approach-the-problem-using-the-%22trial-and-error%22-algorithm
        int const numsSize = nums.size();
        if (ARRAY_LEAST_LEN > numsSize) {
            return INVALID_ANS;
        }
        std::sort(nums.begin(), nums.end());

        // using binary search witn diff
        int low = 0, high = nums.back() - nums[0];
        while (low < high) {
            int mid = low + (high - low) / 2;
            int cnt = 0;
            for (int idx = 0; idx < numsSize; idx++) {
                cnt += smallerThanTargetCnt(nums[idx] + mid, nums.cbegin() + idx, nums.cend());
            }

            #ifdef DEBUG
            std::cout << "\nmid, cnt: " << mid << ",\t" << cnt << "\n";
            #endif

            if (cnt >= k) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        return high;
    }

    int smallerThanTargetCnt(int const target,
                             std::vector<int>::const_iterator bIt,
                             std::vector<int>::const_iterator eIt) {
        int largerCnt = std::upper_bound(bIt, eIt, target) - bIt;
        return largerCnt - 1;
    }

private:
    static int const ARRAY_LEAST_LEN = 2;
    static int const INVALID_ANS = -1;
};
