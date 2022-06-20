#include "../../head.h"


class Solution {
public:
    int rearrangeSticks(int n, int k) {
        // plagiarizing from https://leetcode.com/problems/number-of-ways-to-rearrange-sticks-with-k-sticks-visible/discuss/1211070/C%2B%2B-Detailed-Explanation-with-Thought-Process-or-DP
        // and https://leetcode.com/problems/number-of-ways-to-rearrange-sticks-with-k-sticks-visible/discuss/1211169/JavaC%2B%2BPython-Concise-DP-Solution
        // and https://leetcode.com/problems/number-of-ways-to-rearrange-sticks-with-k-sticks-visible/discuss/1214875/Almost-AC-vs.-4-ms.
        std::vector<std::vector<long long int>> dpMemo(n + 1, std::vector<long long int>(k + 1, 0));
        return backTracking(dpMemo, n, k);
    }
private:
    long long int backTracking(std::vector<std::vector<long long int>> & dpMemo, int n, int k, int mod = MOD) {
        if (0 >= k || k > n) {
            return 0;
        }
        if (k == n) {
            return 1;
        }
        if (0 != dpMemo[n][k]) {
            return dpMemo[n][k];
        }
        dpMemo[n][k] = (backTracking(dpMemo, n - 1, k - 1) + backTracking(dpMemo, n - 1, k) * ( n - 1)) % mod;
        
        return dpMemo[n][k];

    }
private:
    static long long int const MOD = 1e9 + 7;
};