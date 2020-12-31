#include "../../head.h"


// #define DEBUG
class Solution {
public:
    int findMinMoves(std::vector<int> const & machines) {
        // plagiarizing from https://blog.csdn.net/weixin_39350124/article/details/91485753
        if (machines.empty()) {
            return 0;
        }
        int const machinesSize = machines.size();
        int const sum = std::accumulate(machines.begin(), machines.end(), 0);
        if (0 != sum % machinesSize) {
            return -1;
        }
        int const average = sum / machinesSize;

        #ifdef DEBUG
        std::cout << "sum, average: " << sum << ",\t" << average << "\n";
        #endif

        int leftSum = 0;
        int rightSum = sum;
        int ans = 0;
        for (int idx = 0; idx < machinesSize; idx++) {
            rightSum -=  machines[idx];
            // *Move > 0 means need move out
            // *Move < 0 means need move in
            // at any index idx, we can move into idx index at same time,
            // but we can't move out simultaneousely
            int leftMove = leftSum - idx * average;
            int rightMove = rightSum - (machinesSize - 1 - idx) * average;
            #ifdef DEBUG
            std::cout << "leftMove, rightMove: " << leftMove << ",\t" << rightMove
                << "\tat idx: " << idx << "\n";
            #endif
            if (rightMove < 0 && leftMove < 0) {
                ans = std::max(ans, std::abs(leftMove + rightMove));
            } else {
                ans = std::max(ans, std::max(std::abs(leftMove), std::abs(rightMove)));
            }

            #ifdef DEBUG
            std::cout << "ans: " << ans << "\n";
            #endif
            leftSum += machines[idx];
        }
        return ans;
    }
};
