#include "../../head.h"


class Solution {
public:
    bool isSelfCrossing(std::vector<int> const & x) {
        // plagiarizing idea from https://leetcode.com/problems/self-crossing/discuss/79131/Java-Oms-with-explanation
        // first: after 4 step, the idx cross with the idx - 3
        // second: after 5 step, the idx is at the same line with idx - 4 and meet the point;
        // third: after 6 step, the idx is crossing with the idx - 5
        int const xSize = x.size();

        if (AT_LEATST_LEN > xSize) {
            return false;
        }

        for (int idx = AT_LEATST_LEN - 1; idx < xSize; idx++) {
            // first condition
            if (x[idx] >= x[idx - 2] && x[idx - 1] <= x[idx - 3]) {
                return true;
            }
            if (idx >= 4) {
                if (x[idx] >= x[idx - 2] - x[idx - 4] && x[idx - 1] == x[idx - 3]) {
                    return true;
                }
            }
            if (idx >= 5) {
                int crossLine = x[idx - 2] - x[idx - 4];
                if (0 <= crossLine && x[idx] >= crossLine &&
                        x[idx - 1] >= x[idx - 3] - x[idx - 5] && x[idx - 1] <= x[idx - 3]) {
                    return true;
                }
            }
        }
        return false;
    }
private:
    static int const AT_LEATST_LEN = 4;
    static int const DIRECTON_CYCLE_DIFF = 4;
};
