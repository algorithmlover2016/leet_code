#include "../../head.h"


class Solution {
public:
    int largestRectangleArea(std::vector<int> const & heights) {
        // plagiarizing idea from https://leetcode.com/problems/largest-rectangle-in-histogram/
        if (heights.empty()) {
            return 0;
        }

        std::vector<int> incStack;
        incStack.emplace_back(PSEUDO_IDX_FLAG);

        int const heightsSize = heights.size();

        int ansArea = 0;
        for (int idx = 0; idx < heightsSize; idx++) {
            while ((PSEUDO_IDX_FLAG != incStack.back()) && (heights[idx] <= heights[incStack.back()])) {
                int curPopIdx = incStack.back(); incStack.pop_back();
                int width = idx - incStack.back() - 1;
                ansArea = std::max(ansArea, width * heights[curPopIdx]);
            }
            incStack.emplace_back(idx);
        }
        while (PSEUDO_IDX_FLAG != incStack.back()) {
            int curPopIdx = incStack.back(); incStack.pop_back();
            int width = heightsSize - incStack.back() - 1;
            ansArea = std::max(ansArea, width * heights[curPopIdx]);
        }
        return ansArea;
    }

private:
    int const PSEUDO_IDX_FLAG = -1; // there can't be marked as static, because we use the flag to push to stack
};
