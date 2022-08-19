#include "../../head.h"



class Solution {
public:
    long long minimumReplacement(std::vector<int> const & nums) {
        // plagiarizing from https://leetcode.com/problems/minimum-replacements-to-sort-the-array/discuss/2388098/C%2B%2B-Java-or-Google-Interview-Question-or-O(N)
        // and https://leetcode.com/problems/minimum-replacements-to-sort-the-array/discuss/2388265/JavaC%2B%2BPython-One-Reverse-Pass
        long long ans = 0;
        int numsSize = nums.size();
        if (0 == numsSize) {
            return ans;
        }
        int noMoreThan = nums.back(); // after replacement, any num can be not larger than the right most;
        for (int idx = numsSize - 2; idx > EXCLUDE_LEFT_MOST_IDX; idx--) {
            // if nums[idx] % noMoreThan == 0, upRound = nums[idx] / noMoreThan
            // if nums[idx] % noMoreThan != 0, then we need at least (nums[idx] / noMoreThan + 1) operation to split nums[idx] into sub parts
            // And, if that happens, we can get the maximum noMoreThan is (nums[idx] / (nums[idx] / noMoreThan + 1)) (noMoreThan is the minimum integer of this splitting operation), which means its left part
            // can not be larger than that new noMoreThan value.
            int upRound = (nums[idx]  + noMoreThan - 1) / noMoreThan;
            noMoreThan = nums[idx] / upRound;
            ans += upRound - 1;
        }
        return ans;
    }
private:
    static int const EXCLUDE_LEFT_MOST_IDX = -1;
};