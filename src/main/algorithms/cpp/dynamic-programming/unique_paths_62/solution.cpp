#include "../../head.h"


class Solution {
public:
    int uniquePaths(int r, int c) {
        if (0 == r) {
            return 0;
        }
        
        if (0 == c) {
            return 0;
        }

        std::vector<int> dp(c);
        dp[0] = 1;
        for (int i = 0; i < r; i++) {
            for (int j = 0 ; j < c; j++) {
                if (i + j == 0) {
                    continue;
                }
                // std::cout << "pre Up: " << dp[j] << "\t";
                dp[j] = ((i > 0 ? dp[j] : 0)  + (j > 0 ? dp[j - 1] : 0));
                // std::cout << "now: " << dp[j] << "\t";
            }
        }
        return dp[c-1];
    }
};

class Solution {
public:
    int uniquePaths(int m, int n) {
        int dp[m][n];
        dp[m-1][n-1] = 1;
        for(int j = 0; j < n-1; j++){
            dp[m-1][j] = 1;
        }
        for(int i = 0; i < m-1; i++){
            dp[i][n-1] = 1;
        }
        for(int i = m-2; i >= 0; i--){
            for(int j = n-2; j >= 0; j--){
                dp[i][j] = dp[i+1][j] + dp[i][j+1];
            }
        }
        return dp[0][0];
    }
};
