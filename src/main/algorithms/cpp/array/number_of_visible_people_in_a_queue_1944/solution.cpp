#include "../../head.h"



class Solution {
public:
    std::vector<int> canSeePersonsCount(std::vector<int> const & heights) {
        // plagiarizing from https://leetcode.com/problems/number-of-visible-people-in-a-queue/discuss/1359707/JavaC%2B%2BPython-Stack-Solution-Next-Greater-Element
        int const heightsSize = heights.size();
        std::vector<int> ans(heightsSize), desStack;
        if (heights.empty()) {
            return ans;
        }
        for (int idx = 0; idx < heightsSize; idx++) {
            while (!desStack.empty() && (heights[desStack.back()] <= heights[idx])) {
                // the idx-th element will block all the elements which is not larger than it and before it.
                // So, if we arrive the idx-th element, then we can pop previously not-larger than it.
                ans[desStack.back()]++;
                desStack.pop_back();
            }
            if (!desStack.empty()) {
                ans[desStack.back()]++;
            }
            desStack.emplace_back(idx);
        }
        return ans;
    }
};

class Solution {
public:
    std::vector<int> canSeePersonsCount(std::vector<int> const & heights) {
        // plagiarizing from https://leetcode.com/problems/number-of-visible-people-in-a-queue/discuss/1359702/Monostack
        int const heightsSize = heights.size();
        std::vector<int> ans(heightsSize), incStack;
        if (heights.empty()) {
            return ans;
        }
        for (int idx = heightsSize - 1; idx >LEFT_MOST_EXCLUSIVE; idx--) {
            // we look forward(right) and incStack keep the increasing seq;
            while (!incStack.empty() && (heights[idx] > heights[incStack.back()])) {
                ans[idx]++;
                incStack.pop_back();
            }
            
            if (!incStack.empty()) {
                ans[idx]++;
            }
            incStack.emplace_back(idx);
        }
        return ans;
    }
private:
    static int const LEFT_MOST_EXCLUSIVE = -1;
};