#include "../../head.h"


class Solution {
private:
    static int const DIRECTION_SIZE = 4;
    static int const INDEX_NUM = 2;
    static int const X_INDEX = 0;
    static int const Y_INDEX = 1;
    static std::array<std::array<int, INDEX_NUM>, DIRECTION_SIZE> const direction;
    // static std::array<int, DIRECTION_SIZE + 1> direction = {0, 1, 0, -1, 0}; // because the grid[i][j] is 1(0, 1), 2(0, -1), 3(1, 0), 4(-1, 0)
public:
    int minCost(std::vector<std::vector<int>> const & grid) {
        // plagiarizing from https://leetcode.com/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/discuss/524886/JavaC%2B%2BPython-BFS-and-DFS
        int rowSize = grid.size();
        if (0 == rowSize) {
            return 0;
        }
        int colSize = grid[0].size();
        if (0 == colSize) {
            return 0;
        }

        std::queue<std::pair<int, int>> layers;
        std::vector<std::vector<int>> dpMinCosts(rowSize, std::vector<int>(colSize, INT_MAX));
        int cost = 0;
        // add the first element which means add the first layer
        dfs(grid, dpMinCosts, 0, 0, cost, layers);
        while (layers.size()) {
            cost++;
            int layerSize = layers.size();
            for (int index = 0; index < layerSize; index++) {
                std::pair<int, int> & ele = layers.front();
                int row = ele.first;
                int col = ele.second;
                layers.pop();
                for (int index = 0; index < DIRECTION_SIZE; index++) {
                    dfs(grid, dpMinCosts, row + direction[index][X_INDEX], col + direction[index][Y_INDEX], cost, layers);
                }
            }
        }
        return dpMinCosts[rowSize - 1][colSize - 1];
    }
    // find all the layer at the same cost
    void dfs(std::vector<std::vector<int>> const & grid,
             std::vector<std::vector<int>> & dpMinCosts,
             int row, int col, int cost,
             std::queue<std::pair<int, int>> & layers) {
        if (row < 0 || row >= grid.size() ||
            col < 0 || col >= grid[row].size() ||
            // have visited the pair(row, col)
            INT_MAX != dpMinCosts[row][col]) {
            return;
        }
        dpMinCosts[row][col] = cost;
        layers.emplace(std::make_pair(row, col));
        int next = grid[row][col] - 1;
        dfs(grid, dpMinCosts, row + direction[next][X_INDEX], col + direction[next][Y_INDEX], cost, layers);
    }
};
std::array<std::array<int, Solution::INDEX_NUM>, Solution::DIRECTION_SIZE> const Solution::direction = {0, 1, 0, -1, 1, 0, -1, 0};

class Solution {
public:
    int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, { -1, 0}};
    int minCost(std::vector<std::vector<int>> const & grid) {
        int m = grid.size(), n = grid[0].size(), cost = 0;
        std::vector<vector<int>> dp(m, vector<int>(n, INT_MAX));
        std::queue<pair<int, int>> q;
        dfs(grid, 0, 0, dp, cost, q);
        while (!q.empty()) {
            cost++;
            int size = q.size();
            for (int i = 0; i < size; i++) {
                std::pair<int, int> p = q.front();
                int r = p.first, c = p.second;
                q.pop();
                for (int j = 0; j < 4; j++)
                    dfs(grid, r + dir[j][0], c + dir[j][1], dp, cost, q);
            }
        }
        return dp[m - 1][n - 1];
    }
    void dfs(std::vector<std::vector<int>>& grid,
            int r, int c, std::vector<std::vector<int>> & dp,
            int cost, std::queue<pair<int, int>> & q) {
        int m = grid.size(), n = grid[0].size();
        if (r < 0 || r >= m || c < 0 || c >= n || dp[r][c] != INT_MAX) {
            return;
        }
        dp[r][c] = cost;
        q.push(std::make_pair(r, c));
        int nextDir = grid[r][c] - 1;
        dfs(grid, r + dir[nextDir][0], c + dir[nextDir][1], dp, cost, q);
    }
};
