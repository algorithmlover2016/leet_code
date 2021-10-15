#include "../../head.h"\n\n\n

class SolutionTLE {
public:
    int countRangeSum(std::vector<int> const & nums, int lower, int upper) {
        int const RowSize = nums.size();
        if (RowSize == 0) {
            return 0;
        }
        std::vector<std::vector<long>> dpMemo(RowSize, std::vector<long>(RowSize, INT_MIN));
        for (int row = 0; row < RowSize; row++) {
            dpMemo[row][row] = nums[row];
            for (int col = row + 1; col < RowSize; col++) {
                dpMemo[row][col] = dpMemo[row][col - 1] + nums[col];
            }
        }
        int ans = 0;
        for (int row = 0; row < RowSize; row++) {
            for (int col = row; col < RowSize; col++) {
                if (dpMemo[row][col] >= lower && dpMemo[row][col] <= upper)  {
                    ans++;
                }
            }
        }
        return ans;
    }
};

class SolutionTLE {
public:
    int countRangeSum(std::vector<int> const & nums, int lower, int upper) {
        int const RowSize = nums.size();
        if (RowSize == 0) {
            return 0;
        }
        std::vector<long> preSum(RowSize + 1, 0);
        for (int row = 0; row < RowSize; row++) {
            preSum[row + 1] = preSum[row] + nums[row];
        }
        int ans = 0;
        for (int row = 0; row < RowSize; row++) {
            for (int col = 0; col <= row; col++) {
                long curSum = preSum[row + 1] - preSum[col];
                if (curSum >= lower && curSum <= upper)  {
                    ans++;
                }
            }
        }
        return ans;
    }
};

class Solution {
public:
    int countRangeSum(std::vector<int> const & nums, int lower, int upper) {
        // plagiarizing from https://leetcode.com/problems/count-of-range-sum/discuss/77991/Short-and-simple-O(n-log-n)
        int const RowSize = nums.size();
        if (RowSize == 0) {
            return 0;
        }
        std::vector<long> preSum(RowSize + 1, 0);
        for (int row = 0; row < RowSize; row++) {
            preSum[row + 1] = preSum[row] + nums[row];
        }
        return mergeSort(preSum, 0, preSum.size(), lower, upper);
    }
private:
    int mergeSort(std::vector<long> & preSum, int lo, int high, int const lower, int const upper) {
        // the range is [low, high) which means max(high) == preSumSize
        int const preSumSize = preSum.size();
        if (high > preSumSize) {
            return 0;
        }
        int mid = (lo + high) / 2;
        if (mid == lo) {
            return 0;
        }
        int cnt = mergeSort(preSum, lo, mid, lower, upper) + mergeSort(preSum, mid, high, lower, upper);
        int mostLeftRightIdx = mid;
        int mostRightRightIdx = mid;
        for (int idx = lo; idx < mid; idx++) {
            int leftPart = preSum[idx];
            while (mostLeftRightIdx < high && preSum[mostLeftRightIdx] - leftPart < lower) {
                mostLeftRightIdx++;
            }
            while (mostRightRightIdx < high && preSum[mostRightRightIdx] - leftPart <= upper) {
                mostRightRightIdx++;
            }
            cnt += mostRightRightIdx - mostLeftRightIdx;
        }
        // because we have using the all elements in preSum from lo(included) to high(excluded),
        // even if we sorted the preSum from lo to high, it will not change the relative order in next mergeSort.
        auto preSumBegin = std::begin(preSum);
        std::sort(preSumBegin + lo, preSumBegin + high);
        return cnt;
    }
};
