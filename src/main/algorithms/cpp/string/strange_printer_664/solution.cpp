#include "../../head.h"


class Solution {
public:
    int strangePrinter(std::string const & s) {
        // plagiarizing from https://leetcode.com/problems/strange-printer/discuss/106810/Java-O(n3)-DP-Solution-with-Explanation-and-Simple-Optimization/198971
        // get some improving idea from https://leetcode.com/problems/strange-printer/discuss/106794/One-suggestion-for-all-solutions
        // s = re.sub(r'(.)\1*', r'\1', s) //python to simply aaaabbb to ab
        if (2 > s.size()) {
            return s.size();
        }
        std::regex re("(.)\\1*");
        std::string moveRepeat;
        // moveRepeat = std::regex_replace(s, re, "$1");
        std::regex_replace(std::back_inserter(moveRepeat), s.begin(), s.end(), re, "$1");
        int moveRepeatSize = moveRepeat.size();
        std::vector<std::vector<int>> dp(moveRepeatSize, std::vector<int>(moveRepeatSize, moveRepeatSize));
        for (int row = 0; row < moveRepeatSize; row++) {
            dp[row][row] = 1;
        }
        for (int index = 0; index < moveRepeatSize; index++) {
            for (int inner = index - 1; inner >= 0; inner--) {
                for (int middle = inner; middle < index; middle++) {
                    /*
                    if (moveRepeat[middle] == moveRepeat[index]) {
                        dp[inner][index] = std::min(dp[inner][index], dp[inner][middle] + dp[middle + 1][index] - 1);
                    } else {
                        dp[inner][index] = std::min(dp[inner][index], dp[inner][middle] + dp[middle + 1][index]);
                    }
                    */
                    dp[inner][index] = std::min(dp[inner][index],
                                                dp[inner][middle] + dp[middle + 1][index] -
                                                (moveRepeat[middle] == moveRepeat[index] ? 1 : 0));
                    // the equal judgement can be inner == middle + 1, inner == index, middle == index,
                    // but can not be middle == middle + 1
                }
            }
        }
        return dp[0][moveRepeatSize - 1];
    }
};
