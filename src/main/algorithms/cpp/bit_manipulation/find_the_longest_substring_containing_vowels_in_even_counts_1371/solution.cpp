#include "../../head.h"


class Solution {
public:
    int findTheLongestSubstring(std::string const & s) {
        // plagiarizing from https://leetcode.com/problems/find-the-longest-substring-containing-vowels-in-even-counts/discuss/531840/JavaC++Python-One-Pass
        // and https://leetcode.com/problems/find-longest-awesome-substring/discuss/779919/JavaC%2B%2BPython-Prefix-%2B-BitMask
        std::string const VOWELS("aeiou");
        int sSize = s.size();

        std::vector<int> seen(1 << (VOWELS.size() + 1), sSize);
        seen[0] = -1;
        int cur = 0, ans = 0;
        for (int index = 0; index < sSize; index++) {
            cur ^= (1 << (VOWELS.find(s[index]) + 1)) >> 1;
            ans = std::max(ans, index - seen[cur]);
            seen[cur] = std::min(seen[cur], index);
        }
        return ans;

    }
};
