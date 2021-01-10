#include "../../head.h"


class Solution {
public:
    int countPalindromicSubsequences(std::string const & S) {
        // plagiarizing idea from https://leetcode.com/problems/count-different-palindromic-subsequences/discuss/109507/Java-96ms-DP-Solution-with-Detailed-Explanation

        int const SSize = S.size();
        if (JUST_RETURN >= SSize) {
            return SSize;
        }

        std::vector<std::vector<int>> dpMemo(SSize,
                std::vector<int>(SSize, 0));
        for (int idx = 0; idx < SSize; idx++) {
            dpMemo[idx][idx] = 1;
        }

        for (int len = 1; len < SSize; len++) {
            for (int left = 0; left + len < SSize; left++) {
                int right = left + len;
                if (S[left] == S[right]) {
                    int low = left + 1;
                    int high = right - 1;
                    // while (low <= high && S[low] != S[right] && S[low] != S[left]) {
                    while (low <= high && S[low] != S[right]) {
                        low++;
                    }
                    // while (low <= high && S[low] != S[right] && S[high] != S[left]) {
                    while (low <= high && S[high] != S[right]) {
                        high--;
                    }
                    if (low > high) {
                        // there is no S[left] in S from left + 1 to right - 1
                        // [left + 1, right - 1] and left, [left + 1, right - 1], right
                        // and left, and left, right
                        dpMemo[left][right] = dpMemo[left + 1][right - 1] * 2 + 2;
                    } else if (low == high) {
                        // there is one character at low(hight) that S[low] = S[left] = S[right]
                        // [left + 1, right - 1] and left, [left + 1, right - 1], right
                        // left, right; can't add left or right, which has been computed at low(high)
                        dpMemo[left][right] = dpMemo[left + 1][right - 1] * 2 + 1;
                    } else {
                        // there is at least two character which are at low and high, seperately meet
                        // that S[left] = S[low] = S[high] = S[right]
                        // so from low + 1, to high - 1, using low and high or left and right are the same
                        // and left, right and left have already computed, so there is no need to add 2
                        dpMemo[left][right] = dpMemo[left + 1][right - 1] * 2 - dpMemo[low + 1][high - 1];
                    }
                } else {
                    dpMemo[left][right] = dpMemo[left + 1][right] + dpMemo[left][right - 1] -
                                            dpMemo[left + 1][right - 1];
                }
                if (dpMemo[left][right] < 0) {
                    dpMemo[left][right] += MOD;
                } else {
                    dpMemo[left][right] %= MOD;
                }
            }
        }
        return dpMemo[0][SSize - 1];
    }
    private:
    static int const MOD = 1e9 + 7;
    static int const JUST_RETURN = 1;
};
