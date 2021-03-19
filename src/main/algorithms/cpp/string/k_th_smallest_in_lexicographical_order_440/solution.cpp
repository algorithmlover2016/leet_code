#include "../../head.h"


class Solution {
public:
    int findKthNumber(int n, int k) {
        // plagiarizing from https://leetcode.com/problems/k-th-smallest-in-lexicographical-order/discuss/92254/C%2B%2BPython-0ms-O((log-n)2)-time-O(1)-space-super-easy-solution-with-detailed-explanations
        // and https://leetcode.com/problems/k-th-smallest-in-lexicographical-order/discuss/92242/ConciseEasy-to-understand-Java-5ms-solution-with-Explaination
        int ans = 1;
        // because we set ans = 1, which is the first elemnt, so we need let k -= 1
        k--;
        while (k > 0) {
            // the index of ans has been removed
            int curLayerCnt = getCnt(ans, ans + 1, n + 1); // started with prefix ans end to ans + 1(exclude) up to n;
            if (k >= curLayerCnt) {
                // we can jump to ans + 1;
                // the cur layer can be droped
                k -= curLayerCnt;
                ans++;
            } else {
                // we can only jump one more step, which let ans = ans * 10. and k-- means we have arrived at ans * 10;
                --k; // because we just remove ans, the only one element
                ans *= 10; // just remove the ans, ans*, ans**, ..., ans**...* will compute at the next loop
            }
        }
        return ans;
    }
private:
    int getCnt(long long start, long long end, long long maxEnd) {
        int ans = 0;
        for (; start <= maxEnd; start *= 10, end *= 10) {
            ans += std::min(end, maxEnd) - start; // the number of elements from start to std::min(maxEnd, end);
        }
        return ans;
    }
};
