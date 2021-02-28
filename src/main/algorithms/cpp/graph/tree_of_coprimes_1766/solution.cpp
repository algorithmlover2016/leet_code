#include "../../head.h"


// #define STORAGE_WITH_VECTOR
class Solution {
public:
    std::vector<int> getCoprimes(std::vector<int> const & nums, std::vector<std::vector<int>> const & edges) {
        // plagiarizing from https://leetcode.com/problems/tree-of-coprimes/discuss/1074770/C%2B%2B-Save-the-cops
        int const numsSize = nums.size();
        std::vector<int> ans(numsSize, INIT_VAL);
        /*
        if (JUST_ONE == numsSize) {
            return ans;
        }
        */
        #ifndef STORAGE_WITH_VECTOR
        std::unordered_map<int, std::vector<int>> graph;
        #else
        std::vector<std::vector<int>> graph(numsSize);
        #endif
        for (auto const & edge : edges) {
            if (EDGE_SIZE > edge.size()) {
                continue;
            }
            graph[edge[FIRST]].emplace_back(edge[SECOND]);
            graph[edge[SECOND]].emplace_back(edge[FIRST]);
        }

        std::unordered_set<int> numsUsed(std::begin(nums), std::end(nums));
        #ifndef STORAGE_WITH_VECTOR
        std::unordered_map<int, std::vector<int>> coPrimes;
        #else
        std::vector<std::vector<int>> coPrimes(NUMS_MAX_VAL + 1);
        #endif
        for (std::unordered_set<int>::iterator it1 = numsUsed.begin(); it1 != numsUsed.end(); it1++ ) {
            for (std::unordered_set<int>::iterator it2 = it1 /* can't be std::next(it1), it will ignore (1, 1)*/; it2 != numsUsed.end(); it2++ ) {
                int num1 = *it1;
                int num2 = *it2;
                if (JUST_ONE == std::gcd(num1, num2)) {
                    coPrimes[num1].emplace_back(num2);
                    coPrimes[num2].emplace_back(num1);
                }
            }
        }

        std::unordered_map<int, std::vector<std::pair<int, int>>> parents;

        dfs(nums, graph, coPrimes, parents, 0, 0, 0, ans);
        return ans;
    }

    void dfs(std::vector<int> const & nums,
             #ifndef STORAGE_WITH_VECTOR
             std::unordered_map<int, std::vector<int>> & graph,
             std::unordered_map<int, std::vector<int>> & coPrimes,
             #else
             std::vector<std::vector<int>> const & graph,
             std::vector<std::vector<int>> const & coPrimes,
             #endif
             std::unordered_map<int, std::vector<std::pair<int, int>>> & parents,
             int idx, int parentIdx, int height,
             std::vector<int> & ans) {
        int maxLevel = -1;
        for (int const coPrime : coPrimes[nums[idx]]) {
            auto & parent = parents[coPrime];
            if (!parent.empty() && parent.back().first > maxLevel) {
                // for cur idx, there exists a parent who is prime to nums[idx], and it is most recently to cur idx;
                maxLevel = parent.back().first;
                ans[idx] = parent.back().second;
            }
        }
        parents[nums[idx]].emplace_back(std::make_pair(height, idx));
        for (int const nextIdx : graph[idx]) {
            if (nextIdx != parentIdx) { // tarversal its children node
                dfs(nums, graph, coPrimes, parents, nextIdx, idx, height + 1, ans);
            }
        }
        parents[nums[idx]].pop_back();
    }

private:
    static int const EDGE_SIZE = 2;
    static int const FIRST = 0;
    static int const SECOND = 1;
    static int const JUST_ONE = 1;
    int const INIT_VAL = -1;
    static int const NUMS_MAX_VAL = 50;
};
