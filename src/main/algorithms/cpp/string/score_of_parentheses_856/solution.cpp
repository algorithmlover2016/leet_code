#include "../../head.h"


class Solution {
public:
    int scoreOfParentheses(std::string const & S) {
        // plagiarizing from https://leetcode.com/problems/score-of-parentheses/discuss/141975/c%2B%2B-solution-using-stack-(5ms)-detail-explained
        std::stack<int> recordStack;
        recordStack.emplace(0);
        for (char c : S) {
            if ('(' == c) {
                recordStack.emplace(0);
            } else {
                int tmpPairScore = recordStack.top();
                recordStack.pop();
                recordStack.top() += (tmpPairScore == 0 ? 1 : tmpPairScore * 2);
            }
        }
        return recordStack.top();
    }
};

class SolutionO1SpaceON {
public:
    int scoreOfParentheses(std::string const & S) {
        // plagiarizing from https://leetcode.com/problems/score-of-parentheses/discuss/141777/C%2B%2BJavaPython-O(1)-Space
        int res = 0, l = 0;
        for (int i = 0; i < S.length(); ++i) {
            if (S[i] == '(') l++; else l--;
            if (S[i] == ')' && S[i - 1] == '(') res += 1 << l;
        }
        return res;
    }

};
