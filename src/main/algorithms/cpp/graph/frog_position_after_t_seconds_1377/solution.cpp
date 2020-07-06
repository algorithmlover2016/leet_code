#include "../../head.h"


class SolutionWrongAnswer {
public:
    double frogPosition(int n, std::vector<std::vector<int>> const & edges, int t, int const target) {
        std::vector<std::vector<int>> graph(n + 1);
        for (std::vector<int> const & edge : edges) {
            if (2 > edge.size()) {
                continue;
            }
            graph[edge[0]].emplace_back(edge[1]);
            graph[edge[1]].emplace_back(edge[0]);
        }

        int const START = 1;
        if (START == target) {
            return 1;
        }

        std::vector<bool> visited(n + 1, false);
        std::queue<std::pair<int, double>> todo;

        todo.emplace(std::make_pair(START, 1));
        visited[1] = true;

        int layerSize = 0;
        while ((layerSize = todo.size()) && t--) {
            for (; layerSize > 0; layerSize--) {
                auto const & cur = todo.front();
                int vertice = cur.first;
                double probability = cur.second;
                todo.pop();

                double nextLayerPro = 0;
                for (int const connectedVertice : graph[vertice]) {
                    if (!visited[connectedVertice]) {
                        nextLayerPro++;
                    }
                }

                if (nextLayerPro > 0) {
                    nextLayerPro = probability * 1.0 / nextLayerPro;
                }

                for (int nextVertice : graph[vertice]) {
                    if (target == nextVertice) {
                        return t == 0 ? nextLayerPro : 0;
                    }
                    if (!visited[nextVertice]) {
                        visited[nextVertice] = true;
                        todo.emplace(std::make_pair(nextVertice, nextLayerPro));
                    }
                }
            }

        }
        return 0;
    }
};

class SolutionBFS {
public:
    double frogPosition(int n, std::vector<std::vector<int>> const & edges, int t, int const target) {
        // reference to https://leetcode.com/problems/frog-position-after-t-seconds/discuss/532505/Java-Straightforward-BFS-Clean-code-O(N)
        std::vector<std::vector<int>> graph(n + 1);
        for (std::vector<int> const & edge : edges) {
            if (2 > edge.size()) {
                continue;
            }
            graph[edge[0]].emplace_back(edge[1]);
            graph[edge[1]].emplace_back(edge[0]);
        }

        int const START = 1;

        std::vector<bool> visited(n + 1, false);
        std::queue<int> todo;
        std::vector<double> probabilites(n + 1, 0);

        todo.emplace(START);
        visited[START] = true;
        probabilites[START] = 1;

        int layerSize = 0;
        while ((layerSize = todo.size()) && t--) {
            for (; layerSize > 0; layerSize--) {
                int vertice = todo.front();
                todo.pop();

                double nextLayerPro = 0;
                for (int const connectedVertice : graph[vertice]) {
                    if (!visited[connectedVertice]) {
                        nextLayerPro++;
                    }
                }

                if (nextLayerPro > 0) {
                    nextLayerPro = probabilites[vertice] / nextLayerPro;
                    // std::cout << "vertice: " << vertice << "nextPro: " << nextLayerPro << "\n";
                    probabilites[vertice] = 0;
                    // optional begin
                    if (target == vertice) {
                        return 0;
                    }
                    // optional begin
                }

                for (int nextVertice : graph[vertice]) {
                    if (!visited[nextVertice]) {
                        visited[nextVertice] = true;
                        todo.emplace(nextVertice);
                        probabilites[nextVertice] = nextLayerPro;
                    }
                }
            }

        }
        return probabilites[target];
    }
};

class SolutionDFS {
private:
    std::vector<std::vector<int> > G;
    std::vector<bool> seen;
    int target;

public:
    double frogPosition(int n, std::vector<std::vector<int>> const & edges, int t, int const target) {
        if (n == 1) return 1.0;
        this->target = target;
        G = std::vector<std::vector<int>>(n + 1);
        for (auto e : edges) {
            G[e[0]].push_back(e[1]);
            G[e[1]].push_back(e[0]);
        }
        seen = std::vector<bool>(n + 1, false);
        return dfs(1, t);
    }

private:
    double dfs(int i, int t) {
        // if (i != 1 && (G[i].size() == 1 || t == 0)) {
        if (i != 1 && G[i].size() == 1 || t == 0) {
            return i == target;
        }

        seen[i] = true;
        double res = 0;
        // int nextCnt = 0;
        for (auto j : G[i]) {
            if (!seen[j]) {
                res += dfs(j, t - 1);
                // nextCnt++;
            }
        }
        return res / (G[i].size() - (i != 1)); // because all vertices need to minus one, except the start one
        // return res / nextCnt; // because all vertices need to minus one, except the start one
    }
};
