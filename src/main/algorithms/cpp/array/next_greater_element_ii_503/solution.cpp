#include "../../head.h"


class Solution {
public:
    std::vector<int> nextGreaterElements(std::vector<int> const & nums) {
        // one situantion is exclude : [1,2,3,2,1]
        // which means the right last numbers' next greate maybe not the biggest.
        std::vector<int> increaseStack;
        std::vector<int> ans(nums.size(), -1);
        for (int index = 0; index < nums.size(); index++) {
            while (!increaseStack.empty() && nums[increaseStack.back()] < nums[index]) {
                ans[increaseStack.back()] = nums[index];
                increaseStack.pop_back();
            }
            increaseStack.emplace_back(index);
        }
        for (int index = 1; index < increaseStack.size(); index++) {
            if (-1 == ans[increaseStack[index]] && nums[increaseStack[0]] > nums[increaseStack[index]]) {
                ans[increaseStack[index]] = nums[increaseStack[0]];
            }
        }
        return ans;

    }
};


class Solution {
public:
    std::vector<int> nextGreaterElements(std::vector<int> const & nums) {
        int n = A.size();
        std::vector<int> stack, res(n, -1);
        // loop twice to solve the problem
        for (int i = 0; i < n * 2; ++i) {
            while (stack.size() && A[stack.back()] < A[i % n]) {
                res[stack.back()] = A[i % n];
                stack.pop_back();
            }
            stack.push_back(i % n);
        }
        return res;
    }
};
