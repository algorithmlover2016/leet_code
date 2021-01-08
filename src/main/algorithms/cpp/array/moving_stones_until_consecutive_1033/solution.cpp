#include "../../head.h"


class Solution {
public:
    std::vector<int> numMovesStones(int a, int b, int c) {
        // plagiarizing idea from https://www.youtube.com/watch?v=Gwp8hL2F6c0
        int x = std::min(a, std::min(b, c));
        int z = std::max(a, std::max(b, c));
        int y = a + b + c - x - z;

        std::vector<int> ans(ANS_LEN, 0);
        if (DISTANCE_LESS_TWO == z - x) {
            return  ans;
        }
        ans[ANS_MAX_IDX] = z - x - 2;
        if (DISTANCE_LESS_TWO >= y - x || DISTANCE_LESS_TWO >= z - y) {
            ans[ANS_MIN_IDX] = 1;
        } else {
            ans[ANS_MIN_IDX] = 2;
        }
        return ans;
    }
private:
    static int const DISTANCE_LESS_TWO = 2;
    static int const ANS_LEN = 2;
    static int const ANS_MIN_IDX = 0;
    static int const ANS_MAX_IDX = 1;
};
