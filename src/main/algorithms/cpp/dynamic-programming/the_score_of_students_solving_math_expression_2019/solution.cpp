#include <algorithm>
#include "../../head.h"

class Solution {
public:
    int scoreOfStudents(std::string const & s, std::vector<int> const & answers) {
        // plagiarizing from https://leetcode.com/problems/the-score-of-students-solving-math-expression/discuss/1486306/PythonJava-Explanation-with-pictures-DP
        // and https://leetcode.com/problems/the-score-of-students-solving-math-expression/discuss/1486991/312.-Burst-Balloons
        if (s.empty()) {
            return 0;
        }
        int sSize = s.size();
        if (ONLY_ONE_SIZE == sSize) {
            return s[0] - DIGITAL_BASE_OFFSET;
        }
        int numsSize = (sSize / 2) + 1;
        std::vector<std::vector<std::set<int>>> dpMemo(numsSize, std::vector<std::set<int>>(numsSize, std::set<int>()));
        for (int numIdx = 0; numIdx < numsSize; numIdx++) {
            // the diagonal values should be set as the original value
            dpMemo[numIdx][numIdx].insert(s[numIdx * 2] - DIGITAL_BASE_OFFSET);
        }

        for (int diff = 1; diff < numsSize; diff++) {
            for (int start = 0; start < numsSize - diff; start++) {
                int end = start + diff;
                for (int internal = 2 * start + 1; internal < 2 * end; internal += 2) {
                    int left = internal / 2;
                    int right = left + 1; // int right = internal / 2 + 1;
                    if (ADD_OP == s[internal]) {
                        for (int leftNum : dpMemo[start][left]) {
                            for (int rightNum : dpMemo[right][end]) {
                                int curAns = leftNum + rightNum;
                                if (MAX_ANSWER >= curAns) {
                                    dpMemo[start][end].insert(curAns);
                                }
                            }
                        }
                    } else { // '*' == s[internal]
                        for (int leftNum : dpMemo[start][left]) {
                            for (int rightNum : dpMemo[right][end]) {
                                int curAns = leftNum * rightNum;
                                if (MAX_ANSWER >= curAns) {
                                    dpMemo[start][end].insert(curAns);
                                }
                            }
                        }
                    }
                }
            }
        }
        std::unordered_map<int, int> cntsAnswers;
        for (int answer : answers) {
            cntsAnswers[answer]++;
        }
        int correctAns = correct(s);
        int ans = 0;
        for (int eval : dpMemo[0].back()) {
            if (eval == correctAns) {
                ans += 5 * cntsAnswers[eval];
            } else {
                ans += 2 * cntsAnswers[eval];;
            }
        }
        return ans;
    }
private:
    int correct(std::string const & s) {
        // refence to https://leetcode.com/problems/the-score-of-students-solving-math-expression/discuss/1486991/312.-Burst-Balloons
        // according to the description, s.size() must be odd and the operator idx must be odd(index starts from zero)
        if (s.empty()) {
            return 0;
        }
        int sSize = s.size();
        if (ONLY_ONE_SIZE == sSize) {
            return s[0] - DIGITAL_BASE_OFFSET;
        }
        int ans = 0;
        for (int opIdx = 1, numIdx = 0; opIdx <= sSize; opIdx += 2) {
            if (opIdx == sSize /*it means touching all the elements */|| ADD_OP == s[opIdx] /*encouter a plus operator */) {
                int multiply = 1;
                for (; numIdx < opIdx; numIdx += 2) {
                    multiply *= s[numIdx] - DIGITAL_BASE_OFFSET;
                }
                ans += multiply;
            }
        }
        return ans;
    }
private:
    static int const ONLY_ONE_SIZE = 1;
    static char const ADD_OP = '+';
    static char const DIGITAL_BASE_OFFSET = '0';
    static int const MAX_ANSWER = 1000;
};

class Solution {
public:
    int scoreOfStudents(const std::string & s, std::vector<int> const & answers) {
        int term = 0, factor = s[0] - '0';
        for (int i = 1; i < s.size();) {
            if (s[i++] == '*') {
                factor *= s[i++] - '0';
            } else {
                term += factor, factor = s[i++] - '0';
            }
        }
        term += factor;
        
        std::vector<int> dp[16][16];
        for (int i = 0; i < s.size(); i += 2) {
            dp[0][i/2].push_back(s[i] - '0');
        }
        for (int sz = 1, smax = (s.size() + 1) / 2; sz < smax; ++sz) {
            for (int i = 0; i < smax - sz; ++i) {
                bool res[1001] {};
                for (int k = 0; k < sz; ++k) {
                    const auto & left = dp[k][i];
                    const auto & right = dp[sz - k - 1][i + k + 1];
                    char op = s[(i + k) * 2 + 1];
                    for (int l : left) {
                        for (int r : right) {
                            int v = op == '+' ? l + r : l * r;
                            if (v <= 1000) {
                                res[v] = 1;
                            }
                        }
                    }
                }
                for (int v = 0; v <= 1000; ++v) {
                    if (res[v]) {
                        dp[sz][i].push_back(v);
                    }
                }
            }
        }

        int res[1001] {}, cnt = 0;
        for (int v : dp[s.size() / 2][0]) {
            res[v] = 2;
        }
        res[term] = 5;
        for (int a : answers) {
            cnt += res[a];
        }
        return cnt;
    }
};

class Solution {
private:
   std::unordered_set<int> memo[32][32];
private:
    void dfs(std::string const & s, int st, int fin) {
        if (memo[st][fin].empty()) {
            if (fin - st == 1) {
                memo[st][fin].insert(s[st] - '0');
                return;
            }
            for (int i = st + 1; i < fin; i += 2) {
                dfs(s, st, i);
                dfs(s, i + 1, fin);
                for (int n1 : memo[st][i]) {
                    for (int n2 : memo[i + 1][fin]) {
                        int n = s[i] == '*' ? n1 * n2 : n1 + n2;
                        if (n <= 1000) {
                            memo[st][fin].insert(n);
                        }
                    }
                }
            }
        }
    }
public:
    int scoreOfStudents(std::string const & s, std::vector<int> const & answers) {
        // plagiarizing from https://leetcode.com/problems/the-score-of-students-solving-math-expression/discuss/1486991/312.-Burst-Balloons
        int correct = 0;
        for (int i = 1, j = 0; i <= s.size(); i += 2) {
            if (i == s.size() || s[i] == '+') {
                int mul = 1;
                for (; j < i; j += 2) {
                    mul *= s[j] - '0';
                }
                correct += mul;
            }
        }
        dfs(s, 0, s.size());
        return std::accumulate(std::cbegin(answers), std::cend(answers), 0, [&](int sum, int ans) {
            return sum + (ans == correct ? 5 : memo[0][s.size()].count(ans) ? 2 : 0);
        });
    } 
};