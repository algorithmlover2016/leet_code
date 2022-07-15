#include "../../head.h"


class Solution {
public:
    int stoneGameVIII(std::vector<int> const & stones) {
        // plagiarizing from https://leetcode.com/problems/stone-game-viii/discuss/1224640/C%2B%2BPython-DP-O(N)-time-O(1)-space-(2-lines-1-line)
        int stonesSize = stones.size();
        if (stonesSize < MIN_INPUT_SIZE) {
            return INT_MIN;
        }
        std::vector<int> prefixSum(stonesSize, 0);
        std::partial_sum(std::begin(stones), std::end(stones), std::begin(prefixSum));
        /*
        the upper command equal to the following:
        for (int idx = 1; idx < stonesSize; idx++) {
            prefixSum[idx] = stones[idx] + stones[idx - 1];
        }
        */
        return std::accumulate(std::next(std::rbegin(prefixSum)), std::prev(std::rend(prefixSum)), prefixSum.back(), [](int memo, int cur) {return std::max(memo, cur - memo)});
        /*
        the upper command equal to:
        int memo = prefixSum.back();
        for (int idx = stonesSize - 2; idx > 0; idx--) {
            // because (prefixSum[idx] - memo) represents the (idx - 1)-th score.
            memo = std::max(memo, prefixSum[idx] - memo);
        }
        return memo;
        */
    }
private:
    static int const MIN_INPUT_SIZE = 2;
};