#include "../../head.h"


class Solution {
public:
    char findKthBit(int n, int k) {
        // plagiarizing idea from https://youtu.be/aN8ND52Wjac
        int cur = 0;
        int len = (1 << n) - 1;
        while (k > 1) {
            int mid = (len >> 1) + 1;
            if (k == mid) {
                cur ^= 0x01;
                return cur + '0';
            } else if (k > mid) {
                cur ^= 0x01;
                k = len - k + 1;
            }
            len >>= 1;
        }
        return cur + '0';
    }
};
