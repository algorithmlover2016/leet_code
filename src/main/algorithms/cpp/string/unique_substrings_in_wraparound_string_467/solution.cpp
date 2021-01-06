#include "../../head.h"


class SolutionRepeatCnt {
public:
    int findSubstringInWraproundString(std::string p) {
        int const pSize = p.size();
        if (JUST_RETURN >= pSize) {
            return pSize;
        }
        int contineous = 1;
        int ans = contineous;
        for (int idx = 1; idx < pSize; idx++) {
            if ((p[idx] == p[idx - 1] + 1) ||
                    (JUMP_LEFT == p[idx - 1] && JUMP_RIGHT == p[idx])) {
                contineous++;
            } else {
                // ans += contineous * (contineous + 1) / 2;
                contineous = 1;
            }
            ans += contineous;
        }
        // ans += contineous * (contineous + 1) / 2;
        return ans;

    }
private:
    static int const JUST_RETURN = 1;
    static char const JUMP_LEFT = 'z';
    static char const JUMP_RIGHT = 'a';
    static int const INITIALIZE = 1;
};

// #define DEBUG
class SolutionWrongAnswer {
public:
    int findSubstringInWraproundString(std::string p) {
        p += 'A';
        int const pSize = p.size();
        if (JUST_RETURN >= pSize - 1) {
            return pSize - 1;
        }
        std::set<std::string> seen;
        int contineous = 0;
        int ans = 0;
        int needMinus = 0;
        std::string markStr = p.substr(0, 1);
        // seen.insert(std::string(2, p[0]));
        for (int idx = 0; idx < pSize - 1; idx++) {
            contineous++;
            if ((p[idx] == p[idx + 1] - 1) ||
                    (JUMP_LEFT == p[idx] && JUMP_RIGHT == p[idx + 1])) {
                continue;
            } else {
                markStr += p[idx];
                #ifdef DEBUG
                std::cout << "markStr: " << markStr << '\t';
                #endif
                if (seen.find(markStr) == seen.end()) {
                    #ifdef DEBUG
                    std::cout << "markStr add\n";
                    #endif
                    ans += contineous * (contineous + 1) / 2;
                    seen.insert(markStr);
                    if (contineous > 1) {
                        char start = markStr[0];
                        for (int idx = 0; idx < contineous; idx++) {
                            auto it = seen.insert(std::string(2, start));
                            if (!it.second) {
                                needMinus++;
                            }
                            if ('z' == start)  {
                                start = 'a';
                            } else {
                                start++;
                            }
                        }
                    }
                }
                markStr = p.substr(idx + 1, 1);
                contineous = 0;
            }
        }
        // ans += contineous * (contineous + 1) / 2;
        return ans - needMinus;

    }
    private:
    static int const JUST_RETURN = 1;
    static char const JUMP_LEFT = 'z';
    static char const JUMP_RIGHT = 'a';
    static int const INITIALIZE = 1;
};

class Solution {
public:
    int findSubstringInWraproundString(std::string const & p) {
        // plagiarizing from https://leetcode.com/problems/unique-substrings-in-wraparound-string/discuss/95439/Concise-Java-solution-using-DP
        int const pSize = p.size();
        if (JUST_RETURN >= pSize) {
            return pSize;
        }
        std::vector<int> cnt(LOWCASE_LETTER_LEN, 0);
        int maxLen = 0;
        for (int idx = 0; idx < pSize; idx++) {
            if (idx > 0 &&(p[idx] == p[idx - 1] + 1 ||
                        JUMP_DIFF == p[idx - 1] - p[idx])) {
                maxLen++;
            } else {
                maxLen = 1;
            }
            int letterIdx = p[idx] - CHAR_2_IDX;
            cnt[letterIdx] = std::max(cnt[letterIdx], maxLen);
        }
        return std::accumulate(cnt.begin(), cnt.end(), 0);

    }
private:
    static int const JUST_RETURN = 1;
    static int const LOWCASE_LETTER_LEN = 26;
    static int const JUMP_DIFF = 'z' - 'a';
    static char const CHAR_2_IDX = 'a';
};
