#include "../../head.h"


class Solution {
public:
    std::vector<std::string> generateParenthesis(int n) {
        std::vector<std::string> ans;
        if (0 > n) {
            return ans;
        }
        std::string curAns;
        int cnt = 0;
        dfs(n, 0, 0, curAns, ans);
        return ans;
    }
    void dfs(int total, int idx, int cnt, std::string & curAns, std::vector<std::string> & ans) {
        if (idx == total) {
            if (0 == cnt) {
                ans.emplace_back(curAns);
            } else {
                curAns.push_back(')');
                dfs(total, idx, cnt - 1, curAns, ans);
                curAns.pop_back();
            }
            return;
        }

        // we can add a right parenthese
        if (0 < cnt) {
            curAns.push_back(')');
            dfs(total, idx, cnt - 1, curAns, ans);
            curAns.pop_back();
        }

        // we can add a left parenthese
        curAns.push_back('(');
        dfs(total, idx + 1, cnt + 1, curAns, ans);
        curAns.pop_back();
    }
};

class Solution {
private:
    std::vector<std::string> res;
public:
    std::vector<std::string> generateParenthesis(int n) {
        std::string prev = "";
        dfs(n, n, prev);
        return res;
    }

private:
    void dfs(int left, int right, std::string & prev){
        if(!left && !right) {
            res.push_back(prev);
            return;
        }

        if (left) {
            prev += '(';
            dfs(left - 1, right, prev);
            prev.pop_back();
        }

        if (right > left){
            prev += ')';
            dfs(left, right - 1, prev);
            prev.pop_back();
        }
    }
};
