#include "../../head.h"


class Solution {
public:
    int mctFromLeafValues(std::vector<int> const & arr) {
        if (arr.empty()) {
            return 0;
        }
        std::vector<int> numsOrder(arr);
        // can't sort like this. these leafs are in-ordered.
        std::sort(numsOrder.begin(), numsOrder.end());

        int sum = -numsOrder[0], pre = 1;
        for (int num : numsOrder) {
            sum += pre * num;
            pre = num;
        }
        return sum;
    }
};

class Solution {
public:
    int mctFromLeafValues(std::vector<int> const & arr) {
        // plagiarizing from https://leetcode.com/problems/minimum-cost-tree-from-leaf-values/discuss/339959/One-Pass-O(N)-Time-and-Space
        std::vector<int> decreaseStack{{INT_MAX}};

        int res = 0;
        for (int num : arr) {
            while (decreaseStack.back() < num) {
                int needPop = decreaseStack.back();
                decreaseStack.pop_back();
                res += needPop * std::min(decreaseStack.back(), num);
            }
            decreaseStack.emplace_back(num);
        }
        for (int index = 2; index < decreaseStack.size(); index++) {
            res += decreaseStack[index - 1] * decreaseStack[index];
        }

        return res;

    }
};
