#include "../../head.h"


class Solution {
public:
    bool equationsPossible(std::vector<std::string> const & equations) {
        std::vector<int> unEqualIndexes;
        std::vector<int> parentIndex(26, -1);
        std::vector<int> cnt(26, 1);
        for (int index = 0; index < parentIndex.size(); index++) {
            parentIndex[index] = index;
        }
        for (int index = 0; index < equations.size(); index++) {
            std::string const & cur = equations[index];
            if (4 != cur.length()) {
                continue;
            }
            if (cur[1] == '!') {
                unEqualIndexes.emplace_back(index);
                continue;
            }
            unionAndCnt(parentIndex, cnt, cur[0] - 'a', cur[3] - 'a');
        }
        for (int index : unEqualIndexes) {
            std::string const & cur = equations[index];
            int leftOpeRoot = findRoot(parentIndex, cur[0] - 'a');
            int rightOpeRoot = findRoot(parentIndex, cur[3] - 'a');
            if (leftOpeRoot == rightOpeRoot) {
                return false;
            }
        }
        return true;
    }

private:
    int findRoot(std::vector<int> const & parentIndex, int index) {
        while (index != parentIndex[index]) {
            index = parentIndex[index];
        }
        return index;
    }

    int unionAndCnt(std::vector<int> & parentIndex,
            std::vector<int> & cnt, int left, int right) {
        int leftRoot = findRoot(parentIndex, left);
        int rightRoot = findRoot(parentIndex, right);
        if (leftRoot == rightRoot) {
            return cnt[leftRoot];
        }
        int count = cnt[leftRoot] + cnt[rightRoot];
        parentIndex[leftRoot] = rightRoot;
        cnt[rightRoot] = count;
        return count;
    }
};
