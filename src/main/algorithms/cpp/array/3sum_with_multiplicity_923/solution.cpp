#include "../../head.h"


class Solution {
public:
    int threeSumMulti(std::vector<int> const & arr, int target) {
        // plagiairizing idea from https://leetcode.com/problems/3sum-with-multiplicity/discuss/1123612/C%2B%2B-Super-Simple-7-line-Solution-Without-Sorting
        int const arrSize = arr.size();
        std::unordered_map<int, int> twoSum;
        int ans = 0;
        for (int idx = 0; idx < arrSize; idx++) {
            // if twoSum has no the key, its value will be zero (default)
            ans = (ans + twoSum[target - arr[idx]]) % MOD;
            for (int left = 0; left < idx; left++) {
                twoSum[arr[left] + arr[idx]]++;
            }
        }
        return ans;
        
    }
private:
    static int const MOD = 1e9 + 7;
};

class Solution {
public:
    int threeSumMulti(std::vector<int> const & A, int target) {
        // plagiarizing from https://leetcode.com/problems/3sum-with-multiplicity/discuss/181131/C%2B%2BJavaPython-O(N-%2B-101-*-101)
        std::unordered_map<int, long> c;
        for (int a : A) {
            c[a]++;
        }
        long res = 0;
        for (auto it : c) {
            for (auto it2 : c) {
                int i = it.first, j = it2.first, k = target - i - j;
                if (!c.count(k)) {
                    continue;
                }
                if (i == j && j == k) {
                    // if c[i] < 3, then one of c[i], c[i] - 1, c[i] - 2 will be zero, then res will add 0;
                    // c(n, k) = n! / (k! * (n - k)!)
                    res += c[i] * (c[i] - 1) * (c[i] - 2) / 6;
                } else if (i == j && j != k) {
                    res += c[i] * (c[i] - 1) / 2 * c[k];
                } else if (i < j && j < k) {
                    res += c[i] * c[j] * c[k];
                }
            }
        }
        return res % MOD;
    }
private:
    static int const MOD = 1e9 + 7;
};
