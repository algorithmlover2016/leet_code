#include "../../head.h"



class Solution {
public:
    std::vector<int> hitBricks(std::vector<std::vector<int>> & grid,
            std::vector<std::vector<int>> const & hits) {
        // plagiarizing from https://leetcode.com/problems/bricks-falling-when-hit/discuss/195781/Union-find-Logical-Thinking
        int rowSize = grid.size();
        if (0 == rowSize) {
            return {};
        }
        int colSize = grid[0].size();
        if (0 == colSize) {
            return {};
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

        for (auto const & ele : hits) {
            if (ele.size() < 2) {
                continue;
            }
            if (grid[ele[0]][ele[1]] > 0) {
                grid[ele[0]][ele[1]] = 2; // remark to avoid drop;
            }
        }

        for (int row = 0; row < rowSize; row++) {
            for (int col = 0; col < colSize; col++) {
                if (1 == grid[row][col]) {
                    // std::cout << "\n"<< row << "\t" << col << "\t";
                    unionAround(grid, row, col, parentIndex, connectedNodeCnt);
                }
            }
        }

        int index = hits.size();
        int bricksLeft = connectedNodeCnt[findRoot(parentIndex, 0)];
        std::vector<int> res(index, 0);
        while (--index >= 0) {
            int row = hits[index][0];
            int col = hits[index][1];
            if (0 == grid[row][col]) {
                continue;
            }
            grid[row][col] = 1;
            // std::cout << "\nwhile";
            unionAround(grid, row, col, parentIndex, connectedNodeCnt); // change the pos to 1, maybe add some not dropped node. these nodes are all be contributed by this pos
            int newBricksLeft = connectedNodeCnt[findRoot(parentIndex, 0)];
            res[index] = std::max(0, newBricksLeft - bricksLeft - 1);
            bricksLeft = newBricksLeft;
        }
        return res;
    }

private:
    static int const DIRECTION_ARRAY_SIZE = 5;
    static int const DIRECTION_SIZE = DIRECTION_ARRAY_SIZE - 1;
    static std::array<int, DIRECTION_ARRAY_SIZE> directions;

    int getIndex(int x, int y, int colSize) {
        return x * colSize + y + 1;
    }

    void unionAround(std::vector<std::vector<int>> const & grid,
            int row, int col,
            std::vector<int> & parentIndex,
            std::vector<int> & connectedNodeCnt) {
        int newIndex = getIndex(row, col, grid[row].size());
        for (int index = 0; index < DIRECTION_SIZE; index++) {
            int nextRow = directions[index] + row;
            int nextCol = directions[index + 1] + col;
            if (nextRow >= 0 && nextRow < grid.size() &&
                    nextCol >= 0 && nextCol < grid[nextRow].size() &&
                    1 == grid[nextRow][nextCol]) {

                // std::cout << "union: " << row << "\t" << col << "\tto: " << nextRow << "\t" << nextCol << "\t";
                unionNode(parentIndex, connectedNodeCnt, newIndex, getIndex(nextRow, nextCol, grid[nextRow].size()));
            }
        }
        if (0 == row) {
            unionNode(parentIndex, connectedNodeCnt, 0, newIndex);
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
std::array<int, Solution::DIRECTION_ARRAY_SIZE> Solution::directions = {0, 1, 0, -1, 0};
