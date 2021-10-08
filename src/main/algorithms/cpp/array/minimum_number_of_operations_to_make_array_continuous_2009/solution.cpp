#include "../../head.h"


#define USING_SLIDING_WINDOW
#ifdef USING_SLIDING_WINDOW
#define USING_KEEP_MAX_WINDOW_SIZE
#endif
// #undef USING_KEEP_MAX_WINDOW_SIZE
// #undef USING_SLIDING_WINDOW
class Solution {
public:
    int minOperations(std::vector<int> nums) {
        // plagiarizing from https://leetcode.com/problems/minimum-number-of-operations-to-make-array-continuous/discuss/1471689/Sliding-Window and
        // https://leetcode.com/problems/minimum-number-of-operations-to-make-array-continuous/discuss/1470853/Python-Binary-Search-Clean-and-Concise and
        // https://leetcode.com/problems/minimum-number-of-operations-to-make-array-continuous/discuss/1470857/C%2B%2B-Sliding-Window
        int numsOriSize = nums.size();
        if (numsOriSize < MIN_NUMS_LEN) {
            return 0;
        }
        int ans = numsOriSize;
        std::sort(std::begin(nums), std::end(nums));
        nums.erase(std::unique(std::begin(nums), std::end(nums)), std::end(nums));
        #ifdef USING_SLIDING_WINDOW
            #ifndef USING_KEEP_MAX_WINDOW_SIZE
            for (int start = 0, end = 0; start < nums.size(); start++) {
                while (end < nums.size() && nums[end] < nums[start] + numsOriSize) {
                    ans = std::min(ans, numsOriSize - (++end - start));
                }
            }
            #else
            int end = 0, start = 0;
            for (; end < nums.size(); end++) {
                if (nums[start] + numsOriSize <= nums[end]) {
                    start++;
                }
            }
            ans = numsOriSize - (end - start);
            #endif
        #else
        // using binary search
        for (int start = 0; start < nums.size(); start++) {
            int end = nums[start] + numsOriSize - 1;
            int endIdx = std::distance(std::begin(nums), std::upper_bound(std::begin(nums), std::end(nums), end));
            ans = std::min(ans, numsOriSize - (endIdx - start));
        }
        #endif
        return ans;
    }
private:
    static int const MIN_NUMS_LEN = 2;
};
