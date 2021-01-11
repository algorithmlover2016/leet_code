#include "../../head.h"


class Solution {
public:
    int longestCommonSubsequence(std::string const & text1, std::string const & text2) {
        if (text1.empty() || text2.empty()) {
            return 0;
        }
        std::vector<std::vector<int> > dp(text1.size() + 1, std::vector<int>(text2.size() + 1, 0));
        for (int row = 0; row < text1.size(); row++) {
            for (int col = 0; col < text2.size(); col++) {
                if (text1[row] == text2[col]) {
                    dp[row + 1][col + 1] = dp[row][col] + 1;
                } else {
                    dp[row + 1][col + 1] = std::max(dp[row][col + 1], dp[row + 1][col]);
                }
            }
        }
        return dp[text1.size()][text2.size()];

    }
};

class Solution {
public:
    int longestCommonSubsequence(std::string const & str1, std::string const & str2) {
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
};
