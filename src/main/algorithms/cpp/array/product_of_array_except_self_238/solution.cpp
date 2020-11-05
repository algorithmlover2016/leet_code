#include "../../head.h"


class Solution {
public:
    std::vector<int> productExceptSelf(std::vector<int> const & nums) {
        // plagiarizing from https://leetcode.com/problems/product-of-array-except-self/discuss/65622/Simple-Java-solution-in-O(n)-without-extra-space
        std::vector<int> ans(nums.size(), 1);
        for (int index = 1; index < nums.size(); index++) {
            ans[index] = ans[index - 1] * nums[index - 1];
        }
        int right = 1;
        for (int index = nums.size() - 1; index > -1; index--) {
            ans[index] *= right;
            right *= nums[index];
        }
        return ans;
        
    }
};

class SolutionUpgrade {
public:
    std::vector<int> productExceptSelf(std::vector<int> const & nums) {
        // plagiarizing from https://leetcode.com/problems/product-of-array-except-self/discuss/65622/Simple-Java-solution-in-O(n)-without-extra-space
        std::vector<int> ans(nums.size(), 1);
        int right = 1, left = 1;
        for (int index = 0, iRight = nums.size() - 1; index < nums.size(); index++, iRight--) {
            ans[index] *= left;
            left *= nums[index];
            ans[iRight] *= right;
            right *= nums[iRight];
        }
        return ans;

    }
};
