#ifndef UNION_FIND_UNION_FIND_VECTOR_STANDARD_UNION_FIND_H
#define UNION_FIND_UNION_FIND_VECTOR_STANDARD_UNION_FIND_H
#include "../../head.h"

class Union {
private:
    // rank for balance;
    // cnt for record the total number of the same root;
    std::vector<int> parentIndex, rank, cnt;
public:
    Union(int size);
    int findRoot(int const x);
    int unionAndCnt(int const & left, int const & right);
};

#endif // UNION_FIND_UNION_FIND_VECTOR_STANDARD_UNION_FIND_H
