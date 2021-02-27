#include "../../head.h"


class Solution {
public:
    int longestSubstring(std::string const & s, int k) {
        // plagiarizing from https://youtu.be/eNCYapoYsBw
        std::unordered_set<char> letters;
        for (char const c : s) {
            letters.insert(c);
        }
        int lettersNum = letters.size(); // lettersNum <= 26 in this problem

        int ans = 0;
        // sliding window, window with diffLetterNum letters
        for (int diffLetterNum = 1; diffLetterNum <= lettersNum; diffLetterNum++) {
            std::unordered_map<char, int> cnts;
            int left = 0;
            for (int right = 0; right < s.size(); right++) {
                cnts[s[right]] += 1;
                while (cnts.size() > diffLetterNum) {
                    if (0 == --cnts[s[left]]) {
                        cnts.erase(s[left]);
                    }
                    left++;
                }
                bool meet = true;
                for (auto const & [c, cnt] : cnts) {
                    if (cnt < k) {
                        meet = false;
                        break;
                    }
                }
                if (meet) {
                    ans = std::max(ans, right - left + 1);
                }
            }
        }
        return ans;
    }
};

// #define DEBUG
class Solution {
public:
    // I'm plagiarizing from better answer

    // 1. in the first pass record the counts of every character
    //    in a hashmap
    // 2. in the second pass locate the first character that
    //  appear less than k times in the string. this character
    //  is definitely not included in the result, and that separates
    //  the string into two parts. keep doing this recursively
    //  and the maximum of the left/right part is the answer.
    //  consider ccaaabb
    //  recursive calls will be like
    //  cc ==> c, aaabb (the 2nd c is skipped due to 2nd while loop)
    //  aaabb ==> aaa, bb
    //  so results till now are 1(c), 3(a), 2(b)
    // so 3 will be returned;
    // worst case O(n^2), average O(n log n). In each recursion
    // level, we scan the whole string, which is O(n). There will
    // be at most n levels, e.g., k = 2 and every character in s
    // appears exactly once. On average, there are log n levels.
    int longestSubstring(std::string const & s, int k) {
        if (s.size() == 0 || k > s.size()) {
            return 0;
        }
        if (k == 0) {
            return s.size();
        }

        std::unordered_map<char,int> cnts;
        for(int i = 0; i < s.size(); i++){
            cnts[s[i]]++;
        }

        int idx1 = 0;
        while (idx1 < s.size() && cnts[s[idx1]] >= k) {
            idx1++;
        }

        if (idx1 == s.size()) {
            return s.size();
        }

        int idx2 = idx1;
        while (idx2 < s.size() && cnts[s[idx2]] < k) {
            idx2++;
        }

#ifdef DEBUG
        std::cout << idx1 << " " << idx2 << endl;
#endif

        // the first letter that its number is less than k
        int left = longestSubstring(s.substr(0 , idx1) , k);
        // int left = idx1; can't set left = idx1, because we statistic all the letters in s, not the left part
        // first number after idx1, whose number is not less than k
        int right = longestSubstring(s.substr(idx2), k);

        return std::max(left, right);

    }
};
