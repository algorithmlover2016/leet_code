#include "../../head.h"



class Solution {
public:
    int maxValueOfCoins(std::vector<std::vector<int>> const & piles, int K) {
        // plagiarizing from https://leetcode.com/problems/maximum-value-of-k-coins-from-piles/discuss/1887010/JavaC%2B%2BPython-Top-down-DP-solution
        // and https://leetcode.com/problems/maximum-value-of-k-coins-from-piles/discuss/1886905/Python-dp-solution-(complexity-updated)-explained
        int pilesSize = piles.size();
        if (0 == pilesSize || 0 == K) {
            return 0;
        }
        std::vector<std::vector<int>> dpMemo(pilesSize, std::vector<int>(K + 1, 0));
        std::function<int(int, int)> dp = [&] (int idx, int k) {
            if (idx == pilesSize /*we have visited all the piles but we have not choose K coins, invalid */ ||
                0 == k /* we can not add any coin any more, because we have select K coins and valid result */) {
                return 0;
            }
            if (0 < dpMemo[idx][k]) {
                return dpMemo[idx][k];
            }
            int ans = dp(idx + 1, k); // we skip the idx pile and select all coins from the others
            int selectFromCurPile = 0;
            for (int pileIdx = 0; pileIdx < std::min(int(piles[idx].size()), k); pileIdx++) {
                selectFromCurPile += piles[idx][pileIdx]; // we can only select coin in the idx pile from top to the buttom
                ans = std::max(ans, dp(idx + 1, k - (pileIdx + 1)) + selectFromCurPile);
            }
            return dpMemo[idx][k] = ans;
        };
        return dp(0, K);
    }
};