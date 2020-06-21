#include "../../head.h"


class Solution {
public:
    int maxProfit(std::vector<int> const & prices) {
        int pricesSize = prices.size();
        if (0 == pricesSize) {
            return 0;
        }
        int minEle = prices.front();
        int maxEle = minEle;
        int res = 0;
        for (int index = 1; index < pricesSize; index++) {
            if (prices[index] < maxEle) {
                res += maxEle - minEle;
                minEle = prices[index];
            }
            maxEle = prices[index];
        }
        return res + maxEle - minEle;
    }
};

class SolutionBetterSolution {
public:
    int maxProfit(vector<int>& prices) {

        int last_min = prices[0];
        int profit = 0;
        for(int cp : prices) {
            if(cp > last_min) {
                profit += cp - last_min;
            }
            last_min = cp;
        }
        return profit;
    }
};
