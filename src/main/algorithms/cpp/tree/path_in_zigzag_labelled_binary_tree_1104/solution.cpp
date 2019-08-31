#include "../../head.h"
#include "tree.h"

class Solution {
public:
    std::vector<int> pathInZigZagTree(int label) {
        int level = 0;
        while ( (1 << level) <= label) {
            level++;
        }
        std::vector<int> res(level);
        for (; label >= 1; label /=2, level--) {
            res[level - 1] = label;
            label = (1 << level) - 1 - label + (1 << (level - 1));
        }
        return res;
    }

};
