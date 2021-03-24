#include "../../head.h"


class Solution {
public:
    std::vector<std::vector<int>> combinationSum(std::vector<int> const & candidates, int target) {
        std::vector<std::vector<int>> ans;
        
        std::vector<int> curAns;
        dfs(candidates, target, 0, curAns, ans);
        return ans;
    }
private:
    // after traverse the idx, we will never back;
    void dfs(std::vector<int> const & nums, int target, int idx,
            std::vector<int> & curAns, std::vector<std::vector<int>> & ans) {
        int const numsSize = nums.size();
        if (0 == target) {
            ans.emplace_back(curAns);
            return;
        }
        if (idx == numsSize || target < 0) {
            return ;
        }
        dfs(nums, target, idx + 1, curAns, ans);
        // still use the idx element
        curAns.emplace_back(nums[idx]);
        dfs(nums, target - nums[idx], idx, curAns, ans);
        curAns.pop_back();
    }
};

class Solution {
public:
    std::vector<std::vector<int>> combinationSum(std::vector<int> const & candidates, int target) {
        std::vector<int> temp;
        std::vector<std::vector<int>> result;
        solve(candidates, 0, target, temp, result);
        return result;
    }
private:
    void solve(std::vector<int> const & candidates, int start, int target,
            std::vector<int> & temp, std::vector<std::vector<int>> & result) {
        if (target < 0) {
            return;
        } else if(target == 0) {
            result.push_back(temp);
        }
        for (int i = start ; i < candidates.size() ; i++) {
            temp.push_back(candidates[i]);
            solve(candidates, i, target - candidates[i], temp, result);
            temp.pop_back();
        }
    }
};

class Solution { // knapsack complete problem
public:
    std::vector<std::vector<int>> combinationSum(std::vector<int> const & candidates, int target) {
        std::vector<std::vector<int>> ret;
        std::vector<int> tmp;
        dfs2(ret, tmp, 0, candidates, target);
        // cout << std::to_string(dfs(0, candidates, target)) << "->" << ret.size() << endl;
        return ret;
    }
private:
    void dfs2(std::vector<std::vector<int>> & vec, std::vector<int> & level,
            int index, std::vector<int> const & candidates, int target) {
        if (target < 0) {
            return;
        }
        if (target == 0) {
            vec.push_back(level);
        }
        for (int i = index; i < candidates.size(); i++) {
            level.push_back(candidates[i]);
            dfs2(vec, level, i, candidates, target - candidates[i]);
            level.pop_back();
        }
    }

    int dfs(int idx, std::vector<int> & candidates, int target) {
        if (target == 0) {
            return 1;
        }
        if (idx >= candidates.size() || target < 0) {
            return 0;
        }
        if (memo[idx][target]) {
            return  memo[idx][target];
        }
        int ret = dfs(idx + 1, candidates, target) /*skip the cur candidate*/ +
            /*using the cur candidate, if we need move to next one, use the skip expression */
            dfs(idx, candidates, target - candidates[idx]);
        return memo[idx][target] = ret;
    }
private:
    std::unordered_map<int, std::unordered_map<int, int>> memo;
};
