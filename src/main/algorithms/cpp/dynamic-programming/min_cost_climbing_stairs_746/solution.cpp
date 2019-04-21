class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        // the comment that I must add is:
        // I refer to the solution whose site is https://leetcode.com/problems/min-cost-climbing-stairs/discuss/144682/3-Lines-Java-Solution-O(1)-space, which is created by VVtina
        if (cost.size() < 3) {
            return min(cost[0], cost[1]);
        }
        for (int index = 2; index < cost.size(); index++) {
            // which means if we take cost[index] as one step
            cost[index] += min(cost[index - 1], cost[index - 2]);
        }
        // we arived the final(top) floor, we can take step from the last index(cost[-1]) or the pre-next last index(cost[-2]);
        // the meaning of return sentence is different from the computing sentence in the upper.
        return min(cost[cost.size() - 2], cost.back());
    }
};
class subSolution {
public:
	int minCostClimbingStairs(vector<int>& cost) {
		vector<int> dp(cost.size() + 1);
        
        // dp[i] means until i, we can get minimal cost except from cost[i]
		for (int i = 2; i <= cost.size(); i++) {
			dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
		}

		return dp[cost.size()];
	}
};
