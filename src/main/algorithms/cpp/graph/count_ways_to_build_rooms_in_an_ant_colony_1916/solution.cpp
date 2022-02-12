#include "../../head.h"



class Solution {
public:
    int waysToBuildRooms(std::vector<int> const & prevRoom) {
        // plagiarizing from https://leetcode.com/problems/count-ways-to-build-rooms-in-an-ant-colony/discuss/1300085/n!-(cnt_0-*-cnt_1-*-..-*-cnt_n-1)
        // I will add my comments for the code.
        if (prevRoom.empty()) {
            return 1;
        }
        int const prevRoomSize = prevRoom.size();
        long long fact = 1, prod = 1;
        std::vector<std::vector<int>> treeNodes(prevRoomSize);
        for (int idx = 1; idx < prevRoomSize; idx++) {
            assert(prevRoom[idx] < prevRoomSize);
            treeNodes[prevRoom[idx]].emplace_back(idx);
            // If there are no constrants, there are n! posibilities for n different elements
            // n is equal to prevRoomSize here
            fact = fact * (idx + 1) % MOD;
        }
        return fact * modPow(dfsFindNodes(treeNodes, 0, prod, MOD), MOD - 2, MOD) % MOD;


    }
private:
    int modPow(int x, int exp, int mod = MOD) {
        if (0 == exp) {
            // x^0 = 1 for every x
            return 1;
        }
        // first we need the formula: x^exp = x^(exp/2 + exp /2) = (x ^ (exp/2)) * (x^(exp/2))
        long long prod = modPow(x, exp / 2, mod);
        prod = (prod * prod) % mod;
        // if exp id odd, then we need multiply prod with x again.
        return (exp & 0x01) ? (prod * x % mod) : prod;
    }
    int dfsFindNodes(std::vector<std::vector<int>> const & treeNodes, int root, long long & prod, int mod = MOD) {
        assert(root < treeNodes.size());
        int totalNodes = 1;
        for (auto const & subTreeNode : treeNodes[root]) {
            // we count the number of nodes in the subTree nodes of the current node
            totalNodes += dfsFindNodes(treeNodes, subTreeNode, prod, mod);
        }
        // for each current root node and its subtree nodes, if there is no a constrant, then any of the current root node and its subnodes can be
        // set in the position of the current root node. However, because of the constrant, only the root node can be located there.
        // so the posibility from 1 + the number of its subnodes to 1.
        // and for the same layer nodes which belong to the same ancient, their relationships are independent.
        prod = prod * totalNodes % mod;
        return (0 == root) ? prod : totalNodes;
    }
private: 
    static int constexpr MOD = 1e9 + 7;
};