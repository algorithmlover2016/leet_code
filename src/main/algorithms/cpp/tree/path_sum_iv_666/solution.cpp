#include "../../head.h"
#include "../tree.h"

// #define DFS_HELPER
#define TEST_MAIN
// #define DEBUG
class Solution {
public:
    int pathSum(std::vector<int> const & nums) {
        // plagiarizing from https://github.com/grandyang/leetcode/issues/666
        if (nums.empty()) {
            return 0;
        }
        std::unordered_map<int, int> layerPos2Val;
        for (int num : nums) {
            int layerPos = num / 10;
            int val = num % 10;
            layerPos2Val[layerPos] = val;
        }

        int ans = 0;
#ifdef DFS_HELPER
        helper(nums[0] / 10 /* root pos*/, layerPos2Val, 0, ans);
#else
        bfs(nums[0] / 10, layerPos2Val, ans);
#endif
        return ans;
    }
private:
    void bfs(int layerPos, std::unordered_map<int, int> & layerPos2Val, int & ans) {
        std::queue<int> layerPosQue;
        layerPosQue.emplace(layerPos);
        while (!layerPosQue.empty()) {
            int curLayerPos = layerPosQue.front(); layerPosQue.pop();
#ifdef DEBUG
            std::cout << curLayerPos << ". " << layerPos2Val[curLayerPos] << ";\t";
#endif
            int curLayer = curLayerPos / 10;
            int curPos = curLayerPos % 10;
            int leftLayerPos = (curLayer + 1) * 10 + 2 * curPos - 1;
            int rightLayerPos = leftLayerPos + 1;
            if (layerPos2Val.find(leftLayerPos) == layerPos2Val.end() &&
                    layerPos2Val.find(rightLayerPos) == layerPos2Val.end()) {
                ans += layerPos2Val[curLayerPos];
                continue;
            }
            if (layerPos2Val.find(leftLayerPos) != layerPos2Val.end()) {
                layerPos2Val[leftLayerPos] += layerPos2Val[curLayerPos];
                layerPosQue.emplace(leftLayerPos);
            }

            if (layerPos2Val.find(rightLayerPos) != layerPos2Val.end()) {
                layerPos2Val[rightLayerPos] += layerPos2Val[curLayerPos];
                layerPosQue.emplace(rightLayerPos);
            }
        }
    }

    void helper(int layerPos, std::unordered_map<int, int> const & layerPos2Val, int cur, int & ans) {
        int layer = layerPos / 10;
        int pos = layerPos % 10;
        int leftChildLayerPos = (layer + 1) * 10 + 2 * pos - 1;
        int rightChildLayerPos = leftChildLayerPos + 1;
        cur += layerPos2Val.at(layerPos);
        if (layerPos2Val.find(leftChildLayerPos) == layerPos2Val.end() &&
                layerPos2Val.find(rightChildLayerPos) == layerPos2Val.end()) {
            ans += cur;
            return;
        }
        if (layerPos2Val.find(leftChildLayerPos) != layerPos2Val.end()) {
            helper(leftChildLayerPos, layerPos2Val, cur, ans);
        }
        if (layerPos2Val.find(rightChildLayerPos) != layerPos2Val.end()) {
            helper(rightChildLayerPos, layerPos2Val, cur, ans);
        }
    }
};

#ifdef TEST_MAIN
#define PRINT_TO_SCREEN
int main() {
    Solution obj;
    std::vector<int> nums{{113, 215, 221}};
    int ans = obj.pathSum(nums);
#ifdef PRINT_TO_SCREEN
    std::cout << "first ans: " << ans << "\n";
#endif
    assert(ans == 12);

    std::vector<int> nums1{{113, 211, 225, 324, 337, 349}};
    ans = obj.pathSum(nums1);
#ifdef PRINT_TO_SCREEN
    std::cout << "second ans: " << ans << "\n";
#endif
    assert(ans == 40);

    std::cout << "TEST SUCCESSFULLY" << std::endl;
    return 0;
}
#endif
