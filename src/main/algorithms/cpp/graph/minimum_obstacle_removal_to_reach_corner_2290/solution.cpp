#include "../../head.h"



class SolutionGPT {
public:
    int minimumObstacles(std::vector<std::vector<int>> const & grid) {
         int m = grid.size(), n = grid[0].size();
         std::vector<std::vector<int>> dist(m, std::vector<int>(n, -1));
         std::priority_queue<std::pair<int, std::pair<int, int>>, std::vector<std::pair<int, std::pair<int, int>>>, std::greater<>> pq;
         pq.push({0, {0, 0}});
         dist[0][0] = 0;
         while (!pq.empty()) {
             auto [d, p] = pq.top();
             pq.pop();
             auto [i, j] = p;
             if (i == m - 1 && j == n - 1) {
                 return d;
             }
             for (auto [di, dj] : std::vector<std::pair<int, int>>{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {
                 int ni = i + di, nj = j + dj;
                 if (ni >= 0 && ni < m && nj >= 0 && nj < n && grid[ni][nj] == 0 && (dist[ni][nj] == -1 || d < dist[ni][nj]))
                 {
                     dist[ni][nj] = d;
                     pq.push({d, {ni, nj}});
                 } else if (ni >= 0 && ni < m && nj >= 0 && nj < n && grid[ni][nj] == 1 && (dist[ni][nj] == -1 || d + 1 < dist[ni][nj])) {
                     dist[ni][nj] = d + 1;
                     pq.push({d + 1, {ni, nj}});
                 }
             }
         }
         return -1; // no path found
    }

    int minimumObstacles(std::vector<std::vector<int>> const & grid, bool dequeFlag = true) {
        int RowSize = grid.size(), ColSize = grid[0].size();
        std::vector<std::vector<int>> dp(RowSize, std::vector<int>(ColSize, INT_MAX));
        dp[0][0] = grid[0][0];
        std::deque<std::pair<int, int>> dq{{0, 0}};
        std::vector<int> dir{-1, 0, 1, 0, -1};
        while (!dq.empty()) {
            int size = dq.size();
            for (int i = 0; i < size; i++) {
                auto [x, y] = dq.front(); dq.pop_front();
                if (x == RowSize - 1 and y == ColSize - 1) return dp[RowSize - 1][ColSize - 1];
                for (int j = 0; j < 4; j++) {
                    int dx = x + dir[j];
                    int dy = y + dir[j + 1];
                    if (dx < 0 || dy < 0 || dx >= RowSize || dy >= ColSize || dp[dx][dy] != INT_MAX) continue;
                    if (grid[dx][dy] == 1) {
                        dp[dx][dy] = dp[x][y] + 1;
                        dq.push_back({dx, dy});
                    } else {
                        dp[dx][dy] = dp[x][y];
                        dq.push_front({dx, dy});
                    }
                }
            }
        }
        return -1; // no path found
    }
};

class Solution {
public:
    int minimumObstacles(std::vector<std::vector<int>> const & grid) {
         int m = grid.size(), n = grid[0].size();
         std::vector<std::vector<int>> dist(m, std::vector<int>(n, -1));
         std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
         pq.push({0, 0});
         dist[0][0] = 0;
         while (!pq.empty()) {
             auto [d, p] = pq.top();
             pq.pop();
             auto i = p / n, j = p % n;
             if (i == m - 1 && j == n - 1) {
                 return d;
             }
             for (int idx = 0; idx < DIRECT_SIZE; idx++) {
                 int ni = i + DIRECT[idx], nj = j + DIRECT[idx + 1];
                 if (ni >= 0 && ni < m && nj >= 0 && nj < n) {
                    if (grid[ni][nj] == 0 && (dist[ni][nj] == -1 || d < dist[ni][nj])) {
                        dist[ni][nj] = d;
                        pq.push({d, ni * n + nj});
                    } else if (grid[ni][nj] == 1 && (dist[ni][nj] == -1 || d + 1 < dist[ni][nj])) {
                        dist[ni][nj] = d + 1;
                        pq.push({d + 1, ni * n + nj});
                    }
                 }
             }
         }
         return -1; // no path found
    }

private:
    static int const DIRECT_SIZE = 4;
    static std::array<int, DIRECT_SIZE + 1> const DIRECT;
};
std::array<int, Solution::DIRECT_SIZE + 1> const Solution::DIRECT = {0, 1, 0, -1, 0};

class SolutionBest {
public:
    int minimumObstacles(std::vector<std::vector<int>>& grid) {
        const int dir[5] = {1, 0, -1, 0, 1};
        int m = grid.size(), n = grid[0].size();
        std::vector<std::vector<int>> dp(m, std::vector<int>(n, INT_MAX));
        std::deque<std::pair<int, int>> dq;
        dq.push_back({0, 0});
        dp[0][0] = 0;

        while (!dq.empty()) {
            int size = dq.size();
            for (int i = 0; i < size; i++) {
                auto [x, y] = dq.front(); dq.pop_front();
                if (x == m - 1 and y == n - 1) return dp[m - 1][n - 1];
                for (int j = 0; j < 4; j++) {
                    int dx = x + dir[j];
                    int dy = y + dir[j + 1];
                    if (dx < 0 || dy < 0 || dx >= m || dy >= n || dp[dx][dy] != INT_MAX) continue;
                    if (grid[dx][dy] == 1) {
                        dp[dx][dy] = dp[x][y] + 1;
                        dq.push_back({dx, dy});
                    } else {
                        dp[dx][dy] = dp[x][y];
                        dq.push_front({dx, dy});
                    }
                }
            }
        }
        return 0;
    }
};