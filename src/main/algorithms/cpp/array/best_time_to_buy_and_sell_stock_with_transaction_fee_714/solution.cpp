#include "../../head.h"


class SolutionTLE {
public:
    int maxProfit(std::vector<int> const & prices, int fee) {
        int pricesSize = prices.size();
        if (2 > pricesSize) {
            return 0;
        }
        std::vector<int> profit(pricesSize + 1, 0);
        for (int index = 1; index < pricesSize; index++) {
                // std::cout << "\nindex: " << prices[index] << "\t";
            for (int inner = 0; inner <= index; inner++) {
                profit[index + 1] = std::max(profit[index + 1], profit[inner] + prices[index] - prices[inner] - (index == inner ? 0 : fee));
                // std::cout << "inner: " << prices[inner] << "\t";
                // std::cout << "profit: " << profit[index + 1] << "\t";
            }
        }
        return profit.back();
    }
};

class Solution {
public:
    int maxProfit(std::vector<int> const & prices, int fee) {
        int pricesSize = prices.size();
        if (2 > pricesSize) {
            return 0;
        }
        std::vector<int> profit(pricesSize + 1, 0);
        int preProfit = INT_MIN;
        for (int index = 1; index < pricesSize; index++) {
            // std::cout << "\nindex: " << prices[index] << "\t";
            preProfit = std::max(preProfit, profit[index - 1] - prices[index - 1] -  fee);
            // profit[index + 1] = std::max(profit[index + 1], std::max(preProfit + prices[index], profit[index]));
            profit[index + 1] = std::max(preProfit + prices[index], profit[index]);
        }
        return profit.back();
    }
};
static int aa = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();
