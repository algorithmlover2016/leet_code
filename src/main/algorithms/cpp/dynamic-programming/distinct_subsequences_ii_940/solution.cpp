#include <iostream>
#include <sstream>
#include <string>

class Solution {
public:
    int distinctSubseqII(string S) {
        // copy code from https://leetcode.com/problems/distinct-subsequences-ii/discuss/192017/C%2B%2BJavaPython-4-lines-O(N)-Time-O(1)-Space
        int addedNum = 0, sum = 0;
        const int modNum = 1000000007;
        vector<int> endWithCharSum(26, 0);
        for (int index = 0; index < S.size(); index++) {
            // sum is the all element, +1 means the longest string ending with S[index] can add the character
            // addedNum = sum - endWithCharSum[S[index] - 'a'] + 1;
            // sum = (sum + addedNum) % modNum;
            addedNum = (sum - endWithCharSum[S[index] - 'a'] + 1) % modNum;
            sum = (sum + addedNum) % modNum;
            endWithCharSum[S[index] - 'a'] = (endWithCharSum[S[index] - 'a'] + addedNum) % modNum;
        }
        return int((sum + modNum)% modNum);
    }
};
// g++ -std=c++11  -o main solution.cpp
