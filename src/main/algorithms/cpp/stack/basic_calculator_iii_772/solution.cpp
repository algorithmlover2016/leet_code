#include "../../head.h"


class Solution {
public:
    int calculate(std::string const & s) {
        // plagiarizing from https://www.cnblogs.com/grandyang/p/8873471.html
        int const n = s.size();
        long num = 0, curRes = 0, res = 0;
        char op = '+';
        for (int i = 0; i < n; ++i) {
            char c = s[i];
            if (std::isdigit(c)) {
                num = num * 10 + c - '0';
            } else if (c == '(') {
                int j = i, cnt = 0;
                for (; i < n; ++i) {
                    if (s[i] == '(') ++cnt;
                    if (s[i] == ')') --cnt;
                    if (cnt == 0) break;
                }
                num = calculate(s.substr(j + 1, i - j - 1));
            }
            if (c == '+' || c == '-' || c == '*' || c == '/' || i == n - 1) {
                switch (op) {
                    case '+': curRes += num; break;
                    case '-': curRes -= num; break;
                    case '*': curRes *= num; break;
                    case '/': curRes /= num; break;
                }
                if (c == '+' || c == '-' || i == n - 1) {
                    res += curRes;
                    curRes = 0;
                }
                op = c;
                num = 0;
            }
        }
        return res;
    }
};
