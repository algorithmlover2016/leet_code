#include "../../head.h"


class Solution {
public:
    std::vector<std::vector<int>> combine(int n, int k) {
        std::vector<int> nums(n);
        std::iota(std::begin(nums), std::end(nums), 1);
        
        std::vector<std::vector<int>> ans;
        std::vector<int> curAns;
        
        dfs2(nums, 0, k, curAns, ans);
        return ans;
    }
private:
    void dfs(std::vector<int> const & nums, int idx, int k,
             std::vector<int> & curAns, std::vector<std::vector<int>> & ans) {
        int const numsSize = nums.size();
        if (0 == k) {
            ans.emplace_back(curAns);
            return;
        }
        if (idx == numsSize) {
            return ;
        }
        dfs(nums, idx + 1, k, curAns, ans);
        // still use the idx element
        curAns.emplace_back(nums[idx]);
        dfs(nums, idx + 1, k - 1, curAns, ans);
        curAns.pop_back();
    }
    void dfs2(std::vector<int> const & nums, int idx, int k,
             std::vector<int> & curAns, std::vector<std::vector<int>> & ans) {
        int const numsSize = nums.size();
        if (0 == k) {
            ans.emplace_back(curAns);
            return;
        }
        for (int start = idx; start <= numsSize - k; start++) {
            curAns.emplace_back(nums[start]);
            dfs(nums, start + 1, k - 1, curAns, ans);
            curAns.pop_back();
        }
    }
};

class Solution {
public:
    std::vector<std::vector<int>> combine(int n, int k) {
        std::vector<std::vector<int>> combinations;
        std::vector<int> combineList;
        backtraking(combineList, combinations, 1, k, n);
        return combinations;
    }

    void backtraking(std::vector<int> & combineList, std::vector<std::vector<int>>& combinations,
            int start, int k, int n) {
      if (k==0) {
        combinations.push_back(combineList);
        return;
      }

      for (int i = start; i <= n - k + 1; i++) { // because i start from 1
        combineList.push_back(i);
        backtraking(combineList, combinations, i + 1, k - 1, n);
        combineList.pop_back();
      }
    }
};
