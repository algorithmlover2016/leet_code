#include "../../head.h"


class Solution {
public:
    int findKthNumber(int m, int n, int k) {
        // plagiarizing from https://leetcode.com/problems/kth-smallest-number-in-multiplication-table/discuss/106977/Java-solution-binary-search
        int low = 1, high = m * n + 1;
        while (low < high) {
            int mid = (high + low) / 2;
            int cntSmallerMid = countSmallerInAllRows(mid, m ,n);
            if (cntSmallerMid >= k) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        return high;
    }
    int countSmallerInAllRows(int target, int rows, int cols) {
        int cnt = 0;
        for (int row = 1; row <= rows; row++) {
            int curRowSmaller = std::min(target / row, cols);
            cnt += curRowSmaller;
        }
        return cnt;
    }
};
