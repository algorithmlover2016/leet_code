#include "../../head.h"


class SolutionTLE {
public:
    bool isMatch(std::string const & s, std::string const & p) {
        return backTracking(s, p, 0, 0);
    }
    bool backTracking(std::string const & s, std::string const & p,
            int sIndex, int pIndex) {
        if (sIndex == s.size()) {
            for (; pIndex < p.size(); pIndex++) {
                if ('*' != p[pIndex]) {
                    return false;
                }
            }
            return true;
        }
        if (pIndex == p.size()) {
            if ('*' != p[pIndex - 1]) {
                return false;
            }
            return true;
        }

        bool ans = false;
        if ('*' == p[pIndex]) {
            ans = backTracking(s, p, sIndex, pIndex + 1) ||
                backTracking(s, p, sIndex + 1, pIndex) || backTracking(s, p, sIndex + 1, pIndex + 1);
        } else if ((s[sIndex] == p[pIndex]) || ('?' == p[pIndex])) {
            ans = backTracking(s, p, sIndex + 1, pIndex + 1);
        }
        return ans;
    }
};

class Solution {
public:
    bool isMatch(std::string const & s, std::string const & p) {
        // plagiarizing from https://leetcode.com/problems/wildcard-matching/discuss/17810/Linear-runtime-and-constant-space-solution
        const char *sStart = s.c_str(), *pStart = p.c_str();

        const char *sRecord = nullptr;
        const char *lastAsteriskPos = nullptr;
        while (*sStart) {
            if (*pStart == *sStart || '?' == *pStart) {
                pStart++;
                sStart++;
                continue;
            }

            if ('*' == *pStart) {
                lastAsteriskPos = pStart++;
                sRecord = sStart;
                continue;
            }
            if (lastAsteriskPos) {
                sStart = ++sRecord;
                pStart = lastAsteriskPos + 1;
                continue;
            }
            return false;
        }
        while ('*' == *pStart) {
            pStart++;
        }
        return !(*pStart); // can't using nullptr == pStart as a judgement
    }
};
