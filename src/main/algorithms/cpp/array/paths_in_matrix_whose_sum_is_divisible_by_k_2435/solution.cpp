#include "../../head.h"


class SolutionTLE {
public:
    int numberOfPaths(std::vector<std::vector<int>> const & grid, int k) {
        int ans = 0;
        dfs(grid, 0, 0, 0, k, ans);
        return ans;
    }
private:
    void dfs(std::vector<std::vector<int>> const & grids, int row, int col, int sum, int k, int & ans) {
        int const rows = grids.size();
        int const cols = grids.back().size();
        sum += grids[row][col];
        if (rows - 1 == row && cols - 1 == col) {
            ans += (0 == sum % k);
            ans %= MOD;
            return;
        }
        for (int idx = 0; idx < DIRECTION_SIZE; idx++) {
            int nextRow = row + directions[idx];
            int nextCol = col + directions[idx + 1];
            if (0 <= nextRow && nextRow < rows &&
                0 <= nextCol && nextCol < cols) {
                dfs(grids, nextRow, nextCol, sum, k, ans);
            }
        }
    }
private:
    static int constexpr MOD = 1e9 + 7;
    static int constexpr DIRECTION_LEN = 3;
    static int constexpr DIRECTION_SIZE = DIRECTION_LEN - 1;
    static std::array<int, DIRECTION_LEN> directions;
};
std::array<int, SolutionTLE::DIRECTION_LEN> SolutionTLE::directions{{0, 1, 0}};

class Solution {
public:
    int numberOfPaths(std::vector<std::vector<int>> const & grid, int k) {
        // plagiarizing from https://leetcode.com/problems/paths-in-matrix-whose-sum-is-divisible-by-k/solutions/2678788/memoise-mod-k/
        if (grid.empty() || grid.back().empty()) {
            return 0;
        }
        int const ROWS = grid.size();
        int const COLS = grid[0].size();
        std::vector<std::vector<std::vector<int>>> dpMemo(ROWS, std::vector<std::vector<int>>(COLS, std::vector<int>(MAXK + 1, INIT_VAL)));
        std::function<int(int ,int, int)> dfs = [&] (int row, int col, int mod) -> int {
            if (row >= ROWS || col >= COLS) {
                return 0;
            }
            if (ROWS - 1 == row && COLS - 1 == col) {
                return (mod + grid[row][col]) % k ? 0 : 1;
            }
            if (INIT_VAL == dpMemo[row][col][mod]) {
                int nextMod = (mod + grid[row][col]) % k;
                dpMemo[row][col][mod] = (OFFSET +
                                         dfs(row + 1, col, nextMod) +
                                         dfs(row, col + 1, nextMod)) % MOD;
            }
            return dpMemo[row][col][mod] - OFFSET;

        };
        return dfs(0, 0, 0);
    }

private:
    static int constexpr MOD = 1e9 + 7;
    static int constexpr MAXK = 50;
    static int constexpr INIT_VAL = 0;
    static int constexpr OFFSET = 1;
};


class Solution {
public:
    int numberOfPaths(std::vector<std::vector<int>> const & grid, int k) {
        // plagiarizing from https://leetcode.com/problems/paths-in-matrix-whose-sum-is-divisible-by-k/solutions/2678788/memoise-mod-k/
        if (grid.empty() || grid.back().empty()) {
            return 0;
        }
        int const ROWS = grid.size();
        int const COLS = grid[0].size();
        std::vector<std::vector<int>> curRowsMemo(COLS + 1, std::vector<int>(MAXK, 0)), upperRowMemo(curRowsMemo);
        upperRowMemo[1][0] = 1; // there is no row here, so there is only one module which is 0.
        for (int row = 0; row < ROWS; row++) {
            for (int col = 0; col < COLS; col++) {
                for (int mod = 0; mod < k; mod++) {
                    curRowsMemo[col + 1][(mod + grid[row][col]) % k] = (curRowsMemo[col][mod] + upperRowMemo[col + 1][mod]) % MOD;
                }
            }
            std::swap(curRowsMemo, upperRowMemo);
        }
        return upperRowMemo[COLS][0];
    }
private:
    static int constexpr MOD = 1e9 + 7;
    static int constexpr MAXK = 50;
};