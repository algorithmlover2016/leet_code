#include "../../head.h"


class Solution {
public:
    std::vector<std::vector<int>> matrixBlockSum(std::vector<std::vector<int>> & mat, int K) {
        if (mat.empty() || mat[0].empty()) {
            return mat;
        }
        int const rowSize = mat.size();
        int const colSize = mat[0].size();
        std::vector<std::vector<int>> ans(rowSize, std::vector<int>(colSize));
        for (int row = 0; row < rowSize; row++) {
            // preSum of each row
            for (int col = 1; col < colSize; col++) {
                mat[row][col] = mat[row][col - 1] + mat[row][col];
            }
        }
        for (int row = 0; row < rowSize; row++) {
            for (int col = 0; col < colSize; col++) {
                int top = std::max(0, row - K);
                int down = std::min(rowSize - 1, row + K);
                int left = std::max(0, col - K);
                int right = std::min(colSize - 1, col + K);
                for (int cntRow = top; cntRow <= down; cntRow++) {
                    ans[row][col] += mat[cntRow][right] - (0 == left ? 0: mat[cntRow][left - 1]);
                }
            }
        }
        return ans;
        
    }
};

class Solution {
public:
    std::vector<std::vector<int>> matrixBlockSum(std::vector<std::vector<int>> & mat, int K) {
        if (mat.empty() || mat[0].empty()) {
            return mat;
        }
        int const rowSize = mat.size();
        int const colSize = mat[0].size();
        std::vector<std::vector<int>> ans(rowSize, std::vector<int>(colSize + 1));
        for (int row = 0; row < rowSize; row++) {
            // preSum of each row
            for (int col = 0; col < colSize; col++) {
                ans[row][col + 1] = ans[row][col] + mat[row][col];
            }
        }
        for (int row = 0; row < rowSize; row++) {
            for (int col = 0; col < colSize; col++) {
                int top = std::max(0, row - K);
                int down = std::min(rowSize - 1, row + K);
                int left = std::max(0, col - K);
                int right = std::min(colSize, col + K + 1);
                mat[row][col] = 0;
                for (int cntRow = top; cntRow <= down; cntRow++) {
                    mat[row][col] += ans[cntRow][right] - ans[cntRow][left];
                }
            }
        }
        return mat;

    }
};

class Solution {
public:
    std::vector<std::vector<int>> matrixBlockSum(std::vector<std::vector<int>> const & mat, int K) {
        int m = mat.size(), n = mat[0].size();
        std::vector<std::vector<int>> sum(m, std::vector<int>(n));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int a = j > 0 ? sum[i][j-1] : 0;
                int b = i > 0 ? sum[i-1][j] : 0;
                int c = i > 0 && j > 0 ? sum[i-1][j-1] : 0;
                sum[i][j] = a + b - c + mat[i][j];
            }
        }

        std::vector<std::vector<int>> res(m, std::vector<int>(n));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int mi = std::min(m-1, i+K);
                int mj = std::min(n-1, j+K);
                int all = sum[mi][mj];
                int a = j-K > 0 ? sum[mi][j-K-1] : 0;
                int b = i-K > 0 ? sum[i-K-1][mj] : 0;
                int c = i-K > 0 && j-K > 0 ? sum[i-K-1][j-K-1] : 0;
                res[i][j] = all - a - b + c;
            }
        }

        return res;
    }
};
