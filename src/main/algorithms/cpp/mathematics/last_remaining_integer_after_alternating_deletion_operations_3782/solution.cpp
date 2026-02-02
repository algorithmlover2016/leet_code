#include "../../head.h"



class Solution {
public:
    long long lastInteger(long long n) {
        // inspired by https://leetcode.com/problems/last-remaining-integer-after-alternating-deletion-operations/solutions/7426648/olog-n-optimized-solution-fun-clear-by-r-6l5t
        long long head = 1;
        long long step = 1;
        bool leftToRight = true;
        for (long long remaining = n; remaining > 1; remaining /= 2, step *=2, leftToRight = !leftToRight) {
            if ((!leftToRight) && (remaining % 2 == 0)) {
                head += step;
            }
            remaining +=1;
        }
        return head;
    }
};