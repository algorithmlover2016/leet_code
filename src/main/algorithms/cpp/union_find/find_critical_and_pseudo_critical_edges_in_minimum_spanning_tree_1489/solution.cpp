#include "../../head.h"



class Solution {
public:
    std::vector<std::vector<int>> findCriticalAndPseudoCriticalEdges(int n,
            std::vector<std::vector<int>> & edges) {
        // plagiarizing from https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/discuss/697761/C%2B%2B-Solution-enumerating-edges-with-explanation
        // record the weight edge's index
        for (int i = 0; i < edges.size(); ++i) {
            edges[i].push_back(i);
        }

        std::sort(edges.begin(), edges.end(),
                [](std::vector<int> const & lhs, std::vector<int> const & rhs) {
                    return lhs.back() < rhs.back();
                }
                );
        int origin_mst = GetMST(n, edges, -1);
        std::vector<int> critical, non_critical;
        for (int i = 0; i < edges.size(); ++i) {
            if (origin_mst < GetMST(n, edges, i)) {
                critical.push_back(edges[i][3]);
            } else if (origin_mst == GetMST(n, edges, -1, i)) {
                non_critical.push_back(edges[i][3]);
            }
        }
        return {critical, non_critical};
    }

private:
    class UnionFind {
        public:
            UnionFind(int n) {
                rank = std::vector<int>(n, 1);
                f.resize(n);
                for (int i = 0; i < n; ++i) {
                    f[i] = i;
                }
            }

            int Find(int x) {
                int rx = x;
                while (x != f[x]) {
                    x = f[x];
                }
                return f[rx] = x;
            }

            void Union(int x, int y) {
                int fx = Find(x), fy = Find(y);
                if (fx == fy) return;
                if (rank[fx] > rank[fy]) {
                    std::swap(fx, fy);
                }
                f[fx] = fy;
                if (rank[fx] == rank[fy]) {
                    rank[fy]++;
                }
            }

        private:
            std::vector<int> f, rank;
    };
    int GetMST(int const n, std::vector<std::vector<int>> const & edges, int blockedge, int pre_edge = -1) {
        UnionFind uf(n);
        int weight = 0;
        if (pre_edge != -1) {
            weight += edges[pre_edge][2];
            uf.Union(edges[pre_edge][0], edges[pre_edge][1]);
        }
        for (int i = 0; i < edges.size(); ++i) {
            if (i == blockedge) {
                continue;
            }
            auto const & edge = edges[i];
            if (uf.Find(edge[0]) == uf.Find(edge[1])) {
                continue;
            }
            uf.Union(edge[0], edge[1]);
            weight += edge[2];
        }
        for (int i = 0; i < n; ++i) {
            if (uf.Find(i) != uf.Find(0)) {
                return INT_MAX;
            }
        }
        return weight;
    }
};

class SolutionBetterRunTime {
private:
    void prim(vector<bool> &mst, int n,
             const vector<vector<vector<int>>> &graph) {

        vector<int> dis(n, INT_MAX), pre(n, -1);
        vector<bool> vis(n, false);

        dis[0] = 0;
        for (int it = 0; it < n; it++) {
            int ma = INT_MAX, u = -1;
            for (int i = 0; i < n; i++)
                if (!vis[i] && dis[i] < ma) {
                    ma = dis[i];
                    u = i;
                }

            vis[u] = true;

            if (it > 0)
                mst[pre[u]] = true;

            for (const auto &e : graph[u]) {
                int v = e[0], w = e[1], id = e[2];
                if (dis[v] > w) {
                    dis[v] = w;
                    pre[v] = id;
                }
            }
        }
    }

    bool dfs(int u, int target, const vector<bool> &mst,
             const vector<vector<vector<int>>> &graph,
             vector<int> &pre) {

        if (u == target)
            return true;

        for (const auto &e : graph[u]) {
            int v = e[0], w = e[1], id = e[2];
            if (mst[id] && pre[v] == -1) {
                pre[v] = id;
                if (dfs(v, target, mst, graph, pre))
                    return true;
            }
        }

        return false;
    }

public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(
        int n,
        vector<vector<int>>& edges
    ) {
        #define PSEUDO      1
        #define CRITICAL    2
        int m = edges.size();
        vector<vector<vector<int>>> graph(n);

        for (int i = 0; i < m; i++) {
            int x = edges[i][0], y = edges[i][1], w = edges[i][2];
            graph[x].push_back({y, w, i});
            graph[y].push_back({x, w, i});
        }

        vector<bool> mst(m, false);

        prim(mst, n, graph);

        vector<int> res(m, 0);
        for (int i = 0; i < m; i++)
            if (mst[i])
                res[i] = CRITICAL;

        for (int i = 0; i < m; i++)
            if (!mst[i]) {
                int x = edges[i][0], y = edges[i][1], w = edges[i][2];
                vector<int> pre(n, -1);

                assert(dfs(x, y, mst, graph, pre) == true);

                int u = y;
                while (u != x) {
                    int nid = pre[u];

                    if (edges[nid][2] == w) {
                        res[nid] = PSEUDO;
                        res[i] = PSEUDO;
                    }

                    if (edges[nid][0] == u) u = edges[nid][1];
                    else u = edges[nid][0];
                }
            }

        vector<vector<int>> ans(2);

        for (int i = 0; i < m; i++)
            if (res[i] == CRITICAL) ans[0].push_back(i);
            else if (res[i] == PSEUDO) ans[1].push_back(i);

        return ans;
    }
};
