#include "../../head.h"


// #define DEBUG
class Solution {
private:
    class UnionFind {
    public:
        // with rank and count in a group
        UnionFind(int arrSize) {
            parents.resize(arrSize);
            cnt.resize(arrSize);
            rank.resize(arrSize);
            for (int idx = 0; idx < parents.size(); idx++) {
                cnt[idx] = 1;
                parents[idx] = idx;
            }
        }

        int find(int const idx) {
            int tmpIdx = idx;
            while (tmpIdx != parents[tmpIdx]) {
                tmpIdx = parents[tmpIdx];
            }
            return parents[idx] = tmpIdx;
        }

        int unionCntWithRank(int const left, int const right) {
            int leftParent = find(left);
            int rightParent = find(right);
            if (leftParent == rightParent) {
                return cnt[leftParent];
            }
            if (rank[leftParent] < rank[rightParent]) {
                std::swap(leftParent, rightParent);
            } else if (rank[leftParent] == rank[rightParent]) {
                rank[leftParent]++;
            }
            parents[rightParent] = leftParent;
            return cnt[leftParent] = cnt[leftParent] + cnt[rightParent];
        }

    private:
        std::vector<int> parents;
        std::vector<int> cnt;
        std::vector<int> rank;
    };
public:
    int minimumHammingDistance(std::vector<int> const & source,
            std::vector<int> const & target,
            std::vector<std::vector<int>> const & allowedSwaps) {

        // plagiarizing from https://youtu.be/G1vTpGA9Gkc
        int const sourceSize = source.size();
        int const targetSize = target.size();
        if (sourceSize != targetSize) {
            return ERROR_INPUT;
        }
        int const allowedSwapsSize = allowedSwaps.size();
        UnionFind unionObj(sourceSize);
        for (auto const & ele : allowedSwaps) {
            if (SWAP_LEN > ele.size()) {
                continue;
            }
            unionObj.unionCntWithRank(ele[IDX_FIRST], ele[IDX_SECOND]);
        }

        // split the idxes to different group
        std::unordered_map<int, std::vector<int>> groupList;
        for (int idx = 0; idx < sourceSize; idx++) {
            groupList[unionObj.find(idx)].emplace_back(idx);
        }

        #ifdef DEBUG
        std::cout << "group size: " << groupList.size() << "\n";
        #endif
        int ans = 0;
        // according to each group, count the difference
        for (auto const & [groupRoot, idxList] : groupList) {
            #ifdef DEBUG
            std::cout << "root: " << groupRoot << "\n";
            #endif
            std::unordered_map<int, int> cntTimes;
            for (auto const idx : idxList) {
                // every element in source we meet will be add one with its value as key
                cntTimes[source[idx]]++;
                // every element in target we meet will be minus one with its value as key
                cntTimes[target[idx]]--;
            }
            // because in a group, we can free exchange its elements, so we just no need to
            // consider the order in the two sequence
            for (auto const & [val, valCnt] : cntTimes) {
                if (0 < valCnt) {
                #ifdef DEBUG
                std::cout << val << "\t";
                #endif
                    // ans++; // maybe the element appear not only once
                    ans += valCnt;
                }
            }
        }
        return ans;
    }
private:
    static int const JUST_ZERO = 0;
    static int const ERROR_INPUT = -1;

    static int const SWAP_LEN = 2;
    static int const IDX_FIRST = 0;
    static int const IDX_SECOND = 1;
};
