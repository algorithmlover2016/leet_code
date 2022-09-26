#include "../../head.h"


// #define DEBUG
#define CUR_NODE_AS_END_POINT
class Solution {
public:
    int countPaths(std::vector<std::vector<int>> const & grid) {
        // plagiarizing from https://leetcode.com/problems/number-of-increasing-paths-in-a-grid/discuss/2229827/DFS-%2B-Memo
        // and https://leetcode.com/problems/number-of-increasing-paths-in-a-grid/discuss/2229819/C%2B%2BPython-Top-Down-DP
        /*
            First I find it is similar to count_subarrays_with_score_less_than_k_2302 and subarray_product_less_than_k_713
            But I have a question that how to avoid the same path is counted twice (no matter counter the cur node as ending point
            or starting point). However, I forget the condition the path must be strictly increasing.
            If the path from A to B is strictly increasing, then the path from B to A is not a target one. So there is no repeating path.
        */
        // dp solution with Memo is alse named dfs method withi memo?
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }
        int rows = grid.size(), cols = grid[0].size();
        std::vector<std::vector<int>> dpMemo(rows, std::vector<int>(cols, INIT_VAL));
        long long ans = 0;
        #ifdef DEBUG
        std::cout << "begin to compute ans\n";
        #endif
        for (int row = 0; row < grid.size(); row++) {
            for (int col = 0; col < grid[row].size(); col++) {
                #ifdef DEBUG
                std::cout << "cur pos: (" << row << ", " << col << ")\n";
                #endif
                ans = (ans + dfsDp(grid, row, col, dpMemo)) % MOD;
            }
        }
        return ans;
    }
private:
    int dfsDp(std::vector<std::vector<int>> const & grid, int row, int col, std::vector<std::vector<int>> & dpMemo) {
        long long ans = 1;
        #ifdef DEBUG
        std::cout << "dfs cur begin pos: (" << row << ", " << col << ")\n";
        #endif
        if (INIT_VAL != dpMemo[row][col]) {
            #ifdef DEBUG
            std::cout << "have computed: (" << row << ", " << col << ")\n";
            #endif
            return dpMemo[row][col];
        }
        for (int idx = 0; idx < DIRECTION; idx++) {
            int nextRow = row + directions[idx];
            int nextCol = col + directions[idx + 1];
            if (std::min(nextRow, nextCol) < 0 ||
                nextRow >= grid.size() || nextCol >= grid[nextRow].size() ||
                
                #ifdef CUR_NODE_AS_END_POINT
                grid[nextRow][nextCol] >= grid[row][col]
                #else
                grid[nextRow][nextCol] <= grid[row][col]
                #endif
                
               ) {
                 #ifdef DEBUG
                 std::cout << "next pos jump judge: (" << nextRow << ", " << nextCol << ")\n";
                 #endif
                continue;
             }
             #ifdef DEBUG
             std::cout << "next pos: (" << nextRow << ", " << nextCol << ")\n";
             #endif
             ans = (ans + dfsDp(grid, nextRow, nextCol, dpMemo)) % MOD;
        }
        #ifdef DEBUG
        std::cout << "dfs cur end pos: (" << row << ", " << col << ")\n";
        #endif
        return dpMemo[row][col] = ans;

    }

private:
    constexpr int static MOD = 1e9 + 7;
    constexpr int static DIRECTION = 4;
    constexpr int static DIRECTION_SIZE = DIRECTION + 1;
    const int INIT_VAL = 0;

    static std::array<int, DIRECTION_SIZE> directions;
};
std::array<int, Solution::DIRECTION_SIZE> Solution::directions = {0, 1, 0, -1, 0};