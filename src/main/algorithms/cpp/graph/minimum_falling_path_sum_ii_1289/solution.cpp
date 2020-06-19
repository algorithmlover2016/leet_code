#include "../../head.h"


class Solution {
public:
    int minFallingPathSum(std::vector<std::vector<int>> const & arr) {
        int rowSize = arr.size();
        if (0 == rowSize) {
            return 0;
        }

        int colSize = arr[0].size();
        if (0 == colSize) {
            return 0;
        }
        std::vector<vector<int>> memorize(rowSize, std::vector<int>(colSize, INT_MAX));
        int res = INT_MAX;
        for (int col = 0; col < colSize; col++) {
            res = std::min(res, dfs(arr, rowSize, 0, col, memorize));
        }
        return res;
    }
    int dfs(std::vector<std::vector<int>> const & arr,
            int size, int row, int col, std::vector<vector<int>> & memorize) {
        if (row >= size) {
            return 0;
        }
        if (INT_MAX != memorize[row][col]) {
            return memorize[row][col];
        }
        int ans = INT_MAX;
        for (int index = 0; index < arr[row].size(); index++) {
            if (index == col) {
                continue;
            }
            ans = std::min(ans, dfs(arr, size, row + 1, index, memorize));
        }

        memorize[row][col] = arr[row][col] + ans;
        return memorize[row][col];
    }
};

class SolutionBetterSolution {
public:
    // dp 调整前 表示到目前层为止（还未计算当前层），各个index下的和值。
    // 调整方式：将每个index下的值改为除去dp[index]后的最小值； 调整的结果就是出了一个次大值外其余全是最小值，而且次大值位置为首次最小值出现的位置
    // 这个时候的dp 可以直接按下标直接叠加，因为要想取到本层某一index，和值必须不是index，而dp刚好满足这个性质
    int minFallingPathSum(std::vector<std::vector<int>> const & arr) {
        int R = arr.size(), size = arr[0].size();
        std::vector<int> dp(size, 0), tmp(size, 0);
        for (int i = 0; i < R; ++i) {
            tmp[0] = dp[0];
            for (int j = 1; j < size; ++j) {
                tmp[j] = std::min(tmp[j - 1], dp[j]);
            }
            tmp[size - 1] = tmp[size - 2];
            int m = dp[size - 1];
            for (int j = size - 2; j >= 1; --j) {
                m = std::min(m, dp[j + 1]);
                tmp[j] = std::min(m, tmp[j - 1]);
            }
            tmp[0] = std::min(m, dp[1]);
            for (int j = 0; j < size; ++j) {
                tmp[j] += arr[i][j];
            }
            std::swap(tmp, dp);
            std::fill(tmp.begin(), tmp.end(), INT32_MAX);
        }
        return *std::min_element(dp.begin(), dp.end());
    }
};

auto gucciGang = []() {std::ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);return 0;}();
