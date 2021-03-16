#include "../../head.h"


class SolutionWrongAns {
public:
    bool canChoose(std::vector<std::vector<int>> const & groups, std::vector<int> const & nums) {
        if (groups.empty() || groups[0].empty()) {
            return true;
        }
        int row = 0;
        int col = 0;
        for (int idx = 0; idx < nums.size(); idx++) {
            if (groups[row][col] != nums[idx]) {
                // wrong at here;
                // if not set col = 0; no pass [[1, 2]] and [1, 3, 2]
                // if set col = 0; no pass [[21, 22, 21, 22, 21, 30]] and [21, 22, 21, 22, 21, 22, 21, 30]
                continue;
            }
            col++;
            if (col == groups[row].size()) {
                col = 0;
                row++;
            }
            if (row == groups.size()) {
                return true;
            }
        }
        return false;
    }
};

// #define DEBUG
class Solution {
public:
    bool canChoose(std::vector<std::vector<int>> const & groups, std::vector<int> const & nums, int row = 0, int idx = 0) {
        // plagiarizing from https://leetcode.com/problems/form-array-by-concatenating-subarrays-of-another-array/discuss/1074946/C%2B%2B-Simple-Search-%2B-KMP
        // KMP solution
        if (row >= groups.size()) {
            return true;
        }
        #ifdef DEBUG
        std::cout << "calling KMP\n";
        #endif
        std::vector<int> lps = kmp(groups[row]);
        #ifdef DEBUG
        std::cout << "call KMP done\n";
        for (int ele : lps) {
            std::cout << ele << ", ";
        }
        std::cout << "\n";
        #endif
        int const colSize = groups[row].size();
        for (int col = 0; idx + colSize <= nums.size(); col++) {
            if (col == colSize) {
                return canChoose(groups, nums, row + 1, idx + col);
            }
            if (groups[row][col] != nums[idx + col]) {
                // lps[col] means we need compare col position with the cur index. because idx start from zero,
                // so there are col elements when index = col.
                idx += col > 0 ? col - lps[col - 1] : 1;
                // why need lps[col] minus one, because each loop we will add col by one
                col = lps[col] - 1;
            }
        }
        return false;
    }

private:
    std::vector<int> kmp(std::vector<int> const & patterns) {
        int const patternsSize = patterns.size();
        std::vector<int> lps(patternsSize, 0);
        for (int slow = 0, fast = 1; fast < patternsSize; fast++) {
            if (patterns[slow] == patterns[fast]) {
                lps[fast] = ++slow;
            } else if (0 != slow) {
                slow = lps[slow - 1];
                fast--;
            }
        }
        return lps;
    }
};
