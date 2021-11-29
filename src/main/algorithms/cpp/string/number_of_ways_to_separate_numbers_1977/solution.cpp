#include "../../head.h"


// #define DEBUG
class SolutionTLE {
public:
    int numberOfCombinations(std::string const & num) {
        int ans = 0;
        if (num.empty() || '0' == num[0]) {
            return ans;
        }
        backTracking(num, 0, 1, "0", ans);
        return ans;
    }
private:
    void backTracking(std::string const & num, int idx, int len, std::string const & lastNum, int & ans) {
        // idea got by myself.
        int const numSize = num.size();
        if (idx == numSize) {
            // means we take all the comnination belonging to num;
            ans++;
            return;
        }

        // first, we need try to sub cur num;
        std::string curVal = num.substr(idx, len);
        // which means we can not take len characters starting from idx because idx + len > numSize
        if (curVal.size() < lastNum.size()) {
            return;
        }
        // take the same length of lastNum, and curVal is smaller, so we need add one for length to make curVal bigger
        if (0 > curVal.compare(lastNum)) {
            len++;
        }

        #ifdef DEBUG
        std::cout << lastNum << "\n";
        #endif

        for (; len <= numSize - idx; len++) {
            // we take the cur substring (starting from idx and take the length of len, however we can not make the next number starting from zero.)
            // so we need take all the leading zero for the next number
            while (idx + len < numSize && '0' == num[idx + len]) {
                len++;
            }
            curVal = num.substr(idx, len);
            #ifdef DEBUG
            std::cout << "curVal: " << curVal << "\n";
            #endif
            backTracking(num, idx + len, len, curVal, ans);
        }
    }

private:
    static int const MOD = 1e9 + 7;
};

// #define DEBUG
// #define USE_MORE_TIME_WITHOUT_LCP

class Solution {
public:
    int numberOfCombinations(std::string const & num) {
        // plagiarizing from https://leetcode.com/problems/number-of-ways-to-separate-numbers/discuss/1436038/O(n2)-time-or-O(n)-memory
        int ans = 0;
        if (num.empty() || '0' == num[0]) {
            return ans;
        }

        #ifdef USE_MORE_TIME_WITHOUT_LCP
        return ans = dpON3ON(num);
        #else
        return ans = dpON2ON(num);
        #endif
    }
private:
    int dpON3ON(std::string const & num) {
        std::vector<int> nextDp(MAX_LENGTH, 0), curDp(MAX_LENGTH, 0);
        int const numLen = num.size();
        for (int subLen = 1; subLen < numLen + 1; subLen++) {
            curDp[0] = 1;
            for (int idx = 0; idx < numLen; idx++) {
                int idxLen = idx + 1;
                nextDp[idxLen] = curDp[idxLen];
                if (idxLen >= subLen /* can take subLen length letters */&& ZERO_LETTER != num[idxLen - subLen] /* not start from zero*/) {
                    // we can take subLen letters as the current number
                    if (idxLen >= 2 * subLen && num.compare(idxLen - 2 * subLen, subLen, num, idxLen - subLen, subLen) <= STR_COMPARE_NO_LARGERTHAN) {
                        #ifdef DEBUG
                        // please refer to https://www.cplusplus.com/reference/string/string/compare/
                        std::cout << "compare result: " << num.compare(idxLen - 2 * subLen, subLen, num, idxLen - subLen, subLen) << "\n";
                        #endif
                        
                        // we can take subLen letters in current  idx and idx + 1 - subLen index separately
                        nextDp[idxLen] = (nextDp[idxLen] + nextDp[idxLen - subLen]) % MOD;
                    } else {
                        nextDp[idxLen] = (nextDp[idxLen] + curDp[idxLen - subLen]) % MOD;
                    }
                }
            }
            std::swap(curDp, nextDp);
        }
        return curDp[numLen];
    }

    int dpON2ON(std::string const & num) {
        std::vector<int> nextDp(MAX_LENGTH, 0), curDp(MAX_LENGTH, 0), lcpPrefix(MAX_LENGTH, 0);

        int const numLen = num.size();
        for (int subLen = 1; subLen < numLen + 1; subLen++) {
            curDp[0] = 1;
            for (int idx = numLen; idx > subLen; idx--) {
                // lcpPrefix[idx] represents the common length from idx-th to the end,
                // which means the substr from idx-th(included) to (idx-th + lcpPrefix[idx-th])(excluded) is equal to
                // from (idx-th - subLen)(included) to (idx-th - subLen + lcpPrefix[idx-th])(excluded)
                lcpPrefix[idx - 1] = (num[idx - 1 - subLen] == num[idx - 1] ? lcpPrefix[idx] + 1 : 0);
            }
            for (int idx = 0; idx < numLen; idx++) {
                int idxLen = idx + 1;
                nextDp[idxLen] = curDp[idxLen];
                if (idxLen >= subLen && (ZERO_LETTER != num[idxLen - subLen])) {
                    if (idxLen >= (subLen * 2) &&
                    (lcpPrefix[idxLen - subLen] >=subLen /*it means the two substr are equal*/ || num[idxLen - subLen + lcpPrefix[idxLen - subLen]] > num[idxLen - 2 * subLen + lcpPrefix[idxLen - subLen]] )) {
                        nextDp[idxLen] = (nextDp[idxLen] + nextDp[idxLen - subLen]) % MOD;
                    } else {
                        nextDp[idxLen] = (nextDp[idxLen] + curDp[idxLen - subLen]) % MOD;
                    }
                }
            }
            std::swap(curDp, nextDp);
        }
        return curDp[numLen];
    }

private:
    static int const MOD = 1e9 + 7;
    static int const MAX_LENGTH = 3500 + 1;
    static char const ZERO_LETTER = '0';
    static int const STR_COMPARE_NO_LARGERTHAN = 0;
};