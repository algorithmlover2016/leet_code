#include "../../head.h"


class SolutionTLE {
public:
    std::vector<int> findDiagonalOrder(std::vector<std::vector<int>> const & nums) {
        if (nums.empty() || nums[0].empty()) {
            return {};
        }
        int const rowSize = nums.size();
        int colSize = 0;
        for (int row = 0; row < rowSize; row++) {
            colSize = std::max(colSize, (int)nums[row].size());
        }
        int maxAdd = std::max(rowSize, colSize) * 2 - 1;
        std::vector<int> ans;
        for (int skew = 0; skew < maxAdd; skew++) {
            for (int row = skew; row >= 0; row--) {
                int col = skew - row;
                if (row < nums.size() && col < nums[row].size() && col >= 0) {
                    ans.emplace_back(nums[row][col]);
                }
            }
        }
        return ans;
    }
};

class SolutionWithMapStore {
public:
    std::vector<int> findDiagonalOrder(std::vector<std::vector<int>> const & nums) {
        // plagiarizing from https://leetcode.com/problems/diagonal-traverse-ii/discuss/597741/Clean-Simple-Easiest-Explanation-with-a-picture-and-code-with-comments
        if (nums.empty() || nums[0].empty()) {
            return {};
        }
        std::unordered_map<int, std::vector<int>> records;
        int maxKey = 0;
        for (int row = 0; row < nums.size(); row++) {
            for (int col = 0; col < nums[row].size(); col++) {
                records[row + col].emplace_back(nums[row][col]);
                maxKey = std::max(maxKey, row + col);
            }
        }
        std::vector<int> ans;
        for (int key = 0; key <= maxKey; key++) {
            for (auto it = records[key].rbegin(); it != records[key].rend(); it++) {
                ans.emplace_back(*it);
            }
        }
        return ans;
    }
};

class Solution {
public:
    std::vector<int> findDiagonalOrder(std::vector<std::vector<int>> const & nums) {
        // plagiarizing from https://leetcode.com/problems/diagonal-traverse-ii/discuss/597741/Clean-Simple-Easiest-Explanation-with-a-picture-and-code-with-comments
        if (nums.empty() || nums[0].empty()) {
            return {};
        }
        std::map<int, std::vector<int>> records;
        for (int row = 0; row < nums.size(); row++) {
            for (int col = 0; col < nums[row].size(); col++) {
                records[row + col].emplace_back(nums[row][col]);
            }
        }
        std::vector<int> ans;
        for (auto & [key, vals] : records) {
            for (auto it = vals.rbegin(); it != vals.rend(); it++) {
                ans.emplace_back(*it);
            }
        }
        return ans;
    }
};
