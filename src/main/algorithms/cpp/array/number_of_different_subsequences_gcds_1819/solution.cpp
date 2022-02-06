#include "../../head.h"


// #define USE_VECTOR_NOT_MAP

class Solution {
public:
    int countDifferentSubsequenceGCDs(std::vector<int> const & nums) {
        // plagiarizing from https://leetcode.com/problems/number-of-different-subsequences-gcds/discuss/1141309/Simple-explanation-or-O(n-*-sqrt-n)
        #ifdef USE_VECTOR_NOT_MAP
        std::vector<int> factors(MAX_FACTORS_NUM, 0);
        #else
        std::unordered_map<int, int> factors;
        #endif
        for (int const & num : nums) {
            int upperFactor = ceil(std::sqrt(num));
            for (int factor = 1; factor <= upperFactor; factor++) {
                if (0 == num % factor) {
                    int quotient = num / factor;
                    int divisor = factor;
                    // use the feature that getting an non-existing key will be zero-value which will be 0 for int
                    factors[factor] = gcd(factors[factor], num);
                    factors[quotient] = gcd(factors[quotient], num);
                }
            }
        }
        int ans = 0;
        #ifdef USE_VECTOR_NOT_MAP
        for (int idx = 1; idx < factors.size(); idx++) {
            if (idx == factors[idx]) {
                ans++;
            }
        }
        #else
        for (auto const & [factor, val] : factors) {
            if (factor == val) {
                ans++;
            }
        }
        #endif
        return ans;
    }

private:
    int gcd(int left, int right) {
        while (0 != right) {
            int tmp = right;
            right = left % right;
            left = tmp;
        }
        return left;
    }

#ifdef USE_VECTOR_NOT_MAP
private:
    static int const MAX_FACTORS_NUM = 200001;
#endif
};