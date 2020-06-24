#include "../../head.h"


class Solution {
public:
    int longestOnes(std::vector<int> const & A, int K) {
        // plagiarizing from https://leetcode.com/problems/max-consecutive-ones-iii/discuss/247564/javacpython-sliding-window/379427?page=3
        // when the number of 0 equals to K, the longest subarray
        int res = 0, start = 0;
        for (int index = 0; index < A.size(); index++) {
            // std::cout << "\nele: " << A[index] << "\t";
            if (0 == A[index]) {
                // std::cout << "add 0\t" << index << "\t";
                K--;
            }
            if (0 == K) {
                // std::cout << "cur diff: " << index - start + 1 << "\t";
                res = std::max(res, index - start + 1);
            }
            while (0 > K) {
                if (0 == A[start++]) {
                    K++;
                }
            }
        }
        return 0 == K ? res : A.size() - start;
    }
};

class SolutionBetterRumtime {
public:
    int longestOnes(std::vector<int> const & A, int K) {
        std::ios::sync_with_stdio(false);
        cin.tie(nullptr);

        int l = 0;
        int r = 0;

        if (A.size() == 1) return A[0];
        if (K >= A.size()) return A.size();

        while (r < A.size()) {
            if (A[r] == 0) {
                K--;
            }

            if (K < 0) {
                if (A[l] == 0) {
                    K++;
                }
                l++;
            }
            r++;
        }
        return r - l;
    }
    int longestOnes(std::vector<int> const & A, int K) {
        int i = 0, j;
        for (j = 0; j < A.size(); ++j) {
            if (A[j] == 0) {
                K--;
            }
            if (K < 0 && A[i++] == 0) {
                K++;
            }
        }
        return j - i;
    }
};
