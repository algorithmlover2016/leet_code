#include "../../head.h"


// #define DEBUG
class SolutionON3 {
public:
    std::vector<int> maxSumOfThreeSubarrays(std::vector<int> const & nums, int k) {
        int const numsSize = nums.size();
        
        int lSum = 0;
        std::vector<int> diffKSum(numsSize, 0);
        for (int idx = 0; idx < numsSize; idx++) {
            lSum += nums[idx] - (idx >= k ? nums[idx - k] : 0);
            diffKSum[idx] = lSum;
            #ifdef DEBUG
            std::cout << idx << ", " << diffKSum[idx] << "\t";
            #endif
        }
        #ifdef DEBUG
        std::cout << "\n";
        #endif

        int ans = INT_MIN;
        std::vector<int> ansIdx;
        for (int idx = k - 1; idx < numsSize - 2 * k; idx++) {
            for (int next = idx + k; next < numsSize - k; next++) {
                for (int right = next + k; right < numsSize; right++) {
                    int curAns = diffKSum[idx] + diffKSum[next] + diffKSum[right];
                    #ifdef DEBUG
                    std::cout << idx << ", " << next << ", " << right << ":\t" << curAns << "\n";
                    #endif
                    if (ans < curAns) {
                        ans = curAns;
                        ansIdx = std::vector<int>{{idx - k + 1, next - k + 1, right - k + 1}};
                    }
                }
            }
        }
        return ansIdx;
    }
};

// #define DEBUG
class Solution {
public:
    std::vector<int> maxSumOfThreeSubarrays(std::vector<int> const & nums, int k) {
        // plagiarizing from https://leetcode.com/problems/maximum-sum-of-3-non-overlapping-subarrays/discuss/108231/C%2B%2BJava-DP-with-explanation-O(n)
        if (0 == k) {
            return {};
        }

        int const numsSize = nums.size();

        std::vector<int> preSums(numsSize + 1, 0);
        for (int idx = 0; idx < numsSize; idx++) {
            preSums[idx + 1] = preSums[idx] + nums[idx];
        }

        std::vector<int> posLeft(numsSize, 0);
        #ifdef DEBUG
        std::cout << "posLeft\n";
        #endif
        for (int idx = k, tot = preSums[k]; idx < numsSize; idx++) {
            if (preSums[idx + 1] - preSums[idx + 1 - k] > tot) {
                tot = preSums[idx + 1] - preSums[idx + 1 - k];
                posLeft[idx] = idx + 1 - k;
            } else {
                posLeft[idx] = posLeft[idx - 1];
            }
            #ifdef DEBUG
            std::cout << idx << ", " << posLeft[idx] << "\t";
            #endif
        }
        #ifdef DEBUG
        std::cout << "\n";
        #endif
        std::vector<int> posRight(numsSize, numsSize - k);

        #ifdef DEBUG
        std::cout << "posRight\n";
        #endif
        for (int idx = numsSize - k - 1, tot = preSums[numsSize] - preSums[numsSize - k];
             idx > -1; idx--) {
            if (preSums[idx + k] - preSums[idx] >= tot) {
                tot = preSums[idx + k] - preSums[idx];
                posRight[idx] = idx;
            } else {
                posRight[idx] = posRight[idx + 1];
            }
            #ifdef DEBUG
            std::cout << idx << ", " << posRight[idx] << "\t";
            #endif
        }
        #ifdef DEBUG
        std::cout << "\n";
        #endif

        std::vector<int> ansIdx;
        int ans = INT_MIN;
        for (int idx = k; idx <= numsSize - 2 * k; idx++) { // idx as the middle
            int left = posLeft[idx - 1];
            int right = posRight[idx + k];
            int curAns = preSums[left + k] - preSums[left] + preSums[idx + k] - preSums[idx] + preSums[right + k] - preSums[right];
            #ifdef DEBUG
            std::cout << left << ", " << idx << ", " << right << ": " << curAns << "\n";
            #endif
            if (curAns > ans) {
                #ifdef DEBUG
                std::cout << "rep curAns\n";
                #endif
                ans = curAns;
                ansIdx = {{left, idx, right}};
            }
        }
        return ansIdx;
    }
};
