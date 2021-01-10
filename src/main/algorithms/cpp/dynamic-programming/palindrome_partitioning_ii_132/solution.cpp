#include "../../head.h"


class Solution {
public:
    int minCut(std::string const & s) {
        // plagiarizing idea from https://leetcode.com/problems/palindrome-partitioning-ii/discuss/42199/My-DP-Solution-(-explanation-and-code)

        int const sSize = s.size();
        if (JUST_RETURN >= sSize) {
            return 0;
        }
        std::vector<std::vector<bool>> isPalindrome(sSize,
                std::vector<bool>(sSize, false));
        
        std::vector<int> dpMemo(sSize);
        for (int left = sSize - 1; left > -1; left--) {
            dpMemo[left] = sSize - left - 1;
            for (int right = left; right < sSize; right++) {
                if (s[left] == s[right] &&
                        (right - left < 2 || isPalindrome[left + 1][right - 1])) {
                    isPalindrome[left][right] = true;
                    if (right == sSize - 1) {
                        dpMemo[left] = 0;
                    } else {
                        dpMemo[left] = std::min(dpMemo[left], 1 + dpMemo[right + 1]);
                    }
                }
            }
        }
        return dpMemo[0];
    }
private:
    static int const JUST_RETURN = 1;
};

class Solution {
public:
    int minCut(std::string const & s) {
        // plagiarizing idea from https://leetcode.com/problems/palindrome-partitioning-ii/discuss/42198/My-solution-does-not-need-a-table-for-palindrome-is-it-right-It-uses-only-O(n)-space.

        int const sSize = s.size();
        if (JUST_RETURN >= sSize) {
            return 0;
        }

        std::vector<int> dpMemo(sSize + 1);
        for (int idx = 0; idx < dpMemo.size(); idx++) {
            dpMemo[idx] = idx - 1; // dpMemo[0] = -1;
        }
        for (int idx = 0; idx < sSize; idx++) {
            // s[idx] as the middle element
            // if the first time, delta = 0, has no meaning, but if latter update, delta has meaning
            // because we cound update dpMemo[idx1] early, idx1 > idx.
            for (int delta = 0;
                    idx - delta >= 0 && idx + delta < sSize && s[idx - delta] == s[idx + delta];
                    delta++) {
                dpMemo[idx + delta + 1] = std::min(dpMemo[idx + delta + 1], 1 + dpMemo[idx - delta]);
            }
            // s[idx] == s[idx + 1]
            for (int delta = 1;
                    idx - delta + 1 >= 0 && idx + delta < sSize && s[idx - delta + 1] == s[idx + delta];
                    delta++) {
                dpMemo[idx + delta + 1] = std::min(dpMemo[idx + delta + 1], 1 + dpMemo[idx - delta + 1]);
            }
        }
        return dpMemo[sSize];
    }
private:
    static int const JUST_RETURN = 1;
};
