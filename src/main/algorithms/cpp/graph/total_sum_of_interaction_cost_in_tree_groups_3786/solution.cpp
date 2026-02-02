#include "../../head.h"



class Solution {
public:
    long long interactionCosts(int n, vector<vector<int>>& edges, vector<int>& group) {
        const int MAX_GROUP_CNT = *std::max_element(group.begin(), group.end()) + 1;
        long long int ans = 0;
        std::vector<std::vector<int>> graph(n);
        for (const auto &edge : edges) {
            graph[edge[0]].emplace_back(edge[1]);
            graph[edge[1]].emplace_back(edge[0]);
        }
        std::vector<int> sumGroupCount(MAX_GROUP_CNT, 0);
        for (int i = 0; i < n; i++) {
            sumGroupCount[group[i]]++;
        }
        std::vector<std::vector<int>> nodesCount(n, std::vector<int>(MAX_GROUP_CNT, 0));
        dfs(0, -1, graph, group, sumGroupCount, nodesCount, ans);
        return ans;
    }
private:
    void dfs(int node, int parent,
                         std::vector<std::vector<int>> &graph,
                         std::vector<int> &group,
                         std::vector<int> &sumGroupCount,
                         std::vector<std::vector<int>> &nodesCount,
                         long long int &ans) {
        nodesCount[node][group[node]] = 1;
        for (const auto &child : graph[node]) {
            if (child == parent) {
                continue;
            }
            dfs(child, node, graph, group, sumGroupCount, nodesCount, ans);
            for (int g = 0; g < sumGroupCount.size(); g++) {
                ans += (long long)nodesCount[child][g] * (sumGroupCount[g] - nodesCount[child][g]);
                nodesCount[node][g] += nodesCount[child][g];
            }
        }
    }
};