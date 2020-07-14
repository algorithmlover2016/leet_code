#include "../../head.h"


class Solution {
public:
    bool winnerSquareGame(int n) {
        std::vector<bool> dp(n + 1, false);
        for (int stone = 1; stone <= n; stone++) {
            int squareNumber = 1;
            int square = 0;
            while ((square = squareNumber * squareNumber) <= stone) {
                if (!dp[stone - square]) {
                    dp[stone] = true;
                    break;
                }
                squareNumber++;
            }
        }
        return dp[n];
    }
};
