#include "../../head.h"


class Solution {
public:
    std::string removeDuplicateLetters(std::string const & s) {
        // plagiarizing from https://leetcode.com/problems/remove-duplicate-letters/discuss/76767/C%2B%2B-simple-solution-easy-understanding
        std::vector<int> cnt(26, 0);
        int mask = 0;

        // statistic the letter numbers
        for (char c : s) {
            cnt[c - 'a']++;
        }

        // add a first flag to avoid ans be empty;
        std::string ans("A");
        for (char c : s) {
            int index = c - 'a';
            // the letter must be used, so can reduce one;
            cnt[index]--;

            // already append before
            if (mask & (1 << index)) {
                continue;
            }

            // if the letter is smaller than the one that will appear after the letter, just rollback it.
            // meanwhile, remove the mark that it's used
            while ((c < ans.back()) &&
                    (cnt[ans.back() - 'a'] > 0)) {
                mask &= ~(1 << (ans.back() - 'a'));
                ans.pop_back();
            }

            // find the right position to append the letter
            ans += c;
            mask |= 1 << index;
        }
        return ans.substr(1);
    }
};
