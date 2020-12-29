#include "../../head.h"


class Solution {
public:
    int maxResult(std::vector<int> const & nums, int k) {
        // I can only  a idea that dp with k substructure
        // plagiarizing from https://www.youtube.com/watch?v=dHAsYTvbbj4
        if (nums.empty()) {
            return 0;
        }
        int const numsSize = nums.size();

        std::vector<int> dpMemo(numsSize, INT_MIN);
        std::deque<int> decQue; // record the max val of dpMemo with index

        dpMemo[0] = nums[0];
        decQue.emplace_back(0);

        for (int idx = 1; idx < numsSize; idx++) {
            if (decQue.front() < idx - k) {
                // the decQue.front() is out of sliding window
                // sliding window from idx - k to idx
                decQue.pop_front();
            }
            dpMemo[idx] = nums[idx] + dpMemo[decQue.front()];
            while (!decQue.empty() && dpMemo[decQue.back()] <= dpMemo[idx]) {
                decQue.pop_back();
            }
            decQue.emplace_back(idx);
        }
        return dpMemo.back();

    }
};

class SolutionBetter {
public:
    int maxResult(std::vector<int> const & nums, int k) {
        std::vector<int> dp(nums.size(), INT_MIN);
        dp[0] = nums[0];
        for(int i = 0; i < nums.size(); i++) {
            for(int j = 1; j + i < nums.size() && j <= k; j++) {
                dp[i + j]=std::max(dp[i + j], dp[i] + nums[i + j]);
                if (nums[i + j] >= 0) {
                    // when there is a bigger one, there is no need to compute the latter with dp[i],
                    // so we can break the loop
                    break;
                }
            }
        }
        return dp.back();
    }
};
