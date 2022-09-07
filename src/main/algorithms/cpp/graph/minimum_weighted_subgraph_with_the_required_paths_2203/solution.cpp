#include "../../head.h"


class SolutionTLE {
public:
    long long minimumWeight(int n, std::vector<std::vector<int>> const & edges, int src1, int src2, int dest) {
        // plagiarizing from https://leetcode.com/problems/minimum-weighted-subgraph-with-the-required-paths/discuss/1844091/C%2B%2B-Dijkstra-3-times-with-illustration
        std::unordered_map<int, std::vector<std::pair<int, int>>> directedGraph, rDirectedGraph;
        for (auto & edge : edges) {
            if (edge.size() < EDGE_SIZE) {
                continue;
            }
            directedGraph[edge[S_IDX]].emplace_back(std::make_pair(edge[E_IDX], edge[W_IDX]));
            rDirectedGraph[edge[E_IDX]].emplace_back(std::make_pair(edge[S_IDX], edge[W_IDX]));
        }
        std::vector<long long> src1Dist(n, INIT_LONG_MAX), src2Dist(n, INIT_LONG_MAX), destDist(n, INIT_LONG_MAX);
        typedef std::pair<long long, long long> L_PAIR;
        auto bfsDijkstra = [&](int src, std::vector<long long> & dists, std::unordered_map<int, std::vector<std::pair<int, int>>> & graph) {
            std::priority_queue<L_PAIR, std::vector<L_PAIR>, std::greater<L_PAIR>> minQue;
            dists[src] = 0;
            minQue.emplace(std::make_pair(0, src));
            while (!minQue.empty()) {
                auto [dist, curNode] = minQue.top(); minQue.pop();
                for (auto [nextNode, w] : graph[curNode]) {
                    if (dist + w > dists[nextNode]) {
                        continue;
                    }
                    dists[nextNode] = dist + w;
                    minQue.emplace(std::make_pair(dist + w, nextNode));
                }
            }
        };
        bfsDijkstra(src1, src1Dist, directedGraph);
        bfsDijkstra(src2, src2Dist, directedGraph);
        bfsDijkstra(dest, destDist, rDirectedGraph);
        long long ans = INIT_LONG_MAX;
        for (int idx = 0; idx < n; idx++) {
            if (INIT_LONG_MAX == src1Dist[idx] || INIT_LONG_MAX == src2Dist[idx] || INIT_LONG_MAX == destDist[idx]) {
                continue;
            }
            ans = std::min(ans, src1Dist[idx] + src2Dist[idx] + destDist[idx]);
        }
        return ans == INIT_LONG_MAX ? -1 : ans;
    }

private:
    static int const EDGE_SIZE = 3;
    static int const S_IDX = 0;
    static int const E_IDX = 1;
    static int const W_IDX = 2;
    long long const INIT_LONG_MAX = LONG_MAX;
};