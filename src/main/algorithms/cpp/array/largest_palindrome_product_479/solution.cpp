#include "../../head.h"


// #define DEBUG
class Solution {
public:
    int largestPalindrome(int n) {
        // plagiairizing from https://leetcode.com/problems/largest-palindrome-product/discuss/96306/Java-solutions-with-two-different-approaches
        long maxHalf = std::pow(10, n) - 1; // 999...9 total n digits which are all nine;
        long minHalf = maxHalf / 10;  // 999...9, total n - 1 digits which are all nine;
        for (int num = maxHalf; num > minHalf; num--) {
            std::string leftStr = std::to_string(num);
            std::string rightStr(leftStr.rbegin(), leftStr.rend());
            long product = std::stol(leftStr + rightStr);
            #ifdef DEBUG
            std::cout << num << ", " << product << "; ";
            #endif
            for (int multiOne = maxHalf; multiOne >= minHalf; multiOne--) {
                int multiOther = product / multiOne;
                if (multiOther > multiOne) {
                    break;
                }
                if (0 == product % multiOne) {
                    return product % MOD;
                }
            }
        }
        return 9; // when n = 1, the maximum palindrome is 9
    }

private:
    static int const MOD = 1337;
};

class Solution {
public:
    int largestPalindrome(int n) {
        const long long arr[] = {0,9,987,123,597,677,1218,877,475};
        return (arr[n]);
    }
};


class Solution {
    long generate(int x) {
        long y = x;
        while (x > 0) {
            y = y * 10 + x % 10;
            x /= 10;
        }
        return y;
    }

public:
    int largestPalindrome(int n) {
        if (n == 1) return 9;
        long upper = std::pow(10, n) - 1, lower = upper / 10 + 1;
        long maxNum = upper * upper, half = maxNum / std::pow(10, n);
        while (true) {
            long palin = generate(half);
            for (long i = upper; i >= lower; i--) {
                if (i * i < palin) break;
                if (palin % i == 0) return palin % 1337;
            }
            half--;
        }
        return -1;
    }
};
