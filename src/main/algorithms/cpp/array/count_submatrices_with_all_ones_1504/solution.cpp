#include "../../head.h"


class Solution {
public:
    int numSubmat(std::vector<std::vector<int>> const & mat) {
        // plagiarizing from https://leetcode.com/problems/count-submatrices-with-all-ones/discuss/720265/Java-Detailed-Explanation-From-O(MNM)-to-O(MN)-by-using-Stack
        if (mat.empty() || mat[0].empty()) {
            return 0;
        }
        int const matRowSize = mat.size();
        int const matColSize = mat[0].size();
        int ans = 0;
        // startRow means the up boarder of the submatrix
        // endRow means the buttom boarder of the submatrix
        for (int startRow = 0; startRow < matRowSize; startRow++) {
            std::vector<int> bitVals(matColSize, 1);
            for (int endRow = startRow; endRow < matRowSize; endRow++) {
                for (int col = 0; col < matColSize; col++) {
                    bitVals[col] &= mat[endRow][col];
                }
                ans += vectorSubMatrix(bitVals);
            }
        }
        return ans;
    }

private:
    int vectorSubMatrix(std::vector<int> const & vec) {
        int ans = 0;
        int len = 0;
        for (int idx = 0; idx < vec.size(); idx++) {
            len = (RESET == vec[idx] ? 0 : len + 1);
            ans += len;
        }
        return ans;
    }
private:
    static int const RESET = 0;
};

class Solution {
public:
    int numSubmat(std::vector<std::vector<int>> const & mat) {
        // plagiarizing from https://leetcode.com/problems/count-submatrices-with-all-ones/discuss/720265/Java-Detailed-Explanation-From-O(MNM)-to-O(MN)-by-using-Stack
        if (mat.empty() || mat[0].empty()) {
            return 0;
        }
        int const matRowSize = mat.size();
        int const matColSize = mat[0].size();
        int ans = 0;

        std::vector<int> accCol(matColSize, 0);
        for (int row = 0; row < matRowSize; row++) {
            for (int col = 0; col < matColSize; col++) {
                // the cur value = the previous value(the upper row) + 1 when mat[row][col] == 1
                // record the height
                accCol[col] = (RESET == mat[row][col] ? 0 : accCol[col] + 1);
            }
            ans += accIncStack(accCol);
        }
        return ans;
    }
private:
    int accIncStack(std::vector<int> const & accCol) {
        std::vector<int> sums(accCol.size(), 0);
        std::vector<int> incStack; // std::stack
        for (int idx = 0; idx < accCol.size(); idx++) {
            while ((!incStack.empty()) && accCol[incStack.back()] > accCol[idx]) {
                incStack.pop_back();
            }
            if (!incStack.empty()) {
                int preIdx = incStack.back();
                sums[idx] = sums[preIdx];
                sums[idx] += accCol[idx] * (idx - preIdx);
            } else {
                sums[idx] = accCol[idx] * (idx + 1); // because idx starts from zero;
            }
            incStack.emplace_back(idx);
        }
        return std::accumulate(sums.begin(), sums.end(), 0);
    }

private:
    static int const RESET = 0;
};
