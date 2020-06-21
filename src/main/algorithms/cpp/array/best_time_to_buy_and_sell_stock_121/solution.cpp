#include "../../head.h"


class Solution {
public:
    int maxProfit(std::vector<int> const & prices) {
        int size = prices.size();
        if (0 == size) {
            return 0;
        }
        int res = 0;
        int minEle = INT_MAX;
        for (int index = 0; index < size; index++) {
            if (minEle > prices[index]) {
                minEle = prices[index];
            } else {
                res = std::max(res, prices[index] - minEle);

            }
        }
        return res;
        
    }
};

class SolutionBetterRuntime {
public:
    int maxProfit(std::vector<int> const & prices) {
        if (0 == prices.size()) {
            return 0;
        }
        std::vector<int> profit(prices.size(), 0);
        int minimum = prices.front();
        for(int i=1;i<prices.size();i++) {
            profit[i] = prices[i] - minimum;
            minimum = std::min(minimum, prices[i]);
        }
        return *std::max_element(profit.begin(), profit.end());
    }
};
