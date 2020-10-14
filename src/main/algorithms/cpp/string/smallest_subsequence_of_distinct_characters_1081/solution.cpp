#include "../../head.h"


class Solution {
public:
    std::string smallestSubsequence(std::string const & s) {
        // plagiarizing from https://leetcode.com/problems/remove-duplicate-letters/discuss/76767/C%2B%2B-simple-solution-easy-understanding
        std::vector<int> cnt(26, 0);
        int mask = 0;

        for (char c : s) {
            cnt[c - 'a']++;
        }
        std::string ans("A");
        for (char c : s) {
            int index = c - 'a';
            cnt[index]--;
            // already append before
            if (mask & (1 << index)) {
                continue;
            }
            while ((c < ans.back()) &&
                    (cnt[ans.back() - 'a'] > 0)) {
                mask &= ~(1 << (ans.back() - 'a'));
                ans.pop_back();
            }
            ans += c;
            mask |= 1 << index;
        }
        return ans.substr(1);
    }
};
