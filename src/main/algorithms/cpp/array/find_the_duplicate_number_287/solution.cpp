#include "../../head.h"


// the solution, n + 1 elements, and except the duplicate one, the other(1-n) must exist
class Solution {
public:
    int findDuplicate(std::vector<int> const & nums) {
        if (nums.empty()) {
            return -1;
        }
        int res = 0;
        for (int index = 1; index < nums.size(); index++) {
            res ^= index ^ nums[index];
        }
        return res ^ nums[0];
    }
};

class Solution {
public:
    int findDuplicate(std::vector<int> const & nums) {
        if (nums.empty()) {
            return -1;
        }
        // already go forward one step
        int slow = nums[0], fast = nums[slow];
        while (slow != fast) {
            // std::cout << "\nfast, slow: " << fast << "\t" << slow << "\t";
            fast = nums[nums[fast]];
            slow = nums[slow];
        }

        fast = 0;
        while (fast != slow) {
            // std::cout << "\nfast, slow: " << fast << "\t" << slow << "\t";
            fast = nums[fast];
            slow = nums[slow];
        }
        return fast;
    }
};
