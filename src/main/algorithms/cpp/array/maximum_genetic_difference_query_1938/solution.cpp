#include "../../head.h"


class Solution {
private:
    static int const CHILDREN_LEN = 2;
    static int const MAX_NUM_BITS_LEN = 17;
    enum OPS {
        REMOVE = -1,
        ADD = 1,
    };
    struct BitTrie {
        std::array<BitTrie*, CHILDREN_LEN> bitChildren = {};
        int cnts = 0;
        void addOrRemoveNode(int node, OPS op, int bitPos = MAX_NUM_BITS_LEN) {
            cnts += op;
            if (0 <= bitPos) {
                bool leftOrRight = node & (1 << bitPos);
                if (nullptr == bitChildren[leftOrRight]) {
                    bitChildren[leftOrRight] = new BitTrie();
                }
                bitChildren[leftOrRight]->addOrRemoveNode(node, op, bitPos - 1);
            }
        }

        int match(int val, int bitPos = MAX_NUM_BITS_LEN) {
            if (0 > bitPos) {
                return 0;
            }
            bool leftOrRight = val & (1 << bitPos);
            if (nullptr != bitChildren[!leftOrRight] && 0 < bitChildren[!leftOrRight]->cnts) {
                // we can go through the other side of the tree to find the max XOR value from the cur node
                return (1 << bitPos) + bitChildren[!leftOrRight]->match(val, bitPos - 1);
            }
            return (nullptr == bitChildren[leftOrRight] ? 0 : bitChildren[leftOrRight]->match(val, bitPos - 1));
        }
    };
public:
    std::vector<int> maxGeneticDifference(std::vector<int> const & parents, std::vector<std::vector<int>> & queries) {
        // plagiarizing from https://leetcode.com/problems/maximum-genetic-difference-query/discuss/1345128/Bit-Trie-with-picture
        // similar to https://leetcode.com/problems/count-pairs-with-xor-in-a-range/ 1803. Count Pairs With XOR in a Range and
        // https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/ 421. Maximum XOR of Two Numbers in an Array
        int const parentsSize = parents.size();
        int const queriesSize = queries.size();
        if (0 == parentsSize + queriesSize) {
            return std::vector<int>() = {};
        }

        int root = -1;
        std::vector<std::vector<int>> nodeChildren(parentsSize);
        for (int idx = 0; idx < parentsSize; idx++) {
            if (ROOT_VAL == parents[idx]) {
                root = idx;
            } else {
                nodeChildren[parents[idx]].emplace_back(idx);
            }
        }

        std::unordered_map<int, std::vector<std::pair<int, int>>> reshapQueries;
        for (int idx = 0; idx < queriesSize; idx++) {
            if (QUERY_SIZE > queries[idx].size()) {
                continue;
            }
            int node = queries[idx][NODE_IDX];
            int val = queries[idx][VAL_IDX];
            reshapQueries[node].emplace_back(std::make_pair(idx, val));
        }
        std::vector<int> ans(queriesSize);
        dfs(reshapQueries, nodeChildren, ans, root);
        return ans;
    }
private:
    void dfs(std::unordered_map<int, std::vector<std::pair<int, int>>> const & reshapQueries,
             std::vector<std::vector<int>> const & nodeChildren,
             std::vector<int> & ans, int node) {
        bitTrieObj.addOrRemoveNode(node, OPS::ADD);
        if (reshapQueries.find(node) != reshapQueries.end()) {
            for (auto [idx, val] : reshapQueries.at(node)) {
                ans[idx] = bitTrieObj.match(val);
            }
        }
        for (int child : nodeChildren[node]) {
            dfs(reshapQueries, nodeChildren, ans, child);
        }
        bitTrieObj.addOrRemoveNode(node, OPS::REMOVE);
    }

private:
    struct BitTrie bitTrieObj;
    static int const QUERY_SIZE = 2;
    static int const NODE_IDX = 0;
    static int const VAL_IDX = 1;
    static int const ROOT_VAL = -1;
};