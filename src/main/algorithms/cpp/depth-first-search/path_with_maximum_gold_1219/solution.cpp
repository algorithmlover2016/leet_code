#include "../../head.h"


class SolutionBetterRuntime {
public:
    int ans=0;
    int getMaximumGold(std::vector<std::vector<int>> & grid) {
        int i, j, temp;
        for (i = 0;i < grid.size(); i++) {
            for (j = 0;j < grid[0].size(); j++) {
                if (!grid[i][j]) {
                    solve(grid,i,j,0);
                }
            }
        }
        return ans;
    }
    void solve(std::vector<std::vector<int>> & grid, int x, int y, int temp) {
        temp += grid[x][y];
        ans = std::max(ans, temp);
        int vo = grid[x][y];
        grid[x][y] = 0;
        int p, q;
        p = x + 1, q = y;
        if (p<grid.size() && grid[p][q]) {
            solve(grid,p,q,temp);
        }
        p = x - 1, q = y;
        if (p >= 0 && grid[p][q]) {
            solve(grid,p,q,temp);
        }
        p = x, q = y + 1;
        if (q < grid[0].size() && grid[p][q]) {
            solve(grid,p,q,temp);
        }
        p = x, q = y - 1;
        if (q >= 0 && grid[p][q]) {
            solve(grid,p,q,temp);
        }
        grid[x][y]=vo;
    }
};

class SolutionBruteForce {
private:
    static int const DIRECTION_ARRAY_SIZE = 5;
    static int const DIRECTION_SIZE = DIRECTION_ARRAY_SIZE - 1;
    std::array<int, DIRECTION_ARRAY_SIZE> direction{0, 1, 0, -1, 0};

    int dfs(std::vector<std::vector<int>> & grid,
            int row, int col) {
        if (0 == grid[row][col]) {
            return 0;
        }
        int maxLayer = 0;
        int cur = grid[row][col];
        grid[row][col] = 0;
        for (int indexD = 0; indexD < DIRECTION_SIZE; indexD++) {
            int nextRow = row + direction[indexD];
            int nextCol = col + direction[indexD + 1];
            if (nextRow >= 0 && nextRow < grid.size() &&
                    nextCol >= 0 && nextCol < grid[nextRow].size() &&
                    (0 < grid[nextRow][nextCol])) {
                maxLayer = std::max(maxLayer,  dfs(grid, nextRow, nextCol));
            }
        }
        maxLayer += cur;
        grid[row][col] = cur;
        return maxLayer;

    }

public:
    int getMaximumGold(std::vector<std::vector<int>> & grid) {
        // plagiarizing from https://leetcode.com/problems/path-with-maximum-gold/discuss/398184/C%2B%2B-Short-DFS
        int rowSize = grid.size();
        if (0 == rowSize) {
            return 0;
        }
        int colSize = grid[0].size();
        if (0 == colSize) {
            return 0;
        }

        std::array<int, DIRECTION_ARRAY_SIZE> direction{0, 1, 0, -1, 0};
        int res = 0;
        for (int row = 0; row < rowSize; row++) {
            for (int col = 0; col < colSize; col++) {
                res = std::max(res, dfs(grid, row, col));
            }
        }
        return res;
    }
};

class SolutionBFS {
private:
    static int const DIRECTION_ARRAY_SIZE = 5;
    static int const DIRECTION_SIZE = DIRECTION_ARRAY_SIZE - 1;
    static int const QUEUE_ELE_SIZE = 4;

    std::array<int, DIRECTION_ARRAY_SIZE> direction{0, 1, 0, -1, 0}; // direction will add unnecessary judgement in the if statement

public:
    int getMaximumGold(std::vector<std::vector<int>> & grid) {
        // plagiarizing from https://leetcode.com/problems/path-with-maximum-gold/discuss/398282/JavaPython-3-DFS-and-BFS-w-comment-brief-explanation-and-analysis.
        int rowSize = grid.size();
        if (0 == rowSize) {
            return 0;
        }
        int colSize = grid[0].size();
        if (0 == colSize) {
            return 0;
        }
        std::queue<std::array<int, QUEUE_ELE_SIZE>> todo;
        std::vector<std::vector<int>> traceMarks(rowSize, std::vector<int>(colSize, 0));
        int positiveNumIndex = 0; // because the positive numbers will no more than 25, so can be use bit flag to mark
        for (int row = 0; row < rowSize; row++) {
            for (int col = 0; col < colSize; col++) {
                if (0 < grid[row][col]) {
                    traceMarks[row][col] = 1 << positiveNumIndex++;
                    todo.emplace(std::array<int, QUEUE_ELE_SIZE>({row, col, grid[row][col], traceMarks[row][col]}));
                }
            }
        }
        int ans = 0;
        while (!todo.empty()) {
            int row = todo.front()[0], col = todo.front()[1], cur = todo.front()[2], mark = todo.front()[3];
            todo.pop();
            ans = std::max(ans, cur);
            int newRow = row, newCol = col + 1;
            // index not out of range and grid[row][col] are positive and have never visit when start with the node
            // == is priority to &, so there must be a ()
            if (newCol < grid[newRow].size() && 0 < grid[newRow][newCol] && (0 == (mark & traceMarks[newRow][newCol]))) {
                // std::cout << "add right elements: " << grid[newRow][newCol] << "\n";
                todo.emplace(std::array<int, QUEUE_ELE_SIZE>({newRow, newCol, cur + grid[newRow][newCol], mark | traceMarks[newRow][newCol]}));
            }
            newRow = row + 1, newCol = col;
            if (newRow < grid.size() && 0 < grid[newRow][newCol] && (0 == (mark & traceMarks[newRow][newCol]))) {
                // std::cout << "add down elements: " << grid[newRow][newCol] << "\n";
                todo.emplace(std::array<int, QUEUE_ELE_SIZE>({newRow, newCol, cur + grid[newRow][newCol], mark | traceMarks[newRow][newCol]}));
            }
            newRow = row, newCol = col - 1;
            if (0 <= newCol && 0 < grid[newRow][newCol] && (0 == (mark & traceMarks[newRow][newCol]))) {
                // std::cout << "add left elements: " << grid[newRow][newCol] << "\n";
                todo.emplace(std::array<int, QUEUE_ELE_SIZE>({newRow, newCol, cur + grid[newRow][newCol], mark | traceMarks[newRow][newCol]}));
            }
            newRow = row - 1, newCol = col;
            if (0 <= newRow && 0 < grid[newRow][newCol] && (0 == (mark & traceMarks[newRow][newCol]))) {
                // std::cout << "add up elements: " << grid[newRow][newCol] << "\n";
                todo.emplace(std::array<int, QUEUE_ELE_SIZE>({newRow, newCol, cur + grid[newRow][newCol], mark | traceMarks[newRow][newCol]}));
            }
        }
        return ans;
    }
};
