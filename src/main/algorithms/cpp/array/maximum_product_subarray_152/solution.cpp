#include "../../head.h"


// #define DEBUG
class Solution {
public:
    int maxProduct(std::vector<int> const & nums) {
        int const numsSize = nums.size();
        if (EMPTY_LEN == numsSize) {
            return 0;
        }
        if (JUST_ONE == numsSize) {
            return nums.back();
        }
        int intervalMaxPro = 1;
        int start = 0, end = start + 1;
        int maxPro = INIT_MIN;
        int maxStart = 0, maxEnd = maxStart + 1;
        for (int idx = 0; idx < numsSize; idx++) {
            if (0 == nums[idx]) {
                intervalMaxPro = 1;
                start = idx;
                if (0 > maxPro) {
                    maxPro = 0;
                    maxStart = start;
                    maxEnd = start + 1;
                }
                start++;
            } else {
                int curIntervalMaxPro =  intervalMaxPro * nums[idx];
                intervalMaxPro = curIntervalMaxPro;
                end = idx + 1;
                if (0 > curIntervalMaxPro) {
                    /*
                       there exists a traversal from start to idx(exclude), so there will be a O(n)
                       when from start to idx, each element is larger than 0, and nums[idx] < 0
                       */
                    int curStart = start;
                    while (curStart < idx && 0 > curIntervalMaxPro) {
                        curIntervalMaxPro /= nums[curStart++];
                    }
                    if (curIntervalMaxPro > maxPro) {
                        maxPro = curIntervalMaxPro;
                        maxStart = curStart;
                        maxEnd = end;
                    }
                }
#ifdef DEBUG
                std::cout << "intervalMaxPro: " << intervalMaxPro << "\n";
#endif
                if (intervalMaxPro > maxPro) {
                    maxPro = intervalMaxPro;
                    maxStart = start;
                    maxEnd = end;
                }
            }
        }
        return maxPro;

    }
private:
    static int const EMPTY_LEN = 0;
    static int const JUST_ONE = 1;
    static int const INIT_MIN = INT_MIN;

};

class Solution {
public:
    int maxProduct(std::vector<int> const & nums) {
        if (nums.size() == 0) {
            return 0;
        }

        int maxSoFar = nums[0];
        int minSoFar = nums[0];
        int result = maxSoFar;

        for (int i = 1; i < nums.size(); i++) {
            int curr = nums[i];
            int curMax = curr * maxSoFar;
            int curMin = curr * minSoFar;
            int temp_max = std::max(curr, std::max(curMax, curMin));
            minSoFar = std::min(curr, std::min(curMax, curMin));

            maxSoFar = temp_max;

            result = std::max(maxSoFar, result);
        }
        return result;
    }
};
