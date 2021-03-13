#include "../../head.h"


class Solution {
public:
    std::vector<int> constructArray(int n, int k) {
        // plagiarizing from https://leetcode.com/problems/beautiful-arrangement-ii/discuss/106948/C%2B%2B-Java-Clean-Code-4-liner
        // and https://leetcode.com/problems/beautiful-arrangement-ii/discuss/106957/C%2B%2B-concise-code-O(n)
        std::vector<int> ans;
        if (k >= n) {
            // n different number, max n - 1 diff distance
            // it's impossible to get the right answer
            return ans;
        }
        int left = 1, right = k + 1;
        while (left <= right) {
            ans.emplace_back(left++);
            if (left <= right /*because the upper operator have made left add one after push back*/) {
                ans.emplace_back(right--);
                // because we first push back right, and then we minus one from right.
            }
        }
        for (int idx = k + 1; idx < n; idx++) {
            ans.emplace_back(idx + 1);
        }
        return ans;
    }
};

// #define DEBUG
class Solution {
public:
    std::vector<int> constructArray(int n, int k) {
        // plagiarizing from https://leetcode.com/problems/beautiful-arrangement-ii/discuss/106948/C%2B%2B-Java-Clean-Code-4-liner
        // and https://leetcode.com/problems/beautiful-arrangement-ii/discuss/106957/C%2B%2B-concise-code-O(n)
        if (k >= n) {
            // n different number, max n - 1 diff distance
            // it's impossible to get the right answer
            return {};
        }
        std::vector<int> ans(n, 0);
        int left = 1, right = k + 1;
        int idx = 0;
        while (left <= right) {
            #ifdef DEBUG
            std::cout << left << ", " << right << "\n";
            #endif
            ans[idx++] = left++;
            if (left <= right /*because the upper operator have made left add one after push back*/) {
                ans[idx++] = right--;
                // because we first push back right, and then we minus one from right.
            }
        }
        std::iota(ans.begin() + k + 1, ans.end(), k + 2);
        return ans;
    }
};


// #define DEBUG
class Solution {
public:
    std::vector<int> constructArray(int n, int k) {
        // plagiarizing from https://leetcode.com/problems/beautiful-arrangement-ii/discuss/106948/C%2B%2B-Java-Clean-Code-4-liner
        // and https://leetcode.com/problems/beautiful-arrangement-ii/discuss/106957/C%2B%2B-concise-code-O(n)
        if (k >= n) {
            // n different number, max n - 1 diff distance
            // it's impossible to get the right answer
            return {};
        }
        std::vector<int> ans;

        for (int left = 1, right = n; left <= right;) {
            #ifdef DEBUG
            std::cout << left << ", " << right << ", " << k << "\n";
            #endif
            if (k > 1) {
                // when k == 1, it's the last element that make the smallest distance. and before it we have
                // insert k - 1 elements, it will create k - 1 different distance. So at k == 1, we just normally add
                // elements which is increasing, which will create the smallest differnt distance
                ans.emplace_back((k-- & 0x01) ? left++ : right--);
            } else {
                ans.emplace_back(left++);
            }
        }
        return ans;
    }
};
