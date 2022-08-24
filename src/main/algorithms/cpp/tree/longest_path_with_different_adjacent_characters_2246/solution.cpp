#include "../../head.h"


class SolutionDFS {
public:
    int longestPath(std::vector<int> const & parent, std::string const & s) {
        // plagiarizing from https://leetcode.com/problems/longest-path-with-different-adjacent-characters/discuss/1955433/JavaC%2B%2BPython-DFS-on-Tree
        int nodeSize = parent.size();
        if (0 == nodeSize) {
            return 0;
        }
        std::vector<std::vector<int>> p2c(nodeSize);
        for (int idx = 1 /* the parent of 0 is -1, which is no need to save */; idx < parent.size(); idx++) {
            p2c[parent[idx]].emplace_back(idx);
        }
        int ans = 0;
        dfs(p2c, s, 0, ans);
        return ans;
    }
    int dfs(std::vector<std::vector<int>> const & p2c, std::string const & s, int node, int & ans) {
        int biggest = 0, secBiggest = 0;
        for (int child : p2c[node]) {
            int cur = dfs(p2c, s, child, ans);
            if (s[child] == s[node]) {
                continue;
            }
            // we get a path that parent is not same to his child in one path
            // we get the two biggest path
            if (cur > secBiggest) {
                secBiggest = cur;
            }
            if (secBiggest > biggest) {
                std::swap(biggest, secBiggest);
            }
        }
        ans = std::max(ans, biggest + secBiggest + 1);
        return biggest + 1;
    }
};

class Solution {
public:
    int longestPath(std::vector<int> const & parent, std::string const & s) {
        int nodeSize = parent.size();
        if (0 == nodeSize) {
            return 0;
        }
        std::vector<int> indegree(nodeSize, 0);
        for (int idx = 1; idx < parent.size(); idx++) {
            ++indegree[parent[idx]];
        }
        std::queue<int> leafNodes;
        for (int idx = 1; idx < indegree.size(); idx++) {
            if (0 == indegree[idx]) {
                leafNodes.emplace(idx);
            }
        }
        std::vector<int> top1(nodeSize, 1)/*top1 save the largest subpath */, top2(nodeSize, 1) /*top2 save the second largest subpath*/;
        int ans = 1;
        while (!leafNodes.empty()) {
            int cur = leafNodes.front();
            if (0 == cur /*root node*/ ) {
                break;
            }
            int p = parent[cur];
            leafNodes.pop();
            int length = 1 + (s[cur] != s[p] ? top1[cur] : 0);
            if (length > top1[p]) {
                top2[p] = top1[p];
                top1[p] = length;
            } else {
                top2[p] = std::max(top2[p], length);
            }
            if (0 == --indegree[p]) {
                leafNodes.emplace(p);
                ans = std::max(ans, top1[p] + top2[p] - 1);
            }
        }
        return ans;

    }
};