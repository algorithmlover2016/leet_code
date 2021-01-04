#include "../../head.h"


class Solution {
public:
    std::string makeGood(std::string const & s) {
        int const sSize = s.size();
        if (JUST_RETURN >= sSize) {
            return s;
        }
        std::stack<int> leftCharsIdx;
        for (int idx = 0; idx < sSize; idx++) {
            if (!leftCharsIdx.empty() && DIFF_DIS == std::abs(s[idx] - s[leftCharsIdx.top()])) {
                leftCharsIdx.pop();
            } else {
                leftCharsIdx.emplace(idx);
            }
        }

        std::string ans;
        while (!leftCharsIdx.empty()) {
            ans = s[leftCharsIdx.top()] + ans;
            leftCharsIdx.pop();
        }
        return ans;

    }
private:
    static int const JUST_RETURN = 1;
    static int const DIFF_DIS = 'a' - 'A';
};
