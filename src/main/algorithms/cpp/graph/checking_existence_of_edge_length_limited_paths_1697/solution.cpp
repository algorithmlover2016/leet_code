#include "../../head.h"


class Solution {
private:
    class UnionFind {
    public:
        UnionFind(int const size) : _size(size) {
            parents.resize(_size);
            cnt.resize(_size, 1);
            rank.resize(_size, 1);
            for (int idx = 0; idx < _size; idx++) {
                parents[idx] = idx;
            }
        }

        int find(int idx) {
            assert(idx < _size);
            int tmpIdx(idx);
            while (tmpIdx != parents[tmpIdx]) {
                tmpIdx = parents[tmpIdx];
            }
            return parents[idx] = tmpIdx;
        }

        int unionAndCntWithRank(int const left, int const right) {
            int leftRoot = find(left);
            int rightRoot = find(right);
            if (leftRoot == rightRoot) {
                return cnt[leftRoot];
            }
            int curCnt = cnt[leftRoot] + cnt[rightRoot];
            if (rank[leftRoot] > rank[rightRoot]) {
                std::swap(leftRoot, rightRoot);
            } else if (rank[leftRoot] == rank[rightRoot]) {
                rank[rightRoot]++;
            }
            parents[leftRoot] = rightRoot;
            return cnt[rightRoot] = curCnt;

        }

    private:
        int const _size;
        std::vector<int> parents;
        std::vector<int> cnt;
        std::vector<int> rank;
    };

    template<int COMP_LEN = 2>
    class CompMin {
    private:
        bool _reverse;
    public:
        CompMin(bool reverse) : _reverse(reverse) {
        }

        bool operator()(std::vector<int> const & left, std::vector<int> const & right) {
            assert(COMP_LEN < left.size() && COMP_LEN < right.size());
            if (left[COMP_LEN] > right[COMP_LEN]) {
                return !_reverse;
            }
            return _reverse;

        }
    };

    template<bool reverse, int COMP_LEN = 2>
    static bool CompMinFunc(std::vector<int> const & left, std::vector<int> const & right) {
        assert(COMP_LEN < left.size() && COMP_LEN < right.size());
        if (left[COMP_LEN] > right[COMP_LEN]) {
            return !reverse;
        }
        return reverse;
    }


public:
    std::vector<bool> distanceLimitedPathsExist(int n,
            std::vector<std::vector<int>> edgeList,
            std::vector<std::vector<int>> const & queries) {
        // plagiarizing from https://www.youtube.com/watch?v=P8J1W9xB29Y
        // I can only get the idea of brute force solution
        int const queriesSize = queries.size();
        int const edgeListSize = edgeList.size();
        std::vector<bool> ans(queriesSize);
        if (0 == queriesSize || 0 == edgeListSize) {
            return ans;
        }

        std::sort(edgeList.begin(), edgeList.end(), CompMinFunc<true>); // nlog(n)
        // equals to std::sort(edgeList.begin(), edgeList.end(), CompMinFunc<true, W>); // nlog(n)

        std::vector<std::vector<int>> reMapQueries(queriesSize, std::vector<int>(IDX + 1, 0));
        for (int idx = 0; idx < queriesSize; idx++) { // n
            reMapQueries[idx][X] = queries[idx][X];
            reMapQueries[idx][Y] = queries[idx][Y];
            reMapQueries[idx][W] = queries[idx][W];
            reMapQueries[idx][IDX] = idx;
        }
        CompMin compObj(true); // equals to CompMin<W> compObj(true);
        std::sort(reMapQueries.begin(), reMapQueries.end(), compObj); // nlog(n)

        UnionFind ufObj(n);

        int edgeIdx = 0;
        for (int idx = 0; idx < queriesSize; idx++) {
            while (edgeIdx < edgeListSize && edgeList[edgeIdx][W] < reMapQueries[idx][W]) {
                ufObj.unionAndCntWithRank(edgeList[edgeIdx][X], edgeList[edgeIdx][Y]);
                edgeIdx++;
            }
            ans[reMapQueries[idx][IDX]] = ufObj.find(reMapQueries[idx][X]) == ufObj.find(reMapQueries[idx][Y]);
        }
        return ans;
    }
private:
    static int const X = 0;
    static int const Y = 1;
    static int const W = 2;
    static int const IDX = 3;

};
