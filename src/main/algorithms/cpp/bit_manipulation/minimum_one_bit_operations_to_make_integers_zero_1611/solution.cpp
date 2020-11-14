#include "../../head.h"


class Solution {
public:
    int minimumOneBitOperations(int n) {
        // plagiarizing from https://leetcode.com/problems/minimum-one-bit-operations-to-make-integers-zero/discuss/877798/JavaC%2B%2BPython-3-Solutions-with-Prove-O(1)-Space
        // every time we choose the leftmost bit who is 1 to change
        if (n < 2) {
            return n;
        }
        int b = 1;
        while ((b << 1) <= n) {
            b <<= 1;
        }
        return b + minimumOneBitOperations((b >> 1) ^ b ^ n);
    }
};


class SolutionRecursive {
public:
    int minimumOneBitOperations(int n, int res = 0) {
        // plagiarizing from https://leetcode.com/problems/minimum-one-bit-operations-to-make-integers-zero/discuss/877798/JavaC%2B%2BPython-3-Solutions-with-Prove-O(1)-Space
        // every time we choose the leftmost bit who is 1 to change
        if (0 == n) {
            return res;
        }
        int b = 1;
        while ((b << 1) <= n) {
            b <<= 1;
        }
        return minimumOneBitOperations((b >> 1) ^ b ^ n, res + b);
    }
};

class SolutionTraversal {
public:
    int minimumOneBitOperations(int n) {
        int ans = 0;
        while (n > 0) {
            int b = 1;
            while ((b << 1) <= n) {
                b <<= 1;
            }
            n ^= (b >> 1) ^ b;
            ans += b;
        }
        return ans;
    }
};

class SolutionLee215 {
public:
    int minimumOneBitOperations(int n) {
        // plagiarizing from https://leetcode.com/problems/minimum-one-bit-operations-to-make-integers-zero/discuss/877798/JavaC%2B%2BPython-3-Solutions-with-Prove-O(1)-Space
        // std::cout << std::bitset<32>(n) << "\n";
        int ans = 0;
        for (ans = 0; n > 0; n &= (n - 1)) {
            // why do like this?
            // Start from LSB to MSB, what we need to do on a higher bit is already done on the lower bits.
            ans = -(ans + (n ^ (n - 1)));
            // std::cout << "ans: " << ans << "\t";
        }
        return std::abs(ans);
    }
};
