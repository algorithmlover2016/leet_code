#include "union_find_map.h"

int UnionF::findRoot(int const index) {
    if (parentIndex.find(index) == parentIndex.end()) {
        parentIndex[index] = index;
        island++;
    }
    int dfsIndex = index;
    while (dfsIndex != parentIndex[dfsIndex]) {
        dfsIndex = parentIndex[dfsIndex];
    }
    return parentIndex[index] = dfsIndex;
}

int UnionF::unionAndCnt(int const left, int const right) {
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
    island--;
    if (rank[leftRoot] == rank[rightRoot]) {
        rank[rightRoot]++;
    }
    return count;
}

int UnionF::getIsland() {
    return island;
}
