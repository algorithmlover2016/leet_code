#include "../../head.h"


class Solution {
public:
    bool judgeSquareSum(int c) {
        // plagiarizing from https://leetcode.com/problems/sum-of-square-numbers/discuss/104930/Java-Two-Pointers-Solution
        // binary search or two pointer solution
        if (0 > c) {
            return false;
        }
        long left = 0;
        long right = std::sqrt(c);
        while (left <= right) {
            // int mid = left + (right - left) / 2;
            long curSquareSum = left * left + right * right;
            if (curSquareSum < c) {
                left++;
            } else if (curSquareSum > c) {
                right--;
            } else {
                return true;
            }
        }
        return false;
    }
};

class Solution {
public:
    bool judgeSquareSum(int c) {
        // plagiarizing from https://leetcode.com/problems/sum-of-square-numbers/discuss/104932/HashSet-Java-quick-solution-one-for-loop
        // find the target sum
        std::unordered_set<int> visited;
        int maxRight = std::sqrt(c);
        for (int left = 0, right = maxRight; left <= right; left++, right--) {
            int curLeftSquare = left * left;
            visited.insert(curLeftSquare);
            if (visited.find(c - curLeftSquare) != visited.end()) {
                return true;
            }
            int curRightSquare = right * right;
            visited.insert(curRightSquare);
            if (visited.find(c - curRightSquare) != visited.end()) {
                return true;
            }
        }
        return false;
    }
};
