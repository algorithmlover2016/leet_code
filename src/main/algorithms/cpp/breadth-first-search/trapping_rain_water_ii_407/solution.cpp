#include "../../head.h"


class Solution {
public:
    int trapRainWater(std::vector<std::vector<int>> const & heightMap) {
        // plagiarizing from https://leetcode.com/problems/trapping-rain-water-ii/discuss/89461/Java-solution-using-PriorityQueue
        int rowSize = heightMap.size();
        if (0 == rowSize) {
            return 0;
        }
        int colSize = heightMap[0].size();
        if (0 == colSize) {
            return 0;
        }
        std::priority_queue<CoordinateHeight> todo;
        std::vector<std::vector<bool>> visited(rowSize, std::vector<bool>(colSize, false));

        // add the column of the border
        for (int row = 0, lastCol = colSize - 1; row < rowSize; row++) {
            todo.emplace(CoordinateHeight(heightMap[row][0], row, 0));
            todo.emplace(CoordinateHeight(heightMap[row][lastCol], row, lastCol));
            visited[row][0] = true;
            visited[row][lastCol] = true;
        }

        // add the row of the border
        for (int col = 1, lastRow = rowSize - 1, lastCol = colSize - 1; col < lastCol; col++) {
            todo.emplace(CoordinateHeight(heightMap[0][col], 0, col));
            todo.emplace(CoordinateHeight(heightMap[lastRow][col], lastRow, col));
            visited[0][col] = true;
            visited[lastRow][col] = true;
        }

        int res = 0;
        while (todo.size()) {
            auto const & cur = todo.top();
            int curHeight = cur.height; int curRow = cur.row; int curCol = cur.col;
            todo.pop();
            for (int index = 0; index < DIRECTION_SIZE; index++) {
                int nextRow = curRow + directions[index];
                int nextCol = curCol + directions[index + 1];
                if (nextRow >= 0 && nextRow < rowSize &&
                        nextCol >= 0 && nextCol < colSize &&
                        !visited[nextRow][nextCol]) {
                    visited[nextRow][nextCol] = true;
                    if (heightMap[nextRow][nextCol] <= curHeight) {
                        res += curHeight - heightMap[nextRow][nextCol];
                        todo.emplace(CoordinateHeight(curHeight, nextRow, nextCol));
                    } else {
                        todo.emplace(CoordinateHeight(heightMap[nextRow][nextCol], nextRow, nextCol));
                    }
                }
            }
        }
        return res;
    }
private:
    struct CoordinateHeight {
        int height;
        int row;
        int col;
        CoordinateHeight(int height_ = 0, int row_ = 0, int col_ = 0) :
            height(height_), row(row_), col(col_) {
        }
        bool operator<(CoordinateHeight const & other) const {
            return height > other.height; // to make the minimum heap
        }
    };
private:
    static int const DIRECTION_ARRAY_SIZE = 5;
    static int const DIRECTION_SIZE = DIRECTION_ARRAY_SIZE - 1;
    static std::array<int, DIRECTION_ARRAY_SIZE> directions;
};
std::array<int, Solution::DIRECTION_ARRAY_SIZE> Solution::directions = {0, 1, 0, -1, 0};

class SolutionBetterRunTime {
public:
    int trapRainWater(std::vector<std::vector<int>> const & heightMap) {
        int result = 0;
        int m = heightMap.size();
        if (m == 0) {
            return result;
        }
        int n = heightMap[0].size();
        std::vector<std::vector<int>> temp = heightMap;
        for (int i = 1; i < m - 1; i++)
            for (int j = 1; j < n - 1; j++)
                temp[i][j] = std::max(heightMap[i][j], std::min(temp[i - 1][j], temp[i][j - 1]));

        for (int i = m - 2; i > 0; i--)
            for (int j = n - 2; j > 0; j--)
                temp[i][j] = std::max(heightMap[i][j], std::min(temp[i][j], std::min(temp[i + 1][j], temp[i][j + 1])));

        for (int i = 1; i < m - 1; i++)
            for (int j = 1; j < n - 1; j++)
                recompute(temp, heightMap, m, n, i, j);

        for (int i = 1; i < m - 1; i++)
            for (int j = 1; j < n - 1; j++)
                result += temp[i][j] - heightMap[i][j];
        return result;
    }

    void recompute(std::vector<std::vector<int>>& temp, const std::vector<std::vector<int>>& heightMap, int m, int n, int i, int j) {
        if (i == 0 || j == 0 || i == m - 1 || j == n - 1) return;
        int height = std::max(heightMap[i][j],
                std::min(temp[i][j],
                    std::min(temp[i - 1][j],
                        std::min(temp[i][j - 1],
                            std::min(temp[i + 1][j], temp[i][j + 1])))));
        if (height == temp[i][j]) return;
        temp[i][j] = height;
        recompute(temp, heightMap, m, n, i + 1, j);
        recompute(temp, heightMap, m, n, i - 1, j);
        recompute(temp, heightMap, m, n, i, j + 1);
        recompute(temp, heightMap, m, n, i, j - 1);
    }
};
