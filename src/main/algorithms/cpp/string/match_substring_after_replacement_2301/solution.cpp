#include "../../head.h"


// #define NO_CALL_SUBFUNC
class Solution {
public:
    bool matchReplacement(std::string const & s, std::string const & sub, std::vector<std::vector<char>> const & mappings) {
        // plagiarizing from https://leetcode.com/problems/match-substring-after-replacement/discuss/2138790/Greedy-Approach-or-O(N-*K)-or-C%2B%2B-Solution
        // and https://leetcode.com/problems/match-substring-after-replacement/discuss/2139534/Brute-Force-vs.-KMP
        std::unordered_map<char, std::unordered_set<char>> mapps;
        for (auto & mapping : mappings) {
            if (mapping.size() < MAPPING_LEN) {
                continue;
            }
            mapps[mapping[MAPPING_FIRST_IDX]].insert(mapping[MAPPING_SECOND_IDX]);
        }
        /*
        let me explain why we can get = in equation `idx + sub.size() <= s.size()`;
        idx can change from 0 to s.size() - 1;
        Then if we add an offset, we have an equation that offset = s.size() - 1 - idx + 1.
        Here, offset means there are offset characters from idx to s.size() - 1;
        so we have an equation sub.size() = s.size() - 1 - idx + 1 = s.size() - idx;
        which alse means that idx + sub.size() = s.size() is right.
        */
        #ifdef NO_CALL_SUBFUNC
        for (int idx = 0, subIdx = 0; idx + sub.size() <= s.size(); idx++) {
            for (subIdx = 0; subIdx < sub.size(); subIdx++) {
                if (s[idx + subIdx] != sub[subIdx] && mapps[sub[subIdx]].find(s[idx + subIdx]) == mapps[sub[subIdx]].end()) {
                    // we can not find a mapping from sub[subIdx] to s[idx + subIdx]
                    break;
                }
            }
            if (subIdx == sub.size()) {
                return true;
            }
        }
        #else
        for (int idx = 0; idx + sub.size() <= s.size(); idx++) {
            if (check(s, idx, sub, mapps)) {
                return true;
            }
        }
        #endif
        return false;

    }
#ifndef NO_CALL_SUBFUNC
private:
    bool check(std::string const & s, int idx, std::string const & sub, std::unordered_map<char, std::unordered_set<char>> const & mapps) {
        if (idx + sub.size() > s.size()) {
            return false;
        }
        for (int subIdx = 0; subIdx < sub.size(); ) {
            if (s[idx + subIdx] == sub[subIdx] || (mapps.find(sub[subIdx]) != mapps.end() && mapps.at(sub[subIdx]).count(s[idx + subIdx]) > 0)) {
                subIdx++;
            } else {
                return false;
            }
        }
        return true;
    }
#endif

private:
    constexpr int static MAPPING_LEN = 2;
    constexpr int static MAPPING_FIRST_IDX = 0;
    constexpr int static MAPPING_SECOND_IDX = 1;
    
};


// http://jakeboxer.com/blog/2009/12/13/the-knuth-morris-pratt-algorithm-in-my-own-words/
// and https://www.ruanyifeng.com/blog/2013/05/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm.html
// and https://www.zhihu.com/question/21923021
#define DEBUG
class SolutionWrong {
public:
    bool matchReplacement(std::string const & s, std::string const & sub, std::vector<std::vector<char>> const & mappings) {
        std::unordered_map<char, std::unordered_set<char>> mapps;
        for (auto & mapping : mappings) {
            if (mapping.size() < MAPPING_LEN) {
                continue;
            }
            mapps[mapping[MAPPING_FIRST_IDX]].insert(mapping[MAPPING_SECOND_IDX]);
        }
        #ifdef DEBUG
        for (auto & [key, val] : mapps) {
            std::cout << key << ": ";
            for (auto c : val) {
                std::cout << c << ",";
            }
            std::cout << "\n";
        }
        #endif

        std::vector<int> lps = computeLPS(sub, mapps);
        for (int idx = 0, subIdx = 0; idx < s.size();) {
            if (s[idx] == sub[subIdx] || (mapps.find(sub[subIdx]) != mapps.end() && mapps.at(sub[subIdx]).count(s[idx]))) {
                #ifdef DEBUG
                std::cout << idx << ", " << subIdx << " match\n";
                #endif
                idx++;
                subIdx++;
            } else {
                if (subIdx) {
                    subIdx = lps[subIdx - 1];
                    #ifdef DEBUG
                    std::cout << "need adjust subIdx: " << subIdx << "\n";
                    #endif
                } else {
                    #ifdef DEBUG
                    std::cout << "need new start\n";
                    #endif
                    idx++;
                }
            }
            if (subIdx == sub.size()) {
                return true;
            }
        }
        return false;

    }
private:
    std::vector<int> computeLPS(std::string const & str, std::unordered_map<char, std::unordered_set<char>> const & mapps) {
        std::vector<int> lps(str.size());
        for (int idx = 1, subIdx = 0; idx < str.size(); idx++) {
            while (subIdx &&
                    (str[idx] != str[subIdx] &&
                    (mapps.find(str[subIdx]) == mapps.end() || mapps.at(str[subIdx]).find(str[idx]) == mapps.at(str[subIdx]).end()) &&
                    (mapps.find(str[idx]) == mapps.end() || mapps.at(str[idx]).find(str[subIdx]) == mapps.at(str[idx]).end()))) {
                        // the judgement is wrong.
                subIdx = std::max(0, lps[subIdx] - 1);
            }
            subIdx += str[idx] == str[subIdx] ||
                                    (mapps.find(str[subIdx]) != mapps.end() && mapps.at(str[subIdx]).count(str[idx]) > 0) ||
                                    (mapps.find(str[idx]) != mapps.end() && mapps.at(str[idx]).count(str[subIdx]) > 0);
            lps[idx] = subIdx;
        }
        #ifdef DEBUG
        for (int idx = 0; idx < lps.size(); idx++) {
            std::cout << "(" << idx << ", " << lps[idx] << "), ";
        }
        std::cout << "\n";
        #endif
        return lps;
    }

private:
    constexpr int static MAPPING_LEN = 2;
    constexpr int static MAPPING_FIRST_IDX = 0;
    constexpr int static MAPPING_SECOND_IDX = 1;
};