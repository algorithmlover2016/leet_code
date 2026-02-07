#include "../../head.h"


class Solution {
public:
    int countEffective(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        int n = nums.size();

        // 1. Compute OR of all numbers
        int fullOr = 0;
        for (int x : nums) fullOr |= x;
        if (fullOr == 0) return 0;

        // 2. Number of bits needed
        int maxBit = 63 - __builtin_clzll(fullOr) + 1;
        int totalMasks = 1 << maxBit;

        // 3. dp[mask] = number of array elements exactly equal to mask
        vector<int> dp(totalMasks, 0);
        for (int x : nums) dp[x]++;

        
        for (int bit = 1; bit < totalMasks; bit <<= 1)
            for (int mask = 0; mask < totalMasks; mask++)
                if (mask & bit)
                    dp[mask] += dp[mask ^ bit];

        // 5. Precompute powers of 2
        vector<int> pow2(n + 1, 1);
        for (int i = 1; i <= n; i++)
            pow2[i] = (pow2[i - 1] * 2LL) % MOD;

        // 6. dp[mask]
        for (int mask = 0; mask < totalMasks; mask++)
            dp[mask] = (pow2[dp[mask]] - 1 + MOD) % MOD;

        
        for (int bit = 1; bit < totalMasks; bit <<= 1)
            for (int mask = 0; mask < totalMasks; mask++)
                if (mask & bit)
                    dp[mask] = (dp[mask] - dp[mask ^ bit] + MOD) % MOD;

        
        long long result = 1;  
        for (int mask = 0; mask < fullOr; mask++)
            result = (result + dp[mask]) % MOD;

        return result;
    }
};