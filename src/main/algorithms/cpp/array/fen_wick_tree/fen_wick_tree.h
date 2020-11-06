#include "../../head.h"

#ifndef ARRAY_FEN_WICK_TREE_FEN_WICK_TREE_H
#define ARRAY_FEN_WICK_TREE_FEN_WICK_TREE_H
class FenWickTree {
public:
    FenWickTree(std::vector<int> & nums); 

    // the index is the _nums index, index + 1 is the index of the FenWickTree
    void update(int index, int val); 

    // get the sum from zero index to the index index ([0, ... , index])
    int getSum(int index); 

private:
    std::vector<int> tree;
    std::vector<int> & _nums;
};

#endif
