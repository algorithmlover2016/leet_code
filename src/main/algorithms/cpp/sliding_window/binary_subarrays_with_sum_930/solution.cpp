#include "../../head.h"


class Solution {
public:
    int numSubarraysWithSum(std::vector<int> const & A, int S) {
        // plagiarizing from https://leetcode.com/problems/max-consecutive-ones-iii/discuss/247564/javacpython-sliding-window/379427?page=3
        // when the number of 0 equals to K, the longest subarray
        int res = 0, start = 0, prefix = 0;
        for (int index = 0; index < A.size(); index++) {
            // std::cout << "\nele: " << A[index] << "\t";
            if (A[index] > 0) {
                prefix = 0;
            }

            S -= A[index];

            if (0 > S) {
                S += A[start++];
            }

            // all the time, we should maintain the constraint that start <= index.
            if (0 == S && start <= index) {
                // if we add the index element, who is zero, we can't remove it immediately
                while ( start < index && 0 == A[start]) {
                    start++;
                    prefix++;
                }
                // std::cout << "cur diff: " << index - start + 1 << "\t";
                res += prefix + 1;
            }
            
        }
        return res;

    }
};

class Solution {
public:
    int numSubarraysWithSum(std::vector<int> const & a, int s) {
        return atmost(a, s) - atmost(a, s - 1);
    }

    int atmost(std::vector<int> const & a, int s) {
        int res = 0;
        int i = 0, j = 0;

        while (j < a.size()) {
            s -= a[j];
            while (s < 0 && i <= j) {
                s += a[i++];
            }
            res += j - i + 1;
            j++;
        }
        return res;
    }
};

class SolutionMap {
public:
     int numSubarraysWithSum(std::vector<int> const & A, int S) {
         std::unordered_map<int, int> c({{0, 1}});
        int psum = 0, res = 0;
        for (int i : A) {
            psum += i;
            res += c[psum - S]; // if has not the key psum -s, c[psum -s] return 0;
            c[psum]++;
        }
        return res;
    }
};
