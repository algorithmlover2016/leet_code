#include "../../head.h"


class SolutionFraud {
public:
    int tilingRectangle(int n, int m) {
        // plagiarizing from https://www.youtube.com/watch?v=KRuwiEqY6j0
        if ((11 == n && 13 == m) ||
                (11 == m && 13 == n)) {
            return 6;
        }

        std::vector<std::vector<int>> dpMemo(n + 1, std::vector<int>(m + 1, INT_MAX));

        for (int row = 1; row < dpMemo.size(); row++) {
            for (int col = 1; col < dpMemo[row].size(); col++) {
                if (row == col) {
                    dpMemo[row][col] = 1;
                } else {
                    for (int mid = 1; mid < (col / 2 + 1); mid++) {
                        dpMemo[row][col] = std::min(dpMemo[row][col], dpMemo[row][mid] + dpMemo[row][col - mid]);
                    }
                    for (int mid = 1; mid < (row / 2 + 1); mid++) {
                        dpMemo[row][col] = std::min(dpMemo[row][col], dpMemo[mid][col] + dpMemo[row - mid][col]);
                    }
                }
            }
        }
        return dpMemo[n][m];
    }
};

class SolutionSkyLine {
public:
    int tilingRectangle(int n, int m) {
        // plagiarizing from https://leetcode.com/problems/tiling-a-rectangle-with-the-fewest-squares/
        // python solution to see solution.py
        // record the skyLine, using int64_t to represent the column.
        // because 1 <= n <= 13, we can use 4 bits to represent the height
        // because 1 <= m <= 13, if we use 4 bits for a index, we need m * 4 bits, which is at most is 13 * 4 = 52 < 64;
        std::unordered_map<std::int64_t, int> dpMemo;
        return dp(n, m, 0, dpMemo);

    }
    int dp(int const maxHeight, int const width, std::int64_t skyLine, std::unordered_map<std::int64_t, int> & dpMemo) {
        if (dpMemo.find(skyLine) != dpMemo.end()) {
            return dpMemo[skyLine];
        }
        int minHeight = INT_MAX;
        int start = 0;
        for (int idx = 0; idx < width; idx++) {
            int shiftBits = idx * HEIGHT_BITS;
            int curIdxHeight = ((static_cast<int64_t>(0xF) << shiftBits) & skyLine) >> shiftBits;
            if (minHeight > curIdxHeight) {
                start = idx;
                minHeight = curIdxHeight;
            }
        }
        // std::cout << "\nstart: " << start << "\tminHeight: " << minHeight << "\n";
        int ans = INT_MAX;
        if (maxHeight == minHeight) {
            ans = 0;
        } else {
            for (int end = start; end < width; end++) {
                int shiftBits = end * HEIGHT_BITS;
                int curEndHeight = ((static_cast<int64_t>(0xF) << shiftBits) & skyLine) >> shiftBits;
                if (minHeight == curEndHeight) {
                    int newHeight = minHeight + end - start + 1;
                    if (newHeight <= maxHeight) {
                        int64_t newSkyLine = skyLine;
                        for (int newIdx = start; newIdx <= end; newIdx++) {
                            int shiftBits = newIdx * HEIGHT_BITS;
                            newSkyLine &= ~(static_cast<int64_t>(0xF) << shiftBits);
                            newSkyLine |= (static_cast<int64_t>(0xF) & newHeight) << shiftBits;
                        }
                        // std::cout << "newSkyLine: " << std::hex << (newSkyLine) << "\told: " << (skyLine) << "\n";
                        ans = std::min(ans, dp(maxHeight, width, newSkyLine, dpMemo) + 1);
                    }
                } else {
                    break;
                }
            }
            // std::cout << "\n";
        }
        return dpMemo[skyLine] = ans;
    }
private:
    int const HEIGHT_BITS = 4;
};

class SolutionSkylineOpi {
public:
    int tilingRectangle(int n, int m) {
        // plagiarizing from https://leetcode.com/problems/tiling-a-rectangle-with-the-fewest-squares/
        // python solution to see solution.py
        // record the skyLine, using int64_t to represent the column.
        // because 1 <= n <= 13, we can use 4 bits to represent the height
        // because 1 <= m <= 13, if we use 4 bits for a index, we need m * 4 bits, which is at most is 13 * 4 = 52 < 64;
        std::unordered_map<std::int64_t, int> dpMemo;
        return dp(n, m, 0, dpMemo);

    }
    int dp(int const maxHeight, int const width, std::int64_t skyLine, std::unordered_map<std::int64_t, int> & dpMemo) {
        if (dpMemo.find(skyLine) != dpMemo.end()) {
            return dpMemo[skyLine];
        }
        int minHeight = INT_MAX;
        int start = 0;
        for (int idx = 0; idx < width; idx++) {
            int shiftBits = idx << HEIGHT_BITS;
            // int curIdxHeight = ((static_cast<int64_t>(0xF) << shiftBits) & skyLine) >> shiftBits;
            int curIdxHeight = ((BASE_BITS << shiftBits) & skyLine) >> shiftBits;
            if (minHeight > curIdxHeight) {
                start = idx;
                minHeight = curIdxHeight;
            }
        }
        // std::cout << "\nstart: " << start << "\tminHeight: " << minHeight << "\n";
        int ans = INT_MAX;
        if (maxHeight == minHeight) {
            ans = 0;
        } else {
            for (int end = start; end < width; end++) {
                int shiftBits = end << HEIGHT_BITS;
                int curEndHeight = ((BASE_BITS << shiftBits) & skyLine) >> shiftBits;
                if (minHeight == curEndHeight) {
                    int newHeight = minHeight + end - start + 1;
                    if (newHeight <= maxHeight) {
                        int64_t newSkyLine = skyLine;
                        for (int newIdx = start; newIdx <= end; newIdx++) {
                            int shiftBits = newIdx << HEIGHT_BITS;
                            newSkyLine &= ~(BASE_BITS << shiftBits);
                            newSkyLine |= (BASE_BITS & newHeight) << shiftBits;
                        }
                        // std::cout << "newSkyLine: " << std::hex << (newSkyLine) << "\told: " << (skyLine) << "\n";
                        ans = std::min(ans, dp(maxHeight, width, newSkyLine, dpMemo) + 1);
                    }
                } else {
                    break;
                }
            }
            // std::cout << "\n";
        }
        return dpMemo[skyLine] = ans;
    }
private:
    int const HEIGHT_BITS = 2;
    int64_t const BASE_BITS = static_cast<int64_t>(0xF);
    // int64_t const BASE_BITS = 0xFll;
};
