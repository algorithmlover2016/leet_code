#include "fen_wick_tree.h"

FenWickTree::FenWickTree(std::vector<int> & nums) : _nums(nums) {
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
void FenWickTree::update(int index, int val) {
    int deltaVal = val - _nums[index];
    index++;
    while (index < tree.size()) {
        tree[index] += deltaVal;
        index += index & (index ^ (index - 1));
    }
}

// get the sum from zero index to the index index ([0, ... , index])
int FenWickTree::getSum(int index) {
    int sum = 0;
    index++;
    while (index > 0) {
        sum += tree[index];
        index -= index & (index ^ (index - 1));
    }
    return sum;
}
