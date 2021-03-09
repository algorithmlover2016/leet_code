#include "../../head.h"


#define DEBUG
class SolutionWrongAns {
public:
    int maxSubarraySumCircular(std::vector<int> const & A) {
        if (A.empty()) {
            return 0;
        }

        int start = 0;
        int sum = 0;
        int maxSum = sum;
        int const ASize = A.size();
        int const mASize = ASize * 2;
        for (int idx = 0; idx < mASize; idx++) {
            int modIdx = idx;
            if (idx >= ASize) {
                modIdx = idx - ASize;
                if (modIdx == start) {
                    break;
                }
            }
            if (sum > 0) {
                sum += A[modIdx];
            } else {
                sum = A[modIdx];
                start = modIdx;
            }
            #ifdef DEBUG
            std::cout << modIdx << "\t" << sum << "\n";
            #endif
            maxSum = std::max(maxSum, sum);
        }
        return maxSum;
    }
};

#define DEBUG
class Solution {
public:
    int maxSubarraySumCircular(std::vector<int> const & A) {
        // plagiarizing idea from https://leetcode.com/problems/maximum-sum-circular-subarray/discuss/178422/One-Pass
        if (A.empty()) {
            return 0;
        }

        int const ASize = A.size();
        int maxSum = INT_MIN;
        int minSum = INT_MAX;
        int totalSum = 0;
        int curMaxSum = 0;
        int curMinSum = 0;
        for (int idx = 0; idx < ASize; idx++) {
            curMaxSum = std::max(curMaxSum + A[idx], A[idx]);
            maxSum = std::max(maxSum, curMaxSum);
            curMinSum = std::min(curMinSum + A[idx], A[idx]);
            minSum = std::min(minSum, curMinSum);
            totalSum += A[idx];
        }
        return maxSum > 0 ? (std::max(maxSum, totalSum - minSum)) : maxSum;
    }
};
