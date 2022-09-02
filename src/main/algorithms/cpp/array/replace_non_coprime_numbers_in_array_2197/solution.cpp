#include "../../head.h"


class SolutionFunc {
public:
    std::vector<int> replaceNonCoprimes(std::vector<int> const & nums) {
        if (nums.size() < 2) {
            return nums;
        }
        std::vector<int> newNums;
        for (int idx = 0; idx < nums.size(); idx++) {
            int m = nums[idx];
            while (!newNums.empty() && std::gcd(newNums.back(), m) > 1) {
                m = std::lcm(newNums.back(), m);
                newNums.pop_back();
            }
            newNums.emplace_back(m);
        }
        return newNums;
    }
};

class SolutionNoLCM {
public:
    std::vector<int> replaceNonCoprimes(std::vector<int> const & nums) {
        if (nums.size() < 2) {
            return nums;
        }
        std::vector<int> newNums;
        int x = 1;
        for (int idx = 0; idx < nums.size(); idx++) {
            int m = nums[idx];
            while (!newNums.empty() && (x = std::gcd(newNums.back(), m)) > 1) {
                m *= newNums.back() / x;
                newNums.pop_back();
            }
            newNums.emplace_back(m);
        }
        return newNums;
    }
};

class Solution {
public:
    std::vector<int> replaceNonCoprimes(std::vector<int> const & nums) {
        // plagiarizing from https://leetcode.com/problems/replace-non-coprime-numbers-in-array/discuss/1823596/C%2B%2BPython-Stack-%2B-Math
        // and https://leetcode.com/problems/replace-non-coprime-numbers-in-array/discuss/1823798/JavaC%2B%2BPython-Stack-One-Pass-Solution
        // and https://leetcode.com/problems/replace-non-coprime-numbers-in-array/discuss/1823681/List
        if (nums.size() < 2) {
            return nums;
        }
        std::vector<int> newNums;
        for (int idx = 0; idx < nums.size(); idx++) {
            int m = nums[idx];
            while (!newNums.empty()) {
                int x =  std::gcd(newNums.back(), m);
                if (x == 1) {
                    break;
                }
                m *= newNums.back() / x;
                newNums.pop_back();
            }
            newNums.emplace_back(m);
        }
        return newNums;
    }
};