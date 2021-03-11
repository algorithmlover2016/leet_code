#include "../../head.h"

#define TEST_MAIN
class  Solution {
public:
    std::vector<int> twoSum(std::vector<int> const & nums, int target) {
        int const numsSize = nums.size();
        if (JUST_ONE >= numsSize) {
            return {};
        }
        std::unordered_map<int, int> num2Idx;
        for (int idx = 0; idx < numsSize; idx++) {
            num2Idx[nums[idx]] = idx;
        }

        for (int idx = 0; idx < numsSize; idx++) {
            int diff = target - nums[idx];
            if (num2Idx.find(diff) != num2Idx.end()) {
                return {num2Idx[diff], idx};
            }
        }

        return {};
    }
private:
    static int const JUST_ONE = 1;
};


#ifdef TEST_MAIN
#define PRINT_TO_SCREEN

int main() {
    Solution obj;
    std::vector<int> nums{{2, 7, 9 ,10}};
    std::vector<int> ans = obj.twoSum(nums, 9);

#ifdef PRINT_TO_SCREEN
    for (int const idx : ans) {
        std::cout << idx << "\t";
    }
    std::cout << "\n";
#endif

    std::vector<int> rightAns{{0, 1}};
    std::sort(ans.begin(), ans.end());
    assert(ans == rightAns);

    std::cout << "TEST SUCCESSFULLY" << std::endl;
    return 0;

}
#endif
