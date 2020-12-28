#include "../../head.h"


#define DEBUG
class SolutionWrongAnswer {
public:
    int eatenApples(std::vector<int> const & apples, std::vector<int> const & days) {
        // if I arrive at ith, I already have 10 apples with ten days, but at ith, apples[i] = 1, and days[i] = 11;
        // I will not compute the ith apple. So, it's wrong
        if (apples.empty() || days.empty()) {
            return 0;
        }
        int const applesSize = apples.size();
        int const daysSize = days.size();
        if (applesSize != daysSize) {
            return 0;
        }
        // std::vector<uint8_t> reach(applesSize, 0);
        int eatedApple = 0;
        int mostReach = -1;

        for (int idx = 0; idx < applesSize; idx++) {
            int idxMostReach = std::min(apples[idx], days[idx]) + idx;
            #ifdef DEBUG
            std::cout << "idx: " << idx << "\tidxMostReach: " << idxMostReach << "\t";
            #endif
            if (idxMostReach > idx) {
                if (idx > mostReach) {
                    mostReach = idx;
                }
                if (mostReach < idxMostReach) {
                    #ifdef DEBUG
                    std::cout << "eat apple: " << idxMostReach - mostReach << "\t";
                    #endif
                    eatedApple += idxMostReach - mostReach;
                    mostReach = idxMostReach;
                }

            }
            #ifdef DEBUG
            std::cout << "\n";
            #endif

        }
        // return std::accumulate(reach.begin(), reach.end(), 0);
        return eatedApple;


    }
};

// #define DEBUG
class Solution {
private:
    // to construct min_heap with function
    static bool pairCompMinFunc(std::pair<int, int> const & left, std::pair<int, int> const & right) {
        if (left.first < right.first) {
            return true;
        }

        if (left.first > right.first) {
            return false;
        }

        if (left.second > right.second) {
            return false;
        }
        return true;
    }

    // to construct max_heap with object
    class PairCompMaxObj {
    public:
        PairCompMaxObj(bool init = true):_greater(init){
        }
        bool operator()(std::pair<int, int> const & left, std::pair<int, int> const & right) {
            if (left.first > right.first) {
                return _greater;
            }

            if (left.first < right.first) {
                return !_greater;
            }

            if (left.second < right.second) {
                return !_greater;
            }
            return _greater;
        }
    private:
        bool _greater;
    };

    typedef std::priority_queue<std::pair<int, int>,
                                std::vector<std::pair<int, int>>,
                                PairCompMaxObj> MinPairHeap;

    // typedef std::priority_queue<std::pair<int, int>> MinPairHeap; // it return the max element, so if you want to construct a minHeap, you should reverse the comp object

    int eatApple(MinPairHeap &  minHeap, int idx) {
        int eatedApp = 0;
        while ((!minHeap.empty()) && minHeap.top().first <= idx) {
            minHeap.pop();
        }
        if (!minHeap.empty()) {
            auto it = minHeap.top();
            std::pair<int, int> update = std::make_pair(it.first, it.second);
            #ifdef DEBUG
            std::cout << "eat: " << it.first << "\t" << it.second << "\n";
            #endif
            minHeap.pop();
            eatedApp++;
            update.second--;
            if (update.second > 0) {
                minHeap.emplace(update);
            }
        }
        return eatedApp;
    }


    public:
    int eatenApples(std::vector<int> const & apples, std::vector<int> const & days) {
        // plagiarizing from https://www.youtube.com/watch?v=1vRYTJqaZ8s
        if (apples.empty() || days.empty()) {
            return 0;
        }
        int const applesSize = apples.size();
        int const daysSize = days.size();
        if (applesSize != daysSize) {
            return 0;
        }

        MinPairHeap minHeap(PairCompMaxObj(true));

        int idx = 0;
        int ans = 0;
        for (; idx < applesSize; idx++) {
            if (0 < apples[idx] && 0 < days[idx]) {
                minHeap.emplace(idx + days[idx], apples[idx]);
            }
            ans += eatApple(minHeap, idx);
        }
        #ifdef DEBUG
        std::cout << "traversal apples, eated apple: " << ans << "\n";
        #endif
        while (!minHeap.empty()) {
            ans += eatApple(minHeap, idx++);
        }

        return ans;
    }
};
