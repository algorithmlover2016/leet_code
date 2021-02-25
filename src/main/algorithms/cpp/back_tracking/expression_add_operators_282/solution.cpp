#include "../../head.h"


class Solution {
public:
    std::vector<std::string> addOperators(std::string const & num, int target) {
        // plagiarizing from https://youtu.be/171aA2ir8GE
        std::vector<std::string> ans;
        backTracking(num, target, ans, 0, 0, 0, 0, "");
        return ans;
    }
    void backTracking(std::string const & num,
            int const target, std::vector<std::string> & ans,
            int idx, long pre, long cur, long val, std::string curAns) {
        if (idx == num.size()) {
            // reach to the end and all the elements are used
            if (target == val && 0 == cur) {
                ans.emplace_back(curAns);
            }
            return;
        }
        cur = cur * 10 + num[idx] - BASIC_NUM;
        if (0 < cur) {
            // cur can add num without +, -, * operation
            backTracking(num, target, ans, idx + 1, pre, cur, val, curAns);
        }

        if (curAns.empty()) {
            // the first element of num, which can only be executed + operation
            backTracking(num, target, ans, idx + 1, cur, 0, val + cur, curAns + std::to_string(cur));
        } else {
            backTracking(num, target, ans, idx + 1,
                    cur, 0, val + cur, curAns + "+" + std::to_string(cur));
            backTracking(num, target, ans, idx + 1,
                    -cur, 0, val - cur, curAns + "-" + std::to_string(cur));
            backTracking(num, target, ans, idx + 1,
                    pre * cur, 0, val - pre + pre * cur, curAns + "*" + std::to_string(cur));
        }
    }
private:
    static char const BASIC_NUM = '0';
};

class Solution {
public:
    std::vector<std::string> addOperators(std::string const & num, int t) {
        std::vector<std::string> ans;
        std::string path = std::string(num.length() * 2, ' ');
        helper(ans, num, /*pos=*/0, path, /*len=*/0, 0, 0, t);
        return ans;
    }
    void helper(std::vector<std::string> & ans, const std::string & num,
            int pos, std::string & path, int len, int current_value,
            int previous_value, int target) {
        if (pos == num.length()) {
            if (current_value == target) {
                ans.push_back(path.substr(0, len));
            }
            return;
        }
        long number = 0;
        int moving_pos = pos, moving_len = len;
        if (pos != 0) {
            moving_len++; // 1st number does not have leading op. the following numbers have leading op.
        }
        while (moving_pos < num.length()) {
            number = number * 10 + (num[moving_pos] - '0');
            if (num[pos] == '0' && moving_pos - pos > 0) break; // leading 0 is not valid number
            if (number > INT_MAX) break;
            path[moving_len++] = num[moving_pos++];
            if (pos == 0) {
                helper(ans, num, moving_pos, path, moving_len, number, number, target);
                continue; // do not forget.
            }
            path[len] = '+';
            helper(ans, num, moving_pos, path, moving_len, current_value+number, number, target);

            path[len] = '-';
            helper(ans, num, moving_pos, path, moving_len, current_value-number, -number, target);

            path[len] = '*';
            helper(ans, num, moving_pos, path, moving_len, current_value-previous_value+previous_value*number, previous_value*number, target);
        }
    }
};
