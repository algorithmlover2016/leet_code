#include "../../head.h"


class Solution {
public:
    int minSwap(std::vector<int> const & A, std::vector<int> const & B) {
        // copying from https://leetcode.com/problems/minimum-swaps-to-make-sequences-increasing/discuss/119835/Java-O(n)-DP-Solution
        // I just want to reimplement it
        if (A.size() < 2) {
            return 0;
        }
        int swapNum = 1, fixNum = 0;
        // int tmpSwap = 0;
        // the first element, if change, swap = 1 else fix = 0;
        for (int index = 1; index < A.size(); index++) {
            if ((A[index - 1] >= B[index]) || (B[index - 1] >= A[index])) {
                // if swap index, must swap index - 1
                // else not swap index
                fixNum = fixNum;
                swapNum += 1;
            } else if ((A[index - 1] >= A[index]) || (B[index - 1] >= B[index])) {
                // must swap index, and can not need change index - 1
                // or swap index - 1 and can not change index - 1
                int tmpSwap = swapNum;
                swapNum = fixNum + 1;
                fixNum = tmpSwap;
            } else {
                // it's ok to satisfy the need
                fixNum = std::min(swapNum, fixNum);
                // if (fixNum > swapNum) {
                //     fixNum = swapNum;
                // }
                swapNum = fixNum + 1;
            }
        }

        return std::min(swapNum, fixNum);
    }
};

class Solution {
public:
    int minSwap(std::vector<int> const & A, std::vector<int> const & B) {
        const size_t n = A.size();
        std::vector<int> swap(n, n), no_swap(n, n);
        swap[0] = 1;
        no_swap[0] = 0;
        for (size_t i = 1; i < n; ++i) {
            if (A[i] > A[i - 1] && B[i] > B[i - 1]) {
                // If we swap position i, we need to swap position i - 1.
                swap[i] = swap[i - 1] + 1;

                // If we don't swap position i , we should not swap position i - 1.
                no_swap[i] = no_swap[i - 1];
            }

            if (A[i] > B[i - 1] && B[i] > A[i - 1]) {
                // If we swap position i, we should not swap position i - 1.
                swap[i] = std::min(swap[i], no_swap[i - 1] + 1);

                // If we don't swap position i, we should swap position i - 1.
                no_swap[i] = std::min(no_swap[i], swap[i - 1]);
            }
        }

        return std::min(swap.back(), no_swap.back());
    }
};
