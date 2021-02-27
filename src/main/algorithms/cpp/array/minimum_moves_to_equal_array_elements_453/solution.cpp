#include "../../head.h"


#define MATH_SOLUTOIN
class Solution {
public:
    int minMoves(std::vector<int> const & nums) {
        // plagiairizing from https://leetcode.com/problems/minimum-moves-to-equal-array-elements/discuss/93822/Simple-one-liners
        // and https://leetcode.com/problems/minimum-moves-to-equal-array-elements/discuss/93817/It-is-a-math-question
        // and https://leetcode.com/problems/minimum-moves-to-equal-array-elements/discuss/93815/Java-O(n)-solution.-Short.
        // sum + moves * (nums.size() - 1) = (minNum + moves) * nums.size() = minNum * nums.size() + moves * nums.size()
        // moves = sum - minNum * nums.size()
#ifdef MATH_SOLUTOIN
        return std::accumulate(nums.begin(), nums.end(), 0L) - *std::min_element(nums.begin(), nums.end()) * nums.size();
#else
        int minNum = *std::min_element(nums.begin(), nums.end());
        int ans = 0;
        for (int const num : nums) {
            ans += num - minNum;
        }
        return ans;
#endif
    }

};
