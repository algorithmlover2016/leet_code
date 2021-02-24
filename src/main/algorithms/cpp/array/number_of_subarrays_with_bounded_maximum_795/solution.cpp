#include "../../head.h"


class Solution {
public:
    int numSubarrayBoundedMax(std::vector<int> const & A, int L, int R) {

        // plaigiarizing from https://leetcode.com/problems/number-of-subarrays-with-bounded-maximum/discuss/117723/Python-standard-DP-solution-with-explanation
        // plagiarizing from https://leetcode.com/problems/number-of-subarrays-with-bounded-maximum/discuss/117616/C%2B%2B-O(n)-less10-lines

        int const ASize = A.size();
        
        std::vector<int> dpMemo(ASize + 1, 0);
        int ans = 0;
        int pre = -1;

        for (int idx = 0; idx < ASize; idx++) {
            if (A[idx] > R) {
                dpMemo[idx + 1] = 0;
                pre = idx;
            } else if (A[idx] < L) {
                if (idx > 0) {
                    dpMemo[idx + 1] = dpMemo[idx];
                }
            } else {
                dpMemo[idx + 1] = idx - pre;
            }
            ans += dpMemo[idx + 1];
        }
        
        return ans;
    }
private:
    static int const JUST_ZERO = 0;
};


class Solution {
public:
    int numSubarrayBoundedMax(std::vector<int> const & A, int const L, int const R) {
        int left = -1, right = -1 ,ans = 0;
        for (int idx = 0; idx < A.size(); idx++) {
            if (A[idx] > R) {
                left = idx;
            } 

            if (A[idx] >= L) {
                right = idx;
            }
            ans += right - left;
        }
        return ans;
    }
};
