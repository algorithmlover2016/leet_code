#include "../../head.h"


class SolutionMLE {
public:
    std::vector<int> fullBloomFlowers(std::vector<std::vector<int>> const & flowers, std::vector<int> const & persons) {
        std::vector<int> ans;
        if (persons.empty()) {
            return ans;
        }

        std::vector<int> memo(MAX_LEN);
        for (auto const & flower : flowers) {
            if (FLOWER_LEN > flower.size()) {
                continue;
            }
            memo[flower[S_IDX]]++;
            memo[flower[E_IDX] + 1]--;
        }
        int preSum = 0;
        for (int idx = 0; idx < memo.size(); idx++) {
            preSum += memo[idx];
            memo[idx] = preSum;
        }
        for (int person : persons) {
            ans.emplace_back(memo[person]);
        }
        return ans;
    }
private:
    static int const MAX_LEN = 1e9 + 1;
    static int const FLOWER_LEN = 2;
    static int const S_IDX = 0;
    static int const E_IDX = 1;
};

#define BINARY_SEARCH_BY_UPPER_LOWER
// #undef BINARY_SEARCH_BY_UPPER_LOWER
class Solution {
public:
    std::vector<int> fullBloomFlowers(std::vector<std::vector<int>> const & flowers, std::vector<int> const & persons) {
        if (persons.empty()) {
            return {};
        }
        #ifdef BINARY_SEARCH_BY_UPPER_LOWER
        // plagiarizing from https://leetcode.com/problems/number-of-flowers-in-full-bloom/discuss/1977099/C%2B%2BPython-Binary-Search-and-Sweep-Line
        std::vector<int> starts, ends;
        for (auto const & flower : flowers) {
            if (FLOWER_LEN > flower.size()) {
                continue;
            }
            starts.emplace_back(flower[S_IDX]);
            ends.emplace_back(flower[E_IDX]);
        }
        std::sort(std::begin(starts), std::end(starts));
        std::sort(std::begin(ends), std::end(ends));
        std::vector<int> ans;
        for (int person : persons) {
            int started = std::upper_bound(std::begin(starts), std::end(starts), person) - std::begin(starts); // find the first ele which is larger than person
            int ended = std::lower_bound(std::begin(ends), std::end(ends), person) - std::begin(ends); // find the first ele which is not less than person.
            // because only if ele is less than person, it means it ends.
            ans.emplace_back(started - ended);
        }
        #else
        // plagiarizing from https://leetcode.com/problems/number-of-flowers-in-full-bloom/discuss/1983148/Compressed-Line-Sweep
        std::vector<int> ans(persons.size());
        std::map<int, int> cnts;
        cnts.insert({0, 0});
        for (auto const & flower : flowers) {
            if (FLOWER_LEN > flower.size()) {
                continue;
            }
            cnts[flower[S_IDX]]++;
            cnts[flower[E_IDX] + 1]--;
        }
        for (auto it = std::next(cnts.begin()); it != cnts.end(); it++) {
            it->second += std::prev(it)->second;
        }
        std::transform(std::begin(persons), std::end(persons), std::begin(ans), [&](int person) {
            return std::prev(cnts.upper_bound(person))->second;
        });
        #endif
        return ans;


    }
private:
    static int const FLOWER_LEN = 2;
    static int const S_IDX = 0;
    static int const E_IDX = 1;
};