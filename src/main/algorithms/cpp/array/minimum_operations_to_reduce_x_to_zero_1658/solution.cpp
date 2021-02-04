#include "../../head.h"


#define DEBUG
class SolutionWrongAns {
public:
    int minOperations(std::vector<int> const & nums, int const x) {
        if (nums.empty()) {
            return JUST_ZERO == x ? 0 : CANNOT_FIND_ANS;
        }
        int const numsSize = nums.size();
        int ans = -1;
        dfs(nums, x, 0, numsSize - 1, ans);
        return ans;
    }
    int dfs(std::vector<int> const & nums,
            int target, int start, int end, int & ans) {
        if (target < JUST_ZERO) {
            return CANNOT_FIND_ANS;
        }
        #ifdef DEBUG
        std::cout << "start, end: " << start << ",\t" << end << "\n";
        #endif
        if (JUST_ZERO == target) {
            return 0;
        }
        if (start == end) {
            return target == nums[start] ? 1 : CANNOT_FIND_ANS;
        }
        int leftAns = dfs(nums, target - nums[start], start + 1, end);
        int rightAns = dfs(nums, target - nums[end], start, end - 1);
        if (CANNOT_FIND_ANS == leftAns && CANNOT_FIND_ANS == rightAns) {
            return CANNOT_FIND_ANS;
        } else if (CANNOT_FIND_ANS == leftAns) {
            return rightAns;
        } else if (CANNOT_FIND_ANS == rightAns){
            return leftAns;
        } else {
            return 1 + std::min(leftAns, rightAns);
        }

    }
private:
    static int const JUST_ZERO = 0;
    static int const CANNOT_FIND_ANS = -1;
};

// #define DEBUG
class Solution {
public:
    int minOperations(std::vector<int> const & nums, int const x) {
        // plagiairizing idea from https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/discuss/935935/Java-Detailed-Explanation-O(N)-Prefix-SumMap-Longest-Target-Sub-Array
        int const numsSize = nums.size();
        int target = -x;
        for (int const num : nums) {
            target += num;
        }
        #ifdef DEBUG
        std::cout << "transfer to: " << target << "\n";
        #endif
        if (JUST_ZERO == target) {
            return numsSize;
        }

        int preSum = 0;
        int ans = INIT_MIN;
        std::unordered_map<int, int> sum2Idx;
        sum2Idx.emplace(0, -1);
        for (int idx = 0; idx < nums.size(); idx++) {
            preSum += nums[idx];
            if (sum2Idx.find(preSum - target) != sum2Idx.end()) {
                #ifdef DEBUG
                std::cout << "find: " << idx - sum2Idx[preSum - target] << "\n";
                #endif
                ans = std::max(ans, idx - sum2Idx[preSum - target]);
            }
            sum2Idx.emplace(preSum, idx);
        }
        return INIT_MIN == ans ? CANNOT_FIND_ANS : numsSize - ans;
    }
private:
    static int const INIT_MIN = -1;
    static int const JUST_ZERO = 0;
    static int const CANNOT_FIND_ANS = -1;
};

class SolutionDirectCompute {
public:
    int minOperations(std::vector<int> const & nums, int const x) {
        // plagiairizing idea from https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/discuss/935956/C%2B%2B-O(n)-Two-Sum-and-Hash-Map
        int const numsSize = nums.size();

        std::unordered_map<int, int> sum2Idx;
        sum2Idx.emplace(0, 0);
        for (int idx = 0, preSum = 0; idx < numsSize && preSum <= x; idx++) {
            preSum += nums[idx];
            sum2Idx.emplace(preSum, idx + 1);
        }

        #ifdef DEBUG
        #endif

        int ans = INIT_MAX;
        for (int rIdx = numsSize - 1, postFixSum = 0; rIdx > -1 && postFixSum <= x; rIdx--) {
            auto leftIt = sum2Idx.find(x - postFixSum);
            // we just record the rIdx + 1 to the end (numsSize - 1) inclusive
            if (leftIt != sum2Idx.end() && rIdx + 1 >= leftIt->second) {
                // ans = std::min(ans, leftIt->second + 1 + numsSize - 1 - rIdx);
                ans = std::min(ans, leftIt->second + numsSize - 1 - rIdx);
            }
            postFixSum += nums[rIdx];
        }
        return INIT_MAX == ans ? CANNOT_FIND_ANS : ans;
    }
private:
    static int const INIT_MAX = 1e6;
    static int const JUST_ZERO = 0;
    static int const CANNOT_FIND_ANS = -1;
};

class SolutionTwoSum {
public:
    int minOperations(std::vector<int> const & nums, int const x) {
        // plagiairizing idea from https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/discuss/935956/C%2B%2B-O(n)-Two-Sum-and-Hash-Map
        int const numsSize = nums.size();

        int sum = std::accumulate(std::begin(nums), std::end(nums), 0);

        int ans = INIT_MAX;
        int left = 0, right = 0;
        while (left <= right) {
            if (x <= sum) {

                if (x == sum) {
                    ans = std::min(ans, left + numsSize - right);
                }

                if (right < numsSize) {
                    sum -= nums[right++];
                } else {
                    break;
                }

            } else {
                sum += nums[left++];
            }
        }

        return INIT_MAX == ans ? CANNOT_FIND_ANS : ans;
    }
private:
    static int const INIT_MAX = 1e6;
    static int const JUST_ZERO = 0;
    static int const CANNOT_FIND_ANS = -1;
};
