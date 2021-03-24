#include "../../head.h"


class Solution {
public:
    std::vector<std::vector<int>> combinationSum2(std::vector<int> candidates, int target) {
        std::sort(std::begin(candidates), std::end(candidates));
        std::vector<std::vector<int>> ans;

        std::vector<int> curAns;
        dfs(candidates, target, 0, curAns, ans);
        return ans;

    }
private:
    // 12 ms
     void dfs(std::vector<int> const & nums, int target, int idx, std::vector<int> & curAns, std::vector<std::vector<int>> & ans) {
         int const numsSize = nums.size();
         if (0 == target) {
             ans.emplace_back(curAns);
             return;
         }
         if (idx >= numsSize || target < 0) {
             return ;
         }
         int nextIdx = idx;
         while (nextIdx + 1 < numsSize && nums[nextIdx + 1] == nums[nextIdx]) {
             nextIdx++;
         }
         dfs(nums, target, nextIdx + 1, curAns, ans);
         // still use the idx element
         curAns.emplace_back(nums[idx]);
         dfs(nums, target - nums[idx], idx + 1, curAns, ans);
         curAns.pop_back();
     }

     // 8ms
     void dfs3(std::vector<int> const & nums, int target, int idx,
             std::vector<int> & curAns, std::vector<std::vector<int>> & ans) {
         int const numsSize = nums.size();
         if (0 == target) {
             ans.emplace_back(curAns);
             return;
         }
         if (idx >= numsSize || target < 0) {
             return ;
         }
         // still use the idx element
         curAns.emplace_back(nums[idx]);
         dfs(nums, target - nums[idx], idx + 1, curAns, ans);
         curAns.pop_back();
         while(idx + 1 < numsSize && nums[idx] == nums[idx + 1]) {
             idx++;
         }
         dfs(nums, target, idx + 1, curAns, ans);
     }

     // 4ms
     void dfs2(std::vector<int> const & nums, int target, int idx,
             std::vector<int> & curAns, std::vector<std::vector<int>> & ans) {
         int const numsSize = nums.size();
         if (0 == target) {
             ans.emplace_back(curAns);
             return;
         }
         if (idx >= numsSize || target < 0) {
             return ;
         }
         for (int start = idx; start < numsSize; start++) {
             curAns.emplace_back(nums[start]);
             dfs(nums, target - nums[start], start + 1, curAns, ans);
             curAns.pop_back();
             while(start + 1 < numsSize && nums[start] == nums[start + 1]) {
                 start++;
             }
         }
     }
};

class Solution {
private:
    std::vector<std::vector<int>> res;
private:
    void dfs(std::vector<int> const & candidates, int start, int target, std::vector<int> & cur) {
        if (target <= 0) {
            if (target == 0) {
                res.push_back(cur);
            }
            return;
        }
        if (start >= candidates.size()) {
            return;
        }
        for (int i = start; i < candidates.size(); i++) {
            if (i > start && candidates[i] == candidates[i - 1]) {
                continue;
            }
            cur.push_back(candidates[i]);
            dfs(candidates, i + 1, target - candidates[i], cur);
            cur.pop_back();
        }
    }
public:
    std::vector<std::vector<int>> combinationSum2(std::vector<int> const & candidates, int target) {
        std::sort(candidates.begin(), candidates.end());
        std::vector<int> cur;
        dfs(candidates, 0, target, cur);
        return res;
    }
};
