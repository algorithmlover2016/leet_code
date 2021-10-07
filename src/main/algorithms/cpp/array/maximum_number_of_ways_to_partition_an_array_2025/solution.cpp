#include "../../head.h"


class Solution {
public:
    int waysToPartition(std::vector<int> const & nums, int k) {
        // plagiarizing from https://leetcode.com/problems/maximum-number-of-ways-to-partition-an-array/discuss/1500048/Left-and-Right-Differences and for more detail reference to
        // https://leetcode.com/problems/maximum-number-of-ways-to-partition-an-array/discuss/1498999/C%2B%2B-O(n)
        int numsSize = nums.size();
        if (numsSize < MIN_SIZE) {
            return -1;
        }
        std::unordered_map<long long, int> left, right;
        // left means the difference excluding index as left part;
        // right means the difference including index as left part;
        long long sum = std::accumulate(std::begin(nums), std::end(nums), 0l);
        for (long long idx = 0, lsum = 0; idx < numsSize - 1; idx++) {
            // none of left or right part can be empty, so idx can only reach to nums.size() - 2;
            int num = nums[idx];
            lsum += num;
            right[sum - 2 * lsum]++; // the difference means the right part minus left part at index (index belongs to left part)
        }
        int ans = right[0];
        for (long long idx = 0, lsum = 0; idx < numsSize; idx++) {
            // if we change the nums[idx] to be k, the right part of left (recording the difference) will add k - nums[idx]
            // and the right part of the right (map recording the difference between right part and left part) will decrease k - nums[idx]
            // to get the difference to be zero, we need get the number of left[nums[idx] - k] and right[k - nums[idx] respectively
            ans = std::max(ans, left[nums[idx] - k] + right[k - nums[idx]]);
            lsum += nums[idx];
            ++left[sum - 2 * lsum];
            --right[sum - 2 * lsum];
        }
        return ans;
    }
private:
    static int const MIN_SIZE = 2;
};
