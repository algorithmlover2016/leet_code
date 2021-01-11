#include "../../head.h"


#define DEBUG
class SolutionWrongAnswer {
public:
    std::vector<bool> canMakePaliQueries(std::string const & s,
            std::vector<std::vector<int>> const & queries) {
        int const queriesSize = queries.size();
        std::vector<bool> ans(queriesSize, false);

        for (int idx = 0; idx < queriesSize; idx++) {
            auto const & query = queries[idx];
            if (QUERY_MIN_LEN > query.size()) {
                continue;
            }
            std::string subStr = s.substr(query[START_IDX],
                                            query[END_IDX] - query[START_IDX] + 1);
            // because there is a rearrrange operation, so we can't use this function directly
            int minInsertLen = minInsertions(subStr);
            #ifdef DEBUG
            std::cout << "idx, subStr: " << idx << ",\t" << subStr << ",\t" << minInsertLen << "\n";
            #endif
            if (query[MIN_CHANGE_LEN_IDX] >= (minInsertLen + 1) / 2) {
                ans[idx] = true;
            }
        }
        return ans;
    }
private:
    int minInsertions(std::string const & s) {
        // plagiarizing from palindrome_partitioning_ii_132
        // maybe longest common substring
        int const sSize = s.size();
        if (JUST_RETURN >= sSize) {
            return 0;
        }
        std::string ss(s.rbegin(), s.rend());
        int lcSubStrLen = longestCommonSubstring(s, ss);
        return sSize - lcSubStrLen;
    }
    int longestCommonSubstring(std::string const & str1, std::string const & str2) {
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
private:
    static int const JUST_RETURN = 1;
    static int const QUERY_MIN_LEN = 3;
    static int const START_IDX = 0;
    static int const END_IDX = 1;
    static int const MIN_CHANGE_LEN_IDX = 2;
};

// #define DEBUG
class Solution {
public:

    std::vector<bool> canMakePaliQueries(std::string const & s,
            std::vector<std::vector<int>> const & queries) {
        int const sSize = s.size();
        // plagiarizing from https://leetcode.com/problems/can-make-palindrome-from-substring/discuss/372044/Short-and-fast-C%2B%2B-prefix-xor-solution-beats-100
        // plagiarizing from https://leetcode.com/problems/can-make-palindrome-from-substring/discuss/371999/Python-100-runtime-and-memory
        std::vector<std::vector<int>> dpMemo(sSize + 1,
                 std::vector<int>(LOWERCASE_LETTERS_LEN, 0));

        for (int idx = 0; idx < sSize; idx++) {
            dpMemo[idx + 1] = dpMemo[idx];
            dpMemo[idx + 1][s[idx] - MIN_LETTER] += 1;
        }
        int const queriesSize = queries.size();
        std::vector<bool> ans(queriesSize, false);
        for (int idx = 0; idx < queriesSize; idx++) {
            auto const & query = queries[idx];
            if (QUERY_MIN_LEN > query.size()) {
                continue;
            }
            auto & startVec = dpMemo[query[START_IDX]];
            auto & endVec = dpMemo[query[END_IDX] + 1];

            int oddNum = 0;
            
            #ifdef DEBUG
            std::cout << "idx: " << idx << "\n";
            #endif
            for (int letterIdx = 0; letterIdx < LOWERCASE_LETTERS_LEN; letterIdx++) {
                if ((endVec[letterIdx] - startVec[letterIdx]) & 0x01) {
                    #ifdef DEBUG
                    std::cout << "letter: " << static_cast<char>(letterIdx + MIN_LETTER) << "\t";
                    #endif
                    oddNum++;
                }
            }
            #ifdef DEBUG
            std::cout << "\n";
            #endif
            if ((oddNum >> 1) <= query[MIN_CHANGE_LEN_IDX]) {
                ans[idx] = true;
            }
        }
        return ans;

    }
    private:
    static int const LOWERCASE_LETTERS_LEN = 26;
    static char const MIN_LETTER = 'a';
    static int const QUERY_MIN_LEN = 3;
    static int const START_IDX = 0;
    static int const END_IDX = 1;
    static int const MIN_CHANGE_LEN_IDX = 2;
};

class Solution {
public:

    std::vector<bool> canMakePaliQueries(std::string const & s,
            std::vector<std::vector<int>> const & queries) {
        int const sSize = s.size();
        // plagiarizing from https://leetcode.com/problems/can-make-palindrome-from-substring/discuss/372044/Short-and-fast-C%2B%2B-prefix-xor-solution-beats-100
        // plagiarizing from https://leetcode.com/problems/can-make-palindrome-from-substring/discuss/371999/Python-100-runtime-and-memory
        std::vector<int> dpMemo(sSize + 1, 0);
        for (int idx = 0; idx < sSize; idx++) {
            dpMemo[idx + 1] = dpMemo[idx] ^ (1 << (s[idx] - MIN_LETTER));
        }
        int const queriesSize = queries.size();
        std::vector<bool> ans(queriesSize, false);
        for (int idx = 0; idx < queriesSize; idx++) {
            auto const & query = queries[idx];
            if (QUERY_MIN_LEN > query.size()) {
                continue;
            }
            // include start, so dpMemo record from zero to query[idx] - 1;
            int startVal = dpMemo[query[START_IDX]];
            int endVal = dpMemo[query[END_IDX] + 1];
            if ((__builtin_popcount(startVal ^ endVal) >> 1) <= query[MIN_CHANGE_LEN_IDX]) {
                ans[idx] = true;
            }
        }
        return ans;
    }

private:
    static int const LOWERCASE_LETTERS_LEN = 26;
    static char const MIN_LETTER = 'a';
    static int const QUERY_MIN_LEN = 3;
    static int const START_IDX = 0;
    static int const END_IDX = 1;
    static int const MIN_CHANGE_LEN_IDX = 2;
};
