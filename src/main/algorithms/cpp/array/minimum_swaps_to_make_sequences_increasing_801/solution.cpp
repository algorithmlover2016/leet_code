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
