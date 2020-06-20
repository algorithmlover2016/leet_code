#include "../../head.h"


class Solution {
public:
    int minimumMoves(std::vector<std::vector<int>> const & grid) {
        int rowSize = grid.size();
        if (0 == rowSize) {
            return 0;
        }

        int colSize = grid[0].size();
        if (0 == colSize) {
            return 0;
        }

        std::unordered_map<int, int> visited;
        std::queue<int> todo;
        int code = encode(0, 1, 0, 0);
        todo.emplace(code);
        visited[code] = 0;
        int res = INT_MAX;
        while (todo.size()) {
            int cur = todo.front(); todo.pop();
            if (visited[cur] >= res) {
                continue;
            }
            int headRow = 0, headCol = 0, endRow = 0, endCol = 0;
            decode(cur, headRow, headCol, endRow, endCol);
            if (headRow == rowSize - 1 && headCol == colSize - 1 &&
                    endRow == headRow && endCol == headCol - 1) {
                res = std::min(res, visited[cur]);
            }
            if (canRight(grid, headRow, headCol, endRow, endCol)) {
                int newCode = encode(headRow, headCol, endRow, endCol);
                if (visited.find(newCode) == visited.end() || visited[newCode] > visited[cur] + 1) {
                    todo.emplace(newCode);
                    visited[newCode] = visited[cur] + 1;
                }
            }

            decode(cur, headRow, headCol, endRow, endCol);
            if (canDown(grid, headRow, headCol, endRow, endCol)) {
                int newCode = encode(headRow, headCol, endRow, endCol);
                if (visited.find(newCode) == visited.end() || visited[newCode] > visited[cur] + 1) {
                    todo.emplace(newCode);
                    visited[newCode] = visited[cur] + 1;
                }
            }

            decode(cur, headRow, headCol, endRow, endCol);
            if (canClockWise(grid, headRow, headCol, endRow, endCol)) {
                int newCode = encode(headRow, headCol, endRow, endCol);
                if (visited.find(newCode) == visited.end() || visited[newCode] > visited[cur] + 1) {
                    todo.emplace(newCode);
                    visited[newCode] = visited[cur] + 1;
                }
            }

            decode(cur, headRow, headCol, endRow, endCol);
            if (canCounterClockWise(grid, headRow, headCol, endRow, endCol)) {
                int newCode = encode(headRow, headCol, endRow, endCol);
                if (visited.find(newCode) == visited.end() || visited[newCode] > visited[cur] + 1) {
                    todo.emplace(newCode);
                    visited[newCode] = visited[cur] + 1;
                }
            }
        }
        return INT_MAX == res ? -1 : res;
    }
private:
    int encode(int headRow, int headCol, int endRow, int endCol) {
        return (headRow << 24) | (headCol << 16) | (endRow << 8) | (endCol);
    }

    void decode(int res, int & headRow, int & headCol, int & endRow, int & endCol) {
        headRow = (res >> 24) & 0xFF;
        headCol = (res >> 16) & 0xFF;
        endRow = (res >> 8) & 0xFF;
        endCol = res & 0xFF;
    }

    bool canRight(std::vector<std::vector<int>> const & grid,
            int & headRow, int & headCol, int & endRow, int & endCol) {
        int newHeadCol = headCol + 1;
        if (newHeadCol >= grid[headRow].size() || 1 == grid[headRow][newHeadCol]) {
            return false;
        }
        int newEndCol = endCol + 1;
        if (1 == grid[endRow][newEndCol]) {
            return false;
        }
        headCol = newHeadCol;
        endCol = newEndCol;
        return true;
    }

    bool canDown(std::vector<std::vector<int>> const & grid,
            int & headRow, int & headCol, int & endRow, int & endCol) {
        int newHeadRow = headRow + 1;
        if (newHeadRow >= grid.size() || 1 == grid[newHeadRow][headCol]) {
            return false;
        }
        int newEndRow = endRow + 1;
        if (1 == grid[newEndRow][endCol]) {
            return false;
        }
        headRow = newHeadRow;
        endRow = newEndRow;
        return true;
    }

    bool canClockWise(std::vector<std::vector<int>> const & grid,
            int & headRow, int & headCol, int & endRow, int & endCol) {
        if (headRow != endRow) {
            return false;
        }
        int newHeadRow = endRow + 1;
        if (newHeadRow >= grid.size() ||
            1 == grid[newHeadRow][endCol] ||
            1 == grid[newHeadRow][headCol]) {
            return false;
        }
        headRow = newHeadRow;
        headCol = endCol;
        return true;
    }

    bool canCounterClockWise(std::vector<std::vector<int>> const & grid,
            int & headRow, int & headCol, int & endRow, int & endCol) {
        if (headCol != endCol) {
            return false;
        }
        int newHeadCol = endCol + 1;
        if (newHeadCol >= grid[endRow].size() ||
            1 == grid[endRow][newHeadCol] ||
            1 == grid[headRow][newHeadCol]) {
            return false;
        }
        headRow = endRow;
        headCol = newHeadCol;
        return true;
    }
};

class SolutionBFS {
public:
    int minimumMoves(std::vector<std::vector<int>> const & grid) {
        int rowSize = grid.size();
        if (0 == rowSize) {
            return 0;
        }

        int colSize = grid[0].size();
        if (0 == colSize) {
            return 0;
        }

        std::set<int> visited;
        std::queue<int> todo;
        int code = encode(0, 1, 0, 0);
        todo.emplace(code);
        int res = 0;
        while (todo.size()) {
            int size = todo.size();
            for (int index = 0; index < size; index++) {
                int cur = todo.front(); todo.pop();
                int headRow = 0, headCol = 0, endRow = 0, endCol = 0;
                if (visited.find(cur) != visited.end()) {
                    continue;
                }
                visited.emplace(cur);
                decode(cur, headRow, headCol, endRow, endCol);
                if (headRow == rowSize - 1 && headCol == colSize - 1 &&
                        endRow == headRow && endCol == headCol -1) {
                    return res;
                }

                if (canRight(grid, headRow, headCol, endRow, endCol)) {
                    int newCode = encode(headRow, headCol, endRow, endCol);
                    if (visited.find(newCode) == visited.end()) {
                        todo.emplace(newCode);
                    }
                }

                decode(cur, headRow, headCol, endRow, endCol);
                if (canDown(grid, headRow, headCol, endRow, endCol)) {
                    int newCode = encode(headRow, headCol, endRow, endCol);
                    if (visited.find(newCode) == visited.end()) {
                        todo.emplace(newCode);
                    }
                }

                decode(cur, headRow, headCol, endRow, endCol);
                if (canClockWise(grid, headRow, headCol, endRow, endCol)) {
                    int newCode = encode(headRow, headCol, endRow, endCol);
                    if (visited.find(newCode) == visited.end()) {
                        todo.emplace(newCode);
                    }
                }

                decode(cur, headRow, headCol, endRow, endCol);
                if (canCounterClockWise(grid, headRow, headCol, endRow, endCol)) {
                    int newCode = encode(headRow, headCol, endRow, endCol);
                    if (visited.find(newCode) == visited.end()) {
                        todo.emplace(newCode);
                    }
                }
            }
            res++;
        }
        return -1;

    }
private:
    int encode(int headRow, int headCol, int endRow, int endCol) {
        return (headRow << 24) | (headCol << 16) | (endRow << 8) | (endCol);
    }

    void decode(int res, int & headRow, int & headCol, int & endRow, int & endCol) {
        headRow = (res >> 24) & 0xFF;
        headCol = (res >> 16) & 0xFF;
        endRow = (res >> 8) & 0xFF;
        endCol = res & 0xFF;
    }

    bool canRight(std::vector<std::vector<int>> const & grid,
            int & headRow, int & headCol, int & endRow, int & endCol) {
        int newHeadCol = headCol + 1;
        int newEndCol = endCol + 1;
        if (newHeadCol >= grid[headRow].size() ||
                1 == grid[headRow][newHeadCol] ||
                1 == grid[endRow][newEndCol]) {
            return false;
        }
        headCol = newHeadCol;
        endCol = newEndCol;
        return true;
    }

    bool canDown(std::vector<std::vector<int>> const & grid,
            int & headRow, int & headCol, int & endRow, int & endCol) {
        int newHeadRow = headRow + 1;
        int newEndRow = endRow + 1;
        if (newHeadRow >= grid.size() ||
                1 == grid[newHeadRow][headCol] ||
                1 == grid[newEndRow][endCol]) {
            return false;
        }
        headRow = newHeadRow;
        endRow = newEndRow;
        return true;
    }

    bool canClockWise(std::vector<std::vector<int>> const & grid,
            int & headRow, int & headCol, int & endRow, int & endCol) {
        int newHeadRow = endRow + 1;
        if (headRow != endRow ||
                newHeadRow >= grid.size() ||
                (0 != grid[newHeadRow][endCol] + grid[newHeadRow][headCol])) {
            return false;
        }
        headRow = newHeadRow;
        headCol = endCol;
        return true;
    }

    bool canCounterClockWise(std::vector<std::vector<int>> const & grid,
            int & headRow, int & headCol, int & endRow, int & endCol) {
        int newHeadCol = endCol + 1;
        if (headCol != endCol ||
                newHeadCol >= grid[endRow].size() ||
                (0 != grid[endRow][newHeadCol] + grid[headRow][newHeadCol])) {
            return false;
        }
        headRow = endRow;
        headCol = newHeadCol;
        return true;
    }
};
