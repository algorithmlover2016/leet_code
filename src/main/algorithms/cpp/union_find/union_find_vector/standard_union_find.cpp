#include "standard_union_find.h"

Union::Union(int size) {
    parentIndex.resize(size);
    rank.resize(size, 1);
    cnt.resize(size, 1);
}

int Union::findRoot(int const x) {
    int rx(x);
    while (rx != parentIndex[rx]) {
        rx = parentIndex[rx];
    }
    // to reduce the tree height
    return parentIndex[x] = rx;
}

int Union::unionAndCnt(int const & left, int const & right) {
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

#endif // UNION_FIND_UNION_FIND_VECTOR_STANDARD_UNION_FIND_H
