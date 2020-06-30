#ifndef UNION_FIND_STANDARD_UNION_FIND_H
#define UNION_FIND_STANDARD_UNION_FIND_H
#include "../head.h"

class Union {
private:
    // rank for balance;
    // cnt for record the total number of the same root;
    std::vector<int> parentIndex, rank, cnt;
public:
    Union(int size) {
        parentIndex.resize(size);
        rank.resize(size, 1);
        cnt.resize(size, 1);
    }
    int findRoot(int const x) {
        int rx(x);
        while (rx != parentIndex[rx]) {
            rx = parentIndex[rx];
        }
        // to reduce the tree height
        return parentIndex[x] = rx;
    }

    int unionAndCnt(int const & left, int const & right) {
        int leftRoot = findRoot(left);
        int rightRoot = findRoot(right);
        if (leftRoot == rightRoot) {
            return cnt[leftRoot];
        }
        int count = cnt[leftRoot] + cnt[rightRoot];
        if (rank[leftRoot] > rank[rightRoot]) {
            std::swap(leftRoot, rightRoot);
        }
        parentIndex[leftRoot] = rightRoot;
        cnt[rightRoot] = count;
        if (rank[leftRoot] == rank[rightRoot]) {
            rank[rightRoot]++;
        }
        return count;
    }

};

#endif
