#include "../../head.h"

class SolutionWrongAnswer {
public:
    /*
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


class Solution {
public:
    int shortestSubarray(vector<int>& A, int K) {
        const int N = A.size();
        int len = N + 1;
        vector<int> S(N+1);

        for(int i=1; i <= N; i++){
            S[i] = S[i-1] + A[i-1];
        }

        deque<pair<int,int>> Q; // sums and their positions

        for(int i=0; i <= N; i++){
            while(!Q.empty() && S[i] >= Q.back().first + K){
                len = min(len, i - Q.back().second);
                Q.pop_back();
            }

            while(!Q.empty() && S[i] <= Q.front().first){
                Q.pop_front();
            }

            Q.push_front({S[i], i});
        }

        len = (len > N) ? -1 : len;
        return len;
    }
};

class Solution {
public:
    int shortestSubarray(std::vector<int> const & A, int K) {
        // plagiarizing from https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/discuss/143726/C%2B%2BJavaPython-O(N)-Using-Deque
        int res = INT_MAX;
        std::deque<int> minSumIndex;
        std::vector<long int> preSum(A.begin(), A.end());
        for (int index = 0; index < preSum.size(); index++) {
            if (index > 0) {
                preSum[index] += preSum[index - 1];
            }
            if (preSum[index] >= K) {
                res = std::min(res, index + 1);
            }
            // if the sum from front() to index >= K, then it can be consider. and later index even meets this condition, it will be much larger res;
            // so we can pop_front() the ele
            while (minSumIndex.size() && preSum[index] - preSum[minSumIndex.front()] >= K) {
                res = std::min(res, index - minSumIndex.front());
                minSumIndex.pop_front();
            }
            // maintain the preSum, keep it's always smallest.
            // and remove the condition, that preSum[index] - preSum[i] <= K and preSum[index] - preSum[j] >= K and i < j
            // which means there is a vallage in the preSum
            while (minSumIndex.size() && preSum[index] <= preSum[minSumIndex.back()]) {
                minSumIndex.pop_back();
            }
            minSumIndex.emplace_back(index);
        }
        return res == INT_MAX ? -1 : res;
    }
};
