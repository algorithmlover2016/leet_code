#include "../../head.h"


// #define DEBUG
class SolutionWrong {
private:
    template<class T, bool reverse = false>
    class CompMin {
    public:
        bool operator()(T const & left, T const & right) {
            if (left <= right) {
                return !reverse;
            } else {
                return reverse;
            }
        }
    };
public:
    int minCost(int n, std::vector<int> cuts) {
        // plagiarizing from https://youtu.be/aN8ND52Wjac 39:03
        std::sort(cuts.begin(), cuts.end());
        cuts.emplace_back(n);
        int const cutsSize = cuts.size();

        int preCut = 0;
        std::vector<int> diffs(cutsSize);

        for (int idx = 0; idx < cutsSize; idx++) {
            diffs[idx] = cuts[idx] - preCut;
            #ifdef DEBUG
            std::cout << diffs[idx] << "\t";
            #endif
            preCut = cuts[idx];
        }

        CompMin<int, true> compObj;

        std::make_heap(diffs.begin(), diffs.end(), compObj);
        
        int ans = 0;
        while (1 < diffs.size()) {
            int smallest = diffs.front();
            std::pop_heap(diffs.begin(), diffs.end(), compObj); diffs.pop_back();
            int smaller = diffs.front();
            std::pop_heap(diffs.begin(), diffs.end(), compObj); diffs.pop_back();
#ifdef DEBUG
            std::cout << "smallest, smaller: " << smallest << ",\t" << smaller << "\n";
#endif
            ans += smaller + smallest;

            diffs.emplace_back(smaller + smallest);
            std::push_heap(diffs.begin(), diffs.end(), compObj);
        }
        return ans;
    }
};
// #define DEBUG
class Solution {
public:
    int minCost(int n, std::vector<int> cuts) {
        // plagiarizing from https://youtu.be/aN8ND52Wjac 39:03
        std::sort(cuts.begin(), cuts.end());
        cuts.emplace_back(n);
        int const cutsSize = cuts.size();

        int preCut = 0;
        std::vector<int> diffs(cutsSize);

        for (int idx = 0; idx < cutsSize; idx++) {
            diffs[idx] = cuts[idx] - preCut;
            #ifdef DEBUG
            std::cout << diffs[idx] << "\t";
            #endif
            preCut = cuts[idx];
        }
        return mergeStones(diffs, 2);
    }

private:

    int mergeStones(std::vector<int> const & stones, int K) {
        // plagiarizing from https://leetcode.com/problems/minimum-cost-to-merge-stones/discuss/247567/JavaC%2B%2BPython-DP
        int const stonesSize = stones.size();

        /*
           if there is a successful result, there will be a equation that
           stonesSize - I(K - 1) = 1
           which menas each merging will disapear K - 1 elements, and after finite merging, there will be only one left
           */
        if ((stonesSize - 1) % (K - 1)) {
            return -1;
        }

        // compute the first n elements sums
        std::vector<int> preSums(stonesSize + 1, 0);
        for (int index = 0; index < stonesSize; index++) {
            preSums[index + 1] = preSums[index] + stones[index];
            // std::cout << preSums[index + 1] << "\t";
        }
        // std::cout << "\n";

        // dpMemo[i][j] means after enough merging, the minimun cost. Include i, exclude j;
        // at beginning, must init to zero. j - i < K then dpMemo[i][j] = 0(can't merge)
        std::vector<std::vector<int>> dpMemo(stonesSize, std::vector<int>(stonesSize + 1, 0));
        for (int miles = K; miles <= stonesSize; miles++) {
            for (int start = 0; start + miles <= stonesSize; start++) {
                int end = start + miles;
                // std::cout << "start, miles, end: " << start << "\t" << miles << "\t" << end << "\n";
                dpMemo[start][end] = INT_MAX;
                for (int mid = start + 1; mid < end; mid += K - 1) {
                    // dpMemo[start][mid] means from start to mid there will be merge to one pile (exclude mid)
                    dpMemo[start][end] = std::min(dpMemo[start][end], dpMemo[start][mid] + dpMemo[mid][end]);
                }
                if (0 == (end - start - 1) % (K - 1)) {
                // can't use the judgement that (1 == (end - start) % (K - 1))
                    dpMemo[start][end] += preSums[end] - preSums[start];
                }
                // std::cout << "dpMemo: " << dpMemo[start][end] << "\n";
            }
        }
        return dpMemo[0][stonesSize];
    }
};

int main() {

    SolutionWrong wrongObj;
    Solution correctObj;
    
    std::vector<int> cuts{{1, 3, 4, 5}};
    int n = 7;
    std::cout << "wrongAnswer: " << wrongObj.minCost(n, cuts) << "\n";
    std::cout << "correctAnswer: " << correctObj.minCost(n, cuts) << "\n";

}
