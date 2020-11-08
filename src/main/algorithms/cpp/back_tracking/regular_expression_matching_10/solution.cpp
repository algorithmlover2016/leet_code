#include "../../head.h"


class SolutionWrongAnswer {
public:
    // when s = "aab" and p = "c*a*b", the method can't ignore "c*"
    bool isMatch(std::string const & s, std::string const & p) {
        char const *sStart = s.c_str(), *pStart = p.c_str();
        char const *lastAsteriskPos = nullptr;
        char const * sRecord = nullptr;
        while (*sStart) {
            if (('.' == *pStart) || *pStart == *sStart) {
                pStart++;
                sStart++;
                continue;
            }
            if ('*' == *pStart) {
                lastAsteriskPos = pStart - 1;
                sRecord = sStart;
                pStart++;
                continue;
            }
            if (lastAsteriskPos) {
                if ('.' == *lastAsteriskPos || *sStart == *lastAsteriskPos) {
                    sStart = ++sRecord;
                    pStart = ++lastAsteriskPos;
                    continue;
                }
            }
            // std::cout << "judge at while " << "\n";
            return false;
        }
        // std::cout << "*pStart: " << *pStart << "\n";
        while ('*' == *pStart || (*pStart && '*' == *(++pStart))) {
            pStart++;
            // std::cout << "*pStart: " << *pStart << "\n";
        }

        return !(*pStart);
    }
};

class SolutionBackTracking {
public:
     // backTracking
    bool isMatch(std::string const & s, std::string const & p) {
        // plagiarizing from https://leetcode.com/problems/regular-expression-matching/discuss/5665/My-concise-recursive-and-DP-solutions-with-full-explanation-in-C%2B%2B
        if (p.empty()) {
            return s.empty();
        }
        if (1 < p.size() && '*' == p[1]) {
            return isMatch(s, p.substr(2)) || // just ignore the first two elements which is .*
                (!s.empty() && ('.' == p[0] || s[0] == p[0]) && isMatch(s.substr(1), p));
        } else {
            return !s.empty() && ('.' == p[0] || s[0] == p[0]) && isMatch(s.substr(1), p.substr(1));
        }
    }
};

class SolutionDP {
public:

    // dp solution
    bool isMatch(std::string const & s, std::string const & p) {
        // plagiarizing from https://leetcode.com/problems/regular-expression-matching/discuss/5665/My-concise-recursive-and-DP-solutions-with-full-explanation-in-C%2B%2B
        int const sSize = s.size(), pSize = p.size();
        std::vector<std::vector<bool>> dp(sSize + 1, std::vector<bool>(pSize + 1, false));

        dp[0][0] = true; // when s and p are all empty, matched

        // when p is empty, and s is not, is not matched
        for (int row = 1; row < dp.size(); row++) {
            dp[row][0] = false;
        }

        // when s is empty and p is not, but p can match empty which means p must be [a-z.]*, matched
        for (int col = 1; col < dp[0].size(); col++) {
            // can make col start from 2, because p.size() == 1, p can't match empty, init f[0][1] = false;
            dp[0][col] = col > 1 && ('*' == p[col - 1]) && dp[0][col - 2];
        }

        for (int row = 1; row < dp.size(); row++) {
            for (int col = 1; col < dp[row].size(); col++) {
                if ('*' != p[col - 1]) {
                    dp[row][col] = (s[row - 1] == p[col - 1] || '.' == p[col - 1]) && dp[row - 1][col - 1];
                } else {
                    dp[row][col] = dp[row][col - 2] || // doesn't use the [a-z.]* pair
                        // using the pair, so col keep the same and the row need minus one
                        (s[row - 1] == p[col - 2] || '.' == p[col - 2]) && dp[row - 1][col];
                }
            }
        }
        return dp[sSize][pSize];

    }
};
