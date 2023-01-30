#include "../../head.h"


// #define DEBUG
class SolutionTLE {
public:
    int numberOfGoodPaths(std::vector<int> const & vals, std::vector<std::vector<int>> const & edges) {
        int const nodes = vals.size();
        int ans = 0;
        std::vector<std::vector<int>> graph(nodes);
        for (auto & edge : edges) {
            if (edge.size() < EDGE_LEN) {
                continue;
            }
            graph[edge[FIDX]].emplace_back(edge[SIDX]);
            graph[edge[SIDX]].emplace_back(edge[FIDX]);
        }
        #ifdef DEBUG
        std::cout << "construction graph done\n";
        #endif
        std::function<void(int const, int, std::vector<bool>)> dfs = [&](int const val, int cur, std::vector<bool> visited) {
            visited[cur] = true;
            for (int nextNode : graph[cur]) {
                if (vals[nextNode] > val || visited[nextNode]) {
                    continue;
                } else if (vals[nextNode] == val) {
                    ans += 1;
                    #ifdef DEBUG
                    std::cout << "cur idx: " << nextNode << ", ans: " << ans << "\n";
                    #endif
                }
                #ifdef DEBUG
                std::cout << "next node: " << nextNode << ",\t";
                #endif
                dfs(val, nextNode, visited);
            }
        };
        for (int idx = 0; idx < nodes; idx++) {
            std::vector<bool> visited(nodes, false);
            #ifdef DEBUG
            std::cout << "get idx: " << idx << "\n";
            #endif
            dfs(vals[idx], idx, visited);
        }
        return ans / 2 + nodes;
    }
private:
    static int const EDGE_LEN = 2;
    static int const FIDX = 0;
    static int const SIDX = 1;
};

// #define DEBUG
class Solution {
public:
    int numberOfGoodPaths(std::vector<int> const & vals, std::vector<std::vector<int>> const & edges) {
        // plagiarizing from https://leetcode.com/problems/number-of-good-paths/solutions/2648155/union-find/
        int const nodesSize = vals.size();
        std::vector<std::vector<int>> graph(nodesSize);
        for (auto & edge : edges) {
            if (edge.size() < EDGE_LEN) {
                continue;
            }
            // to make sure the directed graph will be smaller node as leaf
            if (vals[edge[FIDX]] < vals[edge[SIDX]]) {
                graph[edge[SIDX]].emplace_back(edge[FIDX]);
            } else {
                graph[edge[FIDX]].emplace_back(edge[SIDX]);
            }
        }
        // cnts represents how many at current connected group with current index value.
        std::vector<int> ids(nodesSize), cnts(nodesSize, 0);
        std::iota(std::begin(ids), std::end(ids), 0);
        std::sort(std::begin(ids), std::end(ids), [&](int idL, int idR) {return vals[idL] < vals[idR];});
        #ifdef DEBUG
        for_each(std::begin(ids), std::end(ids),[](int id) {std::cout << id << ",\t";});
        std::cout << '\n';
        #endif
        std::vector<int> parents(nodesSize, INIT_UF);
        int left = 0;
        for (int idx = 0; idx < nodesSize && vals[ids[left]] < vals[ids.back()]; idx++) {
            while (vals[ids[left]] != vals[ids[idx]]) {
                // we can compute the number of nodes with same val only after we pass this val
                ++cnts[find(ids[left++], parents)];
            }
            for (int smallerNode : graph[ids[idx]]) {
                parents[find(smallerNode, parents)] = find(ids[idx], parents);
            }
        }
        /*
        at current time, val[ids[left]] must be equal to val.back(). Then the total number of whose val is val.back() is (nodesSize - left) = NMax;
        Because the zone must be connected, so the good path is C(NMax, 2) + NMax = NMax * (NMax + 1)
        */
        return std::accumulate(std::begin(cnts), std::end(cnts), (nodesSize - left) * (nodesSize - left + 1) / 2, [](int sum, int cnt) {return sum + cnt * (cnt + 1) / 2;});
    }
private:
    int find(int const idx, std::vector<int> & parents) {
        #ifdef DEBUG
        std::cout << "idx: " << idx << ",p: " << parents[idx] << "\n";
        #endif
        return parents[idx] == INIT_UF ? idx : parents[idx] = find(parents[idx], parents);
    }

private:
    static int const EDGE_LEN = 2;
    static int const FIDX = 0;
    static int const SIDX = 1;
    static int const INIT_UF = -1;
};
int const Solution::INIT_UF;