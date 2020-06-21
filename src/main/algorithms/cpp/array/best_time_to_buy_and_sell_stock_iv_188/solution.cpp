#include "../../head.h"


/**
 * dp[i, j] represents the max profit up until prices[j] using at most i transactions. 
 * dp[i, j] = max(dp[i, j-1], prices[j] - prices[jj] + dp[i-1, jj]) { jj in range of [0, j-1] }
 *          = max(dp[i, j-1], prices[j] + max(dp[i-1, jj] - prices[jj]))
 * dp[0, j] = 0; 0 transactions makes 0 profit
 * dp[i, 0] = 0; if there is only one price data point you can't make any transaction.
 */
class SolutionTwoDem {
public:
    int maxProfit(int k, std::vector<int> const & prices) {
        // plagiarizing from https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/discuss/135704/Detail-explanation-of-DP-solution
        int pricesSize = prices.size();
        if (2 > pricesSize) {
            return 0;
        }
        std::vector<std::vector<int>> mostProfit(k + 1, std::vector<int>(pricesSize, 0));
#ifdef ADD_MAX
        for (int transaction = 1; transaction < mostProfit.size(); transaction++) {
            int maxBefore = -prices[0];
            for (int index = 1; index < prices.size(); index++) {
                maxBefore = std::max(maxBefore, mostProfit[transaction - 1][index - 1] - prices[index - 1]);
                mostProfit[transaction][index] = std::max(mostProfit[transaction][index - 1], maxBefore + prices[index]);
            }
        }
#else
        for (int transaction = 1; transaction < mostProfit.size(); transaction++) {
            int minBefore = prices[0];
            for (int index = 1; index < prices.size(); index++) {
                minBefore = std::min(minBefore, prices[index - 1] - mostProfit[transaction - 1][index - 1]);
                mostProfit[transaction][index] = std::max(mostProfit[transaction][index - 1], prices[index] - minBefore);
            }
        }
#endif
        return mostProfit[k][pricesSize - 1];
    }
};

class SolutionLoopReverse {
public:
    int maxProfit(int k, std::vector<int> const & prices) {
        // plagiarizing from https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/discuss/135704/Detail-explanation-of-DP-solution
        int pricesSize = prices.size();
        if (2 > pricesSize) {
            return 0;
        }
        std::vector<std::vector<int>> mostProfit(k + 1, std::vector<int>(pricesSize, 0));
#ifdef ADD_MAX
        std::vector<int> maxBefore(k + 1, -prices[0]);
        for (int index = 1; index < prices.size(); index++) {
            for (int transaction = 1; transaction < mostProfit.size(); transaction++) {
                maxBefore[transaction] = std::max(maxBefore[transaction], mostProfit[transaction - 1][index - 1] - prices[index - 1]);
                mostProfit[transaction][index] = std::max(mostProfit[transaction][index - 1], maxBefore[transaction] + prices[index]);
            }
        }
#else
        std::vector<int> minBefore(k + 1, prices[0]);
        for (int index = 1; index < prices.size(); index++) {
            for (int transaction = 1; transaction < mostProfit.size(); transaction++) {
                minBefore[transaction] = std::min(minBefore[transaction], prices[index - 1] - mostProfit[transaction - 1][index - 1]);
                mostProfit[transaction][index] = std::max(mostProfit[transaction][index - 1], prices[index] - minBefore[transaction]);
            }
        }
#endif
        return mostProfit[k][pricesSize - 1];
    }
};

// #define ADD_MAX
class Solution {
public:
    int maxProfit(int k, std::vector<int> const & prices) {
        // plagiarizing from https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/discuss/135704/Detail-explanation-of-DP-solution
        int pricesSize = prices.size();
        if (2 > pricesSize) {
            return 0;
        }
        std::vector<int> mostProfit(k + 1, 0);
#ifdef ADD_MAX
        std::vector<int> maxBefore(k + 1, -prices[0]);
        for (int index = 1; index < prices.size(); index++) {
            for (int transaction = 1; transaction < mostProfit.size(); transaction++) {
                // if the mostProfits become one dimenson, then the mostProfit record the current profit at index in different transaction
                // so the difference should be prices[index] not prices[index - 1]
                // mostProfit[transaction -1] - prices[index] + prices[index] means until index, the most profit at index with no deal at index day
                maxBefore[transaction] = std::max(maxBefore[transaction], mostProfit[transaction - 1] - prices[index]);
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
            for (int transaction = 1; transaction < mostProfit.size(); transaction++) {
                minBefore[transaction] = std::min(minBefore[transaction], prices[index] - mostProfit[transaction - 1]);
                mostProfit[transaction] = std::max(mostProfit[transaction], prices[index] - minBefore[transaction]);
            }
        }
#endif
        return mostProfit[k];
    }
};

#define ADD_MAX
#undef ADD_MAX
class Solution {
public:
    int maxProfit(int k, std::vector<int> const & prices) {
        // plagiarizing from https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/discuss/135704/Detail-explanation-of-DP-solution
        int pricesSize = prices.size();
        if (2 > pricesSize) {
            return 0;
        }
        if (k >= (pricesSize >> 1)) {
            return moreThanHalf(prices);
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
private:
    int moreThanHalf(std::vector<int> const & prices) {
        int profit = 0;
        int lastMin = prices[0];
        for (int index = 1; index < prices.size(); index++) {
            if (prices[index] > lastMin) {
                profit += prices[index] - lastMin;
            }
            lastMin = prices[index];
        }
        return profit;
    }
};
