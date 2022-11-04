#include "../../head.h"


// #define DEBUG
class Solution {
public:
    int componentValue(std::vector<int> const & nums, std::vector<std::vector<int>> const & edges) {
        // plagiarizing from https://leetcode.com/problems/create-components-with-same-value/solutions/2707217/bfs/
        if (nums.empty()) {
            return 0;
        }
        long long sum = std::accumulate(std::begin(nums), std::end(nums), 0LL);
        #ifdef DEBUG
        std::cout << "nodes sum: " << sum << "\n";
        #endif
        if (0 == sum % nums.size() &&
            std::all_of(std::begin(nums), std::end(nums), [&](int num) {
                                                                return num == sum / nums.size();
                                                          })) {
            return nums.size() - 1;
        }
        std::vector<std::vector<int>> graphs(nums.size());
        std::vector<int> cnts(nums.size());
        for (auto & edge : edges) {
            if (edge.size() < EDGE_LEN) {
                continue;
            }
            graphs[edge[FIRST_IDX]].emplace_back(edge[SECOND_IDX]);
            graphs[edge[SECOND_IDX]].emplace_back(edge[FIRST_IDX]);

            cnts[edge[FIRST_IDX]]++;
            cnts[edge[SECOND_IDX]]++;
        }
        std::vector<int> leafNodes;
        for (int idx = 0; idx < cnts.size(); idx++) {
            if (FLAG_LEAF == cnts[idx]) {
                #ifdef  DEBUG
                std::cout << "Leaf: " << idx << ",\t";
                #endif
                leafNodes.emplace_back(idx);
            }
        }
        #ifdef  DEBUG
        std::cout << "\n";
        #endif
        for(int val = nums.size() - 1; val > 1; val--) {
            if (0 == sum % val && bfs(sum / val, graphs, leafNodes, nums, cnts)) {
                return val - 1; // need val - 1 spliting operations for val subparts
            }
        }
        return 0;
    }
private:
    bool bfs(int val, std::vector<std::vector<int>> const & graphs, std::vector<int> leafs, std::vector<int> nums, std::vector<int> cnts) {
        while (!leafs.empty()) {
            std::vector<int> nextLeafs;
            for (auto leaf : leafs) {
                if (nums[leaf] > val) {
                    return false;
                }
                for (auto nextLeaf : graphs[leaf]) { // we will visit visited leafs nodes but we only visit once again.
                    nums[nextLeaf] += nums[leaf] < val ? nums[leaf] : 0;
                    if (1 == --cnts[nextLeaf]) {
                        nextLeafs.emplace_back(nextLeaf);
                    }
                }
            }
            std::swap(nextLeafs, leafs);
        }
        return true;
    }
private:
    static int constexpr EDGE_LEN = 2;
    static int constexpr FIRST_IDX = 0;
    static int constexpr SECOND_IDX = 1;
    static int constexpr FLAG_LEAF = 1;
};