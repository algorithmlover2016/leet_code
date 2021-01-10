#include "../../head.h"


class SolutionWrong {
public:
    int numDecodings(std::string const & s) {
        // can't deal with **
        int const sSize = s.size();
        if (ONE_SIZE > sSize) {
            return 0;
        }
        std::vector<int> dpMemo(sSize + 1, 0);
        dpMemo[0] = 0;
        dpMemo[1] = ASTERISK_CHARACTER == s[0] ? 9 : (ZERO_CHARACTER == s[0] ? 0 : 1);

        for (int idx = 2; idx < dpMemo.size(); idx++) {
            if (ASTERISK_CHARACTER == s[idx - 1]) {
                dpMemo[idx] = dpMemo[idx - 1] + ASTERISK_MAP_NUM - 1;
                if (ZERO_CHARACTER + 1 == s[idx - ADJ_LEN]) {
                    dpMemo[idx] += dpMemo[idx - ADJ_LEN] + ASTERISK_MAP_NUM;
                } else if (ZERO_CHARACTER + 2 == s[idx - ADJ_LEN]) {
                    dpMemo[idx] += dpMemo[idx - ADJ_LEN] + ASTERISK_MAP_NUM - 3;
                }
            } else {
                if (ZERO_CHARACTER == s[idx - 1]) {
                    dpMemo[idx] = dpMemo[idx - 1];
                }
                int adjNum = std::stol(s.substr(idx - ADJ_LEN, ADJ_LEN));
                if (LOWER_BOUND < adjNum && UPPER_BOUND > adjNum) {
                    dpMemo[idx] += dpMemo[idx - ADJ_LEN];
                }
            }
            dpMemo[idx] %= MOD;
        }
        return dpMemo[sSize];
    }

private:
    static int const ONE_SIZE = 1;
    static int const MOD = 1e9 + 7;
    static char const ZERO_CHARACTER = '0';
    static char const ASTERISK_CHARACTER = '*';
    static int const ADJ_LEN = 2;
    static int const LOWER_BOUND = 9;
    static int const UPPER_BOUND = 27;
    static int const ASTERISK_MAP_NUM = 9;
};

// #define DEBUG
class Solution {
public:
    int numDecodings(std::string const & s) {
        // plagiarizing from https://leetcode.com/problems/decode-ways-ii/discuss/105258/Java-O(N)-by-General-Solution-for-all-DP-problems
        int const sSize = s.size();
        if (ONE_SIZE > sSize) {
            return 0;
        }
        std::vector<int> dpMemo(sSize + 1, 0);
        dpMemo[0] = 1;
        dpMemo[1] = ASTERISK_CHARACTER == s[0] ? 9 : (ZERO_CHARACTER == s[0] ? 0 : 1);
        for (int idx = 2; idx < dpMemo.size(); idx++) {
            // jump from dpMemo[idx - 1];
            if (ASTERISK_CHARACTER == s[idx - 1]) {
                dpMemo[idx] += ASTERISK_MAP_NUM * dpMemo[idx - 1];
            } else if (ZERO_CHARACTER < s[idx -1]) {
                // dpMemo[idx] += 1 * dpMemo[idx - 1];
                dpMemo[idx] += dpMemo[idx - 1];

            }
            #ifdef DEBUG
            std::cout << "first: " << dpMemo[idx] << "\t";
            #endif
            // jump from idx - 2
            if (ASTERISK_CHARACTER == s[idx - 2]) {
                if (ASTERISK_CHARACTER == s[idx - 1]) {
                    dpMemo[idx] += TWO_ASTERISK_MAP_NUM * dpMemo[idx - 2];
                } else if (ZERO_CHARACTER + 7 > s[idx - 1]) {
                    #ifdef DEBUG
                    std::cout << "*"<< s[idx - 1] << "\t";
                    #endif
                    dpMemo[idx] += 2 * dpMemo[idx - 2];
                } else {
                    // dpMemo[idx] += 1 * dpMemo[idx - 2];
                    dpMemo[idx] += dpMemo[idx - 2]; // 17 - 19
                }
            } else if (ZERO_CHARACTER + 1 == s[idx - 2]) {
                if (ASTERISK_CHARACTER == s[idx - 1]) {
                    #ifdef DEBUG
                    std::cout << std::boolalpha <<  (ZERO_CHARACTER + 1 == s[idx - 2]) << '\t';
                    #endif
                    dpMemo[idx] += ASTERISK_MAP_NUM * dpMemo[idx - 2]; // just from 1 to 9;
                } else {
                    // dpMemo[idx] += 1 * dpMemo[idx - 2];
                    dpMemo[idx] += dpMemo[idx - 2];
                }
            } else if (ZERO_CHARACTER + 2 == s[idx - 2]) {
                if (ASTERISK_CHARACTER == s[idx - 1]) {
                    dpMemo[idx] += 6 * dpMemo[idx - 2]; // just from 1 to 6;
                } else if (ZERO_CHARACTER + 7 > s[idx - 1]) {
                    // dpMemo[idx] += 1 * dpMemo[idx - 2];
                    dpMemo[idx] += dpMemo[idx - 2];
                }
            }

            #ifdef DEBUG
            std::cout << "first + second: " << dpMemo[idx] << "\n";
            #endif
            dpMemo[idx] %= MOD;
        }

        return dpMemo[sSize];
    }

    private:
    static int const ONE_SIZE = 1;
    static int const MOD = 1e9 + 7;
    static char const ZERO_CHARACTER = '0';
    static char const ASTERISK_CHARACTER = '*';
    static int const ADJ_LEN = 2;
    static int const ASTERISK_MAP_NUM = 9;
    static int const TWO_ASTERISK_MAP_NUM = 15; // 11 - 19 and 21 - 26
};
