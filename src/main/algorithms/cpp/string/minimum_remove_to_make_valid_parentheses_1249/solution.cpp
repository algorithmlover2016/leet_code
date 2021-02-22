#include "../../head.h"


class Solution {
public:
    std::string minRemoveToMakeValid(std::string const & s) {
        if (s.empty()) {
            return s;
        }
        static char const rP = ')';
        static char const lP = '(';
        std::string removeLP;
        int rPCnt = JUST_ZERO;
        for (auto it = s.crbegin(); it != s.crend(); it++) {
            if (rP == *it) {
                rPCnt++;
            } else if (lP == *it) {
                if (JUST_ZERO == rPCnt) {
                    continue;
                } else {
                    rPCnt--;
                }
            }
            removeLP += *it;
        }

        std::string removeRP;
        int lPCnt = JUST_ZERO;
        for (std::string::const_reverse_iterator it = removeLP.crbegin();
                it != removeLP.crend();
                it++) {
            if (lP == *it) {
                lPCnt++;
            } else if (rP == *it) {
                if (JUST_ZERO == lPCnt) {
                    continue;
                } else {
                    lPCnt--;
                }
            }
            removeRP += *it;
        }
        return removeRP;

    }
private:
    static int const JUST_ZERO = 0;
};
