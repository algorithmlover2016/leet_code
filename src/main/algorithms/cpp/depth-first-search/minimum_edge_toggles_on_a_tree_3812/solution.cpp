#include "../../head.h"


class Solution {
public:
    std::vector<int> minimumFlips(int n, std::vector<std::vector<int>>& edges, std::string start, std::string target) {
        std::vector<std::vector<std::pair<int, int>>> graph(n);
        for (int index =0 ; index < edges.size(); index++) {
            int u = edges[index][0];
            int v = edges[index][1];
            graph[u].emplace_back(std::make_pair(v, index));
            graph[v].emplace_back(std::make_pair(u, index));
        }
        std::vector<int> s(n, 0);
        for (int i = 0; i < n; i++) {
            s[i] = start[i] - '0';
        }
        std::vector<int> t(n, 0);
        for (int i = 0; i < n; i++) {
            t[i] = target[i] - '0';
        }

        std::vector<int> res;


        dfs(graph, 0, 0, s, t, res, -1);
        if (s[0] != t[0]) {
            return {-1};
        }
        std::sort(res.begin(), res.end());  
        return res;
    }
private:
    void dfs(std::vector<std::vector<std::pair<int, int>>>& graph,
             int u, int parent,
             std::vector<int>& s,
             std::vector<int>& t,
             std::vector<int>& res,
             int edgeIndex) {
        for (const auto& neighbor : graph[u]) {
            int v = neighbor.first;
            int eIndex = neighbor.second;
            if (v == parent) {
                continue;
            }
            dfs(graph, v, u, s, t, res, eIndex);
        }
        if (edgeIndex != -1 && s[u] != t[u]) {
            res.push_back(edgeIndex);
            s[u] ^= 1;
            s[parent] ^= 1;
        }
    }
};