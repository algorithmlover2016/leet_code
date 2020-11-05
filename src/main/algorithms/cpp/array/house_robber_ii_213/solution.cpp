#include "../../head.h"


class SolutionWithOutCircle {
public:
    int rob(std::vector<int> const & nums) {
        int robCur = 0;
        int robNotCur = 0;
        for (int num : nums) {
            int tmpMax = std::max(robCur, robNotCur);
            robCur = robNotCur + num;
            robNotCur = tmpMax;
        }
        return robCur > robNotCur ? robCur : robNotCur;
    }
};


class Solution {
public:
    int rob(std::vector<int> const & nums) {
        // plagiarizing from https://leetcode.com/problems/house-robber-ii/discuss/59934/Simple-AC-solution-in-Java-in-O(n)-with-explanation and https://leetcode.com/problems/house-robber-ii/discuss/59921/9-lines-0ms-O(1)-Space-C%2B%2B-solution
        if (nums.empty()) {
            return 0;
        }
        int numsSize = nums.size();
        if (1 == numsSize) {
            return nums[0];
        }
        // break the circle at the end
        return std::max(rob(nums, 0, numsSize - 1), rob(nums, 1, numsSize));
    }
    int rob(std::vector<int> const & nums, int left, int right) {
        int robCur = 0;
        int robNotCur = 0;
        for (int index = left; index < right; index++) {
            int tmpMax = std::max(robCur, robNotCur);
            robCur = robNotCur + nums[index];
            robNotCur = tmpMax;
        }
        return robCur > robNotCur ? robCur : robNotCur;
    }
};
