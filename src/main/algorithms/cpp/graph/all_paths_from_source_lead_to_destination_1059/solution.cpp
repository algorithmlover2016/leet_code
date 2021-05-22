#include "../../head.h"


#define TEST_MAIN
// #define USING_HASH_MAP_AND_SET
class Solution {
public:
    bool leadsToDestination(int n, std::vector<std::vector<int>> const & edges, int source, int destination) {
        // plagiarizing from https://www.fatalerrors.org/a/leetcode-1059-all-paths-from-source-lead-to-destination.html
        // and https://xingxingpark.com/Leetcode-1059-All-Paths-from-Source-Lead-to-Destination/
        // and https://youtu.be/ZlfXhtq_EFE
#ifdef USING_HASH_MAP_AND_SET
        std::unordered_map<int, std::vector<int>> graph;
        std::unordered_set<int> visited;
#else
        std::vector<std::vector<int>> graph(n);
        std::vector<bool> visited(n, false);
#endif
        for (auto const & edge : edges) {
            if (EDGE_LEN > edge.size()) {
                continue;
            }
            int startNode = edge[0];
            int endNode = edge[1];
            graph[startNode].emplace_back(endNode);
        }
        return helper(graph, visited, source, destination);
    }
private:
#ifdef USING_HASH_MAP_AND_SET
    bool helper(std::unordered_map<int, std::vector<int>> const & graph, std::unordered_set<int> & visited, int cur, int dest) {
        // only when we arrive at the last node, we can make the judgement
        if (graph.find(cur) == graph.end()) {
            return cur == dest;
        }
        visited.emplace(cur);
        for (int const nextNode : graph.at(cur)) {
            if (visited.find(nextNode) != visited.end() /*we encounter a circle*/ ||
                !helper(graph, visited, nextNode, dest)) {
                return false;
            }
        }
        //there is a necessary operation that
        visited.erase(cur);
        return true;
    }
#else
    bool helper(std::vector<std::vector<int>> const & graph, std::vector<bool> & visited, int cur, int dest) {
        // only when we arrive at the last node, we can make the judgement
        // cur will never overpass or equal to graph.size(), which means cur < graph.size()
        if (graph[cur].empty()) {
            return cur == dest;
        }
        visited[cur] = true;
        for (int const nextNode : graph.at(cur)) {
            if (visited[nextNode] /*we encounter a circle*/ ||
                !helper(graph, visited, nextNode, dest)) {
                return false;
            }
        }
        //there is a necessary operation that
        visited[cur] = false;
        return true;
    }
#endif
private:
    static int const EDGE_LEN = 2;
};

#ifdef TEST_MAIN
#define PRINT_TO_SCREEN
int main() {
    Solution obj;
    std::vector<std::vector<int>> edges{{{0, 1},{0, 3}, {1, 2}, {2,1}}};
    bool ans = obj.leadsToDestination(4, edges, 0, 3);

#ifdef PRINT_TO_SCREEN
    std::cout << "first ans: " << ans << "\n";
#endif
    assert(ans == false);

    std::vector<std::vector<int>> edges1{{{0, 1}, {0, 2}, {1, 3}, {2,3}}};
    ans = obj.leadsToDestination(4, edges1, 0, 3);
#ifdef PRINT_TO_SCREEN
    std::cout << "second ans: " << ans << "\n";
#endif
    assert(ans == true);


    std::cout << "TEST SUCCESSFULLY" << std::endl;
    return 0;
}
#endif
