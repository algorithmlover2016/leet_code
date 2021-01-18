#include "../../head.h"


class Solution {
public:
    std::vector<int> sumOfDistancesInTree(int N, std::vector<std::vector<int>> const & edges) {
    // copy from https://leetcode.com/problems/sum-of-distances-in-tree/discuss/130583/C++JavaPython-Pre-order-and-Post-order-DFS-O(N)
    // not my idea
        std::vector<int> res(N, 0);
        if (N < 2) {
            return res;
        }
        std::vector<std::vector<int> > tree(N, std::vector<int>(0));
        for(int index = 0; index < edges.size(); index++) {
            if (edges[index].size() != 2) {
                continue;
            }
            if (edges[index][0] >= N || edges[index][0] < 0 ||
                    edges[index][1] >= N || edges[index][1] < 0) {
                continue;
            }
            tree[edges[index][0]].push_back(edges[index][1]);
            tree[edges[index][1]].push_back(edges[index][0]);
        }

#ifdef DEBUG
        for(int index = 0; index < tree.size(); index++) {
            std::cout << index << "\t";
            for(int subIndex = 0; subIndex < tree[index].size(); subIndex++) {
                std::cout << tree[index][subIndex] << "\t";
            }
            std::cout << std::endl;
        }
#endif

        std::vector<bool> visitTree(N, false);
        std::vector<bool> visitTree2(N, false);

        std::vector<int> cntNodes(N, 0);
        std::vector<int> cntEdges(N, 0);
        dfsIterator(tree, 0, cntNodes, cntEdges, visitTree);
        res[0] = cntEdges[0];
        dfsIterator2(tree, 0, cntNodes, visitTree2, res, N);

        return res;
    }

    void dfsIterator(std::vector<vector<int> > const & tree, int start,
            std::vector<int> & cntNodes, std::vector<int> & cntEdges,
            std::vector<bool> & visitTree) {
        visitTree[start] = true;
        for (int index = 0; index < tree[start].size(); index++) {
            if (!visitTree[tree[start][index]]) {
                dfsIterator(tree, tree[start][index], cntNodes, cntEdges, visitTree);
                cntNodes[start] += cntNodes[tree[start][index]];
                cntEdges[start] += cntEdges[tree[start][index]] + cntNodes[tree[start][index]];
            }
        }
        cntNodes[start] += 1;
        return;
    }
    void dfsIterator2(std::vector<std::vector<int>> const & tree, int start,
            std::vector<int> const & cntNodes,
            std::vector<bool> & visitTree2, std::vector<int> & res, int N) {
        visitTree2[start] = true;
        for (int index = 0; index < tree[start].size(); index++) {
            if (!visitTree2[tree[start][index]]) {
                // res[start] - cntNodes[tree[start][index]] means the substree of tree[start][index] and
                // the tree[start] without the root tree[start][index]
                // N - cntNodes[tree[start][index]] means the other tree[start] substree should add one to
                // reach the cur root.
                res[tree[start][index]] = res[start] - cntNodes[tree[start][index]] + N - cntNodes[tree[start][index]];
                dfsIterator2(tree, tree[start][index], cntNodes, visitTree2, res, N);
            }
        }
    }
};
