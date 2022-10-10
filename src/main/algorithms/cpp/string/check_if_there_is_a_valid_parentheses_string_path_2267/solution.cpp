#include "../../head.h"


// #define DEBUG
class SolutionTLE {
public:
    bool hasValidPath(std::vector<std::vector<char>> const & grid) {
        if (grid.empty() || grid[0].empty()) {
            return false;
        }
        return dfsBackTracking(grid, 0, 0, 0);
    }
private:
    bool dfsBackTracking(std::vector<std::vector<char>> const & grid, int row, int col, int p) {
        #ifdef DEBUG
        std::cout << "cur (" << row << ", " << col << "): " << p << "\n";
        #endif
        if (0 > p) {
            #ifdef DEBUG
            std::cout << "fail in path\n";
            #endif
            return false;
        }
        if (LEFT_PARENTHESE == grid[row][col]) {
            p++;
        } else if (RIGHT_PARENTHESE == grid[row][col]) {
            p--;
        }
        if (row == grid.size() - 1 && col == grid[row].size() - 1) {
            return 0 == p;
        }
        for (int idx = 0; idx < DIRECTION; idx++) {
            int nextRow = row + directions[idx];
            int nextCol = col + directions[idx + 1];
            #ifdef DEBUG
            std::cout << "next (" << nextRow << ", " << nextCol << ")\n";
            #endif
            if (nextRow < grid.size() && nextCol < grid[nextRow].size() && dfsBackTracking(grid, nextRow, nextCol, p)) {
                return true;
            }
        }
        return false;
    }
private:
    char constexpr static LEFT_PARENTHESE = '(';
    char constexpr static RIGHT_PARENTHESE = ')';
    constexpr int static DIRECTION_SIZE = 3;
    constexpr int static DIRECTION = 2;
    std::array<int, DIRECTION_SIZE> static directions;
};
std::array<int, SolutionTLE::DIRECTION_SIZE> SolutionTLE::directions = {{0, 1, 0}};

#define DEBUG
class SolutionWrong {
public:
    bool hasValidPath(std::vector<std::vector<char>> const & grid) {
        if (grid.empty() || grid[0].empty()) {
            return false;
        }
        std::vector<std::vector<int>> dpMemo(grid.size(), std::vector<int>(grid[0].size(), INIT_VAL));
        // for backTracking, we can not use memorizing operation becasue it can not represent all the ways to the cur pos
        return dfsBackTracking(grid, 0, 0, 0, dpMemo);
    }
private:
    bool dfsBackTracking(std::vector<std::vector<char>> const & grid, int row, int col, int p, std::vector<std::vector<int>> & dpMemo) {
        #ifdef DEBUG
        std::cout << "cur (" << row << ", " << col << "): " << p << "\n";
        #endif
        if (dpMemo[row][col] != INIT_VAL) {
            return dpMemo[row][col] > 0;
        }
        if (0 > p) {
            #ifdef DEBUG
            std::cout << "fail in path\n";
            #endif
            return dpMemo[row][col] = false;
        }
        if (LEFT_PARENTHESE == grid[row][col]) {
            p++;
        } else if (RIGHT_PARENTHESE == grid[row][col]) {
            p--;
        }
        if (row == grid.size() - 1 && col == grid[row].size() - 1) {
            return dpMemo[row][col] = (0 == p);
        }
        for (int idx = 0; idx < DIRECTION; idx++) {
            int nextRow = row + directions[idx];
            int nextCol = col + directions[idx + 1];
            #ifdef DEBUG
            std::cout << "next (" << nextRow << ", " << nextCol << ")\n";
            #endif
            if (nextRow < grid.size() && nextCol < grid[nextRow].size() && dfsBackTracking(grid, nextRow, nextCol, p, dpMemo)) {
                return dpMemo[nextRow][nextCol] = false;
            }
        }
        return dpMemo[row][col] = false;
    }
private:
    char constexpr static LEFT_PARENTHESE = '(';
    char constexpr static RIGHT_PARENTHESE = ')';
    constexpr int static DIRECTION_SIZE = 3;
    constexpr int static DIRECTION = 2;
    std::array<int, DIRECTION_SIZE> static directions;
    int constexpr static INIT_VAL = -1;
};
std::array<int, SolutionWrong::DIRECTION_SIZE> SolutionWrong::directions = {{0, 1, 0}};
int constexpr SolutionWrong::INIT_VAL;

// #define DEBUG
class Solution {
public:
    bool hasValidPath(std::vector<std::vector<char>> const & grid) {
        // plagiarizing from https://leetcode.com/problems/check-if-there-is-a-valid-parentheses-string-path/solutions/2017740/dfs/ 
        // and https://leetcode.com/problems/check-if-there-is-a-valid-parentheses-string-path/solutions/2017937/simple-dfs-dp/
        if (grid.empty() || grid[0].empty()) {
            return false;
        }
        if (0 == (1 & (grid.size() + grid.back().size()))) {
            // any path from (0, 0) to (1, 1) must have m + n - 1 letters, and to get a valid path, the number of letters must be even.
            // So m + n must be odd;
            return false;
        }
        std::vector<std::vector<std::vector<int>>> dpMemo(grid.size(), std::vector<std::vector<int>>(grid[0].size(), std::vector<int>(MAX_NUM, INIT_VAL)));
        // for backTracking, we can not use memorizing operation becasue it can not represent all the ways to the cur pos
        return dfsBackTracking(grid, 0, 0, 0, dpMemo);
    }
private:
    bool dfsBackTracking(std::vector<std::vector<char>> const & grid, int row, int col, int p, std::vector<std::vector<std::vector<int>>> & dpMemo) {
        #ifdef DEBUG
        std::cout << "cur (" << row << ", " << col << "): " << p << "\n";
        #endif
        int const ROWS = grid.size();
        int const COLS = grid[row].size();
        if (LEFT_PARENTHESE == grid[row][col]) {
            p++;
        } else if (RIGHT_PARENTHESE == grid[row][col]) {
            p--;
        }
        if (0 > p || p > (ROWS + COLS) / 2) {
            #ifdef DEBUG
            std::cout << "fail in path\n";
            #endif
            return false;
        }
        if (dpMemo[row][col][p] != INIT_VAL) {
            return dpMemo[row][col][p];
        }
        if (row == grid.size() - 1 && col == grid[row].size() - 1) {
            return dpMemo[row][col][p] = (0 == p);
        }
        for (int idx = 0; idx < DIRECTION; idx++) {
            int nextRow = row + directions[idx];
            int nextCol = col + directions[idx + 1];
            #ifdef DEBUG
            std::cout << "next (" << nextRow << ", " << nextCol << ")\n";
            #endif
            if (nextRow < grid.size() && nextCol < grid[nextRow].size() && dfsBackTracking(grid, nextRow, nextCol, p, dpMemo)) {
                return dpMemo[nextRow][nextCol][p] = true;
            }
        }
        return dpMemo[row][col][p] = false;
    }
private:
    int constexpr static MAX_NUM = 100 + 1; // each path will have m + n - 1 characters and the valid path must have (m + n - 1) / 2 left and right parentheses seperaterly.
    char constexpr static LEFT_PARENTHESE = '(';
    char constexpr static RIGHT_PARENTHESE = ')';
    constexpr int static DIRECTION_SIZE = 3;
    constexpr int static DIRECTION = 2;
    std::array<int, DIRECTION_SIZE> static directions;
    int constexpr static INIT_VAL = -1;
};
std::array<int, Solution::DIRECTION_SIZE> Solution::directions = {{0, 1, 0}};
int constexpr Solution::INIT_VAL;