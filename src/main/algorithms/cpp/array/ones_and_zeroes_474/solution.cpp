#include "../../head.h"


class Solution {
public:
    int findMaxForm(std::vector<std::string> const & strs, int m, int n) {
        // plagiarizing from https://youtu.be/rPNV-gC3UoU
        std::vector<std::vector<int>> dpMemo(m + 1, std::vector<int>(n + 1, 0));
        for (auto const & str : strs) {
            int zeros = 0, ones = 0;
            cntZerosAndOnes(str, zeros, ones);
            for (int zeroStart = m; zeroStart >= zeros; zeroStart--) {
                for (int oneStart = n; oneStart >= ones; oneStart--) {
                    dpMemo[zeroStart][oneStart] = std::max(dpMemo[zeroStart][oneStart],
                            dpMemo[zeroStart - zeros][oneStart - ones] + 1);
                }
            }
        }
        return dpMemo[m][n];
    }
private:
    void cntZerosAndOnes(std::string const & str, int & zeros, int & ones) {
        zeros = 0;
        ones = 0;
        for (char const c : str) {
            switch (c) {
                case ZERO_LETTER:
                    zeros++;
                    break;
                case ONE_LETTER:
                    ones++;
                    break;
                default:break;
            }
        }
    }
private:
    static char const ZERO_LETTER = '0';
    static char const ONE_LETTER = '1';
};

class Solution {
public:
    int findMaxForm(std::vector<std::string> const & S, int M, int N) {
        int dp[101][101]{0};
        for (std::string const & str : S) {
            int zeros = 0, ones = 0;
            for (char const c : str) {
                c == '0' ? zeros++ : ones++;
            }
            for (int i = M; i >= zeros; i--) {
                for (int j = N; j >= ones; j--) {
                    dp[i][j] = std::max(dp[i][j], dp[i - zeros][j - ones] + 1);
                }
            }
        }
        return dp[M][N];
    }
};
