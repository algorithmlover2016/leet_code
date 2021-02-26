#include "../../head.h"


class Solution {
public:
    int findUnsortedSubarray(std::vector<int> const & nums) {
        int start = nums.size();
        int end = EXLUDE_LEFT_MOST_IDX;
        int popMaxEle = INT_MIN;
        std::vector<int> incSeq;
        for (int idx = 0; idx < nums.size(); idx++) {
            if (popMaxEle > nums[idx]) {
                end = idx;
            }
            while (!incSeq.empty() && nums[incSeq.back()] > nums[idx]) {
                popMaxEle = std::max(popMaxEle, nums[incSeq.back()]);
                start = std::min(start, incSeq.back());
                incSeq.pop_back();
                end = idx;
            }
            incSeq.emplace_back(idx);
        }

        return EXLUDE_LEFT_MOST_IDX == end ? 0 : end - start + 1;

    }
private:
    static int const EXLUDE_LEFT_MOST_IDX = -1;
};

class Solution {
public:
    int findUnsortedSubarray(std::vector<int> const & nums) {
        int minSoFar = nums.back();
        int maxSoFar = nums.front();

        int mostFrontOutofOrder = nums.size();
        int mostBackOutofOrder = -1;

        for (int i = (int)nums.size() - 2, j = 1; i >= 0; i--, j++) {
            if (nums[i] > minSoFar) {
                mostFrontOutofOrder = i;
            }
            minSoFar = std::min(minSoFar, nums[i]);

            if (nums[j] < maxSoFar) {
                mostBackOutofOrder = j;
            }
            maxSoFar = std::max(maxSoFar, nums[j]);
        }

        if (mostFrontOutofOrder > mostBackOutofOrder) {
            return 0;
        } else {
            return mostBackOutofOrder - mostFrontOutofOrder + 1;
        }


    }
};
