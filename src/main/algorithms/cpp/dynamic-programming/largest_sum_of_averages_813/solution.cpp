#include <iostream>
#include <sstream>
#include <string>

class Solution {
public:
    double largestSumOfAverages(vector<int>& A, int K) {

        // copying solution from https://leetcode.com/problems/largest-sum-of-averages/discuss/122739/C%2B%2BJavaPython-Easy-Understood-Solution-with-Explanation

        memset(dpStorage, 0, sizeof(dpStorage));
        int Len = A.size();
        double sum = 0;
        for (int index = 0; index < Len; index++) {
            sum += A[index];
            dpStorage[index + 1][1] = sum / (index + 1);
        }
        return dpSearch(Len, K, A);
    }
    double dpSearch(int Len, int K, const vector<int> & A) {
        if (dpStorage[Len][K] > 0) {
            return dpStorage[Len][K];
        }
        if (Len < K) {
            return 0;
        }
        double end2CurSum = 0;
        for (int index = Len - 1; index > 0; index--) {
            end2CurSum += A[index];
            dpStorage[Len][K] = max(dpStorage[Len][K], dpSearch(index, K - 1, A) + end2CurSum / (Len - index));
        }
        return dpStorage[Len][K];
    }

    static const int MaxArrayLen = 200;
    double dpStorage[MaxArrayLen][MaxArrayLen];
};
// g++ -std=c++11  -o main solution.cpp
