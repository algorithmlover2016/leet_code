#include <iostream>
#include <sstream>
#include <string>

class Solution {
public:
    int numSubarraysWithSumTimeLimitExceeded(vector<int>& A, int S) {
        int ans = 0;
        for (int index = 0; index < A.size(); index++) {
            int sum = 0;
            for (int subIndex = index; subIndex < A.size(); subIndex++) {
                sum += A[subIndex];
                if (sum == S) {
                    ans++;
                } else if (sum > S) {
                    break;
                }
            }
        }
        return ans;
    }
};
// g++ -std=c++11  -o main solution.cpp
class Solution {
public:
    int numSubarraysWithSum(vector<int>& A, int S) {
        //copying method from https://leetcode.com/problems/binary-subarrays-with-sum/discuss/186683/C%2B%2BJavaPython-Straight-Forward
       // I learn method from his solution, I can not do this
        int psum = 0, ans = 0;
        unordered_map<int, int> untilIndex({{0, 1}});
        for (int index = 0; index < A.size(); index++) {
            psum += A[index];
            ans += untilIndex[psum - S];
            untilIndex[psum]++;
        }
        return ans;
    }
};
