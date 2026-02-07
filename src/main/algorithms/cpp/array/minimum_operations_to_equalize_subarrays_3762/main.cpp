#define __DEBUG__
#define LESS_FIRST
#undef LESS_FIRST
#include "../../head.h"
#include "./solution.cpp"

int main () {
    Solution solution;
    vector<int> nums = {1,4,7};
    int k = 3;
    vector<vector<int>> queries = {{0,0}};
    vector<long long> ans = solution.minOperations(nums, k, queries);
    for (long long val : ans) {
        std::cout << val << ", ";
    }
    return 0;
}