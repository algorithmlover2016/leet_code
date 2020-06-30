#include "../../head.h"



class Solution {
public:
    int numIslands(std::vector<std::vector<char>> & grid) {
        // plagiarizing from https://leetcode.com/problems/bricks-falling-when-hit/discuss/195781/Union-find-Logical-Thinking
        int rowSize = grid.size();
        if (0 == rowSize) {
            return 0;
        }
        int colSize = grid[0].size();
        if (0 == colSize) {
            return 0;
        }
        /*
           init union-find variables
           */
        int const unionMaxIndex = rowSize * colSize + 1; // 0 means the top
        std::vector<int> parentIndex(unionMaxIndex, -1);
        std::vector<int> connectedNodeCnt(unionMaxIndex, 1);
        for (int index = 0; index < parentIndex.size(); index++) {
            parentIndex[index] = index;
        }

        for (int row = 0; row < rowSize; row++) {
            for (int col = 0; col < colSize; col++) {
                if ('1' == grid[row][col]) {
                    // std::cout << "\n"<< row << "\t" << col << "\t";
                    unionAround(grid, row, col, parentIndex, connectedNodeCnt);
                }
            }
        }

        std::set<int> root;
        for (int row = 0; row < rowSize; row++) {
            for (int col = 0; col < colSize; col++) {
                if ('1' == grid[row][col]) {
                    int rt = findRoot(parentIndex, getIndex(row, col, colSize));
                    root.emplace(rt);

                }
            }
        }
        return root.size();
    }

    private:
    static int const DIRECTION_ARRAY_SIZE = 3;
    static int const DIRECTION_SIZE = DIRECTION_ARRAY_SIZE - 1;
    static std::array<int, DIRECTION_ARRAY_SIZE> directions;

    int getIndex(int x, int y, int colSize) {
        return x * colSize + y + 1;
    }

    void unionAround(std::vector<std::vector<char>> const & grid,
                     int row, int col,
                     std::vector<int> & parentIndex,
                     std::vector<int> & connectedNodeCnt) {
        int newIndex = getIndex(row, col, grid[row].size());
        for (int index = 0; index < DIRECTION_SIZE; index++) {
            int nextRow = directions[index] + row;
            int nextCol = directions[index + 1] + col;
            if (nextRow >= 0 && nextRow < grid.size() &&
                nextCol >= 0 && nextCol < grid[nextRow].size() &&
                '1' == grid[nextRow][nextCol]) {

                // std::cout << "union: " << row << "\t" << col << "\tto: " << nextRow << "\t" << nextCol << "\t";
                unionNode(parentIndex, connectedNodeCnt, newIndex, getIndex(nextRow, nextCol, grid[nextRow].size()));
            }
        }
    }

    int findRoot(std::vector<int> const & parentIndex, int index) {
        while (index >= 0 && index < parentIndex.size() && index != parentIndex[index]) {
            index = parentIndex[index];
        }
        return index;
    }
    int unionNode(std::vector<int> & parentIndex, std::vector<int> & cnt, int left, int right) {
        if (left < 0 || left >= parentIndex.size() ||
            right < 0 || right >= parentIndex.size()) {
            return -1;
        }
        int leftRoot = findRoot(parentIndex, left);
        int rightRoot = findRoot(parentIndex, right);
        if (leftRoot == rightRoot) {
            return cnt[leftRoot];
        }
        int count = cnt[leftRoot] + cnt[rightRoot];
        parentIndex[leftRoot] = rightRoot;
        cnt[rightRoot] = count;
        // std::cout << "left, right: " << left << "\t" << right << "\tto " << leftRoot << "\t" << rightRoot << "\tcount: " << count << "\t";
        return count;
    }
};
std::array<int, Solution::DIRECTION_ARRAY_SIZE> Solution::directions = {0, 1, 0};
// std::array<int, Solution::DIRECTION_ARRAY_SIZE> Solution::directions = {0, 1, 0, -1, 0};

static int x = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  return 0;
}();

struct Position {
    int row;
    int column;

    Position(int row, int column) : row(row), column(column) {}
};

class SolutionBFS {
public:
    int numIslands(std::vector<std::vector<char>> & grid) {
        std::queue<Position> q;
        int count = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (grid[i][j] == '1') {
                    q.push(Position(i, j));
                    count++;
                    while (q.size() > 0) {
                        auto pos = q.front();
                        q.pop();
                        if (grid[pos.row][pos.column] != '1') { continue; }
                        grid[pos.row][pos.column] = '2';
                        if (pos.row > 0 && grid[pos.row - 1][pos.column] == '1') { q.push(Position(pos.row - 1, pos.column)); }
                        if (pos.row + 1 < grid.size() && grid[pos.row + 1][pos.column] == '1') { q.push(Position(pos.row + 1, pos.column)); }
                        if (pos.column > 0 && grid[pos.row][pos.column - 1] == '1') { q.push(Position(pos.row, pos.column - 1)); }
                        if (pos.column + 1 < grid[i].size() && grid[pos.row][pos.column + 1] == '1') { q.push(Position(pos.row, pos.column + 1)); }
                    }
                }
            }
        }
        return count;
    }
};
