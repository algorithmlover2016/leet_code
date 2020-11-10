#include "../../head.h"


class SolutionWrongAnswer {
public:
    int mergeStones(std::vector<int> const & stones, int K) {
        return backTracking(stones, K);

    }
    int backTracking(std::vector<int> const & stones, int K) {
        if (2 > stones.size()) {
            return 0;
        }
        if (K > stones.size()) {
            return -1;
        }

        std::vector<int> sums(stones.size() + 1, 0);
        int mergeSum = INT_MAX;
        for (int index = 1; index < sums.size(); index++) {
            sums[index] = sums[index - 1] + stones[index - 1];
            if (index >= K) {
                int sum = sums[index] - sums[index - K];
                if (mergeSum > sum) {
                    mergeSum = sum;
                }
            }
        }
        // std::cout << "mergeSum: " << mergeSum << "\n";

        int ans = INT_MAX;
        for (int index = 0; index + K < sums.size(); index++) {
            int sum = sums[index + K] - sums[index];
            if (mergeSum == sum) {
                std::vector<int> mergeStones(stones.size() - K + 1, 0);
                for (int inner = 0; inner < index; inner++) {
                    mergeStones[inner] = stones[inner];
                }
                mergeStones[index] = mergeSum;
                for (int inner = index + 1; inner < mergeStones.size(); inner++) {
                    mergeStones[inner] = stones[inner + K - 1];
                }
                /*
                std::cout << "ele: " << "\n";
                for (int ele : mergeStones) {
                    std::cout  << ele << "\t";
                }
                std::cout << "\n";
                */
                int next = backTracking(mergeStones, K);
                if (-1 != next) {
                    ans = std::min(ans, mergeSum + next);
                }
            }
        }
        return INT_MAX == ans ? -1 : ans;
    }
};

class SolutionTLE {
public:
    // plagiarizing from https://leetcode.com/problems/minimum-cost-to-merge-stones/discuss/247567/JavaC%2B%2BPython-DP
    // dp 3-D
    int mergeStones(std::vector<int> const & stones, int K) {
        int const stonesSize = stones.size();
        std::vector<int> sums(stonesSize + 1, 0);
        for (int index = 0; index < stones.size(); index++) {
            sums[index + 1] = sums[index] + stones[index];
        }
        int ans = dp(stones, sums, 0, stonesSize, 1, K);
        return INT_MAX == ans ? -1 : ans;
    }


    // [start, end)
    // from start to end(exclude), there are (end - start) elements, if they can be merged successed into miles piles
    // there should be a relationship that end - start - I(K - 1) = miles, I is integer from 0 to some bigger one

    // return INT_MAX means can't find the solution
    int dp(std::vector<int> const & stones,
            std::vector<int> const & sums,
            int start, int end, int miles, int const MK) {
        // because K >= 2, so there is no need to test K - 1 == 0
        if ((end - start - miles) % (MK - 1)) {
            return INT_MAX;
        }
        if (start + 1 == end) {
            return miles == 1 ? 0 : INT_MAX;
        }
        if (1 == miles) {
            return dp(stones, sums, start, end, MK, MK) + sums[end] - sums[start];
        }
        int ans = INT_MAX;
        for (int mid = start + 1; mid < end; mid += MK - 1) {
            int leftAns = dp(stones, sums, start, mid, 1, MK);
            if (INT_MAX == leftAns) {
                continue;
            }
            int rightAns = dp(stones, sums, mid, end, miles - 1, MK);
            if (INT_MAX == rightAns) {
                continue;
            }
            ans = std::min(ans, leftAns + rightAns);
        }
        return ans;


    }
};

class SolutionMemorization {
public:
    // plagiarizing from https://leetcode.com/problems/minimum-cost-to-merge-stones/discuss/247567/JavaC%2B%2BPython-DP
    // dp 3-D
    int mergeStones(std::vector<int> const & stones, int K) {
        int const stonesSize = stones.size();
        std::vector<int> sums(stonesSize + 1, 0);
        for (int index = 0; index < stones.size(); index++) {
            sums[index + 1] = sums[index] + stones[index];
        }
        std::vector<std::vector<std::vector<int>>> memo(stonesSize,
                                                        std::vector<std::vector<int>>(stonesSize + 1,
                                                                         std::vector<int>(K + 1, -1)));

        int ans = dp(stones, sums, memo, 0, stonesSize, 1, K);
        return INT_MAX == ans ? -1 : ans;
    }


    // [start, end)
    // from start to end(exclude), there are (end - start) elements, if they can be merged successed into miles piles
    // there should be a relationship that end - start - I(K - 1) = miles, I is integer from 0 to some bigger one

    // return INT_MAX means can't find the solution
    int dp(std::vector<int> const & stones,
            std::vector<int> const & sums,
            std::vector<std::vector<std::vector<int>>> & memo,
            int start, int end, int miles, int const MK) {
        if (-1 != memo[start][end][miles]) {
            return memo[start][end][miles];
        }

        int ans = INT_MAX;
        // because K >= 2, so there is no need to test K - 1 == 0
        if ((end - start - miles) % (MK - 1)) {
            ans = INT_MAX;
        } else if (start + 1 == end) {
            ans = 1 == miles ? 0 : INT_MAX;
        } else  if (1 == miles) {
            ans =  dp(stones, sums, memo, start, end, MK, MK) + sums[end] - sums[start];
        } else {
            for (int mid = start + 1; mid < end; mid += MK - 1) {
                int leftAns = dp(stones, sums, memo, start, mid, 1, MK);
                if (INT_MAX == leftAns) {
                    continue;
                }
                int rightAns = dp(stones, sums, memo, mid, end, miles - 1, MK);
                if (INT_MAX == rightAns) {
                    continue;
                }
                ans = std::min(ans, leftAns + rightAns);
            }

        }
        memo[start][end][miles] = ans;
        return ans;
    }
};

class SolutionDP2D {
public:
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
