#include "../../head.h"


class Solution {
public:
    int minAddToMakeValid(std::string const & S) {
        int const SSize = S.size();
        if (JUST_RETURN >= SSize) {
            return SSize;
        }

        int ans = 0;
        int curParentheseLeft = 0;
        for (auto const & c : S) {
            if (PARENTHESE_LEFT == c) {
                curParentheseLeft++;
            } else {
                if (0 < curParentheseLeft) {
                    curParentheseLeft--;
                } else {
                    ans++;
                }
            }
        }
        return ans + curParentheseLeft;
        
    }
private:
    static int const JUST_RETURN = 1;
    static char const PARENTHESE_LEFT = '(';
    static char const PARENTHESE_RIGHT = ')';
};
