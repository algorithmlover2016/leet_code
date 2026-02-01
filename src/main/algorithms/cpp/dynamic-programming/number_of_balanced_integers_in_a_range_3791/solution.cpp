#include "../../head.h"


class Solution {
private:
    // maximum length of num is 15, so halfLen is at most 7.5, 7.5 * 9 = 67.5
    const int offset = 100; // to handle negative sums, sum range is [-7.5 * 9, 7.5 * 9]
    const int maxIdxOffset = 165;
    const int minIdxOffset = 35;
    const int INIT_VAL = -1;
    std::vector<std::vector<std::vector<long long>>> memo{16, std::vector<std::vector<long long>>(170, std::vector<long long>(2, INIT_VAL))};
    std::string inputS;
public:
    long long countBalanced(long long low, long long high) {
        return len(high) - len(low - 1);
    }
private:
    long long len(long long num) {
        // must be two digits at least
        if (num < 10) {
            return 0;
        }
        std::string numStr = std::to_string(num);
        const int n = numStr.size();
        inputS = numStr;
        long long res = 0;
        // count all balanced numbers with length less than n
        for (int len = 2; len < n; len++) {
            for (auto & row : memo) {
                for (auto & col : row) {
                    std::fill(col.begin(), col.end(), INIT_VAL);
                }
            }
            for (int numVal = 1; numVal <= 9; numVal++){
                res += countBalancedOfLengthDP(1, offset + numVal, false, len);
            }
        }
        // count balanced numbers with length equal to n
        inputS = numStr;
        for (auto & row : memo) {
            for (auto & col : row) {
                std::fill(col.begin(), col.end(), INIT_VAL);
            }
        }
        for (int firstDigit = 1; firstDigit <= (numStr[0] - '0'); firstDigit++) {
            bool isLimit = (firstDigit == (numStr[0] - '0'));
            res += countBalancedOfLengthDP(1, firstDigit + offset, isLimit, n);
        }
        return res;
    }

    long long countBalancedOfLengthDP(int idx, int currSum, bool isLimit, int len) {
        if (currSum > maxIdxOffset || currSum < minIdxOffset) {
            // we can never find a balance value in this situation.
            return 0;
        }
        if (idx == len) {
            return (currSum == offset) ? 1 : 0;
        }
        if (INIT_VAL != memo[idx][currSum][isLimit]) {
            return memo[idx][currSum][isLimit];
        }
        long long ans = 0;
        int upBound = isLimit ? (inputS[idx] - '0') : 9;
        for (int digit = 0; digit <= upBound; digit++) {
            ans += countBalancedOfLengthDP(idx + 1, currSum + ((idx & 1) ? -digit : digit),
                                            isLimit && (digit == upBound), len);
        }
        memo[idx][currSum][isLimit] = ans;
        return ans;
    }
};