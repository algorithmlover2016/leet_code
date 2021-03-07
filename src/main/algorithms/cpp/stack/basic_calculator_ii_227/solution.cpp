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

// #define SPLIT_PLUS_MINUS_WITH_MULTIPLY_DIVIDE
class Solution {
public:
    int calculate(std::string const & ss) {
        // plagiarizing idea from https://youtu.be/lNSTvbVRpIA
        std::string s(ss + '+');
        std::vector<long> nums;
        std::vector<char> ops;
        int const sSize = s.size();
        long num = 0;
        for (int idx = 0; idx < sSize; idx++) {
            char const c = s[idx];
            if (SPACE == c) {
                continue;
            }
            if (std::isdigit(c)) {
                num  = num * 10 + c - '0';
            } else {
                #ifdef SPLIT_PLUS_MINUS_WITH_MULTIPLY_DIVIDE
                if (opPriority(c) < 2) {
                    while (!nums.empty()) {
                        long num1 = nums.back();
                        num = evaluate(num1, num, ops.back());
                        nums.pop_back(); ops.pop_back();
                    }
                    nums.emplace_back(num);
                    ops.emplace_back(c);
                } else {
                    while (!ops.empty() && opPriority(ops.back()) >= opPriority(c)) {
                        long num1 = nums.back();
                        num = evaluate(num1, num, ops.back());
                        nums.pop_back(); ops.pop_back();
                    }
                    nums.emplace_back(num);
                    ops.emplace_back(c);
                }
                #else
                    while (!ops.empty() && opPriority(ops.back()) >= opPriority(c)) {
                        long num1 = nums.back();
                        num = evaluate(num1, num, ops.back());
                        nums.pop_back(); ops.pop_back();
                    }
                    nums.emplace_back(num);
                    ops.emplace_back(c);
                #endif

                num = 0;
            }
        }
        return nums.back();
    }
private:
    int opPriority(char const op) {
        int ans = 0;
        switch (op) {
            case MINUS_OP:
            case PLUS_OP:
                ans = 1;break;
            case MULTIPLY_OP:
            case DIVIDE_OP:
                ans = 2;break;
            default:
                ans = 0;break;
        }
        return ans;
    }
    long evaluate(int num1, int num2, char const op) {
        int ans = 0;
        switch (op) {
            case MINUS_OP: ans = num1 - num2; break;
            case PLUS_OP: ans = num1 + num2; break;
            case MULTIPLY_OP: ans = num1 * num2; break;
            case DIVIDE_OP: ans = num1 / num2; break;
            default: ans = 0;break;
        }
        return ans;

    }
private:
    static char const MINUS_OP = '-';
    static char const PLUS_OP = '+';
    static char const MULTIPLY_OP = '*';
    static char const DIVIDE_OP = '/';
    static char const SPACE = ' ';
};

// #define SPLIT_PLUS_MINUS_WITH_MULTIPLY_DIVIDE
class Solution {
public:
    int calculate(std::string const & s) {
        // plagiarizing idea from https://youtu.be/lNSTvbVRpIA
        std::vector<long> nums;
        std::vector<char> ops;
        int const sSize = s.size();
        long num = 0;
        for (int idx = 0; idx <= sSize; idx++) {
            char c = '+';
            if (idx < sSize) {
                c = s[idx];
            }

            if (SPACE == c) {
                continue;
            }
            if (std::isdigit(c)) {
                num  = num * 10 + c - '0';
            } else {
                #ifdef SPLIT_PLUS_MINUS_WITH_MULTIPLY_DIVIDE
                if (opPriority(c) < 2) {
                    while (!nums.empty()) {
                        long num1 = nums.back();
                        num = evaluate(num1, num, ops.back());
                        nums.pop_back(); ops.pop_back();
                    }
                    nums.emplace_back(num);
                    ops.emplace_back(c);
                } else {
                    while (!ops.empty() && opPriority(ops.back()) >= opPriority(c)) {
                        long num1 = nums.back();
                        num = evaluate(num1, num, ops.back());
                        nums.pop_back(); ops.pop_back();
                    }
                    nums.emplace_back(num);
                    ops.emplace_back(c);
                }
                #else
                    while (!ops.empty() && opPriority(ops.back()) >= opPriority(c)) {
                        long num1 = nums.back();
                        num = evaluate(num1, num, ops.back());
                        nums.pop_back(); ops.pop_back();
                    }
                    nums.emplace_back(num);
                    ops.emplace_back(c);
                #endif

                num = 0;
            }
        }
        return nums.back();
    }
private:
    int opPriority(char const op) {
        int ans = 0;
        switch (op) {
            case MINUS_OP:
            case PLUS_OP:
                ans = 1;break;
            case MULTIPLY_OP:
            case DIVIDE_OP:
                ans = 2;break;
            default:
                ans = 0;break;
        }
        return ans;
    }
    long evaluate(int num1, int num2, char const op) {
        int ans = 0;
        switch (op) {
            case MINUS_OP: ans = num1 - num2; break;
            case PLUS_OP: ans = num1 + num2; break;
            case MULTIPLY_OP: ans = num1 * num2; break;
            case DIVIDE_OP: ans = num1 / num2; break;
            default: ans = 0;break;
        }
        return ans;

    }
private:
    static char const MINUS_OP = '-';
    static char const PLUS_OP = '+';
    static char const MULTIPLY_OP = '*';
    static char const DIVIDE_OP = '/';
    static char const SPACE = ' ';
};
