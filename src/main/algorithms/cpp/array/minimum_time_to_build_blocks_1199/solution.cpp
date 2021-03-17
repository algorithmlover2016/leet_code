#include "../../head.h"

#define TEST_MAIN
class Solution {
public:
    int minBuildTime(std::vector<int> const & blocks, int split) {
        if (blocks.empty()) {
            return 0;
        }
        // plagairizing idea from https://github.com/luliyucoordinate/Leetcode/blob/master/src/1199-Minimum-Time-to-Build-Blocks/1199.cpp
        std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
        for (auto const block : blocks) {
            minHeap.emplace(block);
        }
        // at begining, we have a worker, if we only have one block, we just return minHeap.top();
        while (minHeap.size() > 1) {
            // if there are more than one block. then what we should do is split the worker into two workers,
            // then there will need split time. and then about the two block, we need min time is
            // std::max(the first worker work on the first smaller block, the second worker work on the second block)
            // because we stroage the data with minHeap, so the second is the larger
            minHeap.pop(); // ignore the smaller one
            int workerTime = minHeap.top(); minHeap.pop(); // the second worker need time to work
            minHeap.emplace(workerTime + split);
        }
        return minHeap.top();
    }
};

#ifdef TEST_MAIN
#define PRINT_TO_SCREEN
int main() {
    std::vector<int> blocks{1};
    Solution obj;
    int ans = obj.minBuildTime(blocks, 1);

#ifdef PRINT_TO_SCREEN
    std::cout << ans << "\n";
#endif
    assert(ans == 1);

    blocks = std::vector<int>{{1, 2}};
    ans = obj.minBuildTime(blocks, 5);
#ifdef PRINT_TO_SCREEN
    std::cout << ans << "\n";
#endif
    assert(ans == 7);

    blocks = std::vector<int>{{1, 2, 3}};
    ans = obj.minBuildTime(blocks, 1);
#ifdef PRINT_TO_SCREEN
    std::cout << ans << "\n";
#endif
    assert(ans == 4);

    std::cout << "TEST SUCCESSFULLY" << std::endl;
    return 0;
}
#endif
