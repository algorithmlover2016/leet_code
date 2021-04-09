#include "../../head.h"


// #define DEBUG
class Solution {
protected:
    class UnionFind {
    public:
        UnionFind(int n) : nodes(n) {
            parents.resize(n + 1, 0);
            std::iota(parents.begin(), parents.end(), 0);

            cnts.resize(n + 1, 0);
            ranks.resize(n + 1, 0);
        }
        int find(int idx) {
            int oriIdx = idx;
            while (idx != parents[idx]) {
               idx = parents[idx];
            }
            return parents[oriIdx] = idx;
        }
        bool unionWithRank(int left, int right) {
            int leftRoot = find(left);
            int rightRoot = find(right);
            if (leftRoot == rightRoot) {
                // there is no need to union
                return false;
            }
            if (ranks[leftRoot] == ranks[rightRoot]) {
                ranks[rightRoot]++;
            } else if (ranks[leftRoot] > ranks[rightRoot]) {
                std::swap(leftRoot, rightRoot);
            }
            parents[leftRoot] = rightRoot;
            cnts[rightRoot] += cnts[leftRoot];
            nodes--; // we connect two nodes
            #ifdef DEBUG
            std::cout << nodes << ", ";
            #endif
            return true;
        }
        bool united() {
            return 1 == nodes;
        }
    private:
        std::vector<int> parents;
        std::vector<int> cnts;
        std::vector<int> ranks;
        int nodes = 0;
    };

public:
    int maxNumEdgesToRemove(int n, std::vector<std::vector<int>> edges) {
        // plagiarizing from https://leetcode.com/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable/discuss/831506/C%2B%2B-Java-Textbook-Union-Find-Data-Structure-Code-with-Explanation-and-comments
        // and https://leetcode.com/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable/discuss/831573/Python-Union-Find
        // and https://leetcode.com/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable/discuss/831536/C%2B%2B-Union-Find-BothOne
        std::sort(edges.begin(), edges.end(),
                [] (std::vector<int> const & left, std::vector<int> const & right) {
                assert(EDGE_SIZE <= left.size());
                assert(EDGE_SIZE <= right.size());
                // first use tyep 3 as edge
                return left[TYPE_IDX] > right[TYPE_IDX];
                });

        UnionFind bobs(n), alice(n);
        int addEdges = 0;
        for (auto const & edge : edges) {
            assert(EDGE_SIZE <= edge.size());
            int type = edge[TYPE_IDX];
            int firstNode = edge[FIRST_IDX];
            int secondNode = edge[SECOND_IDX];
            switch (type) {
                case 3:
                    addEdges += (bobs.unionWithRank(firstNode, secondNode) | alice.unionWithRank(firstNode, secondNode));
                    break;
                case 2:
                    addEdges += bobs.unionWithRank(firstNode, secondNode);
                    break;
                case 1:
                    addEdges += alice.unionWithRank(firstNode, secondNode);
                    break;
                default:
                    break;
            }
            #ifdef DEBUG
            std::cout << addEdges << "\t";
            #endif
        }
        return (bobs.united() && alice.united()) ? (edges.size() - addEdges) : -1;
    }
private:
    static int const EDGE_SIZE = 3;
    static int const TYPE_IDX = 0;
    static int const FIRST_IDX = 1;
    static int const SECOND_IDX = 2;
};
