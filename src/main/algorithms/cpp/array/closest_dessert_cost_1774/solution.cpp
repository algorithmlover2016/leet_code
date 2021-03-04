#include "../../head.h"


class Solution {
public:
    int closestCost(std::vector<int> const & baseCosts,
            std::vector<int> const & toppingCosts,
            int const target) {
        int ans = INT_MAX;
        for (int idx = 0; idx < baseCosts.size(); idx++) {
            dfs(toppingCosts, 0, 0, target - baseCosts[idx], ans);
        }
        return target - ans;
    }

    void dfs(std::vector<int> const & toppingCosts, int idx, int cnt, int target, int & ans) {
        int absTarget = std::abs(target), absAns = std::abs(ans);

        if (absTarget < absAns || (absTarget == absAns && target > ans)) {
            ans = target;
        }
        if (target < 0) {
            return;
        }
        if (idx == toppingCosts.size()) {
            return;
        }
        while (cnt <= 2) {
            dfs(toppingCosts, idx + 1, 0, target - toppingCosts[idx] * cnt, ans);
            cnt++;
        }
    }
};

class SolutionBetter {
public:
    int closestCost(std::vector<int> const & baseCosts, std::vector<int> const & toppingCosts, int T) {
        std::set<int> cost(baseCosts.begin(), baseCosts.end());
        std::set<int> next = cost;
        int bst = baseCosts[0];
        int bstD = std::abs(bst - T);

        for (int c : baseCosts) {
            if (std::abs(c - T) < bstD || (std::abs(c-T) == bstD && c < bst)) {
                bst = c;
                bstD = std::abs(bst - T);
            }
        }

        for(int t : toppingCosts) {
            for (int it : cost) {
                for (int c = it + t; c <= it + 2 * t; c += t) {
                    if (c < T + bstD) next.insert(c);
                    if (std::abs(c - T) < bstD || (std::abs(c-T) == bstD && c < bst)) {
                        bst = c;
                        bstD = std::abs(bst - T);
                    }
                }
            }
            cost = next;
        }
        return bst;
    }
};
