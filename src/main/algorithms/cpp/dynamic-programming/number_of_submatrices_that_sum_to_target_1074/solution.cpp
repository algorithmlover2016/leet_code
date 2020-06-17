#include "../../head.h"


class Solution {
public:
    int numSubmatrixSumTarget(std::vector<std::vector<int>> & matrix, int target) {
        // plagiarizing from https://leetcode.com/problems/number-of-submatrices-that-sum-to-target/discuss/303750/JavaC%2B%2BPython-Find-the-Subarray-with-Target-Sum
        int rowSize = matrix.size();
        if (0 == rowSize) {
            return 0;
        }
        int colSize = matrix[0].size();
        if (0 == colSize) {
            return 0;
        }
        std::vector<std::vector<int>> preSumMatrix(rowSize, std::vector<int>(colSize + 1, 0));
        for (int row = 0; row < rowSize; row++) {
            for (int col = 0; col < colSize; col++) {
                preSumMatrix[row][col + 1] = matrix[row][col] + preSumMatrix[row][col];
            }
        }

        int res = 0;
        std::unordered_map<int, int> sumNumpair;
        for (int startCol = 1; startCol < preSumMatrix[0].size(); startCol++) {
            for (int endCol = startCol; endCol < preSumMatrix[0].size(); endCol++) {
                // memoirize sum of submatrix from startCol to endCol
                sumNumpair = {{0, 1}};
                int multiLayer = 0;
                for (int row = 0; row < rowSize; row++) {
                    // the sum from startCol to endCol and from 0 row to row row
                    // if startCol = 0, the prefix col set to be 0;
                    multiLayer += preSumMatrix[row][endCol] - preSumMatrix[row][startCol - 1];
                    res += sumNumpair.find(multiLayer - target) != sumNumpair.end() ? sumNumpair.at(multiLayer - target) : 0;
                    // res += sumNumpair[multiLayer - target];
                    sumNumpair[multiLayer]++;
                }
            }
        }
        return res;


    }
};

class Solution {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& mat, int target) {
        int n = mat.size();
        int m = mat[0].size();
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                sums[i][j+1] = sums[i][j] + mat[i][j];
            }
        }
        int ans = 0;
        for(int l = 0; l < m; l++){
            for(int r = l; r < m; r++){
                int curSum = 0;
                countArr[OFFSET] = 1;
                for(int i = 0; i < n; i++){
                    curSum += sums[i][r+1] - sums[i][l];
                    int s = curSum - target;
                    ans += countArr[s + OFFSET];
                    countArr[curSum + OFFSET]++;
                }
                curSum = 0;
                for(int i = 0; i < n; i++){
                    curSum += sums[i][r+1] - sums[i][l];
                    countArr[curSum + OFFSET] = 0;
                }
            }
        }
        return ans;
    }
private:
    static int countArr[200'000'002];
    const int OFFSET = 100'000'000;
    const int MAXN = 300;
    int sums[MAXN][MAXN+1];

};
