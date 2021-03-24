#include "../../head.h"


// #define DEBUG
class Solution {
public:
    int numberOfSets(int n, int k) {
        // plagiarizing idea from https://leetcode.com/problems/number-of-sets-of-k-non-overlapping-line-segments/discuss/901894/JavaPython-Top-Down-DP-Clean-and-Concise-O(4*n*k)
        std::vector<std::vector<std::vector<int>>> dpMemo(n + 1,
                std::vector<std::vector<int>>(k + 1, std::vector<int>(2, INIT_FLAG)));
        return dfs(0, n, k, 1, dpMemo);
    }
private:
    int dfs(int start, int end/*exclude*/, int k,  int isStartPoint, std::vector<std::vector<std::vector<int>>> & dpMemo) {
        if (0 == k) {
            return 1;
        }
        if (start == end) {
            return 0;
        }
        if (INIT_FLAG != dpMemo[start][k][isStartPoint]) {
            return dpMemo[start][k][isStartPoint];
        }
        int ans = dfs(start + 1, end, k, isStartPoint, dpMemo); // we do nothing at this point, which means skipp the point,
                                                              // this point will not be start or end point
        if (1 == isStartPoint) {
            // we take the point as start point
            // then  from start + 1 to end, we need find a end point
            ans += dfs(start + 1, end, k, 0, dpMemo);
        } else {
            // we take the point as end point, then k -= 1
            // then from start + 1 to end, we need find a new start point, if k > 0
            // because end point can be as start point, so there is no need to add 1 to start
            ans += dfs(start, end, k - 1, 1, dpMemo);
        }
        #ifdef DEBUG
        std::cout << start << ", " << k << ", " << isStartPoint << ": " << ans << "\n";
        #endif
        return dpMemo[start][k][isStartPoint] = ans % MOD;
    }

private:
    static int const MOD = 1e9 + 7;
    int const INIT_FLAG = -1;
};


class Solution {
public:
    int numberOfSets(int n, int k) {
        // plagiarizing from https://leetcode.com/problems/number-of-sets-of-k-non-overlapping-line-segments/discuss/898685/Java-O(n*k)-or-Detailed-Explanation
        // if k >= n; return 0; at least k + 1 points can form k line segments
        // if k == 1; return n * (n - 1) / 2; // combination(n, 2);
        // if k == n - 1; return 1; // combination(n, n);
        if (1 == k) {
            return n * (n - 1) / 2;
        }
        if (n - 1 == k) {
            return 1;
        }
        std::vector<std::vector<long>> preSumDp(n, std::vector<long>(k, 0));
        // preSumDp[0][0] = 0; // there is only one point, and can't be splited into 1 line segment
        for (int idx = 1; idx < n; idx++) {
            // the idx represents the idx + 1 point(idx start from 0, however n, k start from 1);
            preSumDp[idx][0] /*which means there are idx + 1 points, and need split into 1 line segments*/ =
                (idx + 1) * idx / 2 + preSumDp[idx - 1][0];
            // adding the preSumDp[idx - 1][0] just for the preSum starting from 0 to idx;
        }
        for (int idx = 2; idx < n; idx++) {
            // we have initialize preSumDp[:][0], so ks start from 1;
            for (int ks = 1; ks < k; ks++) {
                preSumDp[idx][ks] = preSumDp[idx - 1][ks] - preSumDp[idx - 2][ks] + preSumDp[idx - 1][ks - 1];
                /*
                   the upper expression need some explanation
                   the reason that we do the minus operation (preSumDp[idx - 1][ks] - preSumDp[idx - 2][ks]) because
                       preSumDp[i][j] is the preSum, after doing the minus operation, it represents
                       the cur value of [idx - 1][ks], which can be marked as cur[idx - 1][ks];
                   all the expresion represent that combination(n, k) = combination(n - 1, k) + combination(n - 1, k - 1);
                       the upper is a mathmatic prove: n = idx + 1; k = ks + 1;
                       one prove:
                           c(n, k) = n!/((k!) * (n - k)!) = A
                           c(n - 1, k) = (n - 1)! /((k!) * (n - 1 - k)!) = B
                           c(n - 1, k - 1) = (n - 1)!/((k - 1)! * (n - k)!) = C; and A = B + C;
                       the second prove:
                           we need select k bolls from n bolls; Assuming we take a boll as base condition;
                           if we choose the boll, we just need choose k - 1 bolls from n - 1 bolls;
                           if we don't, we need choose k bolls from n - 1 bolls;
                   the follow is to explain why we need preSum;
                   however, the preSumDp[idx - ][ks - 1] represents the preSum from cur[ks][ks - 1] to cur[idx - 1][ks - 1]
                   we can consider the situation like this:
                       we choose ks - 1 line segments from idx - 1 points, and then construct the last line segment(ks)
                       between the endPoint of (ks - 1)th line segment and the last point, whose index is idx;
                       however, according to the problem, we can construct these line segments with skiping some points;
                       so, if we want to skip the endPoint of (ks - 1)th line segment, we need construct ks - 1 line
                       segments with idx - 2 points, and the last (ks)th line segment will be (idx - 1, idx); and so on,
                       we need compute the sum from [ks][ks - 1] to [idx - 1][ks - 1]
                 */
                preSumDp[idx][ks] %= MOD;
                preSumDp[idx][ks] += preSumDp[idx - 1][ks];
            }
        }
        return (int)(preSumDp[n - 1][k - 1] - preSumDp[n - 2][k - 1]);
    }
private:
    static int const MOD = 1e9 + 7;
};

// #define DEBUG
class Solution {
public:
    int numberOfSets(int n, int k) {
        // plagiarizing from https://leetcode.com/problems/number-of-sets-of-k-non-overlapping-line-segments/discuss/898727/C%2B%2B-O(n)-solution-explained-in-detail-using-Stars-and-Bars
        // how to compute the combination(n, k);
        // if k >= n; return 0; at least k + 1 points can form k line segments
        // if k == 1; return n * (n - 1) / 2; // combination(n, 2);
        // if k == n - 1; return 1; // combination(n, n);
        if (1 == k) {
            return n * (n - 1) / 2;
        }
        if (n - 1 == k) {
            return 1;
        }
        // the k line segments can't overlap, but can join, if we insert one dummy point if the two line segment are
        // adjacent, which is equal to n + k - 1 points select 2 * k points
        static bool initFlag = (initFact(), true);
        return ncr(n + k - 1, 2 * k);
    }
private:
    int ncr(int n, int k) {
        if (k > n) {
            return 0;
        }
        return multiply(factorial[n], multiply(invertFactorial[n - k], invertFactorial[k]));
    }

    void initFact() {
        // 0! = 1; 1! = 1;
        // 1 / (0!) = 1; 1 / (1!) = 1;
        for (int idx = 2; idx < MAX_N; idx++) {
            factorial[idx] = multiply(factorial[idx - 1], idx);
            invert[idx] = multiply(invert[MOD % idx], MOD - MOD / idx);
            invertFactorial[idx] = multiply(invertFactorial[idx - 1], invert[idx]);
            #ifdef DEBUG
            std::cout << "invert[" << idx << "]: " << invert[idx] << "\t" <<
                "invertFactorial[" << idx << "]: " << invertFactorial[idx] << "; ";
            #endif
        }
    }
    int multiply(int a, int b) {
        return 1LL * a * b % MOD;
    }
private:
    static int const MOD = 1e9 + 7;
    // n <= 1000, and k <= n - 1; n + k <= 2000; and n >= 2 and k >= 1, which means the first 2 elements are useless
    static int const MAX_N = 2e3 + 10;
    static std::vector<int> factorial; // (n + k - 1)!
    static std::vector<int> invert; // 1 / (k)
    static std::vector<int> invertFactorial; // 1 / ((2 * k)!)
};
std::vector<int> Solution::factorial = std::vector<int>(MAX_N, 1); // (n + k - 1)!
std::vector<int> Solution::invert = std::vector<int>(MAX_N, 1); // 1 / (k)
std::vector<int> Solution::invertFactorial = std::vector<int>(MAX_N, 1); // 1 / ((2 * k)!)
