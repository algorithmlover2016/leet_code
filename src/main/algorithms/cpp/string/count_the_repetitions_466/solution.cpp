#include "../../head.h"



class SolutionWrongAns {
public:
    // error when input is
    /*
       "aaa"
       3
       "aa"
       1
     */
    int getMaxRepetitions(std::string const & s1, int n1, std::string const & s2, int n2) {
        int const s2Size = s2.size();
        if (0 == n2) {
            return s1.size() * n1;
        }
        std::string S1;
        int needed = 0;
        while (++needed <= n1) {
            S1 += s1;
            if (s2Size == lcs(S1, s2)) {
                break;
            }
        }
        if (needed > n1) {
            return -1;
        }
        return n1 / (needed * n2);
    }
    int lcs(std::string const & s1, std::string const & s2) {
        int const s1Size = s1.size();
        int const s2Size = s2.size();
        std::vector<std::vector<int>> dpMemo(s1Size + 1, std::vector<int>(s2Size + 1, 0));
        for (int idx1 = 0; idx1 < s1Size; idx1++) {
            for (int idx2 = 0; idx2 < s2Size; idx2++) {
                if (s1[idx1] == s2[idx2]) {
                    dpMemo[idx1 + 1][idx2 + 1] = 1 + dpMemo[idx1][idx2];
                } else {
                    dpMemo[idx1 + 1][idx2 + 1] = std::max(dpMemo[idx1 + 1][idx2], dpMemo[idx1][idx2 + 1]);
                }
            }
        }
        return dpMemo[s1Size][s2Size];
    }
};

// #define ONLY_EXCLUDE_PATTERN
class Solution {
public:
    int getMaxRepetitions(std::string const & s1, int n1, std::string const & s2, int n2) {
        // plagiarizing idea from https://leetcode.com/problems/count-the-repetitions/discuss/95398/C%2B%2B-solution-inspired-by-%4070664914-with-organized-explanation
        // and https://leetcode.com/problems/count-the-repetitions/discuss/95401/Ugly-Java-brute-force-solution-but-accepted.-1088ms.
        // the upper solution can only solve the condition that n * s1 have m * s2.
        // and the left character can't be used again
        if (0 == n2) {
            return -1;
        }

        int const s1Size = s1.size();
        int const s2Size = s2.size();

        std::unordered_map<int, int> nextIdxToNums; // after each traversal for s1, the next idx;
        std::unordered_map<int, int> numsToCnts;
        nextIdxToNums[0] = 0; // the index of s2 need compared with s1
        numsToCnts[0] = 0; // when using keys s1, how many s2 can we get
        int idx2 = 0;
        int cnt = 0;
        for (int num = 1; num <= n1; num++) {
            for (int idx1 = 0; idx1 < s1Size; idx1++) {
                if (s1[idx1] == s2[idx2]) {
                    idx2++;
                    if (idx2 == s2Size) {
                        idx2 = 0;
                        cnt++;
                    }
                }
            }
            if (nextIdxToNums.find(idx2) != nextIdxToNums.end()) {
                int preNum = nextIdxToNums[idx2];
                int preCnt = numsToCnts[preNum];
                int pattern = (n1 - preNum) / (num - preNum) * (cnt - preCnt);
                #ifdef ONLY_EXCLUDE_PATTERN
                int excludedPattern = numsToCnts[preNum + (n1 - preNum) % (num - preNum)];
                return (pattern + excludedPattern) / n2;
                #else
                int suffix = numsToCnts[preNum + (n1 - preNum) % (num - preNum)] - preCnt;
                // which means preCnt + suffix = numsToCnts[preNum + (n1 - num) % (num - preNum)];
                return (preCnt + pattern + suffix) / n2;
                #endif
            }
            nextIdxToNums[idx2] = num;
            numsToCnts[num] = cnt;
        }
        return numsToCnts[n1] / n2;;
    }
};

class SolutionBruteFs {
public:
    int getMaxRepetitions(std::string const & s1, int n1, std::string const & s2, int n2) {
        // plagiarizing idea from https://leetcode.com/problems/count-the-repetitions/discuss/95398/C%2B%2B-solution-inspired-by-%4070664914-with-organized-explanation
        // and https://leetcode.com/problems/count-the-repetitions/discuss/95401/Ugly-Java-brute-force-solution-but-accepted.-1088ms.
        // the upper solution can only solve the condition that n * s1 have m * s2.
        // and the left character can't be used again
        if (0 == n2) {
            return -1;
        }

        int const s1Size = s1.size();
        int const s2Size = s2.size();

        int idx2 = 0;
        int cnt = 0;
        for (int num = 1; num <= n1; num++) {
            for (int idx1 = 0; idx1 < s1Size; idx1++) {
                if (s1[idx1] == s2[idx2]) {
                    idx2++;
                    if (idx2 == s2Size) {
                        idx2 = 0;
                        cnt++;
                    }
                }
            }
        }
        return cnt / n2;;
    }
};
