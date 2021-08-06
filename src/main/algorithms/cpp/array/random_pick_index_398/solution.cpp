#include "../../head.h"


class Solution {
public:
    // reference to https://leetcode.com/problems/random-pick-index/discuss/88071/C%2B%2B_Time%3A-O(n)-Space%3A-O(n)_116ms_96.41_with-clear-explanation-by-probability and
    // https://leetcode.com/problems/random-pick-index/discuss/88072/Simple-Reservoir-Sampling-solution
    Solution(std::vector<int> const & nums) {
        nums_ = nums;
    }

    int pick(int const target) {
        int nextN = 0;
        int ans = -1;
        for (int idx = 0; idx < nums_.size(); idx++) {
            if (target != nums_[idx]) {
                continue;
            }
            nextN++;
            // rand can be replaced by generator c++11
            if (0 == rand() % nextN) {
                ans = idx;
            }
        }
        return ans;
    }
private:
    std::vector<int> nums_;
};
