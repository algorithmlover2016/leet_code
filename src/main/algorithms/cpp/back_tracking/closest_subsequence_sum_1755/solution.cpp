#include "../../head.h"


// #define DEBUG
class Solution {
public:
    int minAbsDifference(std::vector<int> const & nums, int goal) {
        // plagiarizing from https://youtu.be/UtGwxAyJq7Y
        // split and merge
        if (nums.empty()) {
            return std::abs(goal);
        }
        int const numsSize = nums.size();
        int mid = numsSize / 2;

        std::vector<int> leftHalf;
        std::vector<int> rightHalf;

        dfs(0, mid, 0, nums, leftHalf);
        dfs(mid, numsSize, 0, nums, rightHalf);

        int ans = INIT_MAX;
        std::sort(rightHalf.begin(), rightHalf.end());
        for (int const sum : leftHalf) {
            int diff = goal - sum;
            #ifdef DEBUG
            std::cout << "diff: " << diff << "\t";
            #endif
            auto it = std::lower_bound(rightHalf.begin(), rightHalf.end(), diff);
            if (it !=  rightHalf.end()) {
                #ifdef DEBUG
                std::cout << "cur diff: " << *it << "\t";
                #endif
                ans = std::min(ans, std::abs(diff - *it));

            }
            if (it != rightHalf.begin()) {
                #ifdef DEBUG
                std::cout << "prev diff: " << *std::prev(it) << "\t";
                #endif
                ans = std::min(ans, std::abs(diff - *std::prev(it)));
            }
            #ifdef DEBUG
            std::cout << "\n";
            #endif
        }
        return ans;

    }
    void dfs(int start, int end, int cur,
             std::vector<int> const & nums, std::vector<int> & ans) {
        if (start == end) {
            ans.emplace_back(cur);
            return;
        }
        // take nums[start]
        dfs(start + 1, end, cur + nums[start], nums, ans);
        // skip nums[start]
        dfs(start + 1, end, cur, nums, ans);
    }
    private:
    static int const INIT_MAX = INT_MAX;
};
