#include "../../head.h"


class Solution {
public:
    int kInversePairs(int n, int k) {
        // plagiarizing from https://leetcode.com/problems/k-inverse-pairs-array/discuss/104825/Shared-my-C%2B%2B-O(n-*-k)-solution-with-explanation
        // and https://leetcode.com/problems/k-inverse-pairs-array/discuss/104825/Shared-my-C++-O(n-*-k)-solution-with-explanation/107557
        /*
           Mathematical Proof:
           dp[i][j] = dp[i-1][j] + dp[i-1][j-1] + ......+dp[i-1][j-i+1] as per definition ---(1)

           But dp[i][j-1] = dp[i-1][j-1] + dp[i-1][j-2] + ....+ dp[i-1][j-i] as per definition ---(2)

           From (1) and (2)

           dp[i][j] = dp[i-1][j] + (dp[i-1][j-1] + ......+dp[i-1][j-i+1]) + dp[i-1][j-i] - dp[i-1][j-i]
           =>dp[i][j] = dp[i-1][j] + (dp[i-1][j-1] + ......+dp[i-1][j-i+1] + dp[i-1][j-i]) - dp[i-1][j-i]
           =>dp[i][j] = dp[i-1][j] + dp[i][j-1] - dp[i-1][j-i]
         */
        if (0 > n) {
            return  ILLEGAL_ARGUMENT;
        }
        if (0 == k) {
            return 1;
        }
        std::vector<std::vector<long>> dpMemo(n + 1, std::vector<long>(k + 1, 0));
        // the result is 1 if there is no number and no need to create inverse pair
        dpMemo[0][0] = 1;
        for (int idx = 1; idx < dpMemo.size(); idx++) {
            // no need to create inverse pair, the result will be 1
            dpMemo[idx][0] = 1;
            for (int inversePairNum = 1; inversePairNum < dpMemo[idx].size(); inversePairNum++) {
                /*
                   I think I can make an understanding for this formula:
                   at idx, we want to construct inversePairNum pairs, we can have two choices,
                       first: take the idx-th element, then at idx-th position, the idx-th element can
                              generate (idx - 1) inverse pairs, so if we want to generate inversePairNum inverse pairs,
                              we can add some specific number of inverse pair to its left dpMemo[idx][inversePairNum - 1].
                              However, if inversePairNum is less than idx, then there will be enough inverse pair left to
                              be added to dpMemo[idx][inversePairNum - 1] to generate dpMemo[idx][inversePairNum], because
                              the idx-th element can generate (idx - 1) inverse pair, and there must be some unused pair left.
                              if inversePairNum is larger than or equal to idx, then there will be some conditions who can't
                              generate enough inverse pairs. The most left boundary (included) is (inversePairNum - (idx - 1)),
                              so the most right boundary excluded is (inversePairNum - idx). Now we need consider who contribute
                              to the dpMemo[idx][inversePairNum - idx]. Take a notice that we need take the idx-th element,
                              we must let the inverse pairs reach to (inversePairNum - idx) if we want to use the idx-th element.
                              so if we don't consider the idx-th element, we should get the result of
                              dpMemo[idx - 1][inversePairNum - idx];
                       second: don't take the idx-th element to generate a pair, then we need take the idx - 1 elements to
                               generate inversePairNum pairs which is dpMemo[idx - 1][inversePairNum]
                 */
                dpMemo[idx][inversePairNum] = dpMemo[idx][inversePairNum - 1] + dpMemo[idx - 1][inversePairNum];
                if (inversePairNum >= idx) {
                    dpMemo[idx][inversePairNum] += MOD - dpMemo[idx - 1][inversePairNum - idx];
                }

                dpMemo[idx][inversePairNum] %= MOD;
            }
        }
        return dpMemo[n][k];
    }

private:
    static int const ILLEGAL_ARGUMENT = -1;
    static int const MOD = 1e9 + 7;
};

class Solution {

public:
    int kInversePairs(int n, int k) {
        if (0 == k) {
            return 1;
        }
        const int BASE = 1e9 + 7;
        long memo[n + 1][k + 1];
        memset(memo, 0, sizeof(memo));
        for (int i = 1; i <= n; ++i) {
            memo[i][0] = 1;
            int mrpairs = (i - 1) * i / 2;
            for (int tk = 1; tk <= k && tk <= mrpairs; ++tk) {
                memo[i][tk] = memo[i - 1][tk] + memo[i][tk - 1]; //v3
                if (tk >= i) {
                    memo[i][tk] += BASE - memo[i - 1][tk - i]; //v3
                }
                memo[i][tk] = memo[i][tk] % BASE; //v3
            }
        }
        return memo[n][k];
    }
};
