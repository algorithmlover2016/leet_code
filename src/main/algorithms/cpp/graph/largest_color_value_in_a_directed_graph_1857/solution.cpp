#include "../../head.h"

// #define DEBUG
#define ADD_WHEN_CNT
class Solution {
public:
    int largestPathValue(std::string const & colors, std::vector<std::vector<int>> const & edges) {
        // plagiarizing from https://leetcode.com/problems/largest-color-value-in-a-directed-graph/discuss/1198658/C%2B%2B-Topological-Sort
        // and https://leetcode.com/problems/largest-color-value-in-a-directed-graph/discuss/1200575/Topological-Sort-vs.-DFS-vs.-Dijkstra
        // Topological sort
        int nodesCnt = colors.size();
        // std::vector<std::array<int, LOWERCASE_CNT>> curNodesColorsCnt(nodesCnt, std::array<int, LOWERCASE_CNT>({{0}}));
        std::vector<std::array<int, LOWERCASE_CNT>> curNodesColorsCnt(nodesCnt);

        std::vector<int> nodesIndegrees(nodesCnt);
        // std::vector<std::vector<int>> directedGraph(nodesCnt, std::vector<int>());
        std::vector<std::vector<int>> directedGraph(nodesCnt);
        for (auto const & edge : edges) {
            if (edge.size() < EDGE_LEN) {
                continue;
            }
            directedGraph[edge[EDGE_START_IDX]].emplace_back(edge[EDGE_END_IDX]);
            // record the parents num for the cur node (edge[EDGE_END_IDX])
            nodesIndegrees[edge[EDGE_END_IDX]]++;
        }
        #ifdef DEBUG
            std::cout << "contruct the graph\n";
        #endif
        std::queue<int> zeroIndegreeNodes;
        for (int idx = 0; idx < nodesCnt; idx++) {
            if (0 == nodesIndegrees[idx]) {
                zeroIndegreeNodes.emplace(idx);
                #ifndef ADD_WHEN_CNT
                    curNodesColorsCnt[idx][colors[idx] - offset] = 1;
                #endif
            }
        }
        #ifdef DEBUG
            std::cout << "find all the start nodes\n";
        #endif
        int ans = 0, visited = 0;
        while (!zeroIndegreeNodes.empty()) {
            int curNode = zeroIndegreeNodes.front(); zeroIndegreeNodes.pop();
            // int curNodeMaxColor = * std::max_element(std::begin(curNodesColorsCnt[curNode]), std::end(curNodesColorsCnt[curNode]));
            #ifdef ADD_WHEN_CNT
            int curNodeMaxColor = ++curNodesColorsCnt[curNode][colors[curNode] - offset];
            #else
            int curNodeMaxColor = curNodesColorsCnt[curNode][colors[curNode] - offset];
            #endif
            ans = std::max(ans, curNodeMaxColor);
            visited++;
            // now we need visit its downstream nodes
            for (int const next : directedGraph[curNode]) {
                if (0 == --nodesIndegrees[next]) {
                    zeroIndegreeNodes.emplace(next);
                }
                for (int idx = 0; idx < LOWERCASE_CNT; idx++) {
                    #ifdef ADD_WHEN_CNT
                        curNodesColorsCnt[next][idx] = std::max(curNodesColorsCnt[next][idx], curNodesColorsCnt[curNode][idx]);
                    #else
                        curNodesColorsCnt[next][idx] = std::max(curNodesColorsCnt[next][idx], curNodesColorsCnt[curNode][idx] + (idx == (colors[next] - offset)));
                    #endif
                }
            }
        }
        return (visited == nodesCnt) ? ans : -1 /*there is a circle*/;
    }
private:
    static int const LOWERCASE_CNT = 26;
    static int const EDGE_LEN = 2;
    static int const EDGE_START_IDX = 0;
    static int const EDGE_END_IDX = 1;
    static char const offset = 'a';
};