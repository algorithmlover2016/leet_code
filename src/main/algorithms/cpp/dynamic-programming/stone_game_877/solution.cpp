#include <vector>

class Solution {
public:
    bool stoneGame(std::vector<int>& piles) {
        // copying method from https://leetcode.com/problems/stone-game/discuss/154610/C%2B%2BJavaPython-DP-or-Just-return-true
        const int nSize = piles.size();
        if (nSize == 0) {
            return false;
        }
#ifndef LIMIT_MEMORY
        std::vector<std::vector<int> > dp(nSize, std::vector<int>(nSize, 0));
        // the follow loopping means that the diff = 0;
        for (int index = 0; index < nSize; index++) {
            dp[index][index] = piles[index];
        }
        
        for (int diff = 1; diff < nSize; diff++) {
            for (int index = 0; index < nSize - diff; index++) {
                dp[index][index + diff] = std::max(piles[index] - dp[index + 1][index + diff], 
                                             piles[index + diff] - dp[index][index + diff - 1]);
            }
        }
        return dp[0][nSize - 1];
#elif
        // init dp with piels, which means that the diff is zero;
        std::vector<int> dp(piles);
        for (int diff = 1; diff < nSize; diff++) {
            for (int index = 0; index < nSize - diff; index++) {
                // the reason why can do this is that the diff is increasing one by one.
                // which means dp[index + 1] represents dp[index + 1][index + diff], and
                // dp[index] represents dp[index][diff - 1]
                // when you don't update dp[index], it saves the last exterior loop where diff can be called preDiff which is curDiff minus one;
                dp[index] = std::max(piles[index] - dp[index + 1], 
                                             piles[index + diff] - dp[index]);
            }
        }
        return dp[0];
#endif
    }
};
