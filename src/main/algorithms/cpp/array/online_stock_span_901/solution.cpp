#include "../../head.h"


class StockSpanner {
public:
    StockSpanner() {
    }

    int next(int price) {
        // std::cout << "next: " << price << "\n";
        prices.emplace_back(price);
        // std::cout << "prices.size: " << prices.size() << "\n";
        while (!decreaseIndexStack.empty() && prices[decreaseIndexStack.back() - 1] <= price) {
            decreaseIndexStack.pop_back();
        }
        // must add () when using ? :
        int ans = prices.size() - (decreaseIndexStack.empty() ? 0 : decreaseIndexStack.back());
        // std::cout << "prices.size: " << prices.size() << "\n";
        decreaseIndexStack.emplace_back(prices.size());
        return ans;

    }
private:
    std::vector<int> prices;
    std::vector<int> decreaseIndexStack;
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */
