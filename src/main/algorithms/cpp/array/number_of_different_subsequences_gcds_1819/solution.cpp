#include "../../head.h"


// #define USE_VECTOR_NOT_MAP

class SolutionMayTLE {
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

// #define USE_VECTOR_INSTEADOF_SET
class Solution  {
public:
    int countDifferentSubsequenceGCDs(std::vector<int> const & nums) {
        // plagiarizing from https://leetcode.com/problems/number-of-different-subsequences-gcds/discuss/1141361/Python-Python-2-solutions-%2B-2liner-explained
        int ans = 0;
        if (nums.empty()) {
            return ans;
        }

        // records all the elements appearing in nums
        #ifdef USE_VECTOR_INSTEADOF_SET
        std::vector<bool> isExist(MAX_ELE_NUM, false);
        for (int const num : nums) {
            isExist[num] = true;
        }
        #else
        std::unordered_set<int> isExist(std::begin(nums), std::end(nums));
        #endif

        // get the max element in nums, the max gcd factor will never overpass max element
        int const maxEle = 1 + (*std::max_element(std::begin(nums), std::end(nums)));

        for (int factor = 1; factor < maxEle; factor++) {
            int gFactor = 0;
            // multiFac has factor as its factor which means multiFac % factor == 0
            for (int multiFac = factor; multiFac < maxEle; multiFac += factor) {
                // only existing element in nums can generate a gcd
                if (
                #ifdef USE_VECTOR_INSTEADOF_SET
                    isExist[multiFac]
                #else
                    isExist.count(multiFac)
                #endif
                ) {

                    // gcd will be non-increasing which means gFactor will be much less if it changed
                    gFactor = gcd(gFactor, multiFac);
                }
                // we get a combinication which could combine a subsequence and take factor as its gcd
                if (gFactor == factor) {
                    break;
                }
            }
            if (gFactor == factor) {
                ans++;
            }
        }
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

#ifdef USE_VECTOR_INSTEADOF_SET
private:
    static int const MAX_ELE_NUM = 200001;
#endif
};
