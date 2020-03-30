#include "../../head.h"

class Solution {
public:
    int longestValidParentheses(std::string const & s) {
        int pairCnt = 0;
        int leftParentheses = 0;
        for (int index = 0; index < s.size(); index++) {
            if ('(' == s[index]) {
                leftParentheses++;
            } else if (0 < leftParentheses) {
                leftParentheses--;
                pairCnt += 2;
            }

        }
        return pairCnt;

    }
};
