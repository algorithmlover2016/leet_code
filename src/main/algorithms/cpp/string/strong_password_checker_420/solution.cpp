#include "../../head.h"

class SolutionNoMapStore {
public:
    int strongPasswordChecker(std::string const & s) {
        const int n = s.length();
        int insert = 0;
        int replace = 0;
        int has_digit = 0;
        int has_upper = 0;
        int has_lower = 0;
        int ones = 0;
        int twos = 0;
        int repeat = 1;
        for (const auto & ch : s) {
            has_digit = has_digit || isdigit(ch);
            has_upper = has_upper || isupper(ch);
            has_lower = has_lower || islower(ch);
        }
        for (int i = 1; i <= n; ++i) {
            if (i == n || s[i] != s[i - 1]) {
                if (repeat >= 3) {
                    replace += repeat / 3;
                    if (repeat % 3 == 0) {
                        ++ones;
                    } else if (repeat % 3 == 1) {
                        ++twos;
                    }
                }
                repeat = 1;
            } else {
                ++repeat;
            }
        }
        int must_change = 3 - has_digit - has_upper - has_lower;
        if (n < 6) {
            return max(6 - n, must_change);
        }        
        if (n <= 20) {
            return max(replace, must_change);
        }
        int total_remove = n - 20;
        int remove = total_remove;
        replace -= min(ones, remove);
        remove = max(0, remove - ones);
        replace -= min(twos, remove / 2);
        remove = max(0, remove - twos * 2);
        replace = max(0, replace - remove / 3);
        return total_remove + max(replace, must_change);
    }
};

class Solution {
private:
    int const MAXREPLEN = 0x03;
    int const MAXSTRLEN = 20;
    int const MINSTRLEN = 6;
public:
    int strongPasswordChecker(std::string const & s) {
        // plagiarizing from https://leetcode.com/problems/strong-password-checker/discuss/91007/C%2B%2B-0ms-O(n)-35-lines-solution-with-detailed-explanation
        int sSize = s.size();
        // std::cout << "s.size() : " << sSize << std::endl;
        // when sSize > MAXSTRLEN, there are at least (sSize - 20) elements to delete
        // when sSize < MINSTRLEN, there are at least (6 - sSize) elements to add
        int delTarget  = std::max(0, sSize - MAXSTRLEN), addTarget = std::max(0, MINSTRLEN - sSize);
        int toDel = 0, toAdd = 0, toReplace = 0, needUpper = 1, needLower = 1, needDigit = 1;

        // iterator s to find need operations
        for (int l = 0, r = 0, len = 0; r < sSize; r++) {
            if (isdigit(s[r])) {
                needDigit = 0;
            }
            if (islower(s[r])) {
                needLower = 0;
            }
            if (isupper(s[r])) {
                needUpper = 0;
            }

            // if (s[l] != s[r]) {
            //     l = r;
            // }
            // // the const int is meaningless
            // if (((len = r -l) == MAXREPLEN - 1) && (s[l] == s[l + 1]) && (s[l + 1] == s[r])) {
            //     // if need add eleements, add first
            //     if (toAdd < addTarget) {
            //         //        aaa -> aaBa
            //         // index: l r ->    l(r)
            //         toAdd++;
            //         l = r;
            //     // if no need adding(sSize >= 6), then replace elements
            //     } else {
            //         //        aaa -> aaB
            //         // index: l r ->   rl
            //         toReplace++;
            //         l = r + 1;
            //     }
            // }

            // the const int is meaningless
            if (((len = r -l) == MAXREPLEN - 1)) {
                if ((s[l] == s[l + 1]) && (s[l + 1] == s[r])) {
                    // if need add eleements, add first
                    if (toAdd < addTarget) {
                        //        aaa -> aaBa
                        // index: l r ->    l(r)
                        toAdd++;
                        l = r;
                        // if no need adding(sSize >= 6), then replace elements
                    } else {
                        //        aaa -> aaB
                        // index: l r ->   rl
                        toReplace++;
                        l = r + 1;
                    }
                } else {
                    l++;
                }
            }


        }
        // if sSize <= MAXSTRLEN, there will no need delete
        if (delTarget == 0) {
            return std::max(addTarget + toReplace, needUpper + needLower + needDigit);
        }

        toReplace = 0;
        std::vector<std::unordered_map<int ,int>> modLenCnt(MAXREPLEN);
        // account the number of repetition lenght >= MAXREPLEN
        for (int l = 0, r = 0, len = 0; r <= sSize; r++) {
            if ((r == sSize) || (s[l] != s[r])) {
                if ((len = r - l) > (MAXREPLEN - 1)) {
                    modLenCnt[len % MAXREPLEN][len]++;
                }
                l = r;
            }
        }

        // len % MAXREPLEN = 0, one replacement = one delete, after once replacement (or say delete), it's become to (len % MAXREPLEN = 2)
        // len % MAXREPLEN = 1, one replacement = two delete, after twice replacements (or say delete), it's become to (len % MAXREPLEN = 2)
        // len % MAXREPLEN = 2, one replacement = three delete
        for (int index = 0; index < modLenCnt.size(); index++) {
            for (auto it = modLenCnt[index].begin(); it != modLenCnt[index].end(); it++) {
                // first consider deletion that meets len & MAXREPLEN = 1 repetitions, and then len & MAXREPLEN = 2
                if (index < MAXREPLEN - 1) {
                    int numLetter = index + 1;
                    int dec = std::min(it->second, (delTarget - toDel) / numLetter);
                    toDel += dec * numLetter; it->second -= dec;
                    if (it->first - numLetter >= MAXREPLEN) {
                        // record how many repetitions are tranformed
                        modLenCnt[MAXREPLEN - 1][it->first - numLetter] += dec;
                    }
                }
                toReplace += (it->second) * (it->first / MAXREPLEN);
            }
        }
        int dec = (delTarget - toDel) / MAXREPLEN;
        toReplace -= dec; toDel += dec * MAXREPLEN;
        return delTarget + std::max(toReplace, needUpper + needLower + needDigit);
    }
};
