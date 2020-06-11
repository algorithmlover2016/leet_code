#include "../../head.h"
 

class Solution {
public:
    int missingNumber(std::vector<int> const & nums) {
        int size = nums.size();
        long targetSum = size * (size + 1) / 2;
        for (auto ele : nums) {
            targetSum -= ele;
        }
        return targetSum;
    }
};

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        int m = n;
        for (int i = 0; i < n; ++i) {
            m ^= i^nums[i];
        }
        return m;
    }
};
