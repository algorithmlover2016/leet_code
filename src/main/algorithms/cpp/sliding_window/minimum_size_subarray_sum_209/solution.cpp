#include "../../head.h"

class Solution {
public:
    int minSubArrayLen(int K, vector<int>& A) {
        int res = INT_MAX, start = 0;
        for (int index = 0; index < A.size(); index++) {
            K -= A[index];
            // because there is no negative number
            while (start <= index && K <= 0) {
                K += A[start++];
                res = std::min(res, index - start + 2);
            }
        }
        return INT_MAX == res ? 0: res;

    }
};

class SolutionWrongAnswer {
public:
    /*
       problem: shortest_subarray_with_sum_at_least_k_862
       73 / 93 test cases passed.
        Input:
            [-34,37,51,3,-12,-50,51,100,-47,99,34,14,-13,89,31,-14,-44,23,-38,6]
            151
        Output:
            4
        Expected:
            2
     */
    int shortestSubarray(std::vector<int> const & A, int K) {
        int res = INT_MAX, start = 0;
        for (int index = 0; index < A.size(); index++) {
            K -= A[index];
            while (start <= index && (K <= 0 || K + A[start] <= 0)) {
                K += A[start++];
                res = std::min(res, index - start + 2);
            }
        }
        return INT_MAX == res ? -1 : res;

    }
};

static int io = [](){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
}();


