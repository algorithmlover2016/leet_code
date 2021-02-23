#include "../../head.h"


class TreeAncestorTLE {
public:
    TreeAncestor(int n, std::vector<int> const & parent) : parents(parent) {
    }
    
    int getKthAncestor(int node, int k) {
        while (k-- > 0) {
            int p = parents[node];
            if (-1 == p) {
                return p;
            }
            node = p;
        }
        return node;
    }
    
private:
    std::vector<int> parents;
};

/**
 * Your TreeAncestor object will be instantiated and called as such:
 * TreeAncestor* obj = new TreeAncestor(n, parent);
 * int param_1 = obj->getKthAncestor(node,k);
 */

// #define DEBUG

class TreeAncestor {
public:
    TreeAncestor(int n, std::vector<int> const & parents) {
        // self tle, plagiarizing idea from https://youtu.be/QKSfS5VMv_Q
        int logInt = mostLarge(n) + 1;
        dpMemo = std::vector<std::vector<int>>(n, std::vector<int>(logInt, INIT_FLAG));
        for (int idx = 0; idx < parents.size(); idx++) {
            dpMemo[idx][0] = parents[idx];
        }
        for (int idx = 0; idx < parents.size(); idx++) {
            for (int preLog = 1; preLog < logInt; preLog++) {
                if (INIT_FLAG != dpMemo[idx][preLog - 1]) {
                    // 2^preLog = 2 ^ (preLog - 1) + 2 ^ (preLog - 1);
                    dpMemo[idx][preLog] = dpMemo[dpMemo[idx][preLog - 1]][preLog - 1];
                }

            }
        }
    }

    int getKthAncestor(int node, int k) {
        while (k > 0 && INIT_FLAG != node) {
            #ifdef DEBUG
            std::cout << "node, k: " << node << ",\t" << k << "\n";
            #endif

            int subTract = mostLarge(k);
            node = dpMemo[node][subTract];
            k -= (1 << subTract);
        }
        return node;
    }
private:
    int mostLarge(int n) {
        int ans = 0;
        while (n > 1) {
            n >>= 1;
            ans += 1;
        }
        return ans;
    }

private:
    int const INIT_FLAG = -1;
    std::vector<std::vector<int>> dpMemo;
};
