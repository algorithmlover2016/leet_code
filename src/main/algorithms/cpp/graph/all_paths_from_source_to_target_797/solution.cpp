#include "../../head.h"


class Solution {
public:
    std::vector<std::vector<int>> allPathsSourceTarget(std::vector<std::vector<int>> const & graph) {
        std::vector<std::vector<int>> res;
        int rowSize = graph.size();
        if (0 == rowSize) {
            return {{}};
        }
        int colSize = graph[0].size();
        if (0 == colSize) {
            return {{}};
        }
        // std::cout << "row: " << rowSize << "\tcolSize: " << colSize << "\n";
        std::vector<int> dfsAns;
        dfs(graph, rowSize - 1, 0, dfsAns, res);
        return res;
    }
    void dfs(std::vector<std::vector<int>> const & graph,
            int target, int start,
            std::vector<int> & dfsAns,
            std::vector<std::vector<int>> & res) {
        // std::cout << "deal start: " << start << "\t";
        dfsAns.emplace_back(start);
        if (start == target) {
            res.emplace_back(dfsAns);
        }
        for (int linkedEle : graph[start]) {
            // std::cout << linkedEle << "\n";
            dfs(graph, target, linkedEle, dfsAns, res);
        }
        dfsAns.pop_back();
    }
};

class Solution {
private:
    void allPathsSourceTarget(std::vector<std::vector<int>> const & graph,
            int idx, std::vector<std::vector<int>> & ret, std::vector<int> & cur) {
        if (idx == graph.size() - 1) {
            ret.push_back(cur);
            return;
        }
        for (auto v: graph[idx]) {
            cur.push_back(v);
            allPathsSourceTarget(graph, v, ret, cur);
            cur.pop_back();
        }
    }

public:
    std::vector<std::vector<int>> allPathsSourceTarget(std::vector<std::vector<int>> const & graph) {
        std::vector<std::vector<int>> ret;
        std::vector<int> tmp(1, 0);
        allPathsSourceTarget(graph, 0, ret, tmp);
        return ret;
    }
};
