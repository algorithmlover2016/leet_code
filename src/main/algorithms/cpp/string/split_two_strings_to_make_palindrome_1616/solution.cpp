#include "../../head.h"


class Solution {
public:
    bool checkPalindromeFormation(std::string const & a, std::string const & b) {

        int aSize = a.size();
        if (aSize != b.size()) {
            return false;
        }

        if (2 > aSize) {
            return true;
        }

        int left = 0, right = aSize - 1;
        // is wrong judgement condition, we should call the function twice and exchange a, b position.
        // while (left < right && (a[left] == b[right] || a[right] == b[left])) {
        while (left < right && (a[left] == b[right])) {
            left++; right--;
        }
        if (left >= right) {
            return true;
        }
        if (IsPalindrome(a.substr(left, right - left + 1))) {
            return true;
        }
        if (IsPalindrome(b.substr(left, right - left + 1))) {
            return true;
        }

        return false;
    }
    bool IsPalindrome(std::string const & str) {
        int strSize = str.size();
        if (2 > strSize) {
            return true;
        }
        int left = 0, right = strSize - 1;
        while (left < right && str[left] == str[right]) {
            left++; right--;
        }
        return left >= right;
    }
};

class Solution {
public:
    bool isPa(std::string const & s, int i, int j) {
        for (; i < j; ++i, --j)
            if (s[i] != s[j])
                return false;
        return true;
    }

    bool check(std::string const & a, std::string const & b) {
        int aSize = a.size();
        if (aSize != b.size()) {
            return false;
        }
        if (2 > aSize) {
            return true;
        }
        for (int i = 0, j = aSize - 1; i < j; ++i, --j) {
            if (a[i] != b[j]) {
                return isPa(a, i, j) || isPa(b, i, j);
            }
        }
        return true;
    }

    bool checkPalindromeFormation(std::string const & a, std::string const & b) {
        return check(a, b) || check(b, a);
    }
};
