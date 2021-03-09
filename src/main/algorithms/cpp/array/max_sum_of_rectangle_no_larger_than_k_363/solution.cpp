#include "../../head.h"


// #define DEBUG
class Solution {
public:
    int maxSumSubmatrix(std::vector<std::vector<int>> const & matrix, int k) {
        // plagiarizing idea from https://leetcode.com/problems/max-sum-of-rectangle-no-larger-than-k/discuss/83599/Accepted-C%2B%2B-codes-with-explanation-and-references
        // I just come up with the idea that brute force solution
        if (matrix.empty() || matrix[0].empty()) {
            return 0;
        }
        int ans = INIT_MIN;
        int const rowSize = matrix.size();
        int const colSize = matrix[0].size();
        if (rowSize <= colSize) {
            for (int row = 0; row < matrix.size(); row++) {
                std::vector<int> colSums(colSize, 0); // statistic the sum from row to nextRow on each column

                #ifdef DEBUG
                std::cout << "colSums\n";
                #endif
                for (int nextRow = row; nextRow < matrix.size(); nextRow++) {
                    for (int col = 0; col < matrix[nextRow].size(); col++) {
                        colSums[col] += matrix[nextRow][col];
                        #ifdef DEBUG
                        std::cout << colSums[col] << "\t";
                        #endif
                    }
                    #ifdef DEBUG
                    std::cout << "\n";
                    #endif

                    std::set<int> orderedPreSum;
                    orderedPreSum.insert(0);
                    int curSum = 0;
                    for (int const colSum : colSums) {
                        curSum += colSum; // until this col from row to nextRow(included) the subMatrix's sum
                        auto it = orderedPreSum.lower_bound(curSum - k);
                        if (it != orderedPreSum.end()) {
                            // find a preSum, that meeting *it >= curSum - k; which means k >= curSum - *it
                            // then the difference maybe the maximum sum of the problem
                            ans = std::max(ans, curSum - *it);
                        }
                        // record the preSum
                        orderedPreSum.insert(curSum);
                    }
                }
            }
        } else {
            for (int col = 0; col < colSize; col++) {
                std::vector<int> rowSums(rowSize, 0); // statistic the sum from col to nextCol on each row
                for (int nextCol = col; nextCol < colSize; nextCol++) {
                    for (int row = 0; row < rowSize; row++) {
                        rowSums[row] += matrix[row][nextCol];
                    }
                    std::set<int> orderedPreSum;
                    orderedPreSum.insert(0);
                    int curSum = 0;
                    for (int const rowSum : rowSums) {
                        curSum += rowSum; // until this col from row to nextRow(included) the subMatrix's sum
                        auto it = orderedPreSum.lower_bound(curSum - k);
                        if (it != orderedPreSum.end()) {
                            // find a preSum, that meeting *it >= curSum - k; which means k >= curSum - *it
                            // then the difference maybe the maximum sum of the problem
                            ans = std::max(ans, curSum - *it);
                        }
                        // record the preSum
                        orderedPreSum.insert(curSum);
                    }
                }
            }
        }
        return ans;
    }
private:
    static int const INIT_MIN = INT_MIN;
};
