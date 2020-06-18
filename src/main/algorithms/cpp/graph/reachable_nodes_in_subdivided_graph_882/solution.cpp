#include "../../head.h"


class Solution {
private:
    int const ELE_LEN = 3;
    int const ROW = 0;
    int const COL = 1;
    int const VAL = 2;

public:
    int reachableNodes(std::vector<std::vector<int>> const & edges, int M, int N) {
        // plagiarizing from https://leetcode.com/problems/reachable-nodes-in-subdivided-graph/discuss/156777/Java-Dijkstra-Solution
        std::vector<bool> visited(N, false);
        std::vector<std::vector<int>> graph(N, std::vector<int>(N, -1));
        for (auto const & subVec : edges) {
            if (subVec.size() < ELE_LEN) {
                continue;
            }
            graph[subVec[ROW]][subVec[COL]] = subVec[VAL];
            graph[subVec[COL]][subVec[ROW]] = graph[subVec[ROW]][subVec[COL]];
        }
        int res = 0;
        std::priority_queue<std::pair<int, int>> moveIndexTodo;
        moveIndexTodo.emplace(std::make_pair(M, 0));
        while (moveIndexTodo.size()) {
            std::pair<int, int> const & curPair = moveIndexTodo.top();
            int target = curPair.first;
            int curIndex = curPair.second;
            moveIndexTodo.pop();
            if (visited[curIndex]) {
                continue;
            }
            // std::cout << "target: " << target << "\tcurIndex: " << curIndex << "\n";
            visited[curIndex] = true;
            res++;

            for (int index = 0; index < N; index++) {
                if (-1 == graph[curIndex][index]) {
                    continue;
                }
                // can go on
                int add = target;
                if (target > graph[curIndex][index]) {
                    add = graph[curIndex][index];
                    moveIndexTodo.emplace(std::make_pair(target - add - 1, index));
                }
                graph[index][curIndex] -= add;
                // graph[curIndex][index] = graph[index][curIndex]; // there will never visit curIndex, index
                res += add;
            }
        }
        return res;
    }

};

class SolutionBetterRuntime {
public:
    int reachableNodes(std::vector<std::vector<int>> const & edges, int M, int N) {
        std::vector<long long> distance(N, INT_MAX);
        distance[0] = 0;
        // non negative cyclic graph; by relaxing find the shortest path from 0 to any node
        for (int loop = 0; loop < N; loop++) {
            bool relaxed = false;
            for (auto & e : edges) {
                if (distance[e[0]] + e[2] + 1 < distance[e[1]]) {
                    distance[e[1]] = distance[e[0]] + e[2] + 1;
                    relaxed = true;
                }
                if (distance[e[1]] + e[2] + 1 < distance[e[0]]) {
                    distance[e[0]] = distance[e[1]] + e[2] + 1;
                    relaxed = true;
                }
            }
            if (!relaxed) {
                break;
            }
        }

        int count = 0;
        // if shortest path < M, then the node will be counted
        for (int i = 0; i < N; i++) {
            if (distance[i] <= M) {
                count++;
            }
        }

        // the inserted node should also be added
        for (auto & e : edges) {
            long long left = max(0LL, M - distance[e[0]]);
            long long right = max(0LL, M - distance[e[1]]);
            long long total = min((long long)e[2], left+right);

            count += total;
        }
        return count;
    }
};
