#include "../../head.h"


// #define DEBUG
class SolutionTLE {
public:
    int countSpecialSubsequences(std::vector<int> const & nums) {
        int const numsSize = nums.size();
        if (MIN_SIZE > numsSize) {
            return 0;
        }
        int ans = 0;
        ans +=  backTrackingHelp(nums, 0, numsSize, 0, 0);
        ans %= MOD;
        return ans;
    }
private:
    int backTrackingHelp(std::vector<int> const & nums, int start, int end, int const pre, int const mask) {
        #ifdef DEBUG
        std::cout << "start: " << start << ", pre, mask: " << pre << ", " << mask << "\n";
        #endif
        if (start == end) {
            #ifdef DEBUG
            std::cout << "return back\n";
            #endif
            if (mask == 7) {
                return 1;
            } else {
                return 0;
            }
        }
        
        int ans = 0;
        ans += backTrackingHelp(nums, start + 1, end, pre, mask);
        ans %= MOD;
        
        if (pre > nums[start]) {
            return ans;
        }
                
        ans += backTrackingHelp(nums, start + 1, end, nums[start], (mask | (1 << nums[start])));
        ans %= MOD;
        return ans;

    }
private:
    static int const MIN_SIZE = 3;
    static int const MOD = 1e9 + 7;
};

// #define DEBUG
class Solution {
public:
    int countSpecialSubsequences(std::vector<int> const & nums) {
        // plagiarizing from https://leetcode.com/problems/count-number-of-special-subsequences/discuss/1375485/JavaC%2B%2BPython-DP-Solution
        int const numsSize = nums.size();
        if (MIN_SIZE > numsSize) {
            return 0;
        }
        std::vector<int> dpSuffix(MIN_SIZE, 0);
        for (int const num : nums) {
            dpSuffix[num] = ((dpSuffix[num] /*replace the last number with num*/ + dpSuffix[num] /* append num to the existing seqs*/) % MOD +
                            (0 < num ? dpSuffix[num - 1] /* num can be appended to the seqs which is ended with num - 1*/ : 1 /*0 can be used to generate a new seq*/)) % MOD;

        }

        return dpSuffix[MIN_SIZE - 1];
    }
private:
    static int const MIN_SIZE = 3;
    static int const MOD = 1e9 + 7;
};

// #define DEBUG
class Solution {
public:
    int countSpecialSubsequences(std::vector<int> const & nums) {
        // plagiarizing from https://leetcode.com/problems/count-number-of-special-subsequences/discuss/1375541/Top-Down-and-Bottom-Up-DP
        int const numsSize = nums.size();
        if (MIN_SIZE > numsSize) {
            return 0;
        }
        std::vector<long long> dpSuffix(MIN_SIZE + 1, 0);
        dpSuffix[0] = 1;
        for (int const num : nums) {
            dpSuffix[num + 1] = (dpSuffix[num + 1] /*replace the last number with num*/ + dpSuffix[num + 1] /* append num to the existing seqs*/ + dpSuffix[num]) % MOD;
        }

        return dpSuffix[MIN_SIZE];
    }
private:
    static int const MIN_SIZE = 3;
    static int const MOD = 1e9 + 7;
};