#include "../../head.h"


class SolutionTLE_N2 {
public:
    int sumSubarrayMins(std::vector<int> const & A) {
        int res = 0;
        for (int index = 0; index < A.size(); index++) {
            int curMin = A[index];
            for (int inner = index; inner < A.size(); inner++) {
                if (curMin > A[inner]) {
                    curMin = A[inner];
                }
                res += curMin;
                res %= MOD;
            }
        }
        
        return res;
    }
private:
    int const MOD = 1e9 + 7;
};


class Solution {
public:
    int sumSubarrayMins(std::vector<int> const & A) {
        // plagiarizing from https://leetcode.com/problems/sum-of-subarray-minimums/discuss/170750/C%2B%2BJavaPython-Stack-Solution
        int ASize = A.size();
        int res = 0;
        std::vector<int> left(ASize, 0), right(ASize, 0);
        std::stack<std::pair<int, int>> leftStack, rightStack;
        leftStack.emplace(INT_MIN, 0);
        rightStack.emplace(INT_MIN, 0);

        for (int index = 0; index < ASize; index++) {
            int num = A[index];
            int cnt = 1;
            // the left and the right only one get the =.
            while ((leftStack.top().first > num)) {
                // std::cout << "left pop " << leftStack.top().first << "\t" << num << "\n";
                cnt += leftStack.top().second;
                leftStack.pop();
            }
            // std::cout << "insert " << num << " on left" << "\n";
            leftStack.emplace(num, cnt);
            left[index] = cnt;
        }
        // std::cout << " right Size \n";

        for (int index = ASize - 1; index >= 0; index--) {
            int cnt = 1;
            while ((rightStack.top().first >= A[index])) {
                // std::cout << "right pop " << rightStack.top().first << "\t" << A[index] << "\n";
                cnt += rightStack.top().second;
                rightStack.pop();
                // std::cout << "insert " << A[index] << " on right" << "\n";
            }
            rightStack.emplace(A[index], cnt);
            right[index] = cnt;
        }
        for (int index = 0; index < ASize; index++) {
            res = (res + A[index] * left[index] * right[index]) % MOD;
        }


        return res;
    }
private:
    int const MOD = 1e9 + 7;
};

class Solution {
public:

    int sumSubarrayMins(std::vector<int> const & A) {
        //no of greater elements on left/right with cur as minimum element
         int res = 0, n = A.size(), j, k;
         std::stack<int> s;
        for (int i = 0; i <= n; ++i) {
            while (!s.empty() && A[s.top()] > (i == n ? 0 : A[i])) {
                j = s.top(), s.pop();
                k = s.empty() ? -1 : s.top();
                res = (res + A[j] * (i - j) * (j - k)) % MOD;
            }
            s.push(i);
        }
        return res;
    }

private:
    int const MOD = 1e9 + 7;
};
