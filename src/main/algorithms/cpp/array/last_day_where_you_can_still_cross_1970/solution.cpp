#include "../../head.h"



// #define DEBUG
class SolutionBinarySearchBFS {
public:
    int latestDayToCross(int row, int col, std::vector<std::vector<int>> const & cells) {
        // plagiarizing from https://leetcode.com/problems/last-day-where-you-can-still-cross/discuss/1403907/C%2B%2BJavaPython-Binary-Search-and-BFS-Clean-and-Concise
        int const cellsSize = cells.size();
        if (0 == cellsSize) {
            return row * col;
        }
        int left = 1, right = cellsSize;
        int ans = 0;
        while (left <= right) {
            int mid = (left + right + 1) / 2;
            #ifdef DEBUG
            std::cout << "left, right, mid: " << left << ", " << right << ", " << mid << "\n";
            #endif
            
            if (canThrough(cells, row, col, mid)) {
                ans = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return ans;
    }
private:
    bool canThrough(std::vector<std::vector<int>> const & cells, int const row, int const col, int mid) {
        int const cellsSize = cells.size();
        std::vector<std::vector<bool>> grids(row, std::vector<bool>(col, GRID_INIT_STATUS));
        for (int idx = 0; idx < mid; idx++) {
            auto const & cell = cells[idx];
            assert(CELL_SIZE == cell.size());
            grids[cell[CELL_FIRST_IDX] - 1][cell[CELL_SECOND_IDX] - 1] = GRID_BLOCK_STATUS;
        }
        std::queue<std::pair<int, int>> bfsQue;
        for (int idx = 0; idx < col; idx++) {
            if (GRID_INIT_STATUS == grids[FIRST_ROW][idx]) {
                bfsQue.emplace(std::make_pair(FIRST_ROW, idx));
                grids[FIRST_ROW][idx] = GRID_BLOCK_STATUS;
            }
        }
        while (!bfsQue.empty()) {
            auto [curRow, curCol] = bfsQue.front(); bfsQue.pop();
            if (row - 1 == curRow) {
                return true;
            }
            for (int direcIdx = 0; direcIdx < DIRECTION_SIZE; direcIdx++) {
                int nextRow = curRow + directions[direcIdx];
                int nextCol = curCol + directions[direcIdx + 1];
                if (nextRow < 0 || nextRow == row ||
                    nextCol < 0 || nextCol == col ||
                    GRID_BLOCK_STATUS == grids[nextRow][nextCol]) {
                        continue;
                    }
                grids[nextRow][nextCol] = GRID_BLOCK_STATUS;
                bfsQue.push({nextRow, nextCol});
            }
        }
        return false;
    }
private:
    static int const FIRST_ROW = 0;
    bool const GRID_INIT_STATUS = true;
    bool const GRID_BLOCK_STATUS = false;
    static int const CELL_SIZE = 2;
    static int const CELL_FIRST_IDX = 0;
    static int const CELL_SECOND_IDX = 1;
    static int const DIRECTION_SIZE = 4;
    static std::array<int, DIRECTION_SIZE + 1> directions;
};
std::array<int, SolutionBinarySearchBFS::DIRECTION_SIZE + 1> SolutionBinarySearchBFS::directions = {0, 1, 0, -1, 0};

class Solution {
private:
    class UnionFind {
    public:
        UnionFind(int size) {
            parents.resize(size);
            cnts.resize(size);
            ranks.resize(size);
            std::iota(parents.begin(), parents.end(), 0);
            std::vector<int>(size, 0).swap(ranks);
            std::vector<int>(size, 1).swap(cnts);
        };
        int Find(int idx) {
            assert(idx < parents.size());
            int inputIdx = idx;
            while (idx != parents[idx]) {
                idx = parents[idx];
            }
            return parents[inputIdx] = idx;
        }

        int FindRecursive(int idx) {
            assert(idx < parents.size());
            if (idx == parents[idx]) {
                return idx;
            }
            return parents[idx] = FindRecursive(parents[idx]);
        }

        int UnionWithCntAndRank(int left, int right) {
            int leftRoot = Find(left);
            int rightRoot = Find(right);
            if (leftRoot == rightRoot) {
                return cnts[leftRoot];
            }
            if (ranks[leftRoot] > ranks[rightRoot]) {
                std::swap(leftRoot, rightRoot);
            } else if (ranks[leftRoot] == ranks[rightRoot]) {
                ranks[rightRoot] += 1;
            }
            parents[leftRoot] = rightRoot;
            return cnts[rightRoot] += cnts[leftRoot];
        }

    private:
        std::vector<int> parents;
        std::vector<int> cnts;
        std::vector<int> ranks;
    };
public:
    int latestDayToCross(int row, int col, std::vector<std::vector<int>> const & cells) {
        // plagiarizing from https://leetcode.com/problems/last-day-where-you-can-still-cross/discuss/1403930/Python-Union-Find-solution-explained
        // and https://leetcode.com/problems/last-day-where-you-can-still-cross/discuss/1404313/Two-Union-Find-Approaches
        // first, we arrive the last day, which is row * col == cells.length. It means all the grids are water, which is 1;
        std::vector<std::vector<bool>> grids(row, std::vector<bool>(col, WATER_FLAG));
        int const ALLStatus = row * col;
        UnionFind ufObj(ALLStatus + 2);
        for (int idx = cells.size() - 1; idx > LEFT_MOST_EXCLUDED; idx--) {
            auto const & cell = cells[idx];
            assert(CELL_SIZE == cell.size());
            int curRow = cell[CELL_ROW_IDX] - 1;
            int curCol = cell[CELL_COL_IDX] - 1;
            grids[curRow][curCol] = LAND_FLAG;
            int curIdx = getIndex(curRow, curCol, col);
            
            for (int directionIdx = 0; directionIdx < DIRECTION_SIZE; directionIdx++) {
                int nextRow = curRow + directions[directionIdx];
                int nextCol = curCol + directions[directionIdx + 1];
                if (nextRow < 0 || nextRow == row ||
                    nextCol < 0 || nextCol == col ||
                    WATER_FLAG == grids[nextRow][nextCol]) {
                        continue;
                    }
                int nextIdx = getIndex(nextRow, nextCol, col);
                ufObj.UnionWithCntAndRank(curIdx, nextIdx);
            }
            if (TOP_ROW == curRow) {
                ufObj.UnionWithCntAndRank(TOP_ROW, curIdx);
            } else if (row - 1 == curRow) {
                // it's the last row or named bottom row
                ufObj.UnionWithCntAndRank(ALLStatus + 1, curIdx);
            }
            if (ufObj.Find(TOP_ROW) == ufObj.Find(ALLStatus + 1)) {
                return idx;
            }
        }
        return -1;
    }
private:
    int getIndex(int curRow /*start from zero */, int curCol /* start from zero */, int const COL) {
        return (curRow * COL) + curCol + 1; // return an index starting from one
    }
private:
    bool const WATER_FLAG = false;
    bool const LAND_FLAG = true;
    static int const TOP_ROW = 0;
    static int const LEFT_MOST_EXCLUDED = -1;
    static int const CELL_SIZE = 2;
    static int const CELL_ROW_IDX = 0;
    static int const CELL_COL_IDX = 1;
    static int const DIRECTION_SIZE = 4;
    static std::array<int, DIRECTION_SIZE + 1> directions;
};
std::array<int, Solution::DIRECTION_SIZE + 1> Solution::directions = {0, 1, 0, -1, 0};