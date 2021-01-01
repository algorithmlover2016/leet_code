#include "../../head.h"


// #define DEBUG
class Solution {
public:
    int stoneGameVII(std::vector<int> const & stones) {
        // plagiarizing from https://www.youtube.com/watch?v=cOGliK5brbQ
        if (stones.empty()) {
            return 0;
        }
        int const stonesSize = stones.size();

        std::vector<int> preSumStones(stonesSize + 1);

        for (int idx = 0; idx < stonesSize; idx++) {
            preSumStones[idx + 1] = preSumStones[idx] + stones[idx];
        }

        // record the max difference between left and right
        std::vector<std::vector<int>> dpMemo(stonesSize,
                std::vector<int>(stonesSize));

        for (int right = 0; right < stonesSize; right++) {
            // we must from left = right -1 to zero, because we only know dpMemo[i][i] == 0;
            for (int left = right - 1; left > -1; left--) {
                dpMemo[left][right] = std::max(
                        // after remove the left element, we get added sum is
                        // preSumStones[right  + 1] - preSumStones[left + 1]
                        preSumStones[right + 1] - preSumStones[left + 1] - dpMemo[left + 1][right],
                        // after remove the right element, we get add sum is
                        // preSumStones[right] - preSumStones[left]
                        preSumStones[right] - preSumStones[left] - dpMemo[left][right - 1]);
                #ifdef DEBUG
                std::cout << "left, right: " << left << ",\t" << right << ",\tmaxDiff: " << dpMemo[left][right] << "\n";
                #endif
            }
        }
        return dpMemo[0][stonesSize - 1];
    }
};

// #define DEBUG
class SolutionRecursive {
public:
    int stoneGameVII(std::vector<int> const & stones) {
        // plagiarizing from https://www.youtube.com/watch?v=cOGliK5brbQ
        if (stones.empty()) {
            return 0;
        }
        int const stonesSize = stones.size();

        std::vector<int> preSumStones(stonesSize + 1);

        for (int idx = 0; idx < stonesSize; idx++) {
            preSumStones[idx + 1] = preSumStones[idx] + stones[idx];
        }

        // record the max difference between left and right
        std::vector<std::vector<int>> dpMemo(stonesSize,
                std::vector<int>(stonesSize));

        recursiveHelp(preSumStones, dpMemo, 0, stonesSize - 1);
        return dpMemo[0][stonesSize - 1];
    }

    int recursiveHelp(std::vector<int> const & preSumStones,
                      std::vector<std::vector<int>> & dpMemo,
                      int const left, int const right) {
        if (left == right) {
            return 0;
        }
        if (0 != dpMemo[left][right]) {
            return dpMemo[left][right];
        }
        return dpMemo[left][right] = std::max(
            preSumStones[right + 1] - preSumStones[left + 1] -
                recursiveHelp(preSumStones, dpMemo, left + 1, right),
            preSumStones[right] - preSumStones[left] -
                recursiveHelp(preSumStones, dpMemo, left, right - 1));
    }
};
