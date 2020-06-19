#include "../../head.h"


class Solution {
public:
    int minPathSum(std::vector<std::vector<int>> const & grid) {
        int rowSize = grid.size();
        if (0 == rowSize) {
            return 0;
        }
        int colSize = grid[0].size();
        if (0 == colSize) {
            return 0;
        }
        std::vector<std::vector<int> > dpSum(rowSize, std::vector<int>(colSize, 0));
        for (int row = 0; row < grid.size(); row++) {
            for (int col = 0; col < grid[row].size(); col++) {
                int upRow = row - 1;
                int minNum = INT_MAX;
                if (upRow >= 0) {
                    minNum = std::min(minNum, dpSum[upRow][col]);

                }
                int leftCol = col - 1;
                if (leftCol >= 0) {
                    minNum = std::min(minNum, dpSum[row][leftCol]);
                }
                if (INT_MAX == minNum) {
                    minNum = 0;
                }
                dpSum[row][col] = minNum + grid[row][col];
                // std::cout << "dp: " << dpSum[row][col] << "\n";
            }
        }
        return dpSum[rowSize - 1][colSize - 1];
    }
};

class Solution {
public:
    int minPathSum(std::vector<std::vector<int>> const & grid) {
        int n = grid.size(), m = grid[0].size();
        std::vector<std::vector<int>> v(n, std::vector<int>(m, INT_MAX));
        v[0][0] = grid[0][0];
        for (int i = 0; i < n; i++) {
            for(int j = 0;j < m; j++) {
                if(i >= 1)
                    v[i][j] = std::min(v[i][j], v[i - 1][j] + grid[i][j]);
                if(j >= 1)
                    v[i][j] = std::min(v[i][j], v[i][j - 1] + grid[i][j]);
            }
        }
        return v[n - 1][m - 1];
    }
};
