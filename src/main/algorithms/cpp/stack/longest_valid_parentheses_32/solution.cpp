#include "../../head.h"


// #define DEBUG
class Solution {
public:
    int longestValidParentheses(std::string const & s) {
        // plagiarizing idea from https://leetcode.com/problems/longest-valid-parentheses/discuss/14126/My-O(n)-solution-using-a-stack
        int const sSize = s.size();
        if (JUST_RETURN_ZERO >= sSize) {
            return 0;
        }
        std::stack<int> noPairs;
        for (int idx = 0; idx < sSize; idx++) {
            if (LEFT_PARENTHESE == s[idx]) {
                #ifdef DEBUG
                std::cout << "left: " << idx << "\n";
                #endif
                noPairs.emplace(idx);
            } else {
                if (!noPairs.empty() && LEFT_PARENTHESE == s[noPairs.top()]) {  // can make a pair
                    noPairs.pop();
                } else {
                    #ifdef DEBUG
                    std::cout << "right: " << idx << "\n";
                    #endif
                    noPairs.emplace(idx);
                }
            }
        }
        if (noPairs.empty()) { // all are made pairs
            return sSize;
        }
        int ans = 0;

        int right = sSize; // can't be paired idx

        while (!noPairs.empty()) {
            int left = noPairs.top(); noPairs.pop();
            ans = std::max(ans, right - left - 1); // (left, right), exclude both left and right
            right = left;
        }
        
        return std::max(ans, right);
    }
    private:
    static int const JUST_RETURN_ZERO = 1;
    static char const LEFT_PARENTHESE = '(';
    static char const RIGHT_PARENTHESE = ')';
};

class SolutionWrong {
public:
    int longestValidParentheses(std::string const & s) {
        int pairCnt = 0;
        int leftParentheses = 0;
        for (int index = 0; index < s.size(); index++) {
            if ('(' == s[index]) {
                leftParentheses++;
            } else if (0 < leftParentheses) {
                leftParentheses--;
                pairCnt += 2;
            }

        }
        return pairCnt;

    }
};

class SolutionWrong {
public:
    int longestValidParentheses(std::string const & s) {
        int sSize = s.size();
        if (JUST_RETURNZERO >= sSize) {
            return 0;
        }
        int leftParentheses = 0;
        int needAddParentheses = 0;
        for (int idx = 0; idx < sSize; idx++) {
            if ('(' == s[idx]) {
                leftParentheses++;
            } else {
                if (leftParentheses > 0) {
                    leftParentheses--;
                } else {
                    needAddParentheses++;
                }
            }
        }

        return sSize - needAddParentheses - leftParentheses;


    }
    private:
    static int const JUST_RETURNZERO = 1;
};

class SolutionWrong {
public:
    int longestValidParentheses(std::string const & s) {
        // leftParentheses > 0 and end
        int sSize = s.size();
        if (JUST_RETURNZERO >= sSize) {
            return 0;
        }
        int leftParentheses = 0;
        int ans = 0;
        int start = 0;
        for (int idx = 0; idx < sSize; idx++) {
            if ('(' == s[idx]) {
                if (0 >= leftParentheses++) {
                    start = idx;
                }
            } else {
                leftParentheses--;
                if (0 == leftParentheses) {
                    ans = std::max(ans, idx - start + 1);
                }
            }
        }
        
        return ans;
    }
private:
    static int const JUST_RETURNZERO = 1;
};

class SolutionWrong {
public:
    int longestValidParentheses(std::string const & s) {
        // "(()(((()"
        int sSize = s.size();
        if (JUST_RETURNZERO >= sSize) {
            return 0;
        }
        int ans = 0;
        int leftParentheses = 0;
        int cnt = 0;
        int preleftParentheses = 0;
        int preCnt = 0;
        for (int idx = 0; idx < sSize; idx++) {
            if ('(' == s[idx]) {
                if (0 >= leftParentheses) {
                    preleftParentheses = leftParentheses;
                    preCnt = cnt;
                    leftParentheses = 0;
                    cnt = 0;
                }
                leftParentheses++;
            } else {
                leftParentheses--;
                if (0 <= leftParentheses) {
                    cnt += 2;
                    if (0 == leftParentheses && 0 == preleftParentheses) {
                        cnt += preCnt;
                    }
                    ans = std::max(ans, cnt);
                }
            }
        }

        return ans;
    }
private:
    static int const JUST_RETURNZERO = 1;
};

class Solution {
public:
    int longestValidParentheses(std::string const & s) {
        // plagiarizing idea from https://leetcode.com/problems/longest-valid-parentheses/discuss/14126/My-O(n)-solution-using-a-stack
        int const sSize = s.size();
        if (JUST_RETURN_ZERO >= sSize) {
            return 0;
        }
        std::stack<int> noPairs;
        for (int idx = 0; idx < sSize; idx++) {
            if (LEFT_PARENTHESE == s[idx]) {
                noPairs.emplace(idx);
            } else {
                if (!noPairs.empty() && LEFT_PARENTHESE == noPairs.top()) {  // can make a pair
                    noPairs.pop();
                } else {
                    noPairs.emplace(idx);
                }
            }
        }
        if (noPairs.empty()) { // all are made pairs
            return sSize;
        }
        int ans = 0;

        int right = n - 1;

        while (!noPairs.empty()) {
            int left = noPairs.top(); noPairs.pop();
            ans = std::max(ans, right - left);
            right = left;
        }
        return ans;
    }
private:
    static int const JUST_RETURNZERO = 1;
    static char const LEFT_PARENTHESE = '(';
    static char const RIGHT_PARENTHESE = ')';
};
