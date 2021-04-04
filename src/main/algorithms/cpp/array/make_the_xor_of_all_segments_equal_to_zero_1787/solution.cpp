#include "../../head.h"


class Solution {
public:
    int minChanges(std::vector<int> const & nums, int k) {
        // plagiarizing from https://leetcode.com/problems/make-the-xor-of-all-segments-equal-to-zero/discuss/1097537/Explanation-of-DP-Approach-%2B-Code-(C%2B%2B)
        // I can analysis that the cycle period of the numbers will be k by myself
        // for i from 0(included) to k(excluded), the left numbers,
        // eg, nums[i + n * k] (n = 0, 1, ..., nums.size() / k) must have to keep with with nums[i],
        int const numsSize = nums.size();
        std::vector<std::vector<int>> freq(k, std::vector<int>(MAX_VAL, 0));
        for (int idx = 0; idx < numsSize; idx++) {
            // static the cnt
            freq[idx % k][nums[idx]]++;
        }

        std::vector<std::vector<int>> dpMemo(k + 1, std::vector<int>(MAX_VAL, MAX_NEED_CHANGE));
        // if nums.empty() = true and the res will be zero
        dpMemo[0][0] = 0;
        int preMin = 0;

        for (int idx = 0; idx < k; idx++) {
            int setNum = (numsSize - idx + k - 1) / k;
            // int setNum = (numsSize / k) + (((numsSize % k) > idx) ? 1 : 0);
            int nextPreMin = MAX_NEED_CHANGE;
            for (int target = 0; target < MAX_VAL; target++) {
                // the elements that z % k == idx % k == idx;
                for (int z = idx; z < numsSize; z += k) {
                    // we use nums[z]
                    int nextTarget = target ^ nums[z];
                    if (nextTarget < MAX_VAL /*because nums[i] < MAX_VAL, the judge will always be true*/) {
                        dpMemo[idx + 1][nextTarget] = std::min(dpMemo[idx + 1][nextTarget], dpMemo[idx][target] + setNum - freq[idx][nums[z]]);
                    }
                }

                // if we don't change the target, which means that we change nums[z] to let the xor result to be target
                dpMemo[idx + 1][target] = std::min(dpMemo[idx + 1][target], setNum + preMin);
                nextPreMin = std::min(nextPreMin, dpMemo[idx + 1][target]);
            }
            preMin = nextPreMin;
        }
        return dpMemo[k][0];
    }
private:
    int const MAX_NEED_CHANGE = 2e3; // because the problem limit the nums.size() not larger than 2000;
    static int const MAX_VAL = 1025;
};


class Solution {
public:
    int minChanges(std::vector<int> const & v, int k) {
        // plagiarizing from https://leetcode.com/problems/make-the-xor-of-all-segments-equal-to-zero/discuss/1099112/C%2B%2B-An-easy-solution-with-detailed-explanation-to-a-really-hard-problem
        int n = v.size();

        // freq[i][x] = frequency of the number x at position i where i in [0, k - 1]
        std::vector<std::vector<int> > freq(k, std::vector<int>(1024, 0));
        /* dp[i][j] = minimum total number of elements we need to change from index 0 to i so that
           the xor of the subarray from index 0 to i is equal to j */
        std::vector<std::vector<int> > dp(k, std::vector<int>(1024, n + 1));
        // numsAtPosition[i] = set of unique numbers at position i where i in [0, k - 1]
        std::unordered_set<int> numsAtPosition[k];

        for (int i = 0; i < n; i++) {
            int position = i % k;
            freq[position][v[i]]++;
            numsAtPosition[position].insert(v[i]);
        }

        int bestUptoLast = 0;

        for (int i = 0; i < k; i++) { // this loop runs k times
            // how many i indices exist in the array
            int cntOfPos = n / k + (((n % k) > i) ? 1 : 0);

            // will track best value at i
            int bestAti = n + 1;

            // find the best way to make the xor sum equal to j from index 0 to i
            for(int j = 0; j < 1024; j++) { // this loop runs 1024 times
                if(i == 0) {
                    dp[i][j] = cntOfPos - freq[i][j];
                } else {
                    // iterate over all numbers that occur at index i
                    for (auto x : numsAtPosition[i]) { // this loop runs n/k times
                        dp[i][j] = std::min(dp[i][j], dp[i - 1][j ^ x] + cntOfPos - freq[i][x]);
                    }

                    // this will do for all the numbers that don't occur at index i
                    // we are changing all the numbers at index i with an arbitrary number that gives best result
                    dp[i][j] = std::min(dp[i][j], bestUptoLast + cntOfPos);
                }
                bestAti = std::min(bestAti, dp[i][j]);
            }
            bestUptoLast = bestAti;
        }
        return dp[k - 1][0];
    }
};

class Solution {
public:
    int res;
    int minChanges(std::vector<int> const & nums, int k) {
        std::vector<std::unordered_map<int, int>> freq(k);
        std::vector<int> max_save_suffix(k,0), max_save(k,0);

        // statistic the cnt of each element, and normalize index into first k elements
        for (int i = 0; i < nums.size(); i++) {
            freq[i%k][nums[i]]++;
        }

        // statistic the max cnt of appearence time of number in each index,
        for (int i = 0; i < k; i++) {
            for (auto & it : freq[i]) {
                max_save[i] = std::max(max_save[i], it.second);
            }
        }
        max_save_suffix[k-1] = max_save[k-1];
        for (int i = k - 2; i >= 0; i--) {
            // statistic the suffixSum (similar to preSum);
            max_save_suffix[i] = max_save_suffix[i + 1] + max_save[i];
        }
        // case 1:
        // if we don't care the value of one index, the max val of not changing values of nums;
        res = max_save_suffix[0] - *std::min_element(max_save.begin(),max_save.end());
		// case 2:
        DFS(0, 0, 0, freq, max_save_suffix);
        return nums.size() - res;
    }

private:
    void DFS(int i, int state, int cur_save,
            std::vector<std::unordered_map<int,int>> const & freq,
            std::vector<int> & max_save_suffix) {
        if (i == max_save_suffix.size() ){
            if (state == 0) {
                res = std::max(res, cur_save);
            }
        } else if (cur_save + max_save_suffix[i] > res) {
            for (auto it : freq[i]) {
                DFS(i + 1, state ^ it.first, cur_save + it.second, freq, max_save_suffix);
            }
        }
    }
};
