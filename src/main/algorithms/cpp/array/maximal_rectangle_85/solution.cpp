#include "../../head.h"


// #define DEBUG
class Solution {
public:
    int maximalRectangle(std::vector<std::vector<char>> const & mat) {
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
            ans = std::max(ans, accIncStack(accCol));
        }
        return ans;
    }
    
private:
    int accIncStack(std::vector<int> const & accCol) {
        int const accColSize = accCol.size();
        int ans = 0;
        std::vector<int> incStack; // std::stack
        incStack.emplace_back(START_FLAG);
        for (int idx = 0; idx < accColSize; idx++) {
            #ifdef DEBUG
            std::cout << accCol[idx] << "\t";
            #endif
            while ((START_FLAG != incStack.back()) && accCol[incStack.back()] >= accCol[idx]) {
                int curHeight = accCol[incStack.back()]; incStack.pop_back();
                int preIdx = incStack.back();
                ans = std::max(ans, curHeight * (idx - 1 - preIdx));
            }
            incStack.emplace_back(idx);
        }
        while (START_FLAG != incStack.back()) {
            int curPopIdx = incStack.back(); incStack.pop_back();
            int width = accColSize - incStack.back() - 1;
            ans = std::max(ans, width * accCol[curPopIdx]);
        }
        #ifdef DEBUG
        std::cout << "\n";
        #endif
        return ans;
    }

    private:
    static char const RESET = '0';
    int const START_FLAG = -1;
};
