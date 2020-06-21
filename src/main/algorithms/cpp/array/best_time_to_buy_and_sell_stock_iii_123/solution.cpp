#include "../../head.h"


#define ADD_MAX
// #undef  ADD_MAX
class Solution {
public:
    int maxProfit(std::vector<int> const & prices) {
        int k = 2;
        // plagiarizing from https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/discuss/135704/Detail-explanation-of-DP-solution
        int pricesSize = prices.size();
        if (2 > pricesSize) {
            return 0;
        }
        std::vector<int> mostProfit(k + 1, 0);
#ifdef ADD_MAX
        std::vector<int> maxBefore(k + 1, -prices[0]);
        for (int index = 1; index < prices.size(); index++) {
            int previous = mostProfit[0];
            for (int transaction = 1; transaction < mostProfit.size(); transaction++) {
                maxBefore[transaction] = std::max(maxBefore[transaction], previous - prices[index - 1]);
                previous = mostProfit[transaction];
                mostProfit[transaction] = std::max(mostProfit[transaction], maxBefore[transaction] + prices[index]);
                // std::cout << "transaction: " << transaction
                //     << "\tmaxBefore: " << maxBefore[transaction]
                //     << "\tindexEle: " << prices[index]
                //     << "\tmostProfit: " << mostProfit[transaction] << "\n";
            }
        }
#else
        std::vector<int> minBefore(k + 1, prices[0]);
        for (int index = 1; index < prices.size(); index++) {
            int previous = mostProfit[0];
            for (int transaction = 1; transaction < mostProfit.size(); transaction++) {
                minBefore[transaction] = std::min(minBefore[transaction], prices[index - 1] - previous);
                previous = mostProfit[transaction];
                mostProfit[transaction] = std::max(mostProfit[transaction], prices[index] - minBefore[transaction]);
            }
        }
#endif
        return mostProfit[k];
    }
};
