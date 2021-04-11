#include "../../head.h"


class Solution {
public:
    std::vector<bool> checkIfPrerequisite(int n,
            std::vector<std::vector<int>> const & prerequisites,
            std::vector<std::vector<int>> const & queries) {
        // plagiarizing from https://leetcode.com/problems/course-schedule-iv/discuss/660509/JavaPython-FloydWarshall-Algorithm-Clean-code-O(n3)
        // and https://leetcode.com/problems/course-schedule-iv/discuss/660578/Transitive-closure-Floyd-Warshall-with-detailed-explaination-python-c%2B%2B-java
        // reference to https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm and https://youtu.be/oNI0rf2P9gE
        std::vector<std::vector<int>> floydWarshallMatrix(n, std::vector<int>(n, INIT_MAX));
        for (int idx = 0; idx < n; idx++) {
            floydWarshallMatrix[idx][idx] = 0;
        }
        for (auto const & prerequisite : prerequisites) {
            if (PREREQUISITE_SIZE > prerequisite.size()) {
                continue;
            }
            // the weight is set to 1, which means there is a path that connects from prerequisite[PREREQUISITE_SECOND]
            // to prerequisite[PREREQUISITE_FIRST]
            floydWarshallMatrix[prerequisite[PREREQUISITE_FIRST]][prerequisite[PREREQUISITE_SECOND]] = 1;
        }
        shortestPathWithVertexes(floydWarshallMatrix);
        int const queriesSize = queries.size();
        std::vector<bool> ans(queriesSize, false);
        for (int idx = 0 ; idx < queriesSize; idx++) {
            auto const & query = queries[idx];
            ans[idx] = (floydWarshallMatrix[query[PREREQUISITE_FIRST]][query[PREREQUISITE_SECOND]] < INIT_MAX);
        }
        return ans;
    }
private:
    void shortestPathWithVertexes(std::vector<std::vector<int>> & floydWarshallMatrix) {
        int const floydWarshallMatrixSize = floydWarshallMatrix.size();
        for (int k = 0; k < floydWarshallMatrixSize; k++) {
            for (int to = 0; to < floydWarshallMatrixSize; to++) {
                for (int from = 0; from < floydWarshallMatrixSize; from++) {
                    floydWarshallMatrix[to][from] = std::min(floydWarshallMatrix[to][from],
                            floydWarshallMatrix[to][k] + floydWarshallMatrix[k][from]);
                }
            }
        }
    }

private:
    int const INIT_MAX = (INT_MAX >> 2); // the two vertex can't be reached
    static int const PREREQUISITE_SIZE = 2;
    static int const PREREQUISITE_FIRST = 0;
    static int const PREREQUISITE_SECOND = 1;
};


class Solution {
public:
    std::vector<bool> checkIfPrerequisite(int n,
            std::vector<std::vector<int>> const & prerequisites,
            std::vector<std::vector<int>> const & queries) {
        // plagiarizing from https://leetcode.com/problems/course-schedule-iv/discuss/660725/C%2B%2B-or-DFS-or-Memoization
        std::vector<std::vector<int>> directedGraph(n);
        std::vector<std::vector<int>> dpMemo(n, std::vector<int>(n, INIT_FLAG));
        for (auto const & prerequisite : prerequisites) {
            directedGraph[prerequisite[PREREQUISITE_SECOND]].emplace_back(prerequisite[PREREQUISITE_FIRST]);
            dpMemo[prerequisite[PREREQUISITE_SECOND]][prerequisite[PREREQUISITE_FIRST]] = 1;
        }
        int const queriesSize = queries.size();
        std::vector<bool> ans(queriesSize, false);
        for (int idx = 0; idx < queriesSize; idx++) {
            auto const & query = queries[idx];
            ans[idx] = (1 == dfs(directedGraph, query[PREREQUISITE_SECOND], query[PREREQUISITE_FIRST], dpMemo));
        }
        return ans;
    }

    int dfs(std::vector<std::vector<int>> const & directedGraph, int from, int const to,
            std::vector<std::vector<int>> & dpMemo) {
        if (from == to) {
            return dpMemo[from][to] = 1;
        }
        if (INIT_FLAG != dpMemo[from][to]) {
            return dpMemo[from][to];
        }
        for (auto const next : directedGraph[from]) {
            if ((to == next) || dfs(directedGraph, next, to, dpMemo)) {
                return dpMemo[from][to] = 1;
            }
        }
        return dpMemo[from][to] = 0;
    }

private:
    int const INIT_FLAG = -1; // the two vertex can't be reached
    static int const PREREQUISITE_SIZE = 2;
    static int const PREREQUISITE_FIRST = 0;
    static int const PREREQUISITE_SECOND = 1;
};

class Solution {
public:
    std::vector<bool> checkIfPrerequisite(int n,
            std::vector<std::vector<int>> const & prerequisites,
            std::vector<std::vector<int>> const & queries) {
        std::vector<std::vector<int>> adj(n);
        for (auto & p : prerequisites) {
            adj[p[1]].push_back(p[0]);
        }
        std::vector<std::vector<bool>> pre(n, std::vector<bool>(n));
        std::vector<bool> visited(n);
        for (int i = 0; i < n; i++) {
            std::fill(visited.begin(), visited.end(), false);
            dfs(i, i, adj, pre, visited);
        }
        std::vector<bool> res;
        res.reserve(queries.size());
        for (auto & q : queries) {
            res.push_back(pre[q[1]][q[0]]);
        }
        return res;
    }

private:
    void dfs(int p, int v,
            std::vector<std::vector<int>> const & adj,
            std::vector<std::vector<bool>> & pre,
            std::vector<bool> & visited) {
        if (visited[v]) {
            return;
        }
        visited[v] = true;
        pre[p][v] = true;
        for (int w : adj[v]) {
            dfs(p, w, adj, pre, visited);
        }
    }
};
