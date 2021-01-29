#include "../../head.h"


// #define PRE_REVERSE
class Solution {
public:
    std::vector<int> findDuplicates(std::vector<int> nums) {
        // plagiarizing idea from
        // https://leetcode.com/problems/find-all-duplicates-in-an-array/discuss/92395/C%2B%2B-beats-98
        // https://leetcode.com/problems/find-all-duplicates-in-an-array/discuss/92390/Python-O(n)-time-O(1)-space
        // https://leetcode.com/problems/find-all-duplicates-in-an-array/discuss/92387/Java-Simple-Solution
        std::vector<int> ans;
        for (int const num : nums) {
            int const idx = std::abs(num) - 1;
#ifdef PRE_REVERSE
            nums[idx] = -nums[idx];
            if (JUST_ZERO < nums[idx]) {
                ans.emplace_back(idx + 1);
            }
#else
            if (JUST_ZERO > nums[idx]) {
                ans.emplace_back(idx + 1);
            } else {
                nums[idx] = -nums[idx];
            }
#endif
        }
        return ans;
    }
private:
    static int const JUST_ZERO = 0;
};
