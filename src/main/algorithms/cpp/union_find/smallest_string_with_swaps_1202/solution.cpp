#include "../../head.h"


class SolutionTLE {
public:
    std::string smallestStringWithSwaps(std::string const s, std::vector<std::vector<int>> const & pairs) {
        std::vector<int> parentIndex(s.size(), -1);
        std::vector<int> cnt(s.size(), 1); // no use
        for (int index = 0; index < parentIndex.size(); index++) {
            parentIndex[index] = index;
        }
        for (auto const & p : pairs) {
            if (2 != p.size()) {
                continue;
            }
            unionAndCnt(parentIndex, cnt, p[0], p[1]);
        }
        std::vector<std::vector<int>> rootIndexMap(s.size());
        for (int index = 0; index < s.size(); index++) {
            rootIndexMap[findRoot(parentIndex, index)].emplace_back(index);
        }
        std::string res(s);
        for (auto const & layer : rootIndexMap) {
            if (layer.empty()) {
                continue;
            }
            std::string layerStr;
            for (int index : layer) {
                layerStr += s[index];
            }
            std::sort(std::begin(layerStr), std::end(layerStr));
            for (int index = 0; index < layer.size(); index++) {
                res[layer[index]] = layerStr[index];
            }
        }
        return res;

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
