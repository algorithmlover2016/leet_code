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
