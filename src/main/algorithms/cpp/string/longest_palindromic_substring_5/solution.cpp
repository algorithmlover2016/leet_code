#include "../../head.h"


class Solution {
public:
    std::string longestPalindrome(std::string const & s) {
        int pos = 0, maxLen = 0;
        if (s.empty()) {
            return s;
        }
        int sLen = s.size();
        int index = 0, left = 0, right = 0;
        while (index <= sLen - maxLen / 2) {
            left = right = index;
            while ((right < sLen - 1) && (s[right + 1] == s[right])) {
                right++;
            }
            index = right + 1;
            while ((left > 0) && (right < sLen -1) && (s[left - 1] == s[right + 1])) {
                left--;
                right++;
            }
            int len = right - left + 1;
            if (len > maxLen) {
                pos = left;
                maxLen = len;
            }
        }
        return s.substr(pos, maxLen);
    }

};

class Solution {
public:
    std::string longestPalindrome(std::string const & s) {
        // plagiarz  jinwu from https://leetcode.com/problems/longest-palindromic-substring/discuss/2928/Very-simple-clean-java-solution
        if (s.size() < 2) {
            return s;
        }
        for (int index = 0; index < s.size() - 1; index++) {
            helper(s, index, index); // find aba
            helper(s, index, index + 1); // find abba
        }
        return s.substr(pos, maxLen);

    }
    void helper(std::string const & s, int left_end, int right_end) {
        while ((left_end >= 0) && (right_end < s.size()) && (s[left_end] == s[right_end])) {
            left_end--;
            right_end++;
        }
        int len = right_end - (++left_end);
        // std::cout << "find subStr: " << s.substr(left_end, len) << std::endl;
        // std::cout << "find max subStr: " << s.substr(pos, maxLen) << std::endl;

        if (len > maxLen) {
            pos = left_end;
            maxLen = len;
        }
    }

private:
    int pos = 0;
    int maxLen = 0;
};


class Solution {
public:
    std::string longestPalindrome(std::string const & s) {
        // dp
        int const sSize = s.size();
        if (JUST_ONE >= sSize) {
            return s;
        }
        std::vector<std::vector<bool>> dpMemo(sSize, std::vector<bool>(sSize, true));
        int ans = 1;
        int pos = 0;
        for (int right = 1; right < sSize; right++) {
            for (int left = 0; left < right; left++) {
                dpMemo[left][right] = (s[left] == s[right]) && (right - left < 3 || dpMemo[left + 1][right - 1]);
                if (dpMemo[left][right]) {
                    int maxLen = right - left + 1;
                    if (maxLen > ans) {
                        ans = maxLen; 
                        pos = left;
                    }
                }
            }
        }
        return s.substr(pos, ans);
    }
private:
    static int const JUST_ONE = 1;
};

class Solution {
public:

    std::string longestPalindrome(std::string const & s) {
        // dp
        int const sSize = s.size();
        if (JUST_ONE >= sSize) {
            return s;
        }
        std::string ans;
        for (int idx = 0; idx < sSize; idx++) {
            std::string odd = isPalindromic(s, idx, idx);
            std::string even = isPalindromic(s, idx, idx + 1);
            std::string maxLenStr = odd.size() > even.size() ? odd : even;
            if (maxLenStr.size() > ans.size()) {
                ans = maxLenStr;
                
            }
        }
        return ans;
    }
private:
    std::string isPalindromic(std::string const & s, int left, int right) {
        while (left >= 0 && right < s.size()) {
            if (s[left] == s[right]) {
                right++;
                left--;
            } else {
                break;
            }
        }
        return s.substr(left + 1, right - left - 1);
    }
private:
    static int const JUST_ONE = 1;
};
