#include "../../head.h"


class Solution {
public:
    int minMoves(std::vector<int> const & nums, int limit) {
        // plagiarizing from https://leetcode.com/problems/minimum-moves-to-make-array-complementary/discuss/952773/PythonJava-simple-O(max(n-k))-method
        int const numsSize = nums.size();
        if (JUST_ONE >= numsSize) {
            return 0;
        }
        int const range = numsSize / 2;
        std::vector<int> delta(2 * limit + 2, 0); // record the diff when adding a pair
        for (int idx = 0; idx < range; idx++) {
            // each pair should be regard as a layer
            int left = nums[idx], right = nums[numsSize - 1 - idx];

            // when adding a pair, we assume the smallest range will add 2;
            // from 2 to std::min(left, right) (includive) will need 2 move change
            delta[2] += 2;

            // from std::min(left, right) + 1 to (left + right - 1) will need only one move change
            // so we need from the index in delta minus 1
            delta[std::min(left, right) + 1]--;

            // left + right should need no move change
            delta[left + right]--;

            // from left + right + 1 to std::max(left, right) + limit will also need only one move change
            delta[left + right + 1]++;

            // from std::max(left, right) + limit + 1 to 2 * limit will need two move change
            delta[std::max(left, right) + limit + 1]++;
        }
        int ans = delta[2], curAns = 0;
        for (int idx = 2; idx < delta.size(); idx++) {
            curAns += delta[idx];
            ans = std::min(ans, curAns);
        }
        return ans;

    }
private:
    static int const JUST_ONE = 1;
};
