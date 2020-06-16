#include "../../head.h"


class Solution {
public:
    int calculate(std::string const & s) {
        if (s.empty()) {
            return 0;
        }

        long num = 0;
        long res = 0;
        int sign = 1;
        std::stack<long> nums;
        std::stack<int> flags;

        for (char c : s) {
            if (' ' == c) {
                continue;
            } else if (std::isdigit(c)) {
                num = num * 10 + c - '0';
            } else {
                num *= sign;
                res += num;
                num = 0;
                if ('+' == c) {
                    sign = 1;
                } else if ('-' == c) {
                    sign = -1;
                } else if ('(' == c) {
                    nums.emplace(res);
                    flags.emplace(sign);
                    res = 0;
                    sign = 1;
                } else if (')' == c) {
                    res = res * flags.top() + nums.top();
                    flags.pop(); nums.pop();
                }
            }
        }
        if (num > 0) {
            res += num * sign;
        }
        return static_cast<int>(res);

    }
};

static int _ = []{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;
}();
class SolutionOneStack {
public:
    int calculate(std::string const & s) {
        long num=0, sign=1, result=0;
        std::stack<long> nums;
        for (auto &c : s) {
            if (std::isdigit(c)) {
                num = num*10 + (c-'0');
            } else {
                result += sign * num;
                num = 0;
                if (c == '+') {
                    sign = 1;
                } else if (c == '-') {
                    sign = -1;
                } else if (c == '(') {
                    nums.push(result);
                    nums.push(sign);
                    result = 0;
                    sign = 1;
                } else if (c == ')') {
                    result = nums.top() * result;
                    nums.pop();
                    result += nums.top();
                    nums.pop();
                }
            }
        }
        return result + sign*num;
    }
};
