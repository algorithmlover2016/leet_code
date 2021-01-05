#include "../../head.h"


// #define DEBUG
class Solution {
public:
    int minDistance(std::vector<int> houses, int k) {
        // plagiarizing from https://leetcode.com/problems/allocate-mailboxes/discuss/685620/JavaC%2B%2BPython-Top-down-DP-Prove-median-mailbox-O(n^3)
        int const housesSize = houses.size();
        if (JUST_RETURN_ZERO == housesSize || housesSize == k) {
            return 0;
        }
        std::sort(houses.begin(), houses.end());

        std::vector<std::vector<int>> costs(housesSize,
                std::vector<int>(housesSize, 0));
        for (int left = 0; left < housesSize; left++) {
            for (int right = left + 1; right < housesSize; right++) {
                int midVal = houses[(left + right) / 2];
                for (int mid = left; mid <= right; mid++) {
                    costs[left][right] += std::abs(midVal - houses[mid]);
                }
                costs[right][left] = costs[left][right];
            }
        }

        std::vector<std::vector<int>> dpMemo(k + 1,
                std::vector<int>(housesSize + 1, 0));
        dpMemo[1][0] = 0;
        for (int idx = 1; idx < dpMemo[1].size(); idx++) {
            dpMemo[1][idx] = costs[0][idx - 1];
            #ifdef DEBUG
            std::cout << "dpMemo[1]: " << dpMemo[1][idx] << '\t';
            #endif
        }

        for (int mailBox = 2; mailBox < dpMemo.size(); mailBox++) {
            for (int idx = 1; idx < dpMemo[mailBox].size(); idx++) {
                dpMemo[mailBox][idx] = MAX_COST;
                for (int mid = 1; mid < idx; mid++) {
                    dpMemo[mailBox][idx] = std::min(dpMemo[mailBox][idx], dpMemo[mailBox - 1][mid] + costs[mid][idx - 1]);
                }
            }
        }
        return dpMemo[k][housesSize];
    }

private:
    static int const JUST_RETURN_ZERO = 0;
    static int const MAX_COST = 1e5;
};

// #define DEBUG
class SolutionDFS {
public:
    int minDistance(std::vector<int> houses, int k) {
        // plagiarizing from https://leetcode.com/problems/allocate-mailboxes/discuss/685620/JavaC%2B%2BPython-Top-down-DP-Prove-median-mailbox-O(n^3)
        int const housesSize = houses.size();
        if (JUST_RETURN_ZERO == housesSize || housesSize == k) {
            return 0;
        }
        std::sort(houses.begin(), houses.end());

        std::vector<std::vector<int>> costs(housesSize,
                std::vector<int>(housesSize, 0));
        for (int left = 0; left < housesSize; left++) {
            for (int right = left + 1; right < housesSize; right++) {
                int midVal = houses[(left + right) / 2];
                for (int mid = left; mid <= right; mid++) {
                    costs[left][right] += std::abs(midVal - houses[mid]);
                }
                costs[right][left] = costs[left][right];
            }
        }

        std::vector<std::vector<int>> dpMemo(k + 1,
                std::vector<int>(housesSize, NO_VALID_FLAG));
        return dfs(costs, dpMemo, k, 0);
    }
    int dfs(std::vector<std::vector<int>> const & costs,
            std::vector<std::vector<int>> & dpMemo,
            int k, int idx) {
        if (JUST_RETURN_ZERO == k && idx == costs.size()) {
            return 0; // all have been allocated
        }
        if (JUST_RETURN_ZERO == k || idx == costs.size()) {
            return MAX_COST; // not enough k or not enough house
        }

        if (NO_VALID_FLAG != dpMemo[k][idx]){
            return dpMemo[k][idx];
        }
        int ans = MAX_COST;
        for (int nextSplit = idx; nextSplit < costs.size(); nextSplit++) {
            ans = std::min(ans, dfs(costs, dpMemo, k - 1, nextSplit + 1) + costs[idx][nextSplit]);
        }
        return dpMemo[k][idx] = ans;
    }

private:
    static int const JUST_RETURN_ZERO = 0;
    static int const MAX_COST = 1e5;
    int const NO_VALID_FLAG = -1;
};
