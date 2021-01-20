#include "../../head.h"


class Solution {
public:
    int minimumDeviation(std::vector<int> const & nums) {
        // plagiarizing idea from https://youtu.be/nYLSDwlWzq0
        std::priority_queue<int> maxHeap;

        int minNum = INIT_MAX;
        for (auto num : nums) {
            if (num & 0x01) {
                // odd can be multiplied by 2 to make itself bigger
                // even is its biggest val
                num <<= 1;
            }
            maxHeap.emplace(num);
            minNum = std::min(minNum, num);
        }

        int diff = INIT_MAX;
        while (!maxHeap.empty()) {
            int cur = maxHeap.top(); // the max Element
            maxHeap.pop();
            diff = std::min(diff, cur - minNum);
            if (cur & 0x01) {
                break;
            }
            cur >>= 1;
            minNum = std::min(minNum, cur);
            maxHeap.emplace(cur);
        }
        return diff;


    }
private:
    static int const INIT_MIN = INT_MIN;
    static int const INIT_MAX = INT_MAX;
};
