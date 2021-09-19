#include "../../head.h"


// #define DEBUG
class Solution {
public:
    int numberOfGoodSubsets(std::vector<int> const & nums) {
        // plagiarizing from https://leetcode.com/problems/the-number-of-good-subsets/discuss/1451879/Exhaustive-DP-vs.-DP-on-Counts and
        // https://leetcode.com/problems/the-number-of-good-subsets/discuss/1444338/python-dp-on-subsets-explained and
        // https://leetcode.com/problems/the-number-of-good-subsets/discuss/1444213/Python-DP-solution
        std::vector<int> cnts(MAX_VAL, 0);
        for (int num : nums) {
            // assume 0 <= num < MAX_VAL
            cnts[num]++;
        }
        #ifdef DEBUG_P_CNTS
        for (int idx = 0 ; idx < cnts.size(); idx++) {
            std::cout << "idx, val: " << idx << ", " << cnts[idx] << "\n";
        }
        #endif
        std::vector<int> dpMemo((1 << PRIMES_NUMS_LESS_THAN30), 0);
        dpMemo[0] = 1;
        for (int val = 2; val < MAX_VAL; val++) {
            if (0 == val % 4 || 0 == val % 9 || 25 == val) {
                continue;
            }
            int mask = 0;
            for (int pIdx = 0; pIdx < primes.size(); pIdx++) {
                if (0 == val % primes[pIdx]) {
                    mask |= (1 << pIdx);
                }
            }
            #ifdef DEBUG
            std::cout << "val, mask: " << val << ", " << mask << "\n";
            #endif

            for (int idx = 0; idx < dpMemo.size(); idx++) {
                if (0 == (mask & idx)) {
                    dpMemo[mask | idx] = (dpMemo[mask | idx] + (long long)(cnts[val]) * dpMemo[idx]) % MOD;
                }
            }
        }
        int ans = std::accumulate(std::begin(dpMemo) + 1, std::end(dpMemo), 0,
                                  [] (int s, int n) {
                                    return (s + n) % MOD;
                                  }
                                 );
        #ifdef DEBUG
        std::cout << "uncount 1, the res is: " << ans << "\n";
        #endif
        while (cnts[1]-- > 0) {
            ans = (ans << 1) % MOD;
        }
        return ans;
    }

private:
    static int const MOD = 1e9 + 7;
    static int const MAX_VAL = 31;
    static int const PRIMES_NUMS_LESS_THAN30 = 10;
    static std::array<int, PRIMES_NUMS_LESS_THAN30> primes;
};
std::array<int, Solution::PRIMES_NUMS_LESS_THAN30> Solution::primes = {{2, 3, 5, 7, 11, 13, 17, 19, 23, 29}};

// #define DEBUG
class Solution {
public:
    int numberOfGoodSubsets(std::vector<int> const & nums) {
        // plagiarizing from https://leetcode.com/problems/the-number-of-good-subsets/discuss/1451879/Exhaustive-DP-vs.-DP-on-Counts and
        // https://leetcode.com/problems/the-number-of-good-subsets/discuss/1444338/python-dp-on-subsets-explained and
        // https://leetcode.com/problems/the-number-of-good-subsets/discuss/1444213/Python-DP-solution
        static bool initMaskFlag = (initMask(), true);
        std::vector<int> cnts(MAX_VAL, 0);
        for (int num : nums) {
            // assume 0 <= num < MAX_VAL
            cnts[num]++;
        }
        #ifdef DEBUG_P_CNTS
        for (int idx = 0 ; idx < cnts.size(); idx++) {
            std::cout << "idx, val: " << idx << ", " << cnts[idx] << "\n";
        }
        #endif
        std::vector<int> dpMemo((1 << PRIMES_NUMS_LESS_THAN30), 0);
        dpMemo[0] = 1;
        for (int num = 2; num < MAX_VAL; num++) {
            int mask = masks[num];
            if (0 == cnts[num] || -1 == mask) {
                continue;
            }
            for (int idx = 0; idx < dpMemo.size(); idx++) {
                if (0 == (mask & idx)) {
                    dpMemo[mask | idx] = (dpMemo[mask | idx] + (long long)(cnts[num]) * dpMemo[idx]) % MOD;
                }
            }
        }
        int ans = std::accumulate(std::begin(dpMemo) + 1, std::end(dpMemo), 0,
                                  [] (int s, int n) {
                                      return (s + n) % MOD;
                                  }
                                 );
        #ifdef DEBUG
        std::cout << "uncount 1, the res is: " << ans << "\n";
        #endif
        while (cnts[1]-- > 0) {
            ans = (ans << 1) % MOD;
        }
        return ans;
    }
private:
    void initMask() {
        #ifdef DEBUG
        std::cout << "init masks\n";
        #endif
        for (int num = 0; num < MAX_VAL; num++) {
            for (int idx = 0; idx < primes.size(); idx++) {
                if (0 == num % 4 || 0 == num % 9 || 25 == num) {
                    masks[num] = -1;
                } else if (0 == num % primes[idx]) {
                    masks[num] |= (1 << idx);
                }
            }
        }
    }

private:
    static int const MOD = 1e9 + 7;
    static int const MAX_VAL = 31;
    static int const PRIMES_NUMS_LESS_THAN30 = 10;
    static std::array<int, PRIMES_NUMS_LESS_THAN30> primes;
    static std::array<int, MAX_VAL> masks;
};
std::array<int, Solution::PRIMES_NUMS_LESS_THAN30> Solution::primes = {{2, 3, 5, 7, 11, 13, 17, 19, 23, 29}};
std::array<int, Solution::MAX_VAL> Solution::masks{};
