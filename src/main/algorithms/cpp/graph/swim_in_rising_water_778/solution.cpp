#include "../../head.h"


class Solution {
public:
    struct SimTuple {
        int weight;
        int row;
        int col;
        SimTuple(int _weight, int _row, int _col) :
            weight(_weight), row(_row), col(_col) {
            }
        bool operator<(const SimTuple & other) const { //must be const function
            return weight > other.weight; 
        }
    };
    class Cmp {
    public:
        bool operator()(SimTuple const & lhs, SimTuple const & rhs) {
            return lhs.weight > rhs.weight;
        }
    };
public:
    int swimInWater(std::vector<std::vector<int>> const & grid) {
        // plagiarizing from https://leetcode.com/problems/swim-in-rising-water/discuss/113770/C%2B%2BPython-PriorityQueue
        int rowSize = grid.size();
        if (0 == rowSize) {
            return 0;
        }
        int colSize = grid[0].size();
        if (0 == colSize) {
            return 0;
        }
        std::vector<std::vector<bool>> visited(rowSize, std::vector<bool>(colSize, false));
        std::priority_queue<SimTuple> todo; // min_heap because SimTuple define the < operator
        todo.emplace(SimTuple(grid[0][0], 0, 0));
        int res = 0;
        while (todo.size()) {
            auto const &  cur = todo.top();
            int row = cur.row;
            int col = cur.col;
            res = std::max(res, cur.weight);
            todo.pop();
            if (visited[row][col]) {
                continue;
            }
            if (row == rowSize - 1 && col == colSize - 1) {
                return res;
            }
            visited[row][col] = true;
            for (int index = 0; index < DIRECTION_SIZE; index++) {
                int nextRow = row + directions[index];
                int nextCol = col + directions[index + 1];
                if (nextRow >= 0 && nextRow < rowSize &&
                        nextCol >= 0 && nextCol < colSize &&
                        visited[nextRow][nextCol] != true) {
                    todo.emplace(grid[nextRow][nextCol], nextRow, nextCol);
                }
            }
        }
        return -1;

    }
private:
    static int const DIRECTION_ARRAY_SIZE = 5;
    static int const DIRECTION_SIZE = DIRECTION_ARRAY_SIZE - 1;
    static std::array<int, DIRECTION_ARRAY_SIZE> directions;
};
std::array<int, Solution::DIRECTION_ARRAY_SIZE> Solution::directions = {0, 1, 0, -1, 0};

class SolutionPlagiarizingFrom {
public:

    struct T {
        int t, x, y;
        T(int a, int b, int c) : t (a), x (b), y (c){}
        bool operator< (const T &d) const {return t > d.t;}
    };

    int swimInWater(vector<vector<int>>& grid) {
        int N = grid.size (), res = 0;
        priority_queue<T> pq;
        pq.push(T(grid[0][0], 0, 0));
        vector<vector<int>> seen(N, vector<int>(N, 0));
        seen[0][0] = 1;
        static int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, { -1, 0}};

        while (true) {
            auto p = pq.top ();
            pq.pop ();
            res = max(res, p.t);
            if (p.x == N - 1 && p.y == N - 1) return res;
            for (auto& d : dir) {
                int i = p.x + d[0], j = p.y + d[1];
                if (i >= 0 && i < N && j >= 0 && j < N && !seen[i][j]) {
                    seen[i][j] = 1;
                    pq.push (T(grid[i][j], i, j));
                }
            }
        }
    }
};

// 使用binary search来猜值
class Solution {
public:
    Solution() {std::ios::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);}

    int swimInWater(std::vector<std::vector<int>> const & grid) {
        int n = grid.size(), lo = grid[0][0], hi = n*n; //grid[i][j] is a permutation of [0, ..., N*N - 1]
        while (lo < hi) {
            int mid = lo + (hi-lo) / 2;
            if (!valid(grid, mid))
                lo = mid + 1;
            else
                hi = mid;
        }
        return lo;
    }
private:
    bool valid(std::vector<std::vector<int>> const & grid, int waterHeight) {
        int n = grid.size();
        std::vector<std::vector<int>> visited(n, std::vector<int>(n, 0));
        std::vector<int> dir({-1, 0, 1, 0, -1});
        return dfs(grid, visited, dir, waterHeight, 0, 0, n);
    }

    bool dfs(std::vector<std::vector<int>> const & grid, std::vector<std::vector<int>>& visited,
             std::vector<int> const & dir, int wh, int row, int col, int n) {
        visited[row][col] = 1;
        for (int i = 0; i < 4; ++i) {
            int r = row + dir[i], c = col + dir[i+1];
            if (0 <= r && r < n && 0 <= c && c < n &&
                visited[r][c] == 0 && grid[r][c] <= wh) {
                if (r == n-1 && c == n-1) return true; //到达终点
                if (dfs(grid, visited, dir, wh, r, c, n)) return true; //递归
            }
        }
        return false;
    }
};

/*
Name: Rithika Chowdhury
Studentd id: 23955940
Time complexity: O(n^2 logn)
Space complxity: O(n^2)
*/
class Solution {
public:
    int n, moves[4][2] {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int swimInWater(std::vector<std::vector<int>> const & grid) {
	    n = std::size(grid);
	    int l = std::max({2 * (n - 1), grid[0][0], grid[n - 1][n - 1] }), r = n * n - 1, mid;
	    bool vis[50][50]{};
	    while (l <= r) {
		    mid = (l + r) / 2;
		    if (solve(grid, vis, 0, 0, mid)) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
            std::memset(vis, false, sizeof vis);
	    }
	    return l;
    }

    bool solve(vector<vector<int>>& grid, bool vis[][50], int i, int j, int w_lvl) {
	    if (i < 0 || j < 0 || i >= n || j >= n || vis[i][j] || grid[i][j] > w_lvl) {
            return false;
        }
	    if (i == n - 1 && j == n - 1) {
            return true;
        }
	    vis[i][j] = true;
	    for(int k = 0; k < 4; k++) {
		    if (solve(grid, vis, i + moves[k][0], j + moves[k][1], w_lvl)) {
                return true;
            }
        }
	    return false;
    }
};
