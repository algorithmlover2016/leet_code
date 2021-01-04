#include "../../head.h"


class Solution {
public:
    int maxNonOverlapping(std::vector<int> const & nums, int target) {
        // plagaiarizing from https://leetcode.com/problems/maximum-number-of-non-overlapping-subarrays-with-sum-equals-target/discuss/780887/Java-Detailed-Explanation-DPMapPrefix-O(N) and
        // https://youtu.be/aN8ND52Wjac 34:07
        std::unordered_map<int, int> dpMap;
        dpMap[0] = 0;
        int sum = 0;
        int ans = 0;
        for (int idx = 0; idx < nums.size(); idx++) {
            sum += nums[idx];
            int curDiff = sum - target;
            if (dpMap.find(curDiff) != dpMap.end()) {
                ans = std::max(ans, dpMap[curDiff] + 1);
            }
            dpMap[sum] = ans;
        }
        return ans;
    }
};

class SolutionLee {
public:
    int maxNonOverlapping(std::vector<int> const & nums, int target) {
        // plagaiarizing from https://leetcode.com/problems/maximum-number-of-non-overlapping-subarrays-with-sum-equals-target/discuss/780887/Java-Detailed-Explanation-DPMapPrefix-O(N) and
        // https://youtu.be/aN8ND52Wjac 34:07

        std::set<int> seen;
        seen.insert(0);
        int ans = 0;
        int cntSum = 0;
        for (int idx = 0; idx < nums.size(); idx++) {
            cntSum += nums[idx];
            if (seen.find(cntSum - target) != seen.end()) {
                ans += 1;
                cntSum = 0;
                seen.clear();
            }
            seen.insert(cntSum);
        }
        return ans;

    }
};
