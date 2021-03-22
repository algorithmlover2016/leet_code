#include "../../head.h"


class Solution {
public:
    bool isPerfectSquare(int num) {
        // plagiarizing idea from sqrt https://leetcode.com/problems/sqrtx/
        long cur = num;
        while (cur * cur > num) {
            cur = (cur + num / cur) / 2;
        }
        return cur * cur == num;
        
    }
};
