#include "../../head.h"

class SolutionTLE {
public:
    int lengthOfLIS(std::vector<int> const & nums, int k) {
        // Time comlexsity O(n^2), space O(n)
        if (nums.empty()) {
            return 0;
        }
        assert(k >= 0);
        std::vector<int> dp(nums.size(), 1);
        int ans = 1;
        for (int idx = 1; idx < nums.size(); idx++) {
            for (int left = 0; left < idx; left++) {
                if (nums[left] + k >= nums[idx] && nums[idx] > nums[left]) {
                    dp[idx] = std::max(dp[left] + 1, dp[idx]);
                    ans = std::max(ans, dp[idx]);
                }
            }
        }
        return ans;
        
    }
};

class Solution {
    class SEGTree {
    public:
        SEGTree(int size_) : size(size_) {
            /*
                all the leafs are the actual number.
                all the other nodes are the inter-nodes
            */
            trees = std::vector(size * 2, 0);
            // trees.resize(size * 2);
            // trees = std::vector(size * 2, 0);
        }
        int query(int left /*included*/, int right /* excluded*/) {
            left += size;
            right += size;
            int ans = 0;
            while (left < right) {
                if (left & ODD) {
                    ans = std::max(ans, trees[left]);
                    left += 1;
                }
                if (right & ODD) {
                    right -= 1;
                    ans = std::max(ans, trees[right]);
                }
                left >>= 1;
                right >>= 1;
            }
            return ans;
        }

        void update(int idx, int val) {
            idx += size;
            trees[idx] = val;
            while (idx > 1) {
                idx >>= 1;
                trees[idx] = std::max(trees[idx * 2], trees[idx * 2 + 1]);
            }
        }

    private:
        int size = 0;
        std::vector<int> trees;
        static int const ODD = 1;
    };
public:
    int lengthOfLIS(std::vector<int> const & nums, int k) {
        // plagiarizing from https://leetcode.com/problems/longest-increasing-subsequence-ii/solutions/2560085/python-explanation-with-pictures-segment-tree/
        // and https://leetcode.com/problems/longest-increasing-subsequence-ii/solutions/2578352/segment-tree/
        int ans = 0;
        if (nums.empty()) {
            return 0;
        }
        int maxEle = *std::max_element(std::begin(nums), std::end(nums));
        SEGTree segTreeObj(maxEle);
        for (int numIdx : nums) {
            numIdx -= 1;
            int preMax = segTreeObj.query(std::max(0, numIdx - k), numIdx);
            ans = std::max(ans, preMax + 1);
            segTreeObj.update(numIdx, preMax + 1);
        }
        return ans;
    }
};