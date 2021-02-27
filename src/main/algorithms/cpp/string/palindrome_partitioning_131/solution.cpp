#include "../../head.h"


// #define DEBUG
class Solution {
public:
    std::vector<std::vector<std::string>> partition(std::string const & s) {
        // reference to https://leetcode.com/problems/palindrome-partitioning/discuss/41963/Java%3A-Backtracking-solution.
        std::vector<std::vector<std::string>> ans;
        if (s.empty()) {
            return ans;
        }
        int const sSize = s.size();
        std::vector<std::vector<bool>> dpMemo(sSize, std::vector<bool>(sSize, false));
        getPalindrome(s, dpMemo);

        std::vector<std::string> curAns;
        dfs(s, dpMemo, ans, 0, curAns);
        return ans;
    }

private:
    void getPalindrome(std::string const & s, std::vector<std::vector<bool>> & dpMemo) {
        int const sSize = s.size();
        for (int len = 1; len <= sSize; len++) {
            for (int left = 0; left + len - 1 < sSize; left++) {
                int right = left + len - 1;
                if (s[left] == s[right]) {
                    dpMemo[left][right] = (right - left < 2) || dpMemo[left + 1][right - 1];
                    #ifdef DEBUG
                    std::cout << left << ",\t" << right <<"\t" << dpMemo[left][right] << "\t";
                    #endif
                }
            }

            #ifdef DEBUG
            std::cout << "\n";
            #endif
        }
    }
    void dfs(std::string const & s,
             std::vector<std::vector<bool>> const & dpMemo,
             std::vector<std::vector<std::string>> & ans,
             int idx,
             std::vector<std::string> & curAns) {
        if (idx == s.size()) {
            if (!curAns.empty()) {
                ans.emplace_back(curAns);
            }
            return;
        }
        for (int right = idx; right < s.size(); right++) {
            #ifdef DEBUG
            std::cout << idx << ",\t" << right << "\t";
            #endif
            if (dpMemo[idx][right]) {
                #ifdef DEBUG
                std::cout << "extract: " << s.substr(idx, right - idx + 1) << ",\t";
                #endif
                curAns.emplace_back(s.substr(idx, right - idx + 1));
                dfs(s, dpMemo, ans, right + 1, curAns);
                curAns.pop_back();
            }

            #ifdef DEBUG
            std::cout << "\n";
            #endif
        }
    }
};
