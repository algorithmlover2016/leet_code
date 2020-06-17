#include "../../head.h"


class Solution {
public:
    std::string largestNumber(std::vector<int> const & cost, int target) {
        // plagiarizing from https://leetcode.com/problems/form-largest-integer-with-digits-that-add-up-to-target/discuss/635267/C%2B%2BJavaPython-Strict-O(Target)
        // store the max length of the numbers, when the target is i;
        std::vector<int> dp(target + 1, INT_MIN);
        dp[0] = 0;
        for (int t = 1; t <= target; t++) {
            for (int index = 0; index < cost.size(); index++) {
                if (t >= cost[index]) {
                    dp[t] = std::max(dp[t], dp[t - cost[index]] == INT_MIN ? INT_MIN : dp[t - cost[index]] + 1);
                    // std::cout << "dp[" << t << "]:\t" << dp[t] << "\n";
                }
            }
        }
        if (INT_MIN == dp[target]) {
            return "0";
        }
        std::string res;
        for (int index = cost.size() - 1; index >= 0; index--) {
            while (target >= cost[index] && dp[target] == dp[target - cost[index]] + 1) {
                res.push_back(index + '1');
                target -= cost[index];
            }
        }
        return res;
    }
};

class Solution {
public:
    std::string largestNumber(std::vector<int> const & cost, int target) {
        // because target <= 5000 and min(cost) > 0. so even initialize dp to -10000, dp[target] will never > 0 if doesnot exist
        std::vector<int> dp(target + 1, -10000);
        dp[0] = 0;
        for (int t = 1; t <= target; ++t) {
            for (int i = 0; i < 9; ++i) {
                dp[t] = max(dp[t], t >= cost[i] ? 1 + dp[t - cost[i]] : -10000);
            }
        }
        if (dp[target] < 0) return "0";
        std::string res = "";
        for (int i = 8; i >= 0; --i) {
            while (target >= cost[i] && dp[target] == dp[target - cost[i]] + 1) {
                res.push_back('1' + i);
                target -= cost[i];
            }
        }
        return res;
    }
};
