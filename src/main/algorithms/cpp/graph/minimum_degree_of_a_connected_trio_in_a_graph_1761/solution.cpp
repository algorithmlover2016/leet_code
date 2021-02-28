#include "../../head.h"


// #define AVOID_TLE
class Solution {
public:
    int minTrioDegree(int n, std::vector<std::vector<int>> const & edges) {
        // plagiarizing from https://youtu.be/F_rmpodwBBQ
        std::vector<std::unordered_set<int>> graph(n + 1);
        #ifdef AVOID_TLE
        std::vector<int> indegree(n + 1);
        #endif
        for (auto const & edge : edges) {
            if (EDGE_LEN > edge.size()) {
                continue;
            }
            #ifndef AVOID_TLE
            graph[edge[FIRST]].insert(edge[SECOND]);
            graph[edge[SECOND]].insert(edge[FIRST]);
            #else
            int minNode = edge[FIRST];
            int largeNode = edge[SECOND];
            if (minNode > largeNode) {
                std::swap(minNode, largeNode);
            }
            graph[minNode].insert(largeNode);
            indegree[minNode]++;
            indegree[largeNode]++;
            #endif
        }
        #ifndef AVOID_TLE
        size_t ans = INT_MAX;
        #else
        int ans = INT_MAX;
        #endif
        for (int node = 1; node <= n; node++) {
            for (int const n1 : graph[node]) {
                for (int const n2 : graph[node]) {
                    if (graph[n1].find(n2) != graph[n1].end()) {
                        #ifndef AVOID_TLE
                        ans = std::min(ans, graph[node].size() + graph[n1].size() + graph[n2].size() - 6);
                        #else
                        ans = std::min(ans, indegree[node] + indegree[n1] + indegree[n2] - 6);
                        #endif

                    }
                }
            }
        }
        return ans == INT_MAX ? -1 : ans;
    }
private:
    static int const EDGE_LEN = 2;
    static int const FIRST = 0;
    static int const SECOND = 1;
};

// #define DEBUGGG
namespace {
#ifdef DEBUGGG
#define LOG(x) cout << (x) << endl << flush
#define PL(l) { cout << "["; for (auto &e : l) cout << e << ','; cout << "]" << endl; }
#else
#define LOG(x)
#define PL(l)
#endif
static auto _speedupMagic = [] { ios::sync_with_stdio(false); cin.tie(nullptr); return 0; }();
}

class Solution {
public:
    int minTrioDegree(int n, vector<vector<int>>& edges) {
        memset (am, 0, sizeof am);
        memset (cnt, 0, sizeof cnt);
        for (auto e: edges) {
            int u = e[0], v = e[1];
            am[u][v] = am[v][u] = 1;
            cnt[u]++; cnt[v]++;
        }
        int ret = INT_MAX;
        for (int i = 1; i <=n-2 ; ++i) {
            for (int j = i + 1; j <= n -1; ++j) {
                for (int k = j + 1; k <=n; ++k) {
                    if ( am[i][j] && am[j][k] && am[i][k] ){
                        // 3 * 2 = 6 edges
                        ret = min(ret, cnt[i] + cnt[j] + cnt[k] - 6);
                    }
                }
            }
        }
        return ret == INT_MAX ? -1 : ret;
    }
private:
    int am[401][401];//adjacency matrix
    int cnt[401];
};

class Solution {
    public:
        int minTrioDegree(int n, std::vector<std::vector<int>> const & edges) {
            std::vector<std::vector<bool>> con(n + 1, std::vector<bool>(n + 1, false));
            std::vector<std::vector<int>> gra(n + 1);
            int ans = INT_MAX;
            for (auto & ed : edges) {
                con[ed[0]][ed[1]] = con[ed[1]][ed[0]] = true;
                gra[ed[0]].push_back(ed[1]);
                gra[ed[1]].push_back(ed[0]);
            }
            std::vector<int> vs;
            for (int v = 1; v <= n; ++v)
                if (gra[v].size() >= 2) {
                    vs.push_back(v);
                }
            auto cmp = [&](int a, int b) {
                return gra[a].size() < gra[b].size();
            };
            std::sort(vs.begin(), vs.end(), cmp);
            for (int x : vs) {
                auto &yz = gra[x];
                int dx = yz.size();
                if (dx < 2) continue;
                if (dx >= ans - 4) break;
                std::sort(yz.begin(), yz.end(), cmp);
                for (int i = 0; i < dx - 1; ++i) {
                    int dy = gra[yz[i]].size();
                    if (dx + dy + gra[yz[i+1]].size() >= ans) break;
                    for (int j = i + 1; j < dx; ++j) {
                        int deg = dx + dy + gra[yz[j]].size();
                        if (deg >= ans) break;
                        if (con[yz[i]][yz[j]]) {
                            ans = deg;
                        }
                    }
                }
            }
            return ans == INT_MAX ? -1 : ans - 6;
        }
};

