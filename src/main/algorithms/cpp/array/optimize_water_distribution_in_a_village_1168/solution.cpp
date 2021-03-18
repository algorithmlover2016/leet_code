#include "../../head.h"

// #define DEBUG
#define TEST_MAIN
// #define UNION_WITH_RETURN_BOOL
class Solution {
protected:
    class UnionFind {
    public:
        UnionFind(int n = 0) {
            std::vector<int>(n).swap(parents);
            std::vector<int>(n, 0).swap(cnts);
            std::vector<int>(n, 0).swap(rank);
            std::iota(parents.begin(), parents.end(), 0);
        }
        int find(int target) {
            int root = target;
            while (root != parents[root]) {
                root = parents[root];
            }
            return parents[target] = root;
        }
        bool unionWithCntByRank(int left, int right) {
            int leftRoot = find(left);
            int rightRoot = find(right);
            if (leftRoot == rightRoot) {
                return false;
            }

            if (rank[leftRoot] > rank[rightRoot]) {
                std::swap(leftRoot, rightRoot);
            } else if (rank[leftRoot] == rank[rightRoot]) {
                rank[rightRoot]++;
            }

            // append the left union tree to right union tree. because the rank of right is bigger,
            // this operation will not add rank[rightRoot];
            parents[leftRoot] = rightRoot;
            cnts[rightRoot] += cnts[leftRoot];
            return true;
        }
    private:
        std::vector<int> parents;
        std::vector<int> cnts;
        std::vector<int> rank;
    };

public:
    int minCostToSupplyWater(int n, std::vector<int> const & wells, std::vector<std::vector<int>> const & pipes) {
        // plagairizing idea from https://github.com/azl397985856/leetcode/blob/master/problems/1168.optimize-water-distribution-in-a-village-en.md
        // and https://www.youtube.com/watch?v=hTK-yY44h70
        // and https://leetcode.jp/leetcode-1168-optimize-water-distribution-in-a-village-%e8%a7%a3%e9%a2%98%e6%80%9d%e8%b7%af%e5%88%86%e6%9e%90/
        auto cmp = [] (std::vector<int> const & left, std::vector<int> const & right) {
#ifdef DEBUG
            for (int num : left) {
                std::cout << num << ", ";
            }
            std::cout << "; ";
            for (int num : right) {
                std::cout << num << ", ";
            }
            std::cout << "\n";
#endif
            assert(COST_LEN <= left.size());
            assert(COST_LEN <= right.size());
            return left[COST_IDX] <= right[COST_IDX];
        };
        // we can look the wells as a pipes cost from well to house, the well is marked as zero
        int const wellsSize = wells.size();
        int const pipesSize = pipes.size();
        int const allPipesSize = wellsSize + pipesSize;
        UnionFind unionObj(allPipesSize + 1);

        std::vector<std::vector<int>> allPipes(allPipesSize);
        int idx = 0;
        for (; idx < wellsSize; idx++) {
            allPipes[idx] = std::vector<int>{{0, idx + 1, wells[idx]}};
        }
        for (auto const & pipe : pipes) {
            if (pipe.size() < COST_LEN) {
                continue;
            }
            allPipes[idx++] = pipe;
        }
        std::sort(allPipes.begin(), allPipes.end(), cmp);
        int ans = 0;
        for (auto const & pipe : allPipes) {
            if (pipe.size() < COST_LEN) {
                continue;
            }
#ifndef UNION_WITH_RETURN_BOOL
            int firstRoot = unionObj.find(pipe[FIRST_HOUSE_IDX]);
            int secondRoot = unionObj.find(pipe[SECOND_HOUSE_IDX]);
            if (firstRoot == secondRoot) {
                // the two houses have benn connected by smaller cost.
                continue;
            }
            unionObj.unionWithCntByRank(firstRoot, secondRoot);
#else
            if (!unionObj.unionWithCntByRank(pipe[FIRST_HOUSE_IDX], pipe[SECOND_HOUSE_IDX])) {
                continue;
            }
#endif
            ans += pipe[COST_IDX];
            // there are n houses and a dummy node marked as zero.
            // if we union n times, we will union n + 1 node. so we can return
            if (--n == 0) {
                break;
            }
        }
        return ans;
    }
private:
    static int const COST_LEN = 3;
    static int const FIRST_HOUSE_IDX = 0;
    static int const SECOND_HOUSE_IDX = 1;
    static int const COST_IDX = 2;
};

#ifdef TEST_MAIN
#define PRINT_TO_SCREEN
int main() {
    std::vector<int> wells{{1, 2, 2}};
    std::vector<std::vector<int>> pipes{{{1, 2, 1}, {2, 3, 1}}};
    Solution obj;
    int ans = obj.minCostToSupplyWater(wells.size(), wells, pipes);
#ifdef PRINT_TO_SCREEN
    std::cout << ans << "\n";
#endif
    assert(ans == 3);
    std::cout << "TEST SUCCESSFULLY" << std::endl;
}
#endif

