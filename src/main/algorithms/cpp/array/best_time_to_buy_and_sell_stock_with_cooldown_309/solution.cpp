#include "../../head.h"

/*
// mostProfit: 
              0, 1, 2, 3, 4, 5, 6, 7 (index)
                    0, 1, 2, 3, 4, 5 (prices.index = index - 2)
                    1, 2, 3, 0, 3, 5 (prices.value)
mostProfit[index] = std::max(mostProfit[index - 1](not sell the index share), prices[index - 2] - prices[j] + mostProfit[j - 2] j= prices.0 to prices.index)
// prices
*/
class Solution {
public:
    int maxProfit(std::vector<int> const & prices) {
        int pricesSize = prices.size();
        if (2 > pricesSize) {
            return 0;
        }
        std::vector<int> mostProfit(pricesSize + 2, 0);
        int minEle = prices[0];
        for (int index = 3; index < mostProfit.size(); index++) {
            // std::cout << "index: " << index << "\t";
            minEle = std::min(minEle,  prices[index - 2] - mostProfit[index - 2]);
            // std::cout << "minEle: " << minEle << "\t";
            mostProfit[index] = std::max(mostProfit[index - 1], prices[index - 2] - minEle);
            // std::cout << "mostProfit: " << mostProfit[index] << "\n";
        }
        return mostProfit.back();

    }
};

class Solution {
public:
    int maxProfit(std::vector<int> const & prices) {
        // can understand from https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/discuss/75927/Share-my-thinking-process
        /*
           buy[i] = std::max(sell[i-2]-price, buy[i-1])
           sell[i] = std::max(buy[i-1]+price, sell[i-1])
           */
        int buy(INT_MAX), sell(0), prev_sell(0), prev_buy;
        for (int price : prices) {
            prev_buy = buy;
            buy = std::min(buy, price - prev_sell);
            prev_sell = sell;
            sell = std::max(sell, price - prev_buy);
        }
        return sell;
    }
    // the same with different thinking direction
    int maxProfit(std::vector<int> const & prices) {
        int buy(INT_MIN), sell(0), prev_sell(0), prev_buy;
        for (int price : prices) {
            prev_buy = buy;
            buy = std::max(prev_sell - price, buy);
            prev_sell = sell;
            sell = std::max(prev_buy + price, sell);
        }
        return sell;
    }
};
