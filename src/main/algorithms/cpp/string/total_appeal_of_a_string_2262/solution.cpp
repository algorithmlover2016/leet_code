#include "../../head.h"


class Solution {
public:
    long long appealSum(std::string const & s) {
        // plagiarizing from https://leetcode.com/problems/total-appeal-of-a-string/discuss/1996203/DP
        long long ans = 0, cur = 0;
        std::vector<int> prev(CHAR_LEN, -1);
        for (int idx = 0; idx < s.size(); idx++) {
            int cIdx = s[idx] - OFFSET;
            cur += idx - prev[cIdx]; // compared with the (idx - 1)th ele, we only add one for each substr from the prev[cIdx] + 1（include) to idx
            prev[cIdx] = idx;
            ans += cur;
        }
        return ans;
        
    }
private:
    static char const OFFSET = 'a';
    static int const CHAR_LEN = 26;
};