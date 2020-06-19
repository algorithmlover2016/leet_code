#include "../../head.h"


class SolutionBruteForce {
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
        // can not judge like this, becasue std::min will be error
        // if (row >= size || col >= size || col < 0) {
        if (row >= size) {
            return 0;
        }
        if (INT_MAX != memorize[row][col]) {
            return memorize[row][col];
        }
        int ans = INT_MAX;
        ans = std::min(ans, dfs(arr, size, row + 1, col, memorize));
        int index = col + 1;
        if (index < size) {
            ans = std::min(ans, dfs(arr, size, row + 1, index, memorize));
        }
        index = col - 1;
        if (index >= 0) {
            ans = std::min(ans, dfs(arr, size, row + 1, index, memorize));
        }

        memorize[row][col] = arr[row][col] + ans;
        return memorize[row][col];
        }
    }
};

class Solution {
public:
    int minFallingPathSum(std::vector<std::vector<int>> const & A) {
        if (A.size() == 0) {
            return 0;
        }
        std::vector<std::vector<int> > dpSum(A);
        for (int index = 1; index < A.size(); index++) {
            for (int subIndex = 0; subIndex < A[index].size(); subIndex++) {
                int upRow = std::max(0, index - 1);
                int leftCol = std::max(0, subIndex - 1);
                int rightCol = std::min(subIndex + 1, int(A[index].size() - 1));
                int minNum = min(dpSum[upRow][leftCol], min(dpSum[upRow][subIndex], dpSum[upRow][rightCol]));
                // std::cout << "dpSum: " << dpSum[index][subIndex] << " minNum: " << minNum << std::endl;
                dpSum[index][subIndex] += minNum;
            }
        }
        // the follow sentence equal to
        // return *std::min_element(dpSum.back().begin(), dpSum.back().end());
        int minSum = INT_MAX;
        int maxRow = dpSum.size() - 1;
        for (int index = 0; index < dpSum[maxRow].size(); index++) {
            if (minSum > dpSum[maxRow][index]) {
                minSum = dpSum[maxRow][index];
            }
        }
        return minSum;
    }
    
};
