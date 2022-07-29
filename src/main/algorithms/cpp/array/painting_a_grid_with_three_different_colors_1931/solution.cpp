#include "../../head.h"


// #define DEBUG

class SolutionDPDFS {
public:
    int colorTheGrid(int m, int n) {
        // plagiarizing from https://leetcode.com/problems/painting-a-grid-with-three-different-colors/discuss/1330185/C%2B%2BPython-DP-and-DFS-and-Bitmask-Picture-explain-Clean-and-Concise
        this->row = m;
        this->col = n;
        this->max_mask = (1 << (COLOR_BITS * m));
        memo = std::vector<std::vector<int>>(n, std::vector<int>(max_mask, INIT_VAL));
        curCol = std::vector(max_mask, std::vector<int>());
        #ifdef DEBUG
        std::cout << "initialize the curMasks under preMask: " << curCol.back().size() << "\n";
        #endif
        return dpMemo(0, 0);
    }
private:
    int dpMemo(int idxCol, int pre) {
        if (idxCol == col) {
            return 1;
        }
        if (INIT_VAL != memo[idxCol][pre]) {
            return memo[idxCol][pre];
        }
        int curAns = 0;
        for (int cur : getCurs(pre)) {
            curAns = (curAns + dpMemo(idxCol + 1, cur)) % MOD;
        }
        return memo[idxCol][pre] = curAns;
    }

    int getPreColColor(int preMask, int idx) {
        return (preMask & ((COLOR_BASE - 1) << (COLOR_BITS * idx))) >> (COLOR_BITS * idx);
    }
    int setCurColor(int idx, int color, int curMask) {
        curMask |= (color << (COLOR_BITS * idx));
        return curMask;
    }

    std::vector<int> getCurs(int pre) {
        if (curCol[pre].empty()) {
            dpCol(0, pre, 0, curCol[pre]);
        }
        return curCol[pre];
    }

    void dpCol(int curRow, int preMask, int curMask, std::vector<int> & ans) {
        if (curRow == row) {
            ans.emplace_back(curMask);
            return;
        }
        for (int color = INIT_VAL + 1; color < COLOR_BASE; color++) {
            // color: 0 white (initial color), 1 : red, 2 : blue, 3 : green
            if ((getPreColColor(preMask, curRow) != color) /*its left neighbour*/ &&
                (0 == curRow /*it is the first row */ ||
                    (((curMask >> (COLOR_BITS * (curRow - 1 /*its upper row number*/))/*the right most two position means the upper color*/) & (COLOR_BASE - 1)) != color))) {
                // it means the colors on the cur row's left and upper position are not color representing color
                dpCol(curRow + 1, preMask, setCurColor(curRow, color, curMask), ans);
            }
        }
    }



private:
    static int const MAX_COL = 1000;
    static int const COLOR_BITS = 2;
    static int const COLOR_BASE = (1 << COLOR_BITS);
    static int const MOD = 1e9 + 7;
    int const INIT_VAL = 0;
    int row;
    int col;
    int max_mask;
    std::vector<std::vector<int>> memo;
    std::vector<std::vector<int>> curCol;
};

class Solution {
public:
    int colorTheGrid(int const m, int const n, int row = 0, int col = 0, int cur = 0, int pre = 0) {

        if (0 == (row | col)) {
            dpMemo = std::vector(MAX_COL, std::vector<int>((1 << (COLOR_BITS * m)), INIT_VAL));
        }

        // plagiarizing from https://leetcode.com/problems/painting-a-grid-with-three-different-colors/discuss/1330174/Top-down-DP-with-bit-mask
        if (m == row) {
            // it means we set all bits in this col
            return colorTheGrid(m, n, 0, col + 1, 0, cur);
        }
        if (n == col) {
            // we find a combination
            return 1;
        }

        if (0 == row && INIT_VAL != dpMemo[col][pre] ) {
            return dpMemo[col][pre];
        }

        int upper = (0 == row ? INIT_VAL : ((cur >> (COLOR_BITS * (row - 1))) & (COLOR_BASE - 1)));
        int left = (pre >> (COLOR_BITS * row)) & (COLOR_BASE - 1);
        int ans = 0;
        for (int color = INIT_VAL + 1; color <COLOR_BASE; color++) {
            if (color != upper && color != left) {
                ans = (ans + colorTheGrid(m, n, row + 1, col, cur | (color << (COLOR_BITS * row)), pre)) % MOD;
            }
        }
        if (0 == row) {
            dpMemo[col][pre] = ans;
        }
        return ans;

    }
private:
    std::vector<std::vector<int>> dpMemo;
private:
    static int const MAX_COL = 1000;
    static int const COLOR_BITS = 2;
    static int const COLOR_BASE = (1 << COLOR_BITS);
    static int const MOD = 1e9 + 7;
    int const INIT_VAL = 0;
};