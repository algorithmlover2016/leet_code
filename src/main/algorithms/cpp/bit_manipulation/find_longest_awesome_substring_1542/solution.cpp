#include "../../head.h"


class Solution {
public:
    int longestAwesome(std::string const & s) {
        // plagiarizing from https://leetcode.com/problems/find-longest-awesome-substring/discuss/779919/JavaC%2B%2BPython-Prefix-%2B-BitMask
        int const MAX_NUM = 10;
        int const MAX_LEN = 1 << MAX_NUM;
        int sSize = s.size();
        // at most 0 - 9 ten numbers, which maybe 1024 combination
        std::vector<int> seen(MAX_LEN, sSize);

        // cur means the visited number combination
        int cur = 0, ans = 0;
        seen[0] = -1;
        for (int index = 0; index < sSize; index++) {
            cur ^= (1 << (s[index] - '0'));
            for (int val = 0; val < MAX_NUM; val++) {
                // changing one element
                ans = std::max(ans, index - seen[cur ^ (1 << val)]);
            }
            ans = std::max(ans, index - seen[cur]);
            seen[cur] = std::min(seen[cur], index);
        }
        return ans;

    }
};
