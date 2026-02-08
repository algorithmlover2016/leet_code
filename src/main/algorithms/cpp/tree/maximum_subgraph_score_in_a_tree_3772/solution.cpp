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

class Solution2dp {
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



class Solution {
private:
    static const int N = 1e5;
    int pa[N], deg[N], q[N];
public:
    vector<int> maxSubgraphScore(int n, vector<vector<int>>& es, vector<int>& dp) {
        memset(pa, 0, sizeof(int) * n), memset(deg, 0, sizeof(int) * n);

        // Prevent root from entering queue too early.
        // Can be any non-negative int != 1 (0, 2, 3...). If 1, node 0 becomes a leaf pointing to itself.
        // setting it to 1 would cause node 0 to be incorrectly treated as a leaf and point to itself as its parent, leading to calculation errors.
        // if setting to 0, then node 0 would be treated as a leaf and removed first, which is also correct but less intuitive.
        // if setting to 2, 3, 4, ..., node 0 won't be treated as a leaf initially, which is treated as root forever.
        deg[0] = 2;
        for (auto& e : es) {
            int a = e[0], b = e[1];
            deg[a]++, deg[b]++;
            pa[a] ^= b, pa[b] ^= a;
        }
        for (int i = 0; i < n; ++i) dp[i] = (dp[i] << 1) - 1; // Map 0 -> -1, 1 -> 1

        int qi = 0;
        for (int s = 0; s < n; ++s) {
            // Use XOR property to dynamically remove child and point to grand-parent in the loop update
            for (int i = s, p; deg[i] == 1; pa[p] ^= i, --deg[p], i = p) {
                q[qi++] = i;
                deg[i] = 0;
                p = pa[i];
                if (dp[i] > 0) dp[p] += dp[i];
            }
        }

        while (qi--) {
            int i = q[qi];
            // Add parent contribution (excluding self impact)
            dp[i] += max(0, dp[pa[i]] - max(0, dp[i]));
        }
        return dp;
    }
};