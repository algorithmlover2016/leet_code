#include "../../head.h"


class SolutionWrong {
public:
    std::vector<std::vector<std::string>> solveNQueens(int n) {
        std::vector<bool> used(n, false);
        std::vector<std::vector<std::string>> ans;
        std::vector<std::string> res;
        for (int idx = 0; idx < n; idx++) {
            backTracking(n, idx, used, ans, res);
        }
        return ans;
    }
    void backTracking(int n,
                      int lastIdx,
                      std::vector<bool> & used,
                      std::vector<std::vector<std::string>> & ans,
                      std::vector<std::string> res) {
        if (n == res.size()) {
            ans.emplace_back(res);
            return;
        }
        for (int idx = 0; idx < n; idx++) {
            std::string idxStr(n, '.');
            if (used[idx] ||
                    (idx == lastIdx + 1) ||
                    (idx + 1 < lastIdx)) {
                continue;
            }
            used[idx] = true;;
            idxStr[idx] = 'Q';
            res.emplace_back(idxStr);
            backTracking(n, idx, used, ans, res);
            res.pop_back();
            used[idx] = false;
        }
    }

};

class SolutionBaseLoop {
public:
    std::vector<std::vector<std::string>> solveNQueens(int n) {
        // plagiarizing from https://leetcode.com/problems/n-queens/discuss/19808/Accepted-4ms-c%2B%2B-solution-use-backtracking-and-bitmask-easy-understand.
        std::vector<std::vector<std::string>> ans;
        std::vector<std::string> res(n, std::string(n, '.'));
        backTracking(0, n, ans, res);
        return ans;
    }

    void backTracking(int row, int n,
            std::vector<std::vector<std::string>> & ans,
            std::vector<std::string> res) {
        // std::cout << "row: " << row << '\n';
        if (row == n) {
            ans.emplace_back(res);
            return;
        }
        for (int col = 0; col < n; col++) {
            if (isValid(res, row, col, n)) {
                res[row][col] = 'Q';
                backTracking(row + 1, n, ans, res);
                res[row][col] = '.';
            }
        }
    }

    bool isValid(std::vector<std::string> const & res, int row, int col, int n) {
        for (int rowIdx = 0; rowIdx < row; rowIdx++) {
            if ('Q' == res[rowIdx][col]) {
                return false;
            }
        }

        // judge the tan45 1(y = x + b)
        for (int row45 = row- 1, col45 = col + 1; row45 >= 0 && col45 < n; row45--, col45++) {
            if ('Q' == res[row45][col45]) {
                return false;
            }
        }

        // judge the tan135 -1 (y = -x + b)
        for (int row135 = row - 1, col135 = col - 1; row135 >= 0 && col135 >= 0; row135--, col135--) {
            if ('Q' == res[row135][col135]) {
                return false;
            }
        }

        return true;
    }
};


class Solution {
public:
    std::vector<std::vector<std::string>> solveNQueens(int n) {
        // plagiarizing from https://leetcode.com/problems/n-queens/discuss/19808/Accepted-4ms-c%2B%2B-solution-use-backtracking-and-bitmask-easy-understand.
        // (row, col) and row range from 0 to n(not include)
        std::vector<int> notUse(n, 0);

        // (row, col) the slope is y = x + b. b is from -(n - 1) to n - 1.
        // because the index >= 0. so we add an offset n-1. so b range from 0 to 2n - 2; total 2n - 1 numbers
        // the index can be represent by n - 1 + x - y which is b because b is the line
        std::vector<int> lineSlope45(2 * n - 1, 0);

        // (row, col) the slope is y = -x + b. b is from 0 to 2n -2, total 2n - 1 numbers
        // the index can be represent by x + y
        std::vector<int> lineSlope135(2 * n - 1, 0);

        std::vector<std::vector<std::string>> ans;
        std::vector<std::string> res(n, std::string(n, '.'));
        backTracking(0, n, notUse, lineSlope45, lineSlope135, res, ans);
        return ans;
    }
    void backTracking(int row,
            int n,
            std::vector<int> & notUse,
            std::vector<int> & lineSlope45,
            std::vector<int> & lineSlope135,
            std::vector<std::string> res,
            std::vector<std::vector<std::string>> & ans) {
        if (row == n) {
            ans.emplace_back(res);
            return;
        }
        for (int col = 0; col < n; col++) {
            if (notUse[col] ||
                    lineSlope45[n - 1 + col - row] ||
                    lineSlope135[row + col]) {
                continue;
            }
            res[row][col] = 'Q';
            notUse[col] = lineSlope45[n - 1 + col - row] = lineSlope135[row + col] = 1;
            backTracking(row + 1, n, notUse, lineSlope45, lineSlope135, res, ans);
            res[row][col] = '.';
            notUse[col] = lineSlope45[n - 1 + col - row] = lineSlope135[row + col] = 0;
        }
    }
};
