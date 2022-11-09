#include "../../head.h"


#define TOP_DOWN_DP
class Solution {
public:
    int deleteString(std::string const & s) {
        int const sSize = s.size();
        std::vector<int> dpMemo(sSize, INIT);
        #ifdef TOP_DOWN_DP
        // plagiarizing from https://leetcode.com/problems/maximum-deletions-on-a-string/solutions/2648927/top-down-pruning-vs-bottom-up-lps/
        std::function<int(int idx)> dp = [&](int idx) -> int {
            if (INIT == dpMemo[idx]) {
                dpMemo[idx] = 1; // at least can do one deleting operation
                for (int len = 1; dpMemo[idx] <= sSize - (idx + len)/*substring can do at most substring.size() deleting operation*/; len++) {
                    if (EQUAL_VAL == s.compare(idx, len, s, idx + len, len)) {
                        dpMemo[idx] = std::max(dpMemo[idx], 1 + dp(idx + len));
                    }
                }
            }
            return dpMemo[idx];
        };
        return dp(0);
        #else
        // plagiarizing from https://leetcode.com/problems/maximum-deletions-on-a-string/solutions/2648900/java-c-python-dp-solution/
        std::vector<std::vector<int>> lpcs(sSize + 1, std::vector<int>(sSize + 1, INIT)); // memory the longest prefix common substring.
        for (int idx = sSize - 1; idx >= 0; idx--) {
            dpMemo[idx] = 1;
            for (int rIdx = idx + 1; rIdx < sSize; rIdx++) {
                if (s[idx] == s[rIdx]) {
                    lpcs[idx][rIdx] = lpcs[idx + 1][rIdx + 1] + 1; // s[i] == s[j], then we can from s[i + 1] and s[j + 1] to s[i] and s[j]
                }
                if (lpcs[idx][rIdx] >= rIdx - idx) { // we can do a deleting operation [idx, rIdx - 1]
                    dpMemo[idx] = std::max(dpMemo[idx], dpMemo[rIdx] + 1);
                }
            }
        }
        return dpMemo[0];

        #endif

    }
 private:
    static int const INIT = 0;
    static int const EQUAL_VAL = 0;
};
int const Solution::INIT;