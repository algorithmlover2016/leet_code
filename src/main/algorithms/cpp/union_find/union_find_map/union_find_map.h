#ifndef UNION_FIND_UNION_FIND_MAP_UNION_FIND_MAP_H
#define UNION_FIND_UNION_FIND_MAP_UNION_FIND_MAP_H
#include "../../head.h"

class UnionF {
public:
    int findRoot(int const index);
    int unionAndCnt(int const left, int const right);
    int getIsland(); 
private:
    std::unordered_map<int, int> parentIndex;
    std::unordered_map<int, int> cnt;
    std::unordered_map<int, int> rank;
    int island = 0;
};
#endif // UNION_FIND_UNION_FIND_MAP_UNION_FIND_MAP_H
