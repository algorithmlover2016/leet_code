#include "../../head.h"


// #define DEBUG
class Solution {
public:
    long long kSum(std::vector<int> nums, int k) {
        assert((!nums.empty()) && (k > 0));
        // plagiarizing from https://leetcode.com/problems/find-the-k-sum-of-an-array/solutions/2457384/priority-queue-c/
        // and https://leetcode.com/problems/find-the-k-sum-of-an-array/solutions/2465961/decreasing-subsequence-sums/

        // sort the input numbers in increasing direction
        std::sort(std::begin(nums), std::end(nums), [](int left, int right) {return std::abs(left) < std::abs(right);});

        // get the maximum sum which consists of positive numbers.
        long long int maximumSum = std::accumulate(std::begin(nums), std::end(nums), 0LL, [](long long int sum, int num) { return sum += std::max(num, 0);});
        #ifdef DEBUG
        std::cout << "maximumSum: " << maximumSum << "\n";
        #endif
        long long ans = maximumSum;

        std::priority_queue<std::pair<long long int, int>> maxHeap;
        maxHeap.push(std::make_pair(maximumSum - std::abs(nums[0]), 0));
        while (--k) {
            auto [curMaxSum, idx] = maxHeap.top(); maxHeap.pop();
            ans = curMaxSum;
            if (idx + 1 < nums.size()) {
                // add the current element into sum, and then we can consider remove the previous one. So the difference will be nums[idx + 1] - nums[idx]
                maxHeap.push(std::make_pair(curMaxSum - std::abs(nums[idx + 1]), idx + 1));
                maxHeap.push(std::make_pair(curMaxSum - std::abs(nums[idx + 1]) + std::abs(nums[idx]), idx + 1));
            }
        }
        return ans;
    }
};