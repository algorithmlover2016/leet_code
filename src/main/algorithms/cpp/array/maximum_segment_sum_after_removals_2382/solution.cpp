#include "../../head.h"



class Solution {
public:
    std::vector<long long> maximumSegmentSum(std::vector<int> const & nums, std::vector<int> const & removeQueries) {
        // plagiarizing from https://leetcode.com/problems/maximum-segment-sum-after-removals/solutions/2454208/reverse-union-find/
        std::vector<long long int> ans(nums.size()), parents(nums.size(), INIT_MAX);
        for (int queryIdx = removeQueries.size() - 1; queryIdx > 0; queryIdx--) {
            int numIdx = removeQueries[queryIdx];
            parents[numIdx] = -nums[numIdx]; // each node is root node at the begining
            if ((numIdx > INIT_ZERO) && (INIT_MAX != parents[numIdx - 1])) {
                // the node of (numIdx - 1) must be a root node or a subnode belong to some node and it is adjacent to the numIdx node.
                mergeUnion(numIdx - 1, numIdx, parents);
            }
            if ((numIdx < (nums.size() - 1)) && (INIT_MAX != parents[numIdx + 1])) {
                mergeUnion(numIdx, numIdx + 1, parents);
            }
            ans[queryIdx - 1] = std::max(ans[queryIdx], -parents[find(numIdx, parents)]);
        }
        return ans;
    }
private:
    int find(int idx, std::vector<long long int> & parents) {
        /*
        the idx must from INIT_ZERO (included) to parents.size() (excluded)
        */
        assert(idx >= 0 && idx < parents.size());

        /*
        If the parents[idx] < INIT_ZERO, it means the element located in idx-th is a root and it saves the negative sum of its tree.
            because we initialize the parents[idx] with -nums[idx];
        If the parents[idx] >= 0, it means that it has a parent and we need find its root in next step.
        */

        return parents[idx] < INIT_ZERO ? idx : parents[idx] = find(parents[idx], parents);
    }

    void mergeUnion(int left, int right, std::vector<long long int> & parents) {
        int leftRoot = find(left, parents), rightRoot = find(right, parents);
        parents[rightRoot] += parents[leftRoot]; // the value of the root node is saved in parents[root], and we need get the sum.
        parents[leftRoot] = rightRoot; // we need union these nodes
    }

private:
    static int constexpr INIT_ZERO = 0;
    static int constexpr INIT_MAX = INT_MAX;
};