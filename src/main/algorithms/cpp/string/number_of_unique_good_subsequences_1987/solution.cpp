#include "../../head.h"


class Solution {
public:
    int numberOfUniqueGoodSubsequences(std::string const & binary) {
        // plagiarizing from https://leetcode.com/problems/number-of-unique-good-subsequences/discuss/1431819/JavaC%2B%2BPython-DP-4-lines-O(N)-Time-O(1)-Space and
        // https://leetcode.com/problems/number-of-unique-good-subsequences/discuss/1432051/DP-O(n)-or-O(1)

        std::vector<int> dpMemo(ELEMENTS_NUMS_LEN, 0);
        std::vector<bool> elements(ELEMENTS_NUMS_LEN, false);
        for (char const c : binary) {
            int idxMap = c - OFFSET;
            elements[idxMap] = true;
            dpMemo[idxMap] = (std::accumulate(std::begin(dpMemo), std::end(dpMemo), 0) + idxMap) % MOD;
        }
        int ans = 0;
        if (elements[0]) {
            ans += 1;
        }
        ans = std::accumulate(std::begin(dpMemo), std::end(dpMemo), ans) % MOD;
        return ans;
    }
private:
    static int const MOD = 1e9 + 7;
    static char const OFFSET = '0';
    static int const ELEMENTS_NUMS_LEN = 2;

};