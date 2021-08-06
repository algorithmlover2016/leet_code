#include "../../head.h"


class Solution {
public:
    std::vector<std::vector<int>> subsetsWithDup(std::vector<int> & nums) {
        // reference to https://www.youtube.com/watch?v=FUZY-YJ53w8
        std::sort(nums.begin(), nums.end());
        std::vector<std::vector<int>> ans;
        std::vector<int> curAns;
        backTracking(nums, 0, curAns, ans);
        return ans;
    }
    
private:
    void  backTracking(std::vector<int> const & nums, int idx, std::vector<int> & curAns, std::vector<std::vector<int>> & ans) {
        ans.emplace_back(curAns);
        for (int nextIdx = idx; nextIdx < nums.size(); nextIdx++) {
            if (nextIdx > idx && nums[nextIdx] == nums[nextIdx - 1]) {
                continue;
            }
            curAns.emplace_back(nums[nextIdx]);
            backTracking(nums, nextIdx + 1, curAns, ans);
            curAns.pop_back();
        }
        
    }
};
