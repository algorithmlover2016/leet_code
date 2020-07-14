#include "../../head.h"


class Solution {
public:
    int stoneGameII(std::vector<int> piles) {
        // plagiarizing from https://leetcode.com/problems/stone-game-ii/discuss/345354/Java-DP-with-memorization-easy-to-understand(with-explanation)
        // and https://leetcode.com/problems/stone-game-ii/discuss/345230/Python-DP-Solution
        if (piles.empty()) {
            return 0;
        }
        if (1 == piles.size()) {
            return piles.back();
        }
        for (int index = piles.size() - 2; index >= 0; index--) {
            piles[index] += piles[index + 1]; // from end to begin to get sum;
        }
        std::vector<std::vector<int>> memo(piles.size(), std::vector<int>(M, 0));
        return dpHelper(piles, memo, 0, 1);
    }
private:
    int dpHelper(std::vector<int> const & piles, std::vector<std::vector<int>> & memo, int index, int m) {
        int const dM = 2 * m;
        if (dM + index >= piles.size()) {
            return piles[index]; // all belong to the step
        }
        if (0 != memo[index][m]) {
            return memo[index][m];
        }
        int res = INT_MAX;
        for (int step = 1; step <= dM; step++) {
            res = std::min(res, dpHelper(piles, memo, index + step, std::max(m, step)));
        }
        return memo[index][m] = piles[index] - res;
    }

private:
    static int const M = 32; // because piles.length() <= 100; when M = 32,
    // there is already getting at least 32 elements with 4 step, and the next max step can be 2 * M = 64. which is the fifth step;
    // 64 + 32 = 96, the six step will can be 64 * 2 = 128. lee will take all of them left
};
