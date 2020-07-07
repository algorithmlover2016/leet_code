#include "../../head.h"

#include "../union_find_map/union_find_map.h"

class Solution {
public:
    int removeStones(std::vector<std::vector<int>> const & stones) {
        // plagiarizing from https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/discuss/197668/Count-the-Number-of-Islands-O(N)
        UnionF uni;
        int stoneCnt = 0;
        for (auto const & stone : stones) {
            if (2 > stone.size()) {
                continue;
            }
            stoneCnt++;
            uni.unionAndCnt(stone[0], ~stone[1]);
        }
        return stoneCnt - uni.getIsland();
    }
};
