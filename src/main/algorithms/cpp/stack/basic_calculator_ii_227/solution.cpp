#include "../../head.h"


class Solution {
public:
    int calculate(std::string const & s) {
        if (s.empty()) {
            return 0;
        }

        std::string ss(s + "+");

        long num = 0;
        long res = 0;
        int sign = 1;

        std::stack<long> multiply;
        std::stack<int> mdFlags;

        for (char c : ss) {
            if (' ' == c) {
                continue;
            } else if (std::isdigit(c)) {
                num = num * 10 + c - '0';
            } else {
                if ('+' == c || '-' == c) {
                    if (mdFlags.size()) {
                        while (mdFlags.size()) {
                            long numTop = multiply.top();
                            long flagTop = mdFlags.top();
                            if (flagTop == 2) {
                                num = numTop * num;
                            } else if (flagTop == 3) {
                                num = numTop / num;
                            } else {
                                num = numTop + flagTop * num;
                            }
                            mdFlags.pop(); multiply.pop();
                        }
                        res = num;
                    } else {
                        res += num * sign;
                    }
                    sign = '+' == c ? 1 : -1;
                } else if ('*' == c || '/' == c) {
                    if (mdFlags.size() && mdFlags.top() > 1) {
                        num = mdFlags.top() == 2 ? multiply.top() * num : multiply.top() / num;
                        mdFlags.pop(); multiply.pop();
                    }
                    if (sign < 2) {
                        mdFlags.emplace(sign);
                        multiply.emplace(res);
                    }
                    sign = '*' == c ? 2 : 3;
                    mdFlags.emplace(sign);
                    multiply.emplace(num);
                }
                
                num = 0;
            }
        }
        return static_cast<int>(res);
    }
};

static auto fastIo = []() {std::ios::sync_with_stdio(false); cin.tie(nullptr); std::cout.tie(nullptr); return 0; }();

class SolutionBetterRunTime {
private:
    class State {
        private:
            int left = 0;
            char left_oper = 0;
            int middle = 0;
            char right_oper = 0;
            int right = 0;

            int Evaluate(int left, char operation, int right) {
                switch(operation) {
                    case '+': return left + right;
                    case '-': return left - right;
                    case '*': return left * right;
                    case '/': return left / right;
                    default: return right;
                }
            }
        public:
            void Next(char c) {
                if (std::isdigit(c)) {
                    right = 10 * right + (c-'0');
                } else {
                    switch(c) {
                        case ' ':
                            break;
                        case '*':
                        case '/':
                            if (right_oper == '*' || right_oper == '/') {
                                middle = Evaluate(middle, right_oper, right);
                                right_oper = c;
                                right = 0;
                            } else {
                                left = middle;
                                left_oper = right_oper;
                                middle = right;
                                right_oper = c;
                                right = 0;
                            }
                            break;
                        default:
                            middle = Evaluate(left, left_oper, Evaluate(middle, right_oper, right));
                            left = 0;
                            left_oper = 0;
                            right_oper = c;
                            right = 0;
                    }
                }
            }

            int Result() {
                Next('+');
                return middle;
            }
    };

public:
    int calculate(std::string const & s) {
        State state;
        for (auto c: s) {
            state.Next(c);
        }
        return state.Result();
    }
};
