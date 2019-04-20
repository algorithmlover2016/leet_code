#include <iostream>
#include <sstream>
#include <string>

class Solution {
public:
    int racecar(int target) {
        if (dpStorage[target] > 0) {
            return dpStorage[target];
        }
        int upperN = floor(log2(target)) + 1;
        if ((1 << upperN) == target + 1) {
            dpStorage[target] = upperN;
        } else {
            dpStorage[target] = upperN + 1 + racecar((1<< upperN) - 1 - target);
            for (int index = 0; index < upperN - 1;index++) {
                dpStorage[target] = min(dpStorage[target],
                        racecar(target - (1 << upperN - 1) + (1 << index)) + upperN -1 + 1 + 1 + index);
            }
        }
        return dpStorage[target];
    }
    unordered_map<int, int> dpStorage;
};
// g++ -std=c++11  -o main solution.cpp

// code with explation
class Solution {
public:
    int search(int n) {
        if (dp[n] != -1) {
            return dp[n];
        }

        // 1 + 2 + 4 + ... + 2^(k-1) = 2^k - 1 >= n, k steps
        // 2^(k - 1) <= n < 2^k
        int k = floor(log2(n)) + 1;

        if (n == ((1 << k) - 1)) {  // k steps ok
            return dp[n] = k;
        }

        // k steps pass target
        int temp = k + 1 +  search((1 << k) - 1 - n);

        for (int i = 0; i < k - 1; i++) {
            int distLeft = n - ((1 << (k - 1)) - 1) + ((1 << i) - 1);
            int stepLeft = search(distLeft);
            temp = min(k - 1 + 1 + i + 1 + stepLeft, temp);
        }
        return dp[n] = temp;
    }

    vector<int> dp;
    int racecar(int n) {
        dp = vector<int>(n + 1, -1);
        return search(n);
    }
};
