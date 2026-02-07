#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 1. 最长公共子串 (长度) - O(M) 空间
class Solution {
public:
    int longestCommonSubstring(string s1, string s2) {
        int n = s1.length();
        int m = s2.length();
        if (n == 0 || m == 0) return 0;

        vector<int> dp(m + 1, 0);
        int maxLength = 0;

        for (int i = 1; i <= n; i++) {
            for (int j = m; j >= 1; j--) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[j] = dp[j - 1] + 1;
                    maxLength = max(maxLength, dp[j]);
                } else {
                    dp[j] = 0;
                }
            }
        }
        return maxLength;
    }
};

// 2. 最长公共子串 (内容)
class SolutionSubstr {
public:
    string longestCommonSubstring(string s1, string s2) {
        int n = s1.length();
        int m = s2.length();
        if (n == 0 || m == 0) return "";

        vector<int> dp(m + 1, 0);
        int maxLength = 0;
        int endIndexS1 = -1;

        for (int i = 1; i <= n; i++) {
            for (int j = m; j >= 1; j--) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[j] = dp[j - 1] + 1;
                    if (dp[j] > maxLength) {
                        maxLength = dp[j];
                        endIndexS1 = i - 1; 
                    }
                } else {
                    dp[j] = 0;
                }
            }
        }

        if (maxLength == 0) return "";
        return s1.substr(endIndexS1 - maxLength + 1, maxLength);
    }
};

// 3. 最长公共子序列 (长度)
class Subsequence {
public:
    int longestCommonSubsequence(string s1, string s2) {
        int n = s1.length();
        int m = s2.length();
        
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        
        return dp[n][m];
    }
};

// 4. 最长公共子序列 (内容)
class MaxSubSequenceContent {
public:
    /**
     * @brief 获取两个字符串的最长公共子序列的内容
     * 
     * 算法步骤:
     * 1. 构建 DP 表 (同计算长度)
     * 2. 从 DP[n][m] 开始回溯:
     *    - 如果 s1[i-1] == s2[j-1]，则该字符属于 LCS，加入结果，移动到 (i-1, j-1)
     *    - 如果不等，向 DP 值较大的方向移动 (左或上)
     * 3. 反转结果字符串
     */
    string longestCommonSubsequence(string s1, string s2) {
        int n = s1.length();
        int m = s2.length();
        
        // 步骤 1: 构建 DP 表
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        
        // 步骤 2: 回溯构建子序列字符串
        string lcs = "";
        int i = n, j = m;
        while (i > 0 && j > 0) {
            // 如果字符相等，说明来源于 s1[i-1] (或 s2[j-1])
            if (s1[i - 1] == s2[j - 1]) {
                lcs += s1[i - 1];
                i--;
                j--;
            } 
            // 否则，向 DP 值更大的方向回退
            else if (dp[i - 1][j] > dp[i][j - 1]) {
                i--;
            } else {
                j--;
            }
        }
        
        // 步骤 3: 结果是逆序的，需要反转
        reverse(lcs.begin(), lcs.end());
        return lcs;
    }
};

int main() {
    Solution sol;
    SolutionSubstr solSub;
    Subsequence subseq;
    MaxSubSequenceContent subseqContent;
    
    // Test Case 1
    string s1 = "abcdefg";
    string s2 = "xyzbcdmn"; // LCS Substring: "bcd"
    
    cout << "=== Test Case 1 ===" << endl;
    cout << "String 1: " << s1 << endl;
    cout << "String 2: " << s2 << endl;
    cout << "[LCS Substring Length] : " << sol.longestCommonSubstring(s1, s2) << endl;
    cout << "[LCS Substring Content]: " << solSub.longestCommonSubstring(s1, s2) << endl;
    cout << "[LCS Subsequence Len]  : " << subseq.longestCommonSubsequence(s1, s2) << endl; // 3 ("bcd")
    cout << "[LCS Subsequence Str]  : " << subseqContent.longestCommonSubsequence(s1, s2) << endl;

    cout << endl;

    // Test Case 2
    string s3 = "abcde";
    string s4 = "ace"; 
    
    cout << "=== Test Case 2 ===" << endl;
    cout << "String 1: " << s3 << endl;
    cout << "String 2: " << s4 << endl;
    cout << "[LCS Subsequence Len]  : " << subseq.longestCommonSubsequence(s3, s4) << endl;
    cout << "[LCS Subsequence Str]  : " << subseqContent.longestCommonSubsequence(s3, s4) << endl; 
    // Expect: "ace"

    cout << endl;

    // Test Case 3: More complex subsequence
    string s5 = "ACCGGTCGAGTGCGCGGAAGCCGGCCGAA";
    string s6 = "GTCGTTCGGAATGCCGTTGCTGTAAA";
    
    cout << "=== Test Case 3 ===" << endl;
    cout << "[LCS Subsequence Len]  : " << subseq.longestCommonSubsequence(s5, s6) << endl;
    cout << "[LCS Subsequence Str]  : " << subseqContent.longestCommonSubsequence(s5, s6) << endl;

    return 0;
}