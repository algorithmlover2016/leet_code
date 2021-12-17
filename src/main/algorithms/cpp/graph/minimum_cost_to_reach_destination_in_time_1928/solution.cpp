#include "../../head.h"


// #define DEBUG
class SolutionTLE {
public:
    typedef std::tuple<int /*costFee*/, int /*costTime*/, int /*curCity*/, int /*preCity*/, int /*the number of visited cities */> ElementType;
    int minCost(int maxTime, std::vector<std::vector<int>> const & edges, std::vector<int> const & passingFees) {
        int const citiesNum = passingFees.size();
        if (0 == citiesNum) {
            return 0;
        }
        std::vector<std::vector<int>> graphs(citiesNum, std::vector<int>(citiesNum, GRAPH_INIT_VAL));
        for (auto const & edge : edges) {
            if (EDGE_SIZE > edge.size()) {
                continue;
            }
            // because there is a mention that "The graph may contain multiple edges between two nodes."
            /*
            graphs[edge[FIRST_IDX]][edge[SECOND_IDX]] = edge[TIME_CODE_IDX];
            graphs[edge[SECOND_IDX]][edge[FIRST_IDX]] = edge[TIME_CODE_IDX];
            */

            int val = std::min(edge[TIME_CODE_IDX], graphs[edge[FIRST_IDX]][edge[SECOND_IDX]]);
            graphs[edge[FIRST_IDX]][edge[SECOND_IDX]] = val;
            graphs[edge[SECOND_IDX]][edge[FIRST_IDX]] = val;
        }
        auto cmp = [&](ElementType const & left, ElementType const & right) {
            return std::get<COST_FEE_IDX>(left) >= std::get<COST_FEE_IDX>(right);
        };

        typedef std::priority_queue<ElementType, std::vector<ElementType>, decltype(cmp)> MinQue;
        MinQue minQue(cmp);
        minQue.emplace(std::make_tuple(passingFees[0], 0, 0, 0, 1));

        // bfs
        while (!minQue.empty()) {
            auto [passFee, costTime, curCity, preCity, visitedCitiesNum] = minQue.top();
            #ifdef DEBUG
            std::cout << "curFee: " << passFee << ", costTime: " << costTime << ", curCity: " << curCity << ", preCity: " << preCity << "\n";
            #endif
            minQue.pop();
            if (costTime > maxTime) {
                continue;
            }
            if (citiesNum * MAX_VISITED_CITIES_NUM < visitedCitiesNum) {
                return GRAPH_INIT_VAL;
            }

            if (curCity == citiesNum - 1) {
                return passFee;
            }
            for (int nextCity = 0; nextCity < citiesNum; nextCity++) {
                if (GRAPH_INIT_VAL != graphs[curCity][nextCity] && nextCity != preCity) {
                    minQue.emplace(std::make_tuple(passFee + passingFees[nextCity], costTime + graphs[curCity][nextCity], nextCity, curCity, visitedCitiesNum + 1));
                }
            }
        }
        return -1;
    }
private:
    int const GRAPH_INIT_VAL = 2000;
    static int const EDGE_SIZE = 3;
    static int const FIRST_IDX = 0;
    static int const SECOND_IDX = 1;
    static int const TIME_CODE_IDX = 2;
    static int const COST_FEE_IDX = 0;
    static int const MAX_VISITED_CITIES_NUM = 3;
};

// #define DEBUG
class SolutionTLE {
    // TLE at https://leetcode.com/submissions/detail/603058850/
public:
    typedef std::tuple<int /*costFee*/, int /*costTime*/, int /*curCity*/, int /*preCity*/, int /*the number of visited cities */> ElementType;
    int minCost(int maxTime, std::vector<std::vector<int>> const & edges, std::vector<int> const & passingFees) {
        int const citiesNum = passingFees.size();
        if (0 == citiesNum) {
            return 0;
        }
        std::vector<std::vector<std::pair<int, int>>> graphs(citiesNum);
        for (auto const & edge : edges) {
            if (EDGE_SIZE > edge.size()) {
                continue;
            }
            graphs[edge[FIRST_IDX]].emplace_back(std::make_pair(edge[SECOND_IDX], edge[TIME_CODE_IDX]));
            graphs[edge[SECOND_IDX]].emplace_back(std::make_pair(edge[FIRST_IDX], edge[TIME_CODE_IDX]));
        }
        auto cmp = [&](ElementType const & left, ElementType const & right) {
            return std::get<COST_FEE_IDX>(left) >= std::get<COST_FEE_IDX>(right);
        };

        typedef std::priority_queue<ElementType, std::vector<ElementType>, decltype(cmp)> MinQue;
        MinQue minQue(cmp);
        minQue.emplace(std::make_tuple(passingFees[0], 0, 0, 0, 1));

        // bfs
        while (!minQue.empty()) {
            auto [passFee, costTime, curCity, preCity, visitedCitiesNum] = minQue.top();
            #ifdef DEBUG
            std::cout << "curFee: " << passFee << ", costTime: " << costTime << ", curCity: " << curCity << ", preCity: " << preCity << "\n";
            #endif
            minQue.pop();
            if (citiesNum < visitedCitiesNum) {
                continue;
            }

            if (curCity == citiesNum - 1) {
                return passFee;
            }
            for (auto [nextCity, nextCostTime] : graphs[curCity]) {
                if (costTime + nextCostTime <= maxTime && nextCity != preCity) {
                    minQue.emplace(std::make_tuple(passFee + passingFees[nextCity], costTime + nextCostTime, nextCity, curCity, visitedCitiesNum + 1));
                }
            }
        }
        return -1;
    }
private:
    static int const EDGE_SIZE = 3;
    static int const FIRST_IDX = 0;
    static int const SECOND_IDX = 1;
    static int const TIME_CODE_IDX = 2;
    static int const COST_FEE_IDX = 0;
};

// #define DEBUG
// #define DEBUG
class Solution {
public:
    typedef std::tuple<int /*costFee*/, int /*costTime*/, int /*curCity*/> ElementType;
    typedef std::pair<int /*fee cost*/, int /*time cost*/> FeeTimeCost;
    int minCost(int maxTime, std::vector<std::vector<int>> const & edges, std::vector<int> const & passingFees) {
        // plagiarizing from https://leetcode.com/problems/minimum-cost-to-reach-destination-in-time/discuss/1329036/Modified-Dijkstra's
        int const citiesNum = passingFees.size();
        if (0 == citiesNum) {
            return 0;
        }
        std::vector<std::vector<std::pair<int, int>>> graphs(citiesNum);
        for (auto const & edge : edges) {
            if (EDGE_SIZE > edge.size()) {
                continue;
            }
            graphs[edge[FIRST_IDX]].emplace_back(std::make_pair(edge[SECOND_IDX], edge[TIME_CODE_IDX]));
            graphs[edge[SECOND_IDX]].emplace_back(std::make_pair(edge[FIRST_IDX], edge[TIME_CODE_IDX]));
        }
        auto cmp = [&](ElementType const & left, ElementType const & right) {
            return std::get<COST_FEE_IDX>(left) >= std::get<COST_FEE_IDX>(right);
        };

        typedef std::priority_queue<ElementType, std::vector<ElementType>, decltype(cmp)> MinQue;
        MinQue minQue(cmp);
        minQue.emplace(std::make_tuple(passingFees[0], 0, 0));

        std::vector<std::set<FeeTimeCost>> citiesStates(citiesNum);
        // bfs
        while (!minQue.empty()) {
            auto [passFee, costTime, curCity] = minQue.top();
            #ifdef DEBUG
            std::cout << "curFee: " << passFee << ", costTime: " << costTime << ", curCity: " << curCity << ", preCity: " << preCity << "\n";
            #endif
            minQue.pop();

            if (curCity == citiesNum - 1) {
                return passFee;
            }
            for (auto [nextCity, nextCostTime] : graphs[curCity]) {
                int nextTotalTime = costTime + nextCostTime;
                if (nextTotalTime <= maxTime) {
                    auto nextState = std::make_pair(passFee + passingFees[nextCity], nextTotalTime);
                    auto it = citiesStates[nextCity].upper_bound(nextState);
                    if (it == citiesStates[nextCity].begin() || (std::prev(it)->second > nextTotalTime)) {
                        citiesStates[nextCity].insert(nextState);
                        minQue.emplace(std::make_tuple(nextState.first, nextState.second, nextCity));
                    }
                }
            }
        }
        return -1;
    }
private:
    static int const EDGE_SIZE = 3;
    static int const FIRST_IDX = 0;
    static int const SECOND_IDX = 1;
    static int const TIME_CODE_IDX = 2;
    static int const COST_FEE_IDX = 0;
};