#include "../../head.h"


class Solution {
public:
    int minInsertions(std::string const & s) {
        // plagiarizing from palindrome_partitioning_ii_132
        // maybe longest common substring
        int const sSize = s.size();
        if (JUST_RETURN >= sSize) {
            return 0;
        }
        std::string ss(s.rbegin(), s.rend());
        int lcSubStrLen = longestCommonSubstring(s, ss);
        return sSize - lcSubStrLen;
    }
private:
    int longestCommonSubstring(std::string const & str1, std::string const & str2) {
        int const str1Size = str1.size();
        int const str2Size = str2.size();
        std::vector<std::vector<int>> dpMemo(str1Size + 1,
                std::vector<int>(str2Size + 1, 0));
        for (int idxStr1 = 0; idxStr1 < str1Size; idxStr1++) {
            for (int idxStr2 = 0; idxStr2 < str2Size; idxStr2++) {
                if (str1[idxStr1] == str2[idxStr2]) {
                    dpMemo[idxStr1 + 1][idxStr2 + 1] = 1 + dpMemo[idxStr1][idxStr2];
                } else {
                    dpMemo[idxStr1 + 1][idxStr2 + 1] = std::max(dpMemo[idxStr1][idxStr2 + 1],
                            dpMemo[idxStr1 + 1][idxStr2]);
                }
            }
        }
        return dpMemo[str1Size][str2Size];
    }
private:
    static int const JUST_RETURN = 1;
};
