#include "../../head.h"


class SolutionTLE {
public:
    int maximumSum(std::vector<int> const & arr) {
        if (arr.empty()) {
            return 0;
        }
        int const arrSize = arr.size();
        std::vector<int> preSum(arrSize + 1, 0);
        for (int idx = 0; idx < arrSize; idx++) {
            preSum[idx + 1] = preSum[idx] + arr[idx];
        }
        int ans = INT_MIN;
        std::vector<std::vector<int>> dpMemo(arrSize, std::vector<int>(arrSize, INT_MAX));
        for (int idx = 0; idx < arrSize; idx++) {
            dpMemo[idx][idx] = arr[idx];
            ans = std::max(ans, arr[idx]);
            for (int next = idx + 1; next < arrSize; next++) {
                dpMemo[idx][next] = std::min(arr[next], dpMemo[idx][next - 1]);
                if (dpMemo[idx][next] >= 0) {
                    ans = std::max(ans, preSum[next + 1] - preSum[idx]);
                } else {
                    ans = std::max(ans, preSum[next + 1] - preSum[idx] - dpMemo[idx][next]);
                }
            }
        }
        return ans;
    }
};

class Solution {
public:
    int maximumSum(std::vector<int> const & arr) {
    // plagiarizing from https://leetcode.com/problems/maximum-subarray-sum-with-one-deletion/discuss/377397/Intuitive-Java-Solution-With-Explanation
        if (arr.empty()) {
            return INT_MIN;
        }
        int const arrSize = arr.size();
        std::vector<int> maxStartFromIdx(arrSize, 0); // include idx
        std::vector<int> maxEndToIdx(arrSize, 0); // include idx
        int ans = arr[0]; // because start from 1 not zero, so we need initialize ans with arr[0]
        maxEndToIdx[0] = arr[0];
        for (int idx = 1; idx < arrSize; idx++) {
            maxEndToIdx[idx] = std::max(arr[idx], maxEndToIdx[idx - 1] + arr[idx]);
            ans = std::max(ans, maxEndToIdx[idx]); // to include the only one element
        }
        maxStartFromIdx[arrSize - 1] = arr.back();
        for (int idx = arrSize - 2; idx > EXCLUDE_LEFT_MOST_IDX; idx--) {
            maxStartFromIdx[idx] = std::max(arr[idx], maxStartFromIdx[idx + 1] + arr[idx]);
        }

        for (int splitIdx = 1; splitIdx < arrSize - 1; splitIdx++) {
            ans = std::max(ans, maxEndToIdx[splitIdx - 1] + maxStartFromIdx[splitIdx + 1]);
        }
        return ans;
    }
private:
    static int const EXCLUDE_LEFT_MOST_IDX = -1;
};
