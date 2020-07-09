#include "../../head.h"


class Solution {
public:
    std::vector<std::vector<int>> pacificAtlantic(std::vector<std::vector<int>> const & matrix) {
        std::vector<std::vector<int>> res;
        int const ROWSIZE = matrix.size();
        if (0 == ROWSIZE) {
            return res;
        }
        int const COLSIZE = matrix[0].size();
        if (0 == COLSIZE) {
            return res;
        }
        std::vector<std::vector<int>> marked(ROWSIZE, std::vector<int>(COLSIZE, 0));
        for (int row = 0; row < ROWSIZE; row++) {
            for (int col = 0; col < COLSIZE; col++) {
                bruteForceTraversal(matrix, marked, res, row, col, ROWSIZE, COLSIZE);
            }
        }
        return res;
    }
    // 0x01 mark encountering left or top border
    // 0x02 mark encountering right or buttom border
    // 0x04 mark have visited
    // 0x0B mark have meet the request, and have already put into res
    void bruteForceTraversal(std::vector<std::vector<int>> const & matrix,
            std::vector<std::vector<int>> & marked,
            std::vector<std::vector<int>> & res,
            int rowStart, int colStart, int const ROWSIZE, int const COLSIZE) {
        // std::cout << "\n";
        marked[rowStart][colStart] |= 0x04;
        for (int index = 0; index < DIRECTION_SIZE; index++) {
            int nextRow = rowStart + directions[index];
            int nextCol = colStart + directions[index + 1];
            // std::cout << "next: " << nextRow << "\t" << nextCol << "\t";
            if (nextRow < 0 || nextCol < 0) {
                marked[rowStart][colStart] |= 0x01;
            } else if (ROWSIZE == nextRow || COLSIZE == nextCol) {
                marked[rowStart][colStart] |= 0x02;
            } else if (0 == (marked[nextRow][nextCol] & 0x04) &&
                       matrix[rowStart][colStart] >= matrix[nextRow][nextCol]) {
                if (3 != (marked[nextRow][nextCol] & 0x03)) {
                    // std::cout << "enter recursive\t";
                    bruteForceTraversal(matrix, marked, res, nextRow, nextCol, ROWSIZE, COLSIZE);
                }
                marked[rowStart][colStart] |= marked[nextRow][nextCol] & 0x03;
            }

            if (3 == (marked[rowStart][colStart] & 0x0B)) {
                res.emplace_back(std::vector<int>{rowStart, colStart});
                marked[rowStart][colStart] |= 0x0B;
                break;
            }
        }
        marked[rowStart][colStart] &= 0x0B;

        // std::cout <<  "res: " << matrix[rowStart][colStart] << "\t" << marked[rowStart][colStart];
    }
private:
    static int const DIRECTION_ARRAY_SIZE = 5;
    static int const DIRECTION_SIZE = DIRECTION_ARRAY_SIZE - 1;
    static std::array<int, DIRECTION_ARRAY_SIZE> directions;
};
std::array<int, Solution::DIRECTION_ARRAY_SIZE> Solution::directions = {0, 1, 0, -1, 0};

class SolutionBetterRuntime {
public:
    void dfs(std::vector<std::vector<int>> const & matrix,
            int si, int sj, int m, int n, int pVal,
            std::vector<std::vector<int>> & ocean) {
        if(si < 0 || sj < 0 || si >= m || sj >= n) return;
        if(ocean[si][sj] == 1) return;
        if(matrix[si][sj] < pVal) return;

        ocean[si][sj] = 1;
        dfs(matrix, si - 1, sj, m, n, matrix[si][sj], ocean);
        dfs(matrix, si, sj - 1, m, n, matrix[si][sj], ocean);
        dfs(matrix, si + 1, sj, m, n, matrix[si][sj], ocean);
        dfs(matrix, si, sj + 1, m, n, matrix[si][sj], ocean);
    }

    std::vector<std::vector<int>> pacificAtlantic(std::vector<std::vector<int>> const & matrix) {
        int m = matrix.size();
        if (m == 0) {
            return {};
        }
        int n = matrix[0].size();
        if (n == 0) {
            return {};
        }

        std::vector<std::vector<int>> pacific(m, std::vector<int>(n, 0));
        std::vector<std::vector<int>> atlantic(m, std::vector<int>(n, 0));

        for (int i = 0; i < n; i++) {
            dfs(matrix, 0, i, m, n, INT_MIN, pacific);
            dfs(matrix, m - 1, i, m, n, INT_MIN, atlantic);
        }

        for (int i = 0; i < m; i++) {
            dfs(matrix, i, 0, m, n, INT_MIN, pacific);
            dfs(matrix, i, n - 1, m, n, INT_MIN, atlantic);
        }

        std::vector<std::vector<int>> res;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if (pacific[i][j] == 1 && atlantic[i][j] == 1) {
                    res.push_back({i, j});
                }
            }
        }
        return res;
    }
};

auto gucciGang = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();
