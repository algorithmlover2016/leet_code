#include "../../head.h"


// #define DEBUG
class Solution {
public:
    int minimumTotal(std::vector<std::vector<int>> const & triangle) {
        if (triangle.empty() || triangle[0].empty()) {
            return 0;
        }
        std::vector<int> curLayer(1, triangle[0][0]);
        for (int row = 1; row < triangle.size(); row++) {
            std::vector<int> nextLayer(curLayer.size() + 1, 0);
            for (int col = 0; col < triangle[row].size() && col <= row; col++) {
                #ifdef DEBUG
                std::cout << row << ", " << col << ": " << (col < row ? curLayer[col] : -1)<< "\n";
                #endif
                if (0 == col) {
                    nextLayer[col] = curLayer[col] + triangle[row][col];
                } else if (col < row) {
                    nextLayer[col] = std::min(curLayer[col - 1], curLayer[col]) + triangle[row][col];
                } else {
                    nextLayer[col] = curLayer[col - 1] + triangle[row][col];
                }
            }
            std::swap(curLayer, nextLayer);
            std::vector<int>().swap(nextLayer);
        }
        return *std::min_element(curLayer.begin(), curLayer.end());
    }
};

class Solution {
public:
    int minimumTotal(std::vector<std::vector<int>> const & triangle) {
        int n = triangle.size();
        if (n == 0) {
            return 0;
        }
        // traversal from buutom to top. then we can avoid lots of judgement condition
        std::vector<int> dp = triangle[n-1];
        for (int i = n - 2; i >= 0; i--) {
            for (int j = 0; j <= i; j++) {
                dp[j] = triangle[i][j] + std::min(dp[j], dp[j + 1]);
            }
            dp.pop_back();
        }
        return dp[0];
    }
};
