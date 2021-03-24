#include "../../head.h"


class SolutionWrongAns {
public:
    int thirdMax(std::vector<int> & nums) {
        if (3 > nums.size()) {
            return *std::max_element(nums.begin(), nums.end());
        }
        // can't pass example 3
        auto it = nums.end() - 3;
        std::nth_element(nums.begin(), it, nums.end());
        return *it;
    }
};

class Solution {
public:
    int thirdMax(std::vector<int> & nums) {
        if (nums.empty()) {
            return INT_MIN;
        }
        std::set<int> numsSet;
        // can't pass example 3
        for (int const num : nums) {
            numsSet.insert(num);
            if (numsSet.size() > 3) {
                numsSet.erase(numsSet.begin());
            }
        }
        return numsSet.size() == 3 ? *(numsSet.begin()) : *std::prev(numsSet.end());
    }
};

class Solution {
public:
    int thirdMax(std::vector<int> const & n) {
        std::set<int> m(n.begin(), n.end());
        auto it = m.end();
        if (m.size() < 3) {
            std::advance(it, -1);
            return *it;
        }
        std::advance(it, -3) ;
        return *it;
    }
};
