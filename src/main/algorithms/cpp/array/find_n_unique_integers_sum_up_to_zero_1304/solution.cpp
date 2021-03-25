#include "../../head.h"


class Solution {
public:
    std::vector<int> sumZero(int n) {
        // plagiarizing from https://leetcode.com/problems/find-n-unique-integers-sum-up-to-zero/discuss/465585/JavaC%2B%2BPython-Find-the-Rule
        if (n < 1) {
            return {};
        }
        std::vector<int> ans(n);
        for (int idx = 0; idx < n; idx++) {
            // idx from 0 to n - 1(included), 2 * idx from 0 to 2n - 2, 2 * idx + 1 will be from 1 to 2n - 1;
            // because each time idx add 1, so the delta will be 2;
            // shift n will be -(n - 1) to (n - 1);
            ans[idx] = idx * 2 - n + 1;
        }
        return ans;
    }
};

class SolutionPreSum {
public:
    std::vector<int> sumZero(int n) {
        // plagiarizing from https://leetcode.com/problems/find-n-unique-integers-sum-up-to-zero/discuss/464344/Trivial-PythonRubyJavaC%2B%2B
        if (n < 1) {
            return {};
        }
        std::vector<int> ans(n, 0);
        for (int idx = 1; idx < n; idx++) {
            ans[idx] = idx;
            ans[0] -= idx;
        }
        return ans;
    }
};

class SolutionSuffixSum {
public:
    std::vector<int> sumZero(int n) {
        // plagiarizing from https://leetcode.com/problems/find-n-unique-integers-sum-up-to-zero/discuss/463998/Keep-it-simple.-Add-all-values-till-n-1-and-then-balance-it-with-sum.
        if (n < 1) {
            return {};
        }
        std::vector<int> ans(n, 0);
        for (int idx = 0; idx < n - 1; idx++) {
            ans[idx] = idx + 1;
            ans[n - 1] -= ans[idx];
        }
        return ans;
    }
};

class SolutionFillBothSide {
    std::vector<int> sumZero(int n) {
        // plagiarizing from https://leetcode.com/problems/find-n-unique-integers-sum-up-to-zero/discuss/463890/Simple-Java-%3A-Fill-from-both-sides
        if (n < 1) {
            return {};
        }
        std::vector<int> ans(n, 0);
        int left = 0, right = n - 1;
        int start = 1;
        while (left < right) {
            ans[left++] = start;
            ans[right--] = -start;
            start++;
        }
        // if 0 == n % 2, there will be no middle element
        // if 1 == n % 2, because left < right, the midddle will meet left = right, which we initialize it to zero
        return ans;
    }
};
