#include "../../head.h"


class SolutionTLE {
public:
    int numTrees(int n) {
        if(n == 0) {
            return 0;
        }
        return recurse(1,n);
    }
    
    int recurse(int start, int end){
        if(start > end){
            return 1;
        }
        
        int ans = 0;
        for(int i=start; i <= end; i++){
            int left_subtree  = recurse(start, i-1);
            int right_subtree = recurse(i+1,   end);
            ans += left_subtree * right_subtree;
        }
        return ans;
    }
};


class Solution {
public:
    int numTrees(int n) {
        // plagiairizing from https://leetcode.com/problems/unique-binary-search-trees/discuss/31666/DP-Solution-in-6-lines-with-explanation.-F(i-n)-G(i-1)-*-G(n-i)
        std::vector<int> dpMemo(n + 1, 0);
        dpMemo[0] = dpMemo[1] = 1;
        // when there is no nodes, return 0;
        // if there is a node, return 1;
        for (int nodes = 2; nodes <= n; nodes++) {
            for (int root = 1; root <= nodes; root++) {
                dpMemo[nodes] += dpMemo[root - 1] * dpMemo[nodes - root];
            }
        }
        dpMemo[0] = 0;
        return dpMemo[n];
    }
};
