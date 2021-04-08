#include "../../head.h"


// #define DEBUG
class Solution {
public:
    int findIntegers(int num) {
        // plagiarizing idea from https://leetcode.com/problems/non-negative-integers-without-consecutive-ones/discuss/103754/C%2B%2B-Non-DP-O(32)-Fibonacci-solution
        static bool fibonacciInitFlag = (init(), true);
        int ans = 0;

        bool preBitSet = false;
        for (int bitIdx = INT_MAX_BITS - 1; bitIdx >= 0; bitIdx--) {
            #ifdef DEBUG
            std::cout << bitIdx << ", " << (num & (1 << bitIdx)) << "\t";
            #endif
            if (0 != (num & (1 << bitIdx))) {
                // we set the bit of (1 << bitIdx) to be zero, and the added number will be the left (bigIdx) bits
                ans += fibonacci[bitIdx];
                // then we set the bitIdx with zero, we traverse to next bit.
                if (preBitSet) {
                    return ans;
                }
                preBitSet = true;
            } else {
                preBitSet = false;
            }
        }
        return ans + 1;
    }
private:
    void init() {
        fibonacci[0] = 1;
        fibonacci[1] = 2;
        for (int idx = 2; idx < INT_MAX_BITS; idx++) {
            fibonacci[idx] = fibonacci[idx - 1] + fibonacci[idx - 2];
            #ifdef DEBUG
            std::cout << fibonacci[idx] << ", ";
            #endif
        }
        #ifdef DEBUG
        std::cout << "\n";
        #endif
    }
    private:
    static std::vector<int> fibonacci;
    static int const INT_MAX_BITS = 31;
};
std::vector<int> Solution::fibonacci(Solution::INT_MAX_BITS, 0);

// #define DEC_TO_BIN_WITH_REVERSE
// #define DEBUG
class Solution {
public:
    int findIntegers(int num) {
        // plagiarizing https://leetcode.com/problems/non-negative-integers-without-consecutive-ones/discuss/103749/Java-Solution-DP
        #ifdef DEBUG_WITH_BITSET
        std::cout << std::bitset<std::numeric_limits<unsigned int>::digits>(num) << '\n';
        #endif
#ifdef DEC_TO_BIN_WITH_REVERSE
        std::string numStr(dec2Bin(num, true));
#else
        std::string numStr(dec2Bin(num));
        std::reverse(numStr.begin(), numStr.end());
#endif
        #ifdef DEBUG
        std::cout << numStr << "\n";
        #endif
        int const numStrSize = numStr.size();
        std::vector<int> formerFibonacci(numStrSize, 1);
        std::vector<int> fibonacci(numStrSize, 1);
        for (int idx = 1; idx < numStrSize; idx++) {
            fibonacci[idx] = fibonacci[idx - 1] + formerFibonacci[idx - 1];
            formerFibonacci[idx] = fibonacci[idx - 1];
            #ifdef DEBUG
            std::cout << idx << ": " << fibonacci[idx] << ", " << formerFibonacci[idx] << ";\t";
            #endif
        }
        int ans = fibonacci[numStrSize - 1] + formerFibonacci[numStrSize - 1];
        // from most significant bit to least significant bit
        for (int idx = numStrSize - 2; idx >= 0; idx--) {
            if ('1' == numStr[idx] && '1' == numStr[idx + 1]) {
                // there are two 1 adjoin together
                return ans;
            } else if ('0' == numStr[idx] && '0' == numStr[idx + 1]) {
                // we can't set "10" when meeting 00
                ans -= formerFibonacci[idx];

            }
        }
        return ans;
    }

private:
    std::string dec2Bin(int num, bool reverse = false) {
        std::string ans;
        if (reverse) {
            while (num > 0) {
                if (1 & num) {
                    ans.append(1, '1');
                } else {
                    ans.append(1, '0');
                }
                num >>= 1;
            }
        } else {
            bool mostSigBit = false;
            for (int idx = std::numeric_limits<int>::digits - 1; idx >= 0; idx--) {
                if (num & (1 << idx)) {
                    ans.append(1, '1');
                    mostSigBit = true;
                } else {
                    if (mostSigBit) {
                        ans.append(1, '0');
                    }
                }
            }
        }
        return ans;
    }
};
