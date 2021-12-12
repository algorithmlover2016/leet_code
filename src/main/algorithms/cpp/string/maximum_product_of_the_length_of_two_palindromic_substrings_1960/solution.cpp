#include "../../head.h"


// #define DEBUG
#define USE_QUEUE
class Solution {
public:
    long long maxProduct(std::string const & s) {
        // plagiarizing from https://leetcode.com/problems/maximum-product-of-the-length-of-two-palindromic-substrings/discuss/1389958/Manacher-and-Queue
        long long ans = 1LL;
        if (s.empty()) {
            return ans;
        }
        int sSize = s.size();
        std::vector<int> odd, even;
        auto [left2RightOddMaxLen, left2RightEvenMaxLen] = manachers(s, odd, even);
        #ifdef DEBUG
        std::cout << "call manacher first done\n";
        #endif

        #ifdef USE_QUEUE
        std::queue<std::pair<int, int>> left2Right, right2Left;
        std::vector<long long> rightLen(sSize);
        for (int idx = sSize - 1; idx > LEFT_MOST_EXCLUSIVE; idx--) {
            while (!right2Left.empty() && (right2Left.front().first - right2Left.front().second > idx - 1)) {
                // the palindromic substring can not be reached at idx
                right2Left.pop();
            }
            rightLen[idx] = 1LL + (right2Left.empty() ? 0 : (right2Left.front().first - idx) * 2);
            #ifdef DEBUG
            std::cout << "rightLen[idx]: " << rightLen[idx] << "\n";
            #endif
            right2Left.emplace(std::make_pair(idx, odd[idx]));
        }

        long long res = 1LL;
        for (int idx = LEFT_MOST_INCLUSIVE; idx < sSize - 1; idx++) {
            // please note the length and the start-idx, first means the center, and second means the length and it contains the center.
            // so if we want to compute the most-right inclusive, we should center + (length - 1).
            while (!left2Right.empty() && (left2Right.front().first + left2Right.front().second < idx + 1)) {
                left2Right.pop();
            }
            res = std::max(res, 1LL + (left2Right.empty() ? 0 : (idx - left2Right.front().first) * 2));
            #ifdef DEBUG
            std::cout << "idx: " << idx  << ", res: " << res << "\n";
            #endif
            ans = std::max(ans, res * rightLen[idx + 1]);
            left2Right.emplace(std::make_pair(idx, odd[idx]));
        }
        #else
        auto [right2LeftOddMaxLen, right2LeftEvenMaxLen] = manachers(std::string (std::crbegin(s), std::crend(s)), odd, even); 
        // idx means from left to right, revIdx means from right to left, we should contain all the lenght of s
        // which means idx + revIdx = sSize - 1;
        for (int idx = LEFT_MOST_INCLUSIVE, revIdx = sSize - 2; idx < sSize - 1; idx++, revIdx--) {
            ans = std::max(ans, (long long)left2RightOddMaxLen[idx] * right2LeftOddMaxLen[revIdx]);
        }
        #endif
        return ans;

    }
private:
    std::pair<std::vector<int>, std::vector<int>> manachers(std::string const & str, std::vector<int> & odd, std::vector<int> & even) {
        int const strSize = str.size();
        odd.resize(strSize);
        even.resize(strSize);
        #ifdef DEBUG
        std::cout << "str.size: " << strSize << "\n";
        #endif

        std::vector<int> left2RightOddMaxLen(strSize, 1);

        for (int idx = 0, left = 0, right = -1; idx < strSize; idx++) {
            #ifdef DEBUG
            std::cout << "mirror:" << left + right - idx << "\n";
            #endif
            int len = (idx > right) ? 1 : std::min(odd[left + right - idx], right - idx + 1);
            while (LEFT_MOST_EXCLUSIVE < idx - len && idx + len < strSize &&
                   str[idx - len] == str[idx + len]) {
                left2RightOddMaxLen[idx + len] = 2 * len + 1;
                len++;
            }
            odd[idx] = len--;
            if (idx + len > right) {
                right = idx + len;
                left = idx - len;
            }
        }

        std::vector<int> left2RightEvenMaxLen(strSize, 0);
        for (int idx = 0, left = 0, right = -1; idx < strSize; idx++) {
            int len = (idx > right) ? 0 : std::min(even[left + right - idx + 1], right - idx + 1);
            while (LEFT_MOST_EXCLUSIVE < idx - 1 - len && idx + len < strSize &&
                   str[idx - 1 - len] == str[idx + len]) {
                len++;
                left2RightEvenMaxLen[idx + len - 1] = 2 * len;
            }
            even[idx] = len--;
            if (idx + len > right) {
                right = idx + len;
                left = idx - 1 - len;
            }
        }

        for (int idx = LEFT_MOST_INCLUSIVE + 1; idx < strSize; idx++) {
            left2RightOddMaxLen[idx] = std::max(left2RightOddMaxLen[idx], left2RightOddMaxLen[idx - 1]);
            left2RightEvenMaxLen[idx] = std::max(left2RightEvenMaxLen[idx], left2RightEvenMaxLen[idx - 1]);
        }
        return std::make_pair(left2RightOddMaxLen, left2RightEvenMaxLen);

    }
private:
    static int const LEFT_MOST_EXCLUSIVE = -1;
    static int const LEFT_MOST_INCLUSIVE = 0;
};
