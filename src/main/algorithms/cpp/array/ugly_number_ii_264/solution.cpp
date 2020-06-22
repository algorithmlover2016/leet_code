#include "../../head.h"


class Solution {
public:
    int nthUglyNumber(int n) {
        // plagiarizing from https://leetcode.com/problems/ugly-number-ii/discuss/69364/My-16ms-C%2B%2B-DP-solution-with-short-explanation
        if (n < 4) {
            return n;
        }
        std::vector<int> minMulti(n, 0);
        minMulti[0] = 1; //n = 1, return 1

        int cnt2 = 0, cnt3 = 0, cnt5 = 0;
        // cnt2 record that the least index that can multiply 2
        // cnt3 record that the least index that can multiply 3
        // cnt5 record that the least index that can multiply 5
        for (int index = 2; index <= n; index++) {
            minMulti[index - 1] = std::min(minMulti[cnt2] * 2, std::min(minMulti[cnt3] * 3, minMulti[cnt5]  *5));
            // std::cout << "cnt2: " << cnt2 << "\tcnt3: " << cnt3 << "\tcnt5: " << cnt5 << "\n";
            // std::cout << "Ugly Number: " <<minMulti[index - 1] << "\tindex: " << index << "\n";
            if (minMulti[index - 1] == minMulti[cnt2] * 2) {
                cnt2++;
            }
            if (minMulti[index - 1] == minMulti[cnt3] * 3) {
                cnt3++;
            }
            if (minMulti[index - 1] == minMulti[cnt5]  *5) {
                cnt5++;
            }
        }
        return minMulti[n - 1];
    }
};
