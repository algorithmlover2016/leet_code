#include "../../head.h"


class SolutionBruteForceSolution {
public:
    int uniquePathsWithObstacles(std::vector<std::vector<int>> obstacleGrid) {
        int const rowSize = obstacleGrid.size();
        if (0 == rowSize) {
            return 0;
        }
        int const colSize = obstacleGrid[0].size();
        if (0 == colSize) {
            return 0;
        }
        std::vector<std::vector<int>> memo(rowSize, std::vector<int>(colSize, 0));
        return dfsHelper(memo, obstacleGrid, 0, 0);
    }

private:
    int dfsHelper(std::vector<std::vector<int>> & memo,
                  std::vector<std::vector<int>> & obstacleGrid,
                  int startRow, int startCol) {
        if (!checkValid(obstacleGrid, startRow, startCol)) {
            return 0;
        }
        if (startRow == obstacleGrid.size() - 1 && startCol == obstacleGrid[startRow].size() - 1) {
            return 1;
        }
        if (0 != memo[startRow][startCol]) {
            return memo[startRow][startCol];
        }
        // obstacleGrid[startRow][startCol] = -1;
        int ans = 0;
        for (int index = 0; index < DIRECTION_SIZE; index++) {
            ans += dfsHelper(memo, obstacleGrid, startRow + directions[index], startCol + directions[index + 1]);
        }
        // obstacleGrid[startRow][startCol] = 0;
        return memo[startRow][startCol] = ans;
    }

    bool checkValid(std::vector<std::vector<int>> const & obstacleGrid, int startRow, int startCol) {
        if (startRow >= 0 && startRow < obstacleGrid.size() &&
                startCol >= 0 && startCol < obstacleGrid[startRow].size() &&
                0 == obstacleGrid[startRow][startCol]) {
            return true;
        }
        return false;
    }
private:
    static int const DIRECTION_ARRAY_SIZE = 5;
    static int const REMOVE_DIRECTION = 2;
    static int const DIRECTION_SIZE = DIRECTION_ARRAY_SIZE - 1 - REMOVE_DIRECTION; // only right and down
    static std::array<int, DIRECTION_ARRAY_SIZE> directions;
};
std::array<int, Solution::DIRECTION_ARRAY_SIZE> Solution::directions = {0, 1, 0, -1, 0};

class SolutionDP {
public:
    int uniquePathsWithObstacles(std::vector<std::vector<int>> const & g) {

        int r = g.size();
        if (0 == r) {
            return 0;
        }
        int c = g[0].size();
        if (0 == c) {
            return 0;
        }

        bool noi= false, noj=false;

        std::vector<std::vector<int> > dp(r, std::vector<int>(c));

        for (int i = 0; i < r; i++) {
            for (int j = 0 ; j < c; j++) {
                if (i == 0 && j == 0) {
                    if (g[i][j] == 0) {
                        dp[i][j] = 1;
                    } else {
                        return 0;
                    }
                } else {
                    if (g[i][j] == 0) {
                        dp[i][j] = ((i-1 >= 0 ? dp[i - 1][j] : 0)  + ( j - 1 >= 0 ?  dp[i][j-1] : 0));
                    }
                }

            }
        }
        return dp[r-1][c-1];
    }
};

class SolutionDP_OM_ {
public:
    int uniquePathsWithObstacles(std::vector<std::vector<int>> const & g) {
        int r = g.size();
        if (0 == r) {
            return 0;
        }

        int c = g[0].size();
        if (0 == c) {
            return 0;
        }

        std::vector<int> dp(c);
        if (g[0][0] == 0) {
            dp[0] = 1;
        } else {
            return 0;
        }
        for (int i = 0; i < r; i++) {
            for (int j = 0 ; j < c; j++) {
                if (i + j == 0) {
                    continue;
                }
                if (g[i][j] == 0) {
                    // std::cout << "pre Up: " << dp[j] << "\t";
                    dp[j] = ((i > 0 ? dp[j] : 0)  + (j > 0 ? dp[j - 1] : 0));
                    // std::cout << "now: " << dp[j] << "\t";
                } else {
                    dp[j] = 0;
                }

            }
        }
        return dp[c-1];
    }
};
