#include "../../head.h"


class SolutionTLE {
public:
    bool find132pattern(std::vector<int> const & nums) {
        int numsSize = nums.size();
        if (3 > numsSize) {
            return false;
        }
        for (int i = 0; i < numsSize - 2; i++) {
            for (int j = i + 1; j < numsSize - 1; j++) {
                if (nums[j] > nums[i]) {
                    for (int k = j + 1; k < numsSize; k++) {
                        if (nums[j] > nums[k] && nums[k] > nums[i]) {
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }
};

class SolutionMustStartFromSmallestoneBegin {
public:

    bool find132pattern(std::vector<int> const & nums) {
        int numsSize= nums.size();
        if (3 > numsSize) {
            return false;
        }
        // wrong answer
        std::vector<int> increaseStack;
        for (int num : nums) {
            bool pushed = false;
            while (!increaseStack.empty() && increaseStack.back() > num) {
                pushed = true;
                increaseStack.pop_back();
            }
            if (!increaseStack.empty() && pushed) {
                return true;
            }
            increaseStack.emplace_back(num);
        }
        return false;
    }

};

class SolutionFrombackToStart {
public:
    bool find132pattern(std::vector<int> const & nums) {
        // plagiarizing from https://leetcode.com/problems/132-pattern/discuss/94071/Single-pass-C%2B%2B-O(n)-space-and-time-solution-(8-lines)-with-detailed-explanation.
        int numsSize= nums.size();
        if (3 > numsSize) {
            return false;
        }
        std::vector<int> decreaseStackFromBack;
        int s3 = INT_MIN;
        for (int index = numsSize - 1; index > -1; index--) {
            while (!decreaseStackFromBack.empty() && decreaseStackFromBack.back() < nums[index]) {
                if (s3 < decreaseStackFromBack.back()) {
                    s3 = decreaseStackFromBack.back();
                }
                decreaseStackFromBack.pop_back();
            }
            if (nums[index] < s3) {
                return true;
            }
            decreaseStackFromBack.emplace_back(nums[index]);
        }
        return false;
    }
};


class SolutionFromLeftToRightWrong {
public:
    bool find132pattern(std::vector<int> const & nums) {
        // plagiarizing from https://leetcode.com/problems/132-pattern/discuss/94071/Single-pass-C%2B%2B-O(n)-space-and-time-solution-(8-lines)-with-detailed-explanation.
        int numsSize= nums.size();
        if (3 > numsSize) {
            return false;
        }
        std::vector<int> decreaseStackFromStart;
        int s1 = INT_MAX;
        for (int num : nums) {
            while (!decreaseStackFromStart.empty() && decreaseStackFromStart.back() < num) {
                if (s1 > decreaseStackFromStart.back()) {
                    s1 = decreaseStackFromStart.back();
                }
                decreaseStackFromStart.pop_back();
            }
            // wrong when input is 1 0 1 -4 3 || can't solve the situation when input is 1 -2 1 -4 -1
            if (num > s1 && !decreaseStackFromStart.empty()) {
                return true;
            }
            decreaseStackFromStart.emplace_back(num);
        }
        return false;
    }
};
