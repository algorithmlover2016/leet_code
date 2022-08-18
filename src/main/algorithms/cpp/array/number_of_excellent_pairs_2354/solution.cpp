#include "../../head.h"


#define NO_IF
class Solution {
public:
    long long countExcellentPairs(std::vector<int> const & nums, int k) {
        // plagiarizing from https://leetcode.com/problems/number-of-excellent-pairs/discuss/2324634/Formula
        // and https://leetcode.com/problems/number-of-excellent-pairs/discuss/2324984/JavaC%2B%2BPython-Inclusion-Exclusion-Principle
        
        // cnts record the setting bits of num in nums, because any num in nums will never larger that 10^9, which means there will never 29 setting bits.
        // because if 29 bits are all setting with 1, it will be 2 ^ 30 - 1 = 1073741823, which is larger than 10 ^ 9.
        std::vector<long long> cnts(MAX_LEN_BITS);
        for (int num : std::unordered_set<int>(std::begin(nums), std::end(nums)) /* we do not care the num in nums are repeated, only consider distinct num */) {
            ++cnts[__builtin_popcount(num)]; // how many different nums that with each same bits setting
        }
        long long ans = 0;
        for (int idx = 1 /*because assume num > 0*/; idx < MAX_LEN_BITS; idx++) {
            #ifdef NO_IF
            for (int next = std::max(1, k - idx); next < MAX_LEN_BITS; next++) {
                ans += cnts[idx] * cnts[next];
            }
            #else
            for (int next = std::max(idx, k - idx); next < MAX_LEN_BITS; next++) {
                // if idx != next, then the nums in cnts[idx] will never equal to any of num in cnts[next], so the pair can be reversed.
                // so the problem becomes Cn1(1) * Cn2(1) * 2
                // if idx == next, then we need select two num in cnts[idx], because each representing num in cnts[idx] is different.
                // so the problem becomes Cn(1) * Cn(1)
                ans += cnts[idx] * cnts[next] * (idx == next ? 1 : 2);
            }
            #endif
        }
        return ans;
    }
private:
    static int const MAX_LEN_BITS = 30; // because each num in nums is less than 10^9 and larger than 0,  which is also less than 2^30.
                                        // so after `or` and `and`, the setting bits will be smaller than 30.
};