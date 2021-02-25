#include "../../head.h"


class Solution {
public:
    std::vector<int> restoreArray(std::vector<std::vector<int>> const & adjacentPairs) {
        // plagiarizing idea from https://youtu.be/SGfdp6CFDrA
        std::unordered_map<int, std::vector<int>> graph;
        for (auto const & p : adjacentPairs) {
            if (p.size() < PAIR_SIZE) {
                continue;
            }
            graph[p[FIRST]].emplace_back(p[SECOND]);
            graph[p[SECOND]].emplace_back(p[FIRST]);
        }

        int cur = INIT_FLAG;
        for (auto const & [key, val] : graph) {
            if (START_ELE == val.size()) {
                cur = key;
                break;
            }
        }

        std::unordered_set<int> seen;
        std::vector<int> ans;
        while (INIT_FLAG != cur) {
            ans.emplace_back(cur);
            seen.insert(cur);
            std::vector<int> & adj = graph[cur];
            cur = INIT_FLAG;
            for (int const next : adj) {
                if (seen.find(next) == seen.end()) {
                    cur = next;
                }
            }
        }
        return ans;
    }
private:
    static int const PAIR_SIZE = 2;
    static int const FIRST = 0;
    static int const SECOND = 1;
    static int const START_ELE = 1;
    static int const INIT_FLAG = INT_MIN;
};
