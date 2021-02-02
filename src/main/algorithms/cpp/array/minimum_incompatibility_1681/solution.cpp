#include "../../head.h"


#define DEBUG
class SolutionWrongAns {
public:
    int minimumIncompatibility(std::vector<int> const & nums, int k) {
        // using a map
        int const numsSize = nums.size();
        if (JUST_ZERO != numsSize % k) {
            return -1;
        }
        int const groupSize = numsSize / k;
        std::map<int, int> valCnt;

        for (auto const num : nums) {
            valCnt[num]++;
            if (valCnt[num] > k) {
                return -1;
            }
        }

        int ans = 0;
        while (!valCnt.empty()) {
            int curGroupSize = 0;
            int curDiff = 0;
            auto it = valCnt.begin();
            int begin = it->first;

            #ifdef DEBUG
            std::cout << "start: " << begin << "\t";
            #endif

            while (curGroupSize++ < groupSize) {
                curDiff = it->first - begin;
                #ifdef DEBUG
                std::cout << it->first << "\t";
                #endif
                auto pre = it++;
                if (JUST_ZERO == --pre->second) {
                    valCnt.erase(pre);
                }
                if (it == valCnt.end()) {
                    it = valCnt.begin();
                }
            }
            #ifdef DEBUG
            std::cout << "\n";
            #endif

            ans += curDiff;
        }
        return ans;

    }
    private:
    static int const JUST_ZERO = 0;
};

// #define DEBUG
#define MINUS_STEP_HARD_TO_UNDERSTAND
class Solution {
public:
    int minimumIncompatibility(std::vector<int> const & nums, int k) {
        // plagiarizing idea from https://leetcode.com/problems/minimum-incompatibility/discuss/961451/C%2B%2B-DP-with-explanation-and-comments
        int const numsSize = nums.size();
        if (JUST_ZERO != numsSize % k) {
            return -1;
        }
        int const groupSize = numsSize / k;
        std::vector<std::pair<int, int>> bMaps;
        getMaps(nums, groupSize, bMaps);

        std::vector<int> dpMemo(1 << numsSize, INIT_FLAG);
        dpMemo[0] = 0;
        for (int bIdx = 0; bIdx < dpMemo.size(); bIdx++) {
            if (JUST_ZERO != __builtin_popcount(bIdx) % groupSize) {
                continue;
            }
            for (auto const & [bitMap, val] : bMaps) {
                if (bitMap > bIdx) {
                    continue;
                }
                if (bitMap != (bitMap & bIdx)) {
                    continue;
                }
                #ifdef MINUS_STEP_HARD_TO_UNDERSTAND
                int preBIdx = bIdx - bitMap;
                #else
                int preBIdx = bIdx & (~bitMap);
                #endif
                if (INIT_FLAG == dpMemo[preBIdx]) {
                    continue;
                }
                if (INIT_FLAG == dpMemo[bIdx]) {
                    dpMemo[bIdx] = dpMemo[preBIdx] + val;
                } else {
                    dpMemo[bIdx] = std::min(dpMemo[bIdx], dpMemo[preBIdx] + val);
                }
            }
        }
        return dpMemo.back();
    }

    void getMaps(std::vector<int> const & nums,
                 int const groupSize,
                 std::vector<std::pair<int, int>> & bMaps) {
        int const numsSize = nums.size();
        int const BComb = 1 << numsSize;
        for (int bIdx = 0; bIdx < BComb; bIdx++) {
            if (__builtin_popcount(bIdx) != groupSize) {
                continue;
            }

            int visited = 0;
            int groupMax = INIT_MIN;
            int groupMin = INIT_MAX;
            bool canTaken = true;

            for (int idx = 0; idx < numsSize; idx++) {
                if (JUST_ZERO == (bIdx & (1 << idx))) {
                    continue;
                }
                if (visited & (1 << nums[idx])) {
                    canTaken = false;
                    break;
                }

                visited |= 1 << nums[idx];
                groupMin = std::min(groupMin, nums[idx]);
                groupMax = std::max(groupMax, nums[idx]);
            }
            if (canTaken) {
                // #ifdef DEBUG
                // std::bitset<32> bitVal(bIdx);
                // std::cout << "bit, val: " << bitVal << ",\t" << groupMax - groupMin << "\n";
                // #endif
                bMaps.emplace_back(bIdx, groupMax - groupMin);
            }
        }
        #ifdef DEBUG
        // std::cout << "combSize: " << __func__ << "\n";
        std::cout << "combSize: " << bMaps.size() << "\n";
        #endif
    }

    private:
    static int const JUST_ZERO = 0;
    static int const INIT_MIN = INT_MIN;
    static int const INIT_MAX = INT_MAX;
    int const INIT_FLAG = -1;
};

class SolutionUpgrade {
public:
    int minimumIncompatibility(std::vector<int> const & nums, int k) {
        const int n = nums.size(), m = n/k;
        const vector<int> bmap = getMap(nums, m);

        std::vector<int> dp(1 << n, -1);
        dp[0] = 0;
        for (int b = 0; b < (1<<n); ++b) {
            if (__builtin_popcount(b) % m != 0) continue;
			// Reference: https://cp-algorithms.com/algebra/all-submasks.html
            for (int tb = b; tb; tb = (tb-1)&b) {
                if (bmap[tb] == -1) {
                    continue;
                }
                if (dp[b-tb] == -1) {
                    continue;
                }
                if (dp[b] == -1) {
                    dp[b] = dp[b-tb]+bmap[tb];
                } else {
                    dp[b] = min(dp[b], dp[b-tb]+bmap[tb]);
                }
            }
        }
        return dp.back();
    }

private:
    // Generates a vetor v where:
    //   v[b] = the incompatibility of bitmask b, if b represents a valid subset of size m
    //   v[b] = -1, if b is not a valid subset of size m
    std::vector<int> getMap(std::vector<int> const & nums, int m) {
	    const int n = nums.size();
        std::vector<int> ans(1<<n, -1);
        for (int b = 0; b < (1<<n); ++b) {
            if (__builtin_popcount(b) != m) {
                continue;
            }

            int vis = 0;
            int mx = 0, mn = 16;
            bool is_good = true;
            for (int i = 0; i < n; ++i) {
                if ((b & (1<<i)) == 0) {
                    continue;
                }
                if (vis & (1<<nums[i])) {
                    is_good = false;
                    break;
                }
                vis |= (1<<nums[i]);
                mx = max(mx, nums[i]);
                mn = min(mn, nums[i]);
            }
            if (!is_good) {
                continue;
            }
            ans[b] = mx-mn;
        }
        return ans;
    }
};
