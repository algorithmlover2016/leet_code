#include "../../head.h"



class SolutionDFS {
public:
    int longestCycle(std::vector<int> const & edges) {
        // plagiarizing from https://leetcode.com/problems/longest-cycle-in-a-graph/discuss/2357750/Simple-DFS-Traversal-or-Easy-Explanation-or-C%2B%2B
        int ans = -1;
        if (edges.empty()) {
            return ans;
        }
        int vertexesSize = edges.size();
        std::vector<bool> visited(vertexesSize, false);
        for (int vertex = 0; vertex < vertexesSize; vertex++ ) {
            if (visited[vertex]) {
                continue;
            }
            std::vector<int> traversalVertexes;
            dfs(edges, vertex, visited, traversalVertexes, ans);
        }
        return ans;
    }
private:
    void dfs(std::vector<int> const & edges,
                int vertex,
                std::vector<bool> & visited,
                std::vector<int> & traversalVertexes,
                int & ans) {
        if (END_POINT == vertex) {
            return;
        }
        if (visited[vertex]) {
            int cnt = INIT_NO_MEET;
            int tarversalVertexesSize = traversalVertexes.size();
            for (int idx = 0; idx < tarversalVertexesSize; idx++) {
                if (traversalVertexes[idx] == vertex) {
                    cnt = idx;
                    break; // we find the idx of vertex where we first encounter it.
                }
            }
            if (INIT_NO_MEET == cnt /*vertex is encountered on the previous tarversal*/) {
                return;
            }
            ans = std::max(ans, tarversalVertexesSize - cnt);
            return;
        }
        visited[vertex] = true;
        traversalVertexes.emplace_back(vertex);
        dfs(edges, edges[vertex], visited, traversalVertexes, ans);
    }
private:
    static int const END_POINT = -1;
    static int const INIT_NO_MEET = -1;
};

class Solution {
public:
    int longestCycle(std::vector<int> const & edges) {
        // plagiarizing from https://leetcode.com/problems/longest-cycle-in-a-graph/discuss/2357750/Simple-DFS-Traversal-or-Easy-Explanation-or-C%2B%2B
        int ans = -1;
        int vertexesSize = edges.size();
        if (0 == vertexesSize) {
            return ans;
        }
        std::vector<std::pair<int, int>> visited(vertexesSize, {INIT_VAL, INIT_VAL});
        for (int vertex = 0; vertex < vertexesSize; vertex++ ) {
            // tarverse the edge following the edge starting from vertex
            for (int next = vertex, dist = 0; next != END_POINT; next = edges[next]) {
                auto [distance, from_vertex] = visited[next];
                if (INIT_VAL == distance) {
                    // we encounter the next from the vertex with dist steps;
                    visited[next] = std::make_pair(dist++, vertex);
                } else {
                    // we encounter another vertex which is visited before
                    if (from_vertex == vertex) {
                        ans = std::max(ans, dist - distance);
                    }
                    // no matter it is visited by teh cur vertex, only if it is visited,
                    // we can be out of the break because each vertex can only point to one next vertex.
                    break;
                }
            }
        }
        return ans;
    }
private:
    static int const END_POINT = -1;
    int const INIT_VAL = -1;
};