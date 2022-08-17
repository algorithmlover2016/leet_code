#include "../../head.h"


// #define DEBUG
#define DFS_NO_RECURSIVE
class Solution {
public:
    int closestMeetingNode(std::vector<int> const & edges, int node1, int node2) {
        // refer to https://leetcode.com/problems/longest-cycle-in-a-graph/discuss/2357750/Simple-DFS-Traversal-or-Easy-Explanation-or-C%2B%2B
        int vertexesSize = edges.size();
        int ans = -1;
        if (0 == vertexesSize) {
            return ans;
        }
        std::vector<int> node1Dist(vertexesSize, -1);
        std::vector<int> node2Dist(vertexesSize, -1);
        #ifdef DFS_NO_RECURSIVE
        dfsNonrecursive(edges, node1, 0, node1Dist);
        dfsNonrecursive(edges, node2, 0, node2Dist);
        #else
        dfs(edges, node1, 0, node1Dist);
        dfs(edges, node2, 0, node2Dist);
        #endif
        int res = INT_MAX;
        #ifdef DEBUG
        for (int idx = 0; idx < vertexesSize; idx++) {
            std::cout << "(" << idx << ", " << node1Dist[idx] << ")\t(" << idx << ", " << node2Dist[idx] << ")\n";
        }
        #endif
        for (int idx = 0; idx < vertexesSize; idx++) {
            if ((std::min(node1Dist[idx], node2Dist[idx]) >= 0) && (std::max(node1Dist[idx], node2Dist[idx]) < res)) {
                res = std::max(node1Dist[idx], node2Dist[idx]);
                ans = idx;
            }
        }
        return ans;
    }
private:
    void dfs(std::vector<int> const & edges, int node, int dist, std::vector<int> & nodeDist) {
        if (END_POINT == node) {
            return;
        }
        if (INIT_DIST == nodeDist[node]) {
            nodeDist[node] = dist++;
            dfs(edges, edges[node], dist, nodeDist);
        } else {
            // we encounter a circle and we no need to traverse
            return;
        }
    }
    void dfsNonrecursive(std::vector<int> const & edges, int node, int dist, std::vector<int> & nodeDist) {
        while (END_POINT != node /* Traverse the graph to the end */ && INIT_DIST == nodeDist[node] /* Encounter a circle */) {
            nodeDist[node] = dist++;
            #ifdef DEBUG
            std::cout << "node: " << node << ", ";
            #endif
            node = edges[node];
        }
        #ifdef DEBUG
        std::cout << "\n";
        #endif
    }
private:
    static int const END_POINT = -1;
    int const INIT_DIST = -1;
};