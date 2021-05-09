#include "../../head.h"


class Solution {
public:
    std::vector<int> countPairs(int const n,
            std::vector<std::vector<int>> const & edges,
            std::vector<int> const & queries) {
        // plagairizing from https://leetcode.com/problems/count-pairs-of-nodes/discuss/1096740/C%2B%2BJavaPython3-Two-Problems-O(q-*-(n-%2B-e))
        // because edge index start from 1 to n(included), so we set the vector size to n + 1
        int const queriesSize = queries.size();
        std::vector<int> cnts(n + 1, 0), sortedCnt(n + 1, 0), ans(queriesSize, 0);
        std::vector<std::unordered_map<int, int>> sharedEdge(n + 1);
        for (auto const & edge : edges) {
            if (EDGE_SIZE > edge.size()) {
                continue;
            }
            int firstEle = edge[EDGE_FIRST_IDX];
            int secondEle = edge[EDGE_SECOND_IDX];
            sortedCnt[firstEle] = ++cnts[firstEle];
            sortedCnt[secondEle] = ++cnts[secondEle];

            if (firstEle > secondEle) {
                std::swap(firstEle, secondEle);
            }
            ++sharedEdge[firstEle][secondEle];
        }
        // make sortedCnt increasing order
        std::sort(sortedCnt.begin(), sortedCnt.end());
        for (int idx = 0; idx < queriesSize; idx++) {
            auto const & query = queries[idx];
            for (int left = 1, right = n; left < right;) {
                if (query < sortedCnt[left] + sortedCnt[right]) {
                    // which means from left to right - 1, these node can construct a pair with right,
                    // which make cnt > query
                    ans[idx] += (right--) - left;
                } else {
                    left++;
                }
            }
            for (int node = 1; node <= n; node++) {
                for (auto const & [adjNode, edgeCnt] : sharedEdge[node]) {
                    int cntWithRepeat = cnts[node] + cnts[adjNode];
                    // although the cntWithRepeat meets the request, however it has repeating edges
                    if (query < cntWithRepeat && query + edgeCnt >= cntWithRepeat) {
                        // in the upper loop, we just compute the pair number, so
                        // we just remove the pair node, which means minus 1
                        --ans[idx];
                    }
                }
            }
        }
        return ans;
    }

private:
    static int const EDGE_SIZE = 2;
    static int const EDGE_FIRST_IDX = 0;
    static int const EDGE_SECOND_IDX = 1;
};

class Solution {
public:
    std::vector<int> countPairs(int n,
            std::vector<std::vector<int>> const & edges,
            std::vector<int> const & queries) {
        std::vector<int> node_degrees(n);
        std::unordered_map<int, int> edge_freq;
        for (auto & e : edges) {
            std::sort(std::begin(e), std::end(e));
            ++node_degrees[--e[0]];
            ++node_degrees[--e[1]];
            // using left most 16bits as left node
            // and right most 16bits as the right node
            ++edge_freq[(e[0] << 16) | e[1]];
        }

        const int max_degree = *std::max_element(std::begin(node_degrees),
                std::end(node_degrees));

        // Need pad one more to handle "not found / 0" case.
        // not found means counts[max_degree * 2 + 1]
        std::vector<int> counts(max_degree * 2 + 2);

        std::unordered_map<int, int> degree_count;
        for (int i = 0; i < n; ++i) {
            ++degree_count[node_degrees[i]];
        }

        for (auto & [d1, c1] : degree_count) {
            for (auto& [d2, c2] : degree_count) {
                if (d1 < d2) {
                // Only count once if degrees are different to ensure (a < b)
                    counts[d1 + d2] += c1 * c2;
                } else if (d1 == d2)  {
                    // If degrees are the same C(n, 2) to ensure (a < b)
                    counts[d1 * 2] += c1 * (c1 - 1) / 2;
                }
            }
        }

        for (auto& [key, freq] : edge_freq) {
            const int u = key >> 16;
            const int v = key & 0xFFFF;
            // For a pair of (u, v) their actual edge count is
            // d[u] + d[v] - freq[(u, v)] instead of d[u] + d[v]
            counts[node_degrees[u] + node_degrees[v]] -= 1;
            counts[node_degrees[u] + node_degrees[v] - freq] += 1;
        }

        // counts[i] = # of pairs whose total edges >= i
        for (int i = counts.size() - 2; i >= 0; --i) {
            counts[i] += counts[i + 1];
        }

        std::vector<int> ans;
        for (int q : queries) {
            ans.push_back(counts[std::min(q + 1, static_cast<int>(counts.size() - 1))]);
        }
        return ans;
    }
};
