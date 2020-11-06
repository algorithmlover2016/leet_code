#include "../../head.h"


class Solution {
public:
    std::vector<int> processQueries(std::vector<int> const & queries, int m) {
        // plagiarizing from https://leetcode.com/problems/queries-on-a-permutation-with-key/discuss/575071/PythonC%2B%2B-NlogN-Short-Fenwick-Tree-With-Detailed-Explanations

        std::vector<int> ans;

        // Fenwick Tree, init with zero. each value record the index (start from 1, not zero)
        std::vector<int> fenWickTree(2 * m + 1, 0);

        std::unordered_map<int, int> hmap;

        for (int index = 1; index <= m; index++) {
            hmap[index] = index + m;
            update(fenWickTree, index + m, 1); // start from m + 1, index is counted by sum
        }

        for (int query : queries) {
            ans.emplace_back(getSum(fenWickTree, hmap[query]) - 1); // the index from Permutation is zero, but the tree record from 1;
            update(fenWickTree, hmap[query], -1); // set the query index to zero, which means there is no value here.
            update(fenWickTree, m, 1); // the queried value is set to m index;
            hmap[query] = m;
            m--;
        }
        return ans;


    }

    void update(std::vector<int> & fenWickTree, int index, int deltaVal) {
        while (index < fenWickTree.size()) {
            fenWickTree[index] += deltaVal;
            index += index & (index ^ (index - 1));
        }
    }

    int getSum(std::vector<int> const & fenWickTree, int index) {
        int sum = 0;
        while (index > 0) {
            sum += fenWickTree[index];
            index -= index & (index ^ (index - 1));
        }
        return sum;
    }
};

class FenWickTree {
public:
    FenWickTree(std::vector<int> & nums) : _nums(nums) {
        tree.clear();

        tree.resize(_nums.size() + 1, 0);
        for (int index = 1; index < tree.size(); index++) {
            int sum = 0;
            int lowbit = index & (index ^ (index - 1));
            for (int interval = index; interval > index - lowbit; interval--) {
                sum += _nums[interval - 1];
            }
            tree[index] = sum;
        }
    }

    // the index is the _nums index, index + 1 is the index of the FenWickTree
    void update(int index, int val) {
        int deltaVal = val - _nums[index];
        index++;
        while (index < tree.size()) {
            tree[index] += deltaVal;
            index += index & (index ^ (index - 1));
        }
    }

    // get the sum from zero index to the index index ([0, ... , index])
    int getSum(int index) {
        int sum = 0;
        index++;
        while (index > 0) {
            sum += tree[index];
            index -= index & (index ^ (index - 1));
        }
        return sum;
    }

private:
    std::vector<int> tree;
    std::vector<int> & _nums;
};
