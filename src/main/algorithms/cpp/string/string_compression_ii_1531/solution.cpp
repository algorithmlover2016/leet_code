#include "../../head.h"


class SolutionTLE {
public:
    int getLengthOfOptimalCompression(std::string const & s, int k) {
        // plagiarizing from https://leetcode.com/problems/string-compression-ii/discuss/755970/Python-dynamic-programming
        // and https://leetcode.com/problems/string-compression-ii/discuss/755762/C%2B%2B-top-down-dynamic-programming-with-explanation

        std::vector<std::vector<std::vector<std::vector<int>>>> dpMemo(MAX_STR_LEN, /*cur index*/
                std::vector<std::vector<std::vector<int>>>(LETTER_CNTS, /*last character store with int*/
                    std::vector<std::vector<int>>(MAX_STR_LEN, /*the number of the contineous last character */
                        std::vector<int>(MAX_STR_LEN, -1)))); // the k
        return dfs(s /*input str*/, 0 /*cur idx*/, 26 /*last character*/, 0 /*the number of the last character*/, k, dpMemo);
    }
    int dfs(std::string const & str, int idx, int lastLetter, int lastLetterCnt, int left,
            std::vector<std::vector<std::vector<std::vector<int>>>> & dpMemo) {
        int const strSize = str.size();
        if (0 > left) {
            return strSize;
        }
        if (left >= strSize || (strSize - idx <= left)) {
            return 0;
        }

        if (-1 != dpMemo[idx][lastLetter][lastLetterCnt][left]) {
            return dpMemo[idx][lastLetter][lastLetterCnt][left];
        }

        int curLetter = str[idx] - OFFSET;
#ifdef NORMAL_WRITE_WAYS
        int ans = dfs(str, idx + 1, lastLetter, lastLetterCnt, left - 1, dpMemo); // delete the cur letter
        if (curLetter == lastLetter) {
            int inc = ((1 == lastLetterCnt) || (9 == lastLetterCnt) || (99 == lastLetterCnt)) ? 1 : 0;
            ans = std::min(ans, inc + dfs(str, idx + 1, lastLetter, lastLetterCnt + 1, left, dpMemo));
        } else {
            ans = std::min(ans, 1 + dfs(str, idx + 1, curLetter, 1, left, dpMemo));
        }
        return dpMemo[idx][lastLetter][lastLetterCnt][left] = ans;
#else
        if (curLetter == lastLetter) {
            int inc = ((1 == lastLetterCnt) || (9 == lastLetterCnt) || (99 == lastLetterCnt)) ? 1 : 0;
            return dpMemo[idx][lastLetter][lastLetterCnt][left] =
                inc + dfs(str, idx + 1, lastLetter, lastLetterCnt + 1, left, dpMemo);
        } else {
            int keepCurLetter = 1 + dfs(str, idx + 1, curLetter, 1, left, dpMemo);
            int removeCurLetter = dfs(str, idx + 1, lastLetter, lastLetterCnt, left - 1, dpMemo);
            return dpMemo[idx][lastLetter][lastLetterCnt][left] =
                std::min(keepCurLetter, removeCurLetter);
        }
#endif
    }
private:
    static int const LETTER_CNTS = 27;
    static int const MAX_STR_LEN = 127; // no more than 100 according to the constraints of the problem;
    static char const OFFSET = 'a';
};

class Solution {
public:
    int getLengthOfOptimalCompression(std::string const & s, int k) {
        // plagiarizing from https://leetcode.com/problems/string-compression-ii/discuss/756022/C%2B%2B-Top-Down-DP-with-explanation-64ms-short-and-clear
        std::vector<std::vector<int>> dpMemo(MAX_STR_LEN, std::vector<int>(MAX_STR_LEN, -1));
        return dfs(s, 0, k, dpMemo);
    }
private:
    int cntDigitsLen(int num) {
        if (1 == num) {
            return 0;
        }
        if (10 > num) {
            return 1;
        }
        if (100 > num) {
            return 2;
        }
        return 3;
    }

    int dfs(std::string const & s, int start, int left, std::vector<std::vector<int>> & dpMemo) {
        int const sSize = s.size();
        if (0 > left) {
            return MAX_STR_LEN;
        }
        if (left >= sSize || sSize - start <= left) {
            return 0;
        }
        if (-1 != dpMemo[start][left]) {
            return dpMemo[start][left];
        }
        int ans = MAX_STR_LEN;
        std::vector<int> cnts(LETTER_CNTS, 0);
        for (int idx = start, mostSameCnt = 0; idx < sSize; idx++) {
            mostSameCnt = std::max(mostSameCnt, ++cnts[s[idx] - OFFSET]);
            ans = std::min(ans,
                    1 /*the length of letter*/ + cntDigitsLen(mostSameCnt) /*the length number of the letter*/ +
                    dfs(s, idx + 1, left - (idx - start + 1 - mostSameCnt), dpMemo));
        }
        return dpMemo[start][left] = ans;
    }
private:
    static int const LETTER_CNTS = 26;
    static int const MAX_STR_LEN = 127; // no more than 100 according to the constraints of the problem;
    static char const OFFSET = 'a';
};

static int const LETTER_CNTS = 27;
static int const MAX_STR_LEN = 127; // no more than 100 according to the constraints of the problem;
static char const OFFSET = 'a';

static int dpMemo[MAX_STR_LEN][LETTER_CNTS][MAX_STR_LEN][MAX_STR_LEN];

#define NORMAL_WRITE_WAYS
class SolutionAlmostTLE {
    public:
    int getLengthOfOptimalCompression(std::string const & s, int k) {
        // plagiarizing from https://leetcode.com/problems/string-compression-ii/discuss/755970/Python-dynamic-programming
        // and https://leetcode.com/problems/string-compression-ii/discuss/755762/C%2B%2B-top-down-dynamic-programming-with-explanation
        std::memset(dpMemo, -1, sizeof(dpMemo));

        return dfs(s /*input str*/, 0 /*cur idx*/, 26 /*last character*/, 0 /*the number of the last character*/, k);
    }
    int dfs(std::string const & str, int idx, int lastLetter, int lastLetterCnt, int left) {
        int const strSize = str.size();
        if (0 > left) {
            return strSize;
        }
        if (left >= strSize || (strSize - idx <= left)) {
            return 0;
        }

        int & val = dpMemo[idx][lastLetter][lastLetterCnt][left];
        if (-1 != val) {
            return val;
        }

        int curLetter = str[idx] - OFFSET;
        #ifdef NORMAL_WRITE_WAYS
        int ans = dfs(str, idx + 1, lastLetter, lastLetterCnt, left - 1); // delete the cur letter
        if (curLetter == lastLetter) {
            int inc = ((1 == lastLetterCnt) || (9 == lastLetterCnt) || (99 == lastLetterCnt)) ? 1 : 0;
            ans = std::min(ans, inc + dfs(str, idx + 1, lastLetter, lastLetterCnt + 1, left));
        } else {
            ans = std::min(ans, 1 + dfs(str, idx + 1, curLetter, 1, left));
        }
        return val = ans;
        #else
        if (curLetter == lastLetter) {
            int inc = ((1 == lastLetterCnt) || (9 == lastLetterCnt) || (99 == lastLetterCnt)) ? 1 : 0;
            return val = inc + dfs(str, idx + 1, lastLetter, lastLetterCnt + 1, left);
        } else {
            int keepCurLetter = 1 + dfs(str, idx + 1, curLetter, 1, left);
            int removeCurLetter = dfs(str, idx + 1, lastLetter, lastLetterCnt, left - 1);
            return val = std::min(keepCurLetter, removeCurLetter);
        }
        #endif
    }
};
