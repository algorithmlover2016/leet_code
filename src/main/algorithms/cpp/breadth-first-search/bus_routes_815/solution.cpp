#include "../../head.h"


class Solution {
public:
    int numBusesToDestination(std::vector<std::vector<int>> & routes, int S, int T) {
        // plagiarizing from https://leetcode.com/problems/bus-routes/discuss/122771/C%2B%2BJavaPython-BFS-Solution
        int rowSize = routes.size();
        if (0 == rowSize) {
            return S == T ? 0 : -1;
        }
        if (S == T) {
            return 0;
        }
        std::unordered_map<int, std::vector<int>> graph;
        for (int index = 0; index < routes.size(); index++) {
            for (int ele : routes[index]) {
                graph[ele].emplace_back(index);
            }
        }
        std::queue<std::pair<int, int>> todo;
        std::set<int> visited;
        todo.emplace(std::make_pair(S, 1));
        visited.emplace(S);
        do {
            auto const & cur= todo.front();
            int curStop = cur.first;
            int usedBus = cur.second;
            todo.pop();
            // std::cout << "\n";
            for (int index : graph[curStop]) {
                for (int stop : routes[index]) {
                    // std::cout << "next: " << stop << "\t";
                    if (stop == T) {
                        return usedBus;
                    }
                    if (visited.find(stop) == visited.end()) {
                        // std::cout << "add : " << stop << "\t";
                        visited.emplace(stop);
                        todo.emplace(std::make_pair(stop, usedBus + 1));
                    }
                }
                // for reducing the runtime
                // we have iterator routes[index], no need to iterator again
                routes[index].clear();
            }
        } while (todo.size());
        return -1;

    }
};
