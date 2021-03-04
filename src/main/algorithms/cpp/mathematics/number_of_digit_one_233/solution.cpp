#include "../../head.h"


class Solution {
public:
    int countDigitOne(int n) {
        // plagiarizing from https://leetcode.com/problems/number-of-digit-one/discuss/64381/4%2B-lines-O(log-n)-C%2B%2BJavaPython
        // each time check a digit bit
        /*
           n = 3458607189
                 ^  ^ ^
                 |  | |
                 k  i j
           for example,
           at index i. a = 34586 0 (b = )7189. n[i] = 0, it must meet a' = 0 -> 34585 and at each a',
                b can range from 0 to 9999, which means there will be a * 10000
           at index j, a = 3458607 1 (b = )89. n[i] = 1, it must meet a' = 0 -> 3458606 and at each a',
                b can range from 0 to 99. which means there will be (a' + 1) * 100 + when a' = 3458607,
                n[i] = 1, b' can range from 0 to 89. So the total number is a  * 100 + b' + 1
           at index k, a = 34, n[i] = 1, b = 8607189. then a can be range from 0 to 34 which is 35 numbers
                because 1 < n[k] = 5, there is no meaning to consider b. (a + 1) * 10000000

           */
        int ans = 0;
        for (long m = 1; m <= n; m *= 10) {
            int a = n / m;
            int b = n % m;
            ans += (a + 8) / 10 * m + (a % 10 == 1) * (b + 1);
        }
        return ans;
    }
};
