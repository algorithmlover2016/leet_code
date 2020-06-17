#include "../../head.h"


class Solution {
public:
    std::vector<int> pathsWithMaxScore(std::vector<std::string> const & board) {
        int const MOD = 1e9 + 7;
        if (board.empty() || board[0].empty()) {
            return {};
        }
        int rowSize = board.size();
        int colSize = board[0].size();
        std::vector<std::vector<int>> dp(rowSize + 1, std::vector<int>(colSize + 1, INT_MIN));
        std::vector<std::vector<int>> path(rowSize + 1, std::vector<int>(colSize + 1, 0));
        dp[rowSize - 1][colSize - 1] = 0;
        path[rowSize - 1][colSize - 1] = 1;
        for (int row = rowSize - 1; row >= 0; row--) {
            for (int col = colSize - 1; col >=0; col--) {
                if ('X' == board[row][col] ||
                    'S' == board[row][col]) {
                    continue;
                }
                int add = board[row][col] - '0';
                if ('E' == board[row][col]) {
                    add = 0;
                }
                dp[row][col] = std::max({dp[row][col + 1], dp[row + 1][col], dp[row + 1][col + 1]});
                if (INT_MIN == dp[row][col]) {
                    continue;
                }
                if (dp[row][col] == dp[row][col + 1]) {
                    path[row][col] += path[row][col + 1];
                }
                if (dp[row][col] == dp[row + 1][col]) {
                    path[row][col] += path[row + 1][col];
                }
                if (dp[row][col] == dp[row + 1][col + 1]) {
                    path[row][col] += path[row + 1][col + 1];
                }
                path[row][col] %= MOD;
                dp[row][col] += add;
                // std::cout << "row: " << row << "\tcol: " << col << "\tdp: "
                //     << dp[row][col] << "\tpath: " << path[row][col] << "\n";
            }
        }
        if (INT_MIN == dp[0][0]) {
            return {0, 0};
        }
        return {dp[0][0], path[0][0]};


    }
};

class Solution {
public:
    int getValue(char h) {
        if (h == 'E') return 0;
        return h - '0';
    }
    vector<int> pathsWithMaxScore(vector<string>& board) {
        int m = board.size();
        int n = board[0].size();
        int MODULO = 1000000007;
        int f[m][n];
        int g[m][n];
        memset(f, 0, sizeof(f));
        memset(g, 0, sizeof(g));
        f[m-1][n-1] = 0; g[m-1][n-1] = 1;
        for (int i = m-1; i >= 0; i--)
            for (int j = n - 1; j >= 0; j--)
            if (board[i][j] != 'X') {
                int value = getValue(board[i][j]);
                for (int k = 0; k < 3; k++) {
                    int x = i + dx[k];
                    int y = j + dy[k];
                    if (x >= 0 && x < m && y >= 0 && y < n && g[x][y] > 0) {
                        if (f[i][j] < f[x][y] + value) {
                            f[i][j] = f[x][y] + value;
                            g[i][j] = g[x][y];
                        } else if (f[i][j] == f[x][y] + value)
                            g[i][j] = (g[i][j] + g[x][y]) % MODULO;
                    }
                }
            }
        vector<int> res;
        res.push_back(f[0][0]); res.push_back(g[0][0]);
        return res;
    }
private:
//           x,x+1,x+1
int dx[3] = {0, 1, 1};
//          y+1,y,y+1
int dy[3] = {1, 0, 1};
};
