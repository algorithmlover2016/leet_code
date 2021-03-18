#include "../../head.h"


// #define DEBUG
class Solution {
public:
    int getMaxGridHappiness(int m, int n, int introvertsCount, int extrovertsCount) {
        // plagiarizing from https://leetcode.com/problems/maximize-grid-happiness/discuss/936081/C%2B%2B-5D-DP
        // this is so great solution.
#ifdef DEBUG
        std::cout << sizeof(dpMemo) << "\n";
#endif
        memset(dpMemo, 0, sizeof(dpMemo));
        if (0 == n) {
            return 0;
        }
        // using maskIn and maskEx just record the last colSize elements. because we just care about the left, up, right
        // and down which is its neightbours. and we set pos from top-left to buttom-right, so the right and down need not
        // be considered, we just need care about the left and upper
        return dfs(m, n, 0, introvertsCount, extrovertsCount, 0, 0);
    }
private:
    int onCost(int colSize, int row, int col, int maskIn, int maskEx, int d) {
        int diff = 0;
        int left = 0x01;
        int upper = 1 << (colSize - 1); // because mask record the last status not include the cur.
        if (0 < col && (maskIn & left)) {
            // the cur pos has its left neighbour, and its left neighbour is set as introvert
            diff += d - 30;
        }

        if (0 < row && (maskIn & upper)) {
            // the cur pos has its upper neightbour, and its upper neightbour is set as introvert
            diff += d - 30;
        }

        if (0 < col && (maskEx & left)) {
            // the cur pos has its left neighbour, and its left neighbour is set as extrovert
            diff += d + 20;
        }

        if (0 < row && (maskEx & upper)) {
            // the cur pos has its upper neightbour, and its upper neightbour is set as extrovert
            diff += d + 20;
        }

        return diff;
    }

    int dfs(int const rowSize, int const colSize, int pos,
            int introvertsCount, int extrovertsCount, int maskIn, int maskEx) {
        int row = pos / colSize;
        int col = pos % colSize;
        if (row == rowSize) {
            // it's over.
            return 0;
        }
        if (0 != dpMemo[pos][introvertsCount][extrovertsCount][maskIn][maskEx]) {
            return dpMemo[pos][introvertsCount][extrovertsCount][maskIn][maskEx] - 1;
        }


        int nextMaskIn = (maskIn << 1) & (MASK_RESET);
        int nextMaskEx = (maskEx << 1) & (MASK_RESET);

        // if we set the cur pos as empty
        int res = dfs(rowSize, colSize, pos + 1, introvertsCount, extrovertsCount, nextMaskIn, nextMaskEx);

        // we can set the cur pos living a introvert
        if (0 < introvertsCount) {
            int diff = 120 + onCost(colSize, row, col, maskIn, maskEx, -30);
            res = std::max(res, diff + dfs(rowSize, colSize, pos + 1,
                        introvertsCount - 1, extrovertsCount, nextMaskIn + 1, nextMaskEx));
        }
        if (0 < extrovertsCount) {
            int diff = 40 + onCost(colSize, row, col, maskIn, maskEx, 20);
            res = std::max(res, diff + dfs(rowSize, colSize, pos + 1,
                        introvertsCount, extrovertsCount - 1, nextMaskIn, nextMaskEx + 1));
        }
        // because we need to split the status with no compute and computed with ans = 0;
        dpMemo[pos][introvertsCount][extrovertsCount][maskIn][maskEx] = res + 1;
        return res;
    }
private:
    static int const MAX_SIZE = 5;
    static int const MAX_PEOPLE_SIZE = 6;
    static int const MASK_STATUS_SIZE = 1 << (MAX_SIZE + 1);
    static int const MASK_RESET = MASK_STATUS_SIZE - 1;
    int dpMemo[MAX_SIZE * MAX_SIZE][MAX_PEOPLE_SIZE + 1][MAX_PEOPLE_SIZE + 1][MASK_STATUS_SIZE][MASK_STATUS_SIZE];
};
