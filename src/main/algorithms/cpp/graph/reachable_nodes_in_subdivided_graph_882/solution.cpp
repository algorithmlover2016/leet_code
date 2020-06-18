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

class SolutionLee215 {
public:
    int reachableNodes(std::vector<std::vector<int>> const & edges, int M, int N) {
        // plagiarizing from https://leetcode.com/problems/reachable-nodes-in-subdivided-graph/discuss/156739/C%2B%2BJavaPython-Dijkstra-%2B-Priority-Queue
        std::unordered_map<int, std::unordered_map<int, int>> e;
        for (auto v : edges) {
            e[v[0]][v[1]] = e[v[1]][v[0]] = v[2];
        }
        std::priority_queue<std::pair<int, int>> pq;
        pq.push({M, 0});
        std::unordered_map<int, int> seen;
        // 从定点开始，看在规定的步数内可以看到多少个非插入新增节点，已经看过的不再重复 BFS
        while (pq.size()) {
            int moves = pq.top().first, i = pq.top().second; pq.pop();
            if (!seen.count(i)) {
                seen[i] = moves;
                for (auto j : e[i]) {
                    int moves2 = moves - j.second - 1;
                    if (!seen.count(j.first) && moves2 >= 0)
                        pq.push({moves2, j.first});
                }
            }
        }

        int res = seen.size();
        // 在能看到的节点中，在看能否相互看中间的新增节点
        for (auto v : edges) {
            int a = seen.find(v[0]) == seen.end() ? 0 : seen[v[0]];
            int b = seen.find(v[1]) == seen.end() ? 0 : seen[v[1]];
            res += std::min(a + b, v[2]);
        }
        return res;
    }
};

class SolutionLee215Equal {
public:
    int reachableNodes(std::vector<std::vector<int>> const & edges, int M, int N) {
        // plagiarizing from https://leetcode.com/problems/reachable-nodes-in-subdivided-graph/discuss/156739/C%2B%2BJavaPython-Dijkstra-%2B-Priority-Queue
        std::unordered_map<int, std::unordered_map<int, int>> e;
        for (auto v : edges) {
            e[v[0]][v[1]] = e[v[1]][v[0]] = v[2];
        }
        std::priority_queue<std::pair<int, int>> pq;
        pq.push({M, 0});
        std::unordered_map<int, int> seen;
        int res = 0;
        while (pq.size()) {
            int moves = pq.top().first, i = pq.top().second; pq.pop();
            if (!seen.count(i)) {
                seen[i] = moves;
                res++;
                // std::cout << "iterator: " << i << "\tremindedMoves: " << moves << "\n";
                for (auto & j : e[i]) {
                    int moves2 = moves - j.second - 1;
                    int add = std::min(moves, j.second);
                    if (!seen.count(j.first) && moves2 >= 0) {
                        // std::cout << "push moves: " << moves2 << "\tindex: " << j.first << "\n";
                        pq.push({moves2, j.first});
                    }
                    e[i][j.first] -= add;
                    e[j.first][i] -= add;
                    res += add;
                    // std::cout << "res: " << res << "\tadd: " << add << "\n";
                }
            }
        }
        return res;
    }
};
