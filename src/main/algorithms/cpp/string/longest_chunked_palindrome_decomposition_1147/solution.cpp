#include "../../head.h"


class Solution {
public:
    int longestDecomposition(std::string const & text) {
        // plagiarizing from https://leetcode.com/problems/longest-chunked-palindrome-decomposition/discuss/350589/Python-Simple-DP
        if (text.empty()) {
            return 0;
        }
        int const textSize = text.size();
        std::vector<std::vector<int>> dpMemo(textSize, std::vector<int>(textSize, 0));
        return dfs(text, 0, textSize - 1, dpMemo);
    }
    int dfs(std::string const & text, int left, int right, std::vector<std::vector<int>> & dpMemo) {
        if (left > right) {
            return 0;
        }
        if (left == right) {
            return 1;
        }
        if (0 != dpMemo[left][right]) {
            return dpMemo[left][right];
        }
        int ans = 1; // the whole str can be seen as a split
        int maxLen = (right - left + 1) / 2;
        for (int len = 1; len <= maxLen; len++) {
            if (text.substr(left, len) == text.substr(right - len + 1, len)) {
                ans = std::max(ans, 2 + dfs(text, left + len, right - len, dpMemo));
                // according to the explanation of https://leetcode.com/problems/longest-chunked-palindrome-decomposition/discuss/350560/JavaC%2B%2BPython-Easy-Greedy-with-Prove
                // if we find a len (which is smallest), it will lead to max ans. so we just break;
                break;
            }
        }
        return dpMemo[left][right] = ans;
    }
};

class SolutionRecursive {
public:
    int longestDecomposition(std::string const & text) {
        // plagiarizing from https://leetcode.com/problems/longest-chunked-palindrome-decomposition/discuss/350560/JavaC%2B%2BPython-Easy-Greedy-with-Prove
        // plagiarizing from https://leetcode.com/problems/longest-chunked-palindrome-decomposition/discuss/350762/Java-0ms-concise-beats-100-(both-time-and-memory)-with-algo
        int const textSize = text.size();
        for (int len = 1; len <= textSize / 2; len++) {
            if (text.substr(0, len) == text.substr(textSize - len, len)) {
                return 2 + longestDecomposition(text.substr(len, textSize - len * 2));
            }
        }
        // return (0 == textSize) ? 0 : 1;
        return (0 < textSize) ? 1 : 0;
    }
private:
    static int const JUST_ONE = 1;
};

class Solution {
public:
    int longestDecomposition(std::string const & text) {
        // plagiarizing from https://leetcode.com/problems/longest-chunked-palindrome-decomposition/discuss/350560/JavaC%2B%2BPython-Easy-Greedy-with-Prove
        int const textSize = text.size();
        std::string left, right;
        int ans = 0;
        for (int idx = 0; idx < textSize; idx++) {
            left += text[idx]; right = text[textSize - 1 - idx] + right;
            if (left == right) {
                ans ++;
                left = "";
                right = "";
            }
        }
        return ans;
    }
};

#define COMPARE_WITH_HASH
class Solution {
public:
    int longestDecomposition(std::string const & text) {
        // plagiarizing from https://leetcode.com/problems/longest-chunked-palindrome-decomposition/discuss/350560/JavaC%2B%2BPython-Easy-Greedy-with-Prove
        int const textSize = text.size();
        std::string left, right;
#ifdef COMPARE_WITH_HASH
        std::hash<std::string> strHash;
#endif
        int ans = 0;
        int idx = 0;
        for (; idx < textSize / 2; idx++) {
            left += text[idx]; right = text[textSize - 1 - idx] + right;

#ifdef COMPARE_WITH_HASH
            if (strHash(left) == strHash(right))
#else
            if (left == right)
#endif
            {
                ans += 2;
                left = "";
                right = "";
            }
        }
        return !left.empty() || (idx * 2 == textSize - 1) ? ans + 1 : ans;
    }
};

class SolutionOverFlowRange {
public:
    int longestDecomposition(std::string const & text) {
        // plagiarizing from https://leetcode.com/problems/longest-chunked-palindrome-decomposition/discuss/350711/Close-to-O(n)-Python-Rabin-Karp-Algorithm-with-two-pointer-technique-with-explanation-(~40ms)
        int const textSize = text.size();
        // the hash can't make sure the answer will be right;
        long long lowHash = 0;
        long long highHash = 0;
        int curHashLen = 0;
        int left = 0, right = textSize - 1;
        int ans = 0;

        while (left < right) {
            lowHash *= LETTER_CNT;
            lowHash += text[left] - BASE_OFFSET;
            lowHash %= magicPrime;
            highHash = (text[right] - BASE_OFFSET) * std::pow(LETTER_CNT, curHashLen) + highHash; // insert at begining
            highHash %= magicPrime;
            left++;
            right--;
            curHashLen++;
            if (lowHash == highHash) {
                ans += 2;
                lowHash = 0;
                highHash = 0;
                curHashLen = 0;
            }
        }
        if (0 != curHashLen || left == right) {
            ans++;
        }
        return ans;
    }
private:
    static int const BASE_OFFSET = 'a';
    static int const LETTER_CNT = 26;
    static int const magicPrime = 32416189573;
};    
