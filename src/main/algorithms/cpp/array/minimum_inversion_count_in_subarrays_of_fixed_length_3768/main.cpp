#define __DEBUG__
#include "../../head.h"
#include "solution.cpp"
int main() {
    Solution sln;
    std::vector<int> nums = {3,1,2,5,4};
    int k = 4;
    auto res = sln.minInversionCount(nums, k);
    std::cout << res << std::endl;
    return 0;
}