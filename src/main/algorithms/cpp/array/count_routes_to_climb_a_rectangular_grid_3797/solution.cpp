#include "../../head.h"


class Solution {
private:
    const int MOD = 1e9 + 7;
public:
    int numberOfRoutes(vector<string>& grid, int d) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }
        int rows = grid.size();
        int cols = grid[0].size();
        
        auto helper = [&](std::vector<long long int> & dp, int dist, std::string const & rowStr) {
            std::vector<long long int> newDp(cols, 0);
            long long int targetWindowSum = 0;
            for (int col = 0; col <= std::min(cols - 1, dist); col++) {
                targetWindowSum += dp[col];
                targetWindowSum %= MOD;
            }
            newDp[0] = targetWindowSum;
            for (int col = 1; col < cols; col++) {
                targetWindowSum = newDp[col - 1];
                if (col - dist >= 1) {
                    // remove the left most value
                    targetWindowSum -= dp[col - dist -1];
                    targetWindowSum += MOD;
                    targetWindowSum  %= MOD;
                }
                if (col + dist < cols) {
                    // add the new right most value
                    targetWindowSum += dp[col + dist];
                    targetWindowSum %= MOD;
                }
                newDp[col] = targetWindowSum;
            }
            for (int col = 0; col < cols; col++) {
                if (rowStr[col] == '#') {
                    newDp[col] = 0;
                }
            }
            return newDp;
        };
        std::vector<long long int> dp(cols, 1);
        for (int row = rows -1; row >=0; row--) {
            if (row == rows -1) {
                // initialize the last row
                dp = helper(dp, 0, grid[row]);
            } else {
                // from the lower row to the current row
                int dist = std::sqrt(d * d - 1);
                dp = helper(dp, dist, grid[row]);
            }
            // we can reach any cell in the current row
            dp = helper(dp, d, grid[row]);
        }
        int result = 0; 
        for (int col = 0; col < cols; col++) {
            result = (result + dp[col]) % MOD;
        }
        return result;
    }

};