#include "../../head.h"


class Solution {
public:
    string stoneGameIII(std::vector<int> piles) {
       // plagiarizing from https://leetcode.com/problems/stone-game-ii/discuss/345354/Java-DP-with-memorization-easy-to-understand(with-explanation)
        // and https://leetcode.com/problems/stone-game-ii/discuss/345230/Python-DP-Solution
        if (piles.empty()) {
            return "Alice";
        }
        if (1 == piles.size()) {
            int ele = piles.back();
            return ele > 0 ? "Alice" : (0 == ele ? "Tie" : "Bob");
        }
        for (int index = piles.size() - 2; index >= 0; index--) {
            piles[index] += piles[index + 1]; // from end to begin to get sum;
        }
        std::vector<std::vector<int>> memo(piles.size(), std::vector<int>(M + 1, 0));
        int res = dpHelper(piles, memo, 0, 1);
        int other = piles[0] - res;
        return res > other ? "Alice" : (other == res ? "Tie" : "Bob");

    }
private:
    int dpHelper(std::vector<int> const & piles, std::vector<std::vector<int>> & memo, int index, int m) {
        if (index >= piles.size()) {
            return 0; // all belong to the step
        }
        if (0 != memo[index][m]) {
            return memo[index][m];
        }
        int res = INT_MAX;
        for (int step = 1; step <= M; step++) {
            res = std::min(res, dpHelper(piles, memo, index + step, step));
        }
        return memo[index][m] = piles[index] - res;
    }

private:
    static int const M = 3;
};

static auto io_accelerator = [](){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
}();
class SolutionBetterRumTime {
public:
    std::string stoneGameIII(std::vector<int> const & stoneValue) {
        // must reverse traversal
        // great solution
        const int n = stoneValue.size();
        std::vector<int> dp(n + 1);

        dp[n] = 0;
        for (int i = n - 1; i >= 0; i--) {
            int best = INT_MIN;
            int acc = 0;

            for (int j = 0; j < 3 && i + j < n; j++) {
                acc += stoneValue[i + j];
                int p = acc - dp[i + j + 1];

                best = std::max(best, p);
            }

            dp[i] = best;
        }

        if (dp[0] == 0) {
            return "Tie";
        }

        return dp[0] > 0 ? "Alice" : "Bob";
    }
};
