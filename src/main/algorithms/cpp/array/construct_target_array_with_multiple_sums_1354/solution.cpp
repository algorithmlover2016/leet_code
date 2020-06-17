#include "../../head.h"


class SolutionStackOverFlow {
public:
    bool isPossible(std::vector<int> & target) {
        int targetSize = target.size();
        if (0 == targetSize) {
            return true;
        }
        std::sort(target.begin(), target.end());
        int index = 0;
        while (index < targetSize && 1 == target[index]) {
            index++;
        }
        std::vector<int> basic(targetSize, 1);
        return dfs(basic, target, targetSize, index);
    }
    bool dfs(std::vector<int> & basic,
            std::vector<int> const & target,
            int sum,
            int ts) {
        if (ts >= target.size()) {
            return true;
        }
        if (sum > target[ts]) {
            return false;
        } else if (sum == target[ts]) {
            ts++;
        }
        for (int index = 0; index < basic.size(); index++) {
            int newSum = sum + sum - basic[index];
            int tmp = basic[index];
            basic[index] = sum;
            if (dfs(basic, target, newSum, ts)) {
                return true;
            }
            basic[index] = tmp;
        }
        return false;
    }
};

class Solution {
public:
    bool isPossible(std::vector<int> const & target) {
        // plagiarizing from https://leetcode.com/problems/construct-target-array-with-multiple-sums/discuss/510256/JavaC%2B%2BPython-Backtrack-OJ-is-wrong
        /*
        for example: target = [A, B, C] (A > B >C)
        sum = A + B + C;
        after remove A; sum = B + C != 0 and sum < A; becasue according rules: A = D + B + C;
        if D = n * (B + C), then after some iteration, the position of D will be zero,
        however D, B, C >= 1
        */
        std::priority_queue<int> backTracing(target.begin(), target.end());
        long int sum = 0;
        for (int ele : target) {
            sum += ele;
        }
        
        while (!backTracing.empty()) {
            int cur = backTracing.top(); backTracing.pop();
            sum -= cur;
            if (1 == cur || 1 == sum) { // the 1 element means the last
                return true;
            }
            if (cur < sum || sum == 0 || cur % sum == 0) {
                return false;
            }
            cur %= sum;
            sum += cur;
            backTracing.emplace(cur);
        }
        return false;
    }
};
