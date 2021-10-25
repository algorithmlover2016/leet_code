#include "../../head.h"

typedef std::tuple<int, int> DistIdxPair;
int const DIST_IDX = 0;
int const VERTICE_IDX = 1;

#define CLASS_CMP
#undef CLASS_CMP
#ifdef CLASS_CMP
class Cmp {
public:
    Cmp(bool needMin = false) : _needMin(needMin) {
    }

    bool operator()(DistIdxPair const & left, DistIdxPair const & right) {
        if (_needMin) {
            return std::get<DIST_IDX>(left) > std::get<DIST_IDX>(right) ||
                (std::get<DIST_IDX>(left) == std::get<DIST_IDX>(right) && std::get<VERTICE_IDX>(left) >= std::get<VERTICE_IDX>(right));
        } else {
            return std::get<DIST_IDX>(left) < std::get<DIST_IDX>(right) ||
                (std::get<DIST_IDX>(left) == std::get<DIST_IDX>(right) && std::get<VERTICE_IDX>(left) <= std::get<VERTICE_IDX>(right));
            ;
        }
    }
private:
    bool _needMin = false;
};
#endif

class Solution {
public:
    int secondMinimum(int n, std::vector<std::vector<int>> const & edges, int time, int change) {
        // plagiarizing from https://leetcode.com/problems/second-minimum-time-to-reach-destination/discuss/1525149/Python-Modified-Dijkstra-explained
        std::vector<std::vector<int>> verticesDist(n + 1);
        verticesDist[1].emplace_back(0);
        std::vector<std::vector<int>> graph(n + 1);
        // construct the bi-directional graph
        for (auto & edge : edges) {
            assert(EDGE_LEN <= edge.size());
            int first = edge[EDGE_FIRST];
            int second = edge[EDGE_SECOND];
            graph[first].emplace_back(second);
            graph[second].emplace_back(first);
        }
        #ifndef CLASS_CMP
        bool needMin = true;
        auto cmp = [&](DistIdxPair const &left, DistIdxPair const &right) {
            if (needMin) {
                return std::get<DIST_IDX>(left) > std::get<DIST_IDX>(right) ||
                    (std::get<DIST_IDX>(left) == std::get<DIST_IDX>(right) && std::get<VERTICE_IDX>(left) >= std::get<VERTICE_IDX>(right));
            } else {
                return std::get<DIST_IDX>(left) < std::get<DIST_IDX>(right) ||
                    (std::get<DIST_IDX>(left) == std::get<DIST_IDX>(right) && std::get<VERTICE_IDX>(left) <= std::get<VERTICE_IDX>(right));
                ;
            }
        };
        typedef std::priority_queue<DistIdxPair, std::vector<DistIdxPair>, decltype(cmp)> MinHeap;
        MinHeap minHeap(cmp);
        #else
        typedef std::priority_queue<DistIdxPair, std::vector<DistIdxPair>, Cmp> MinHeap;
        MinHeap minHeap(true);
        #endif

        minHeap.emplace(std::make_tuple(0, 1));
        // the first vertice need 0 time to achieve
        while (!minHeap.empty()) {
            const auto [dist, idx] = minHeap.top(); minHeap.pop();
            if (n == idx && SECOND_MIN == verticesDist[idx].size())  {
                return *(std::max_element(std::begin(verticesDist[idx]), std::end(verticesDist[idx])));
            }
            for (int next : graph[idx]) {
                int cand = 0;
                if (0 == (dist / change) % 2) {
                    // because 0 means begin. so the condition means we can through the vertice
                    cand = dist + time;
                } else {
                    // cand = ceil(dist / (2.0 * change)) * 2 * change + time;
                    cand = (dist / change + 1) * change + time;
                }
                if (verticesDist[next].empty() || (SECOND_MIN > verticesDist[next].size() && verticesDist[next].back() != cand)) {
                    verticesDist[next].emplace_back(cand);
                    minHeap.emplace(std::make_tuple(cand, next));
                }
            }
        }
        return -1;
    }
    private:
    static int const SECOND_MIN = 2;
    static int const EDGE_LEN = 2;
    static int const EDGE_FIRST = 0;
    static int const EDGE_SECOND = 1;
};

class SolutionVotrubac {
    // plagiarizing from https://leetcode.com/problems/second-minimum-time-to-reach-destination/discuss/1525154/No-Dijkstra%3A-(n-%2B-1)-or-(n-%2B-2)
private:
    int stepsTime(int steps, int time, int change) {
    int res = 0;
    while (--steps) {
        res += time;
        if ((res / change) % 2) {
            // we encounter a red traffice signal, we have to wait until the light is green
            res = (res / change + 1) * change;
        }
    }
    return res + time;
}
public:
    int secondMinimum(int n, std::vector<std::vector<int>> & edges, int time, int change) {
        std::vector<std::vector<int>> al(n + 1);
        // there are at most 1e4 points, so we want to reach any vertice twice, the most step maybe 1e4 + 2
        // if there are more than two vertices, we just need take a detour at the shortest path, so need shortest path + 1
        // if there are only two vertices, we have to go back-and-forth once for arriving at the vertice twice, so need + 2 for the shortest path
        std::vector<int> minSteps(n + 1, 10001);
        for (auto & e : edges) {
            al[e[0]].push_back(e[1]);
            al[e[1]].push_back(e[0]);
        }
        int step = -1;
        std::vector<int> q({1});
        while (!q.empty() && ++step <= minSteps[n] + 1) {
            std::vector<int> q1;
            for (int i : q) {
                if (step == minSteps[i] /*more than one shortest path can reach at the vertice i*/ ||
                    step > minSteps[i] + 1 /*reach the vertice twice only need shortest path adding one*/) {
                    continue;
                }
                minSteps[i] = std::min(minSteps[i], step);
                if (i == n && step > minSteps[n]) {
                    // we reach the n-th vertice twice, we can finish the work
                    return stepsTime(step, time, change);
                }
                for (int j : al[i]) {
                    q1.push_back(j);
                }
            }
            std::swap(q, q1);
        }
        // there are only two vertices in the graph.
        return stepsTime(minSteps[n] + 2, time, change);
    }
};