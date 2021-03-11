#include "../../head.h"


class Solution {
public:
    int removeDuplicates(std::vector<int> & nums) {
        if (nums.empty()) {
            return 0;
        }
        int start = 0;
        for (int idx = 1; idx < nums.size(); idx++) {
            if (nums[idx - 1] == nums[idx]) {
                continue;
            } else {
                nums[++start] = nums[idx];
            }
        }
        return ++start;

    }
};
