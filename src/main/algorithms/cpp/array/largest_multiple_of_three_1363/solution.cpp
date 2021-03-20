#include "../../head.h"


// #define DEBUG
class Solution {
public:
    std::string largestMultipleOfThree(std::vector<int> const & digits) {
        // plagiarizing idea from https://leetcode.com/problems/largest-multiple-of-three/discuss/518830/C%2B%2BJava-Concise-O(n)
        // if mod is 1, we should first try to remove 1, which can be 1, 4, 7, however, there will be two of (2, 5, 8)
        // to make the mod is 1, then we have to try to remove 2, 5 or 8;
        std::array<int, MOD_LEN> modLeftOne{{1, 4, 7, 2, 5, 8}};
        // if mod is 2, we should first try to remove 1, which can be 2, 5, 8, however, there will be two of (1, 4, 7)
        // to make the mod is 2, then we have to try to remove 1, 4 or 7;
        std::array<int, MOD_LEN> modLeftTwo{{2, 5, 8, 1, 4, 7}};
        std::string ans;
        if (digits.empty()) {
            return ans;
        }
        std::array<int, DIGITS_LEN> digitsCnt{{}};
        int sum = 0;
        for (int digit : digits) {
            digitsCnt[digit]++;
            sum += digit;
        }
        while (0 != (sum % MOD)) {
            for (auto mod : (1 == sum % MOD) ? modLeftOne : modLeftTwo) {
                // find the first that let the sum % mod == mod, we can get the ans;
                // if not exist, remove the (sum + 1) % mod, then will need another remove operation
                if (digitsCnt[mod] > 0) {
                    digitsCnt[mod]--;
                    sum -= mod;
                    break;
                }
            }
        }
        // get the max ans
        for (int digit = 9; digit > -1; digit--) {
            #ifdef DEBUG
            std::cout << digitsCnt[digit] << ": " << '0' + digit << "\n";
            #endif

            ans += std::string(digitsCnt[digit], '0' + digit);
        }
        // remove the unnecessary leading zeros, which means if ans start from '0', it must be "0"
        return (!ans.empty() && ans.front() == '0') ? "0" : ans;
    }
private:
    static int const MOD_LEN = 6;
    static int const DIGITS_LEN = 10;
    static int const MOD = 3;
};

class Solution {
public:
    std::string largestMultipleOfThree(std::vector<int> & digits) {
        // plagiarizing from https://leetcode.com/problems/largest-multiple-of-three/discuss/517628/Python-Basic-Math
        // dp solution
        std::vector<int> dpMemo(3, -1);
        std::sort(digits.begin(), digits.end(), [] (int left, int right) {
                return left >= right;
                });
        int y = 0;
        for (auto const digit : digits) {
            dpMemo.emplace_back(0);
            for (auto ele : dpMemo) {
                y = ele * 10 + digit;
                int mod = y % MOD;
                if (mod < 0) {
                    mod += MOD;
                }
                dpMemo[mod] = std::max(dpMemo[mod], y);
            }
        }
        return dpMemo[0] >= 0 ? std::to_string(dpMemo[0]) : "";
    }
private:
    static int const MOD = 3;
};

// #define DEBUG
class SolutionDpSignedIntegerOverflow {
public:
    std::string largestMultipleOfThree(std::vector<int> & digits) {
        // plagiarizing from https://leetcode.com/problems/largest-multiple-of-three/discuss/517628/Python-Basic-Math
        // dp solution
        std::vector<long long> curDpMemo{{-1, -1, -1, 0}};
        #ifdef DEBUG
        std::cout << "sort begin\n";
        #endif
        // if use lambda expression, it will overflow when digits.size() is too large
        std::sort(digits.begin(), digits.end(), std::greater<int>());
        #ifdef DEBUG
        std::cout << "sort done\n";
        #endif

        for (auto const digit : digits) {
            std::vector<long long> nextDpMemo(curDpMemo);
            for (auto ele : curDpMemo) {
                long long y = ele * 10 + digit;
                int mod = y % MOD;
                if (mod < 0) {
                    mod += MOD;
                }
                #ifdef DEBUG
                std::cout << digit << ", " << ele << ", " << y << ", " << mod << "\n";
                #endif
                nextDpMemo[mod] = std::max(nextDpMemo[mod], y);
            }
            std::swap(curDpMemo, nextDpMemo);
        }
        return curDpMemo[0] >= 0 ? std::to_string(curDpMemo[0]) : "";
    }
private:
    static int const MOD = 3;
};
