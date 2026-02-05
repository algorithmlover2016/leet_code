#include "../../head.h"


class Solution_TLE {
private:
    const int EDGE_SIZE = 2;
    const int U_IDX = 0;
    const int V_IDX = 1;
public:
    vector<int> maxSubgraphScore(int n, vector<vector<int>>& edges, vector<int>& good) {
        std::vector<std::vector<int>> graph(n);
        for (auto & edge : edges) {
            if (edge.size() < EDGE_SIZE) {
                continue;
            }
            int u = edge[U_IDX];
            int v = edge[V_IDX];
            graph[u].emplace_back(v);
            graph[v].emplace_back(u);
        }
        std::vector<int> ans(n, 0);
        for (int idx = 0; idx < n; idx++) {
            ans[idx] = helper(graph, idx, -1, good);
        }
        return ans;
    }
private:
    int helper(std::vector<std::vector<int>> const & graph, int u, int p, std::vector<int> const & good) {
        int val = good[u] > 0 ? 1 : -1;
        for (int v : graph[u]) {
            if (v == p) {
                continue;
            }
            int nextVal = helper(graph, v, u, good);
            if (nextVal > 0) {
                val += nextVal;
            }
        }
        return val;
    }
};

class Solution {
public:
    vector<int> maxSubgraphScore(int n, vector<vector<int>>& edges, vector<int>& good) {
        std::vector<std::vector<int>> graph(n);
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        std::vector<int> dp(n);
        // Pass 1: Bottom-up DP (assuming root 0)
        dfs1(0, -1, graph, good, dp);

        std::vector<int> ans(n);
        ans[0] = dp[0];

        // Pass 2: Top-down Re-rooting
        dfs2(0, -1, graph, dp, ans);

        return ans;
    }

private:
    void dfs1(int u, int p, const std::vector<std::vector<int>>& graph, const vector<int>& good, std::vector<int>& dp) {
        dp[u] = good[u] > 0 ? 1 : -1;
        for (int v : graph[u]) {
            if (v == p) continue;
            dfs1(v, u, graph, good, dp);
            if (dp[v] > 0) {
                dp[u] += dp[v];
            }
        }
    }

    void dfs2(int u, int p, const std::vector<std::vector<int>>& graph, const std::vector<int>& dp, std::vector<int>& ans) {
        for (int v : graph[u]) {
            if (v == p) continue;

            // When moving root from u to v:
            // The score consists of:
            // 1. The original subtree logic for v (dp[v])
            // 2. The contribution from the 'u' side (which is now a child of v)
            
            // Calculate 'u' branch score excluding 'v'
            int u_score = ans[u];
            int v_contribution = (dp[v] > 0 ? dp[v] : 0);
            int u_without_v = u_score - v_contribution;

            // Compute ans[v]
            ans[v] = dp[v];
            if (u_without_v > 0) {
                ans[v] += u_without_v;
            }

            dfs2(v, u, graph, dp, ans);
        }
    }
};
// https://leetcode.com/problems/maximum-subgraph-score-in-a-tree/solutions/7396921/python-3-c-optimized-iterative-bottom-up-eat7/