#include "../../head.h"


class Solution {
public:
    int superEggDrop(int K, int N) {
        // copyt from solution III combination method
        int left = 1, right = N;
        while (left < right) {
            int middle = left + (right - left) >> 1;
            if (combination(middle, K, N) < N) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }
        return left;
    }

private:
    int combination(int middle, int K, int N) {
        int res = 1, ans = 0;
        for (int k = 1; k <= K; k++) {
            res *= middle - k + 1;
            res /= k;
            ans += res;
            if (ans >= N) {
                break;
            }
        }
        return ans;
    }
};

class SolutionTLE {
public:
    int superEggDrop(int K, int N) {
        // plagiarizing from https://youtu.be/2iuvW8q4ToI
        std::vector<std::vector<int>> dpMemo(K + 1, std::vector<int>(N + 1, N));

        // if there is only one egg, we have to drop from 0 to n, untill the egg is broken, or at n is not broken;
        for (int n = 0; n <= N; n++) {
            dpMemo[1][n] = n;
        }

        for (int k = 1; k <= K; k++) {
            dpMemo[k][0] = 0;
            dpMemo[k][1] = 1;
        }
        for (int k = 2; k <= K; k++) {
            for (int n = 2; n <= N; n++) {
#ifdef BINARY_SEARCH_MID
                int left = 1, right = n;
                while (left < right) {
                    int mid = left + (right - left) / 2;
                    int leftMoves = dpMemo[k - 1][mid - 1];
                    int rightMoves = dpMemo[k][n - mid];
                    if (leftMoves < rightMoves) {
                        left = mid + 1;
                    } else {
                        right = mid;
                    }
                }
                int mid = left;

                dpMemo[k][n] = std::min(dpMemo[k][n],
                        // we drop a egg at mid,
                        // if it is broken, we will know the F is in [0, mid), and eggs' number will minus one
                        // if it isn't broken, we will know the F is in [mid, n], and the number of eggs will keep same
                        std::max(dpMemo[k - 1][mid - 1], dpMemo[k][n - mid]) + 1);
#else
                for (int mid = 1; mid <= n; mid++) {
                    dpMemo[k][n] = std::min(dpMemo[k][n],
                            // we drop a egg at mid,
                            // if it is broken, we will know the F is in [0, mid), and eggs' number will minus one
                            // if it isn't broken, we will know the F is in [mid, n], and the number of eggs will keep same
                    std::max(dpMemo[k - 1][mid - 1], dpMemo[k][n - mid]) + 1);
                }
#endif
            }
        }
        return dpMemo[K][N];

    }
};


#define ONE_DEMENSION_DP
class Solution {
public:
    int superEggDrop(int K, int N) {
        // plagiarizing from https://leetcode.com/problems/super-egg-drop/discuss/158974/C%2B%2BJavaPython-2D-and-1D-DP-O(KlogN)
#ifdef ONE_DEMENSION_DP
        std::vector<int> dpMemo(K + 1, 0);
#else
        std::vector<std::vector<int>> dpMemo(N + 1, std::vector<int>(K + 1, 0));
#endif
        int moves = 0;
#ifdef ONE_DEMENSION_DP
        while (dpMemo[K] < N)
#else
        while (dpMemo[moves][K] < N)
#endif
        {
            moves++;
#ifdef ONE_DEMENSION_DP
            for (int k = K; k > 0; k--) {
                dpMemo[k] += dpMemo[k - 1] + 1;
            }
#else
            for (int k = 1; k <= K; k++) {
                /*
                   The dp equation is:
                   dp[m][k] = dp[m - 1][k - 1] + dp[m - 1][k] + 1,
                   which means we take 1 move to a floor,
                   if egg breaks, then we can check dp[m - 1][k - 1] floors.
                   if egg doesn't breaks, then we can check dp[m - 1][k] floors.
                 */
                dpMemo[moves][k] = dpMemo[moves - 1][k - 1] + dpMemo[moves - 1][k] + 1;
            }
#endif
        }
        return moves;
    }
};
