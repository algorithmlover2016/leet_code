#include "../../head.h"


class Solution {
public:
    bool isValid(std::string const & s) {
        std::vector<char> parentheseStack;
        if (s.empty()) {
            return true;
        }
        for (char c : s) {
            switch (c) {
                case '(':
                case '[':
                case '{':
                    parentheseStack.emplace_back(c);
                    break;
                case ')':
                    if (!parentheseStack.empty() && parentheseStack.back() == '(') {
                        parentheseStack.pop_back();
                    } else {
                        return false;
                    }
                    break;
                case ']':
                    if (!parentheseStack.empty() && parentheseStack.back() == '[') {
                        parentheseStack.pop_back();
                    } else {
                        return false;
                    }
                    break;
                case '}':
                    if (!parentheseStack.empty() && parentheseStack.back() == '{') {
                        parentheseStack.pop_back();
                    } else {
                        return false;
                    }
                    break;
                default:
                    break;
            }
        }
        return parentheseStack.empty();
    }
};

class Solution {
public:
    bool isValid(std::string const & s) {
        std::stack<char> mStack;
        for (int i = 0; i < s.size(); i++) {
            if (mStack.empty()) {
                mStack.push(s[i]);
                continue;
            }

            if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
                mStack.push(s[i]);
            } else if (s[i] == ')' && mStack.top() == '(') {
                mStack.pop();
            } else if (s[i] == ']' && mStack.top() == '[') {
                mStack.pop();
            } else if (s[i] == '}' && mStack.top() == '{') {
                mStack.pop();
            } else {
                return false;
            }
        }

        if (mStack.empty()) {
            return true;
        } else {
            return false;
        }
    }
};
