#include "../../head.h"
 

class SolutionBFS {
public:
    int networkDelayTime(std::vector<std::vector<int>> const & times, int N, int K) {
        std::unordered_map<int, std::vector<std::pair<int, int>>> graph;
        std::vector<int> weights(N + 1, INT_MAX);
        weights[0] = 0;
        for (int index = 0; index < times.size(); index++) {
            if (3 > times[index].size()) {
                continue;
            }
            graph[times[index][0]].emplace_back(std::make_pair(times[index][1], times[index][2]));
        }

        std::queue<std::pair<int, int>> todo;
        todo.emplace(std::make_pair(K, 0));
        // std::set<int> visited;
        while (!todo.empty()) {
            int curSize = todo.size();
            while (curSize) {
                curSize--;
                int cur = todo.front().first;
                int curWeight = todo.front().second;
                // std::cout << "cur: " << cur << "\t" << "weight: " << curWeight << "\n";
                todo.pop();
                weights[cur] = std::min(weights[cur], curWeight);
                // visited.emplace(cur);
                for (auto const & neighbor : graph[cur]) {
                    int neighborWeight = curWeight + neighbor.second;
                    if (neighborWeight < weights[neighbor.first]) {
                        todo.emplace(neighbor.first, neighborWeight);

                    }
                }
            }
        }
        int ans = *std::max_element(weights.begin(), weights.end());
        return ans == INT_MAX ? -1 : ans;
    }
};

class SolutionBetterRuntime {
public:
    int networkDelayTime(std::vector<std::vector<int>> const & times, int N, int K) {
        std::vector<int> reachability(N, -1);
        std::vector<std::vector<int>> links(N, std::vector<int>(N, -1));

        for (auto& time : times) {
            links[time[0] - 1][time[1] - 1] = time[2];
        }

        std::queue<int> frontier;
        frontier.push(K - 1);
        reachability[K - 1] = 0;
        int reachable_num = 1;
        while (!frontier.empty()) {
            const int curr = frontier.front();
            frontier.pop();

            for (size_t next = 0; next < N; ++next) {
                if (next != curr && // not the same
                    links[curr][next] >= 0 && // there exists a edge
                    ( reachability[next] < 0 || // have never visited
                        reachability[next] > (reachability[curr] + links[curr][next]) // much shorted than existing path weight
                    )
                ) {
                    frontier.push(next);
                    if (reachability[next] < 0) {
                        ++reachable_num;
                    }
                    reachability[next] = reachability[curr] + links[curr][next];
                }
            }
        }

        if (reachable_num < N) {
            return -1;
        }

        int furthest = -1;
        for (auto& latency : reachability) {
            if (furthest < latency) {
                furthest = latency;
            }
        }
        return furthest;
    }
};
