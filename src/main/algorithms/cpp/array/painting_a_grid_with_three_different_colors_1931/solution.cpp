#include "../../head.h"


class Solution {
public:
    int colorTheGrid(int m, int n) {
        this->row = m;
        this->col = n;
        this->max_mask = (COLOR_BASE << m);
        memo = std::vector<std::vector<int>>(n, std::vector<int>(max_mask));
        curCol = std::vector(max_mask, std::vector<int>());
    }
private:
    static int const MAX_COL = 1000;
    static int const COLOR_BITS = 2;
    static int const COLOR_BASE = (2 << COLOR_BITS);
    int row;
    int col;
    int max_mask;
    std::vector<std::vector<int>> memo;
    std::vector<std::vector<int>> curCol;
};