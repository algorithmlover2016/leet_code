#include "../../head.h"


// #define DEBUG
class Solution {
public:
    int palindromePartition(std::string const & s, int k) {
        // plagiarizing from https://leetcode.com/problems/palindrome-partitioning-iii/discuss/441427/Python3-Top-down-DFS-with-Memoization
        int const sSize = s.size();
        if (sSize < k) {
            return -1;
        }

        std::vector<std::vector<int>> costDp(sSize, std::vector<int>(sSize, 0));
        getPalindrome(s, costDp);

        std::vector<std::vector<int>> dpMemo(sSize, std::vector<int>(k + 1, INIT_FLAG));
        return dfs(s, 0, k, costDp, dpMemo);
    }
private:
    int dfs(std::string const & s, int idx, int k, std::vector<std::vector<int>> const & costDp,
            std::vector<std::vector<int>> & dpMemo) {
        if (INIT_FLAG != dpMemo[idx][k]) {
            return dpMemo[idx][k];
        }
        int const sSize = s.size();
        if (sSize - idx == k) {
            // only left k element, and they need split into k group.
            return dpMemo[idx][k] = 0;
        }
        if (1 == k) {
            return dpMemo[idx][k] = costDp[idx][sSize - 1];
        }
        int ans = sSize;
        for (int right = idx + 1; right < sSize - k + 2; right++) {
            // from idx + 1 to sSize(excluded), we need to split into k - 1 groups
            // so from idx + 1 to sSize(excluded), at least exist k - 1 elements, which mean sSize - right >= k - 1,
            // what's meaning that k - 1 can be got. right + (k - 1) <= sSize
            ans = std::min(ans, dfs(s, right, k - 1, costDp, dpMemo) + costDp[idx][right - 1]);
        }
        return dpMemo[idx][k] = ans;
    }

    void getPalindrome(std::string const & s,
                       std::vector<std::vector<int>> & costDp) {
        for (int len = 2; len <= s.size(); len++) {
            for (int left = 0; left + len - 1 < s.size(); left++) {
                int right = left + len - 1;
                if (s[left] == s[right]) {
                    costDp[left][right] = (left + 1 == right ? 0 : costDp[left + 1][right - 1]);
                } else {
                    costDp[left][right] = (left + 1 == right ? 1 : costDp[left + 1][right - 1] + 1);
                }
                #ifdef DEBUG
                std::cout << left << ",\t" << right << ",\t" << costDp[left][right] << ";\t";
                #endif
            }
            #ifdef DEBUG
            std::cout << "\n";
            #endif
        }
    }
private:
    int const INIT_FLAG = -1;

};

// #define DEBUG
class Solution {
public:
    int palindromePartition(std::string const & s, int k) {
        // plagiarizing from https://leetcode.com/problems/palindrome-partitioning-iii/discuss/442083/Simple-C%2B%2B-Dp-O(N2K)-Beats-100-with-Explanation
        int const sSize = s.size();
        if (sSize < k) {
            return -1;
        }

        std::vector<std::vector<int>> costDp(sSize, std::vector<int>(sSize, 0));
        getPalindrome(s, costDp);

        std::vector<std::vector<int>> dpMemo(sSize, std::vector<int>(k + 1));
        for (int idx = 0; idx < sSize; idx++) {
            dpMemo[idx][1] = costDp[0][idx];
        }

        for (int kk = 2; kk <= k; kk++) {
            // idx = 0, dpMemo[0][kk] can't be implemented, there is only one element. so idx start from 1;
            for (int idx = 1; idx < sSize; idx++) {
                dpMemo[idx][kk] = idx + 1;
                for (int start = 0; start < idx; start++) {
                    dpMemo[idx][kk] = std::min(dpMemo[idx][kk], dpMemo[start][kk - 1] + costDp[start + 1][idx]);
                }
            }
        }

        return dpMemo[sSize - 1][k];
    }
    
private:
    
    void getPalindrome(std::string const & s,
                       std::vector<std::vector<int>> & costDp) {
        for (int len = 2; len <= s.size(); len++) {
            for (int left = 0; left + len - 1 < s.size(); left++) {
                int right = left + len - 1;
                if (s[left] == s[right]) {
                    costDp[left][right] = (left + 1 == right ? 0 : costDp[left + 1][right - 1]);
                } else {
                    costDp[left][right] = (left + 1 == right ? 1 : costDp[left + 1][right - 1] + 1);
                }
                #ifdef DEBUG
                std::cout << left << ",\t" << right << ",\t" << costDp[left][right] << ";\t";
                #endif
            }
            #ifdef DEBUG
            std::cout << "\n";
            #endif
        }
    }
};
