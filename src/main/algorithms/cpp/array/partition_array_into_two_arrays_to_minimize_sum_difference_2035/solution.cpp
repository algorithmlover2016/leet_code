#include "../../head.h"


// #define DEBUG
class Solution {
public:
    int minimumDifference(std::vector<int> const & nums) {
        // plagiarizing from https://leetcode.com/problems/partition-array-into-two-arrays-to-minimize-sum-difference/discuss/1515202/Replace-up-to-n-2-elements
        int numsSize = nums.size();
        int halfLen = numsSize / HALF, quarterLen = numsSize / QUARTER;

        // if we split the array into two parts each size of which is halfLen, then we can only adjust quarterLen elements in one part
        std::vector<std::vector<int>> qLeft(quarterLen + 1), qRight(quarterLen + 1);
        // exchange costs
        dfs(nums, 0, halfLen, 0, 0, qLeft);
        dfs(nums, halfLen, numsSize, 0, 0, qRight);

        long sumLeft = std::accumulate(std::begin(nums), std::begin(nums) + halfLen, 0L);
        long sumRight = std::accumulate(std::begin(nums) + halfLen, std::end(nums), 0L);
        long average = (sumLeft + sumRight) / 2;
        #ifdef DEBUG
        std::cout << "sumLeft: " << sumLeft << ", sumRight: " << sumRight << ", average: " << average << "\n";
        #endif
        int ans = INT_MAX;
        for (int exchangeNum = 0; exchangeNum < qRight.size(); exchangeNum++) {
            std::sort(std::begin(qRight[exchangeNum]), std::end(qRight[exchangeNum]));
            for (int leftTargetSum : qLeft[exchangeNum]) {
                // this will compute how close between the left part and mid, which will make the difference to be zero
                int compliment = average - (sumLeft - leftTargetSum);

                // leftTargetSum will be move to the right part
                int diff = (sumLeft - leftTargetSum) - sumRight - leftTargetSum;
                
                int idx = std::upper_bound(std::begin(qRight[exchangeNum]), std::end(qRight[exchangeNum]), compliment) - std::begin(qRight[exchangeNum]);
                #ifdef DEBUG
                std::cout << "need compliment: " << compliment << ", difference: " << diff << ", idx: " << idx << "\n";
                std::cout << qRight[exchangeNum].size() << "\n";
                #endif
                // then we need move the same number of elements into the left part, and we choose the target which is mostly close the compliment to make the diff be zero
                if (idx < qRight[exchangeNum].size()) {
                    ans = std::min(ans, std::abs(diff + qRight[exchangeNum][idx] * 2));
                }
                if (idx > 0) {
                    ans = std::min(ans, std::abs(diff + qRight[exchangeNum][idx - 1] * 2));
                }
            }
        }
        return ans;

    }
private:
    void dfs(std::vector<int> const & nums, int start, int end, int k, int sum, std::vector<std::vector<int>> & sums) {
        int numsSize = nums.size();
        int quarterLen = numsSize / QUARTER;
        if (start == end || k >= quarterLen) {
            sums[k].emplace_back(sum);
        } else {
            // if we do not take this element into target exchange array
            dfs(nums, start + 1, end, k, sum, sums);

            // if we do take this element into target exchange array
            dfs(nums, start + 1, end, k + 1, sum + nums[start], sums);
        }
    }
private:
    static int const QUARTER = 4;
    static int const HALF = 2;
};

// #define DEBUG
class Solution {
public:
    int minimumDifference(std::vector<int> const & nums) {
        // plagiarizing from https://leetcode.com/problems/partition-array-into-two-arrays-to-minimize-sum-difference/discuss/1513298/C%2B%2B-Meet-In-Middle
        int n = nums.size(), res = 0, sum = 0;
        sum = std::accumulate(nums.begin(), nums.end(),0);

        int N = n/2;
        std::vector<std::vector<int>> left(N + 1), right(N + 1);

                //storing all possible sum in left and right part
        for (int mask = 0; mask < (1 << N); ++mask) {
            int sz = 0, l = 0, r = 0;
            for (int i = 0; i < N; ++i) {
                if (mask & (1 << i)) {
                    sz ++;
                    l += nums[i];
                    r += nums[i + N];
                }
            }
            left[sz].push_back(l);
            right[sz].push_back(r);
        }

        for (int sz = 0; sz <= N; ++sz) {
            std::sort(right[sz].begin(), right[sz].end());
        }

        #ifdef DEBUG
        std::cout << "left, right size: " << left[N].size() << ", " << right[N].size() << "\n";
        #endif
        // res = std::min(std::abs(sum - 2 * left[N][0]), std::abs(sum - 2 * right[N][0]));
        // left[N] and right[N] means select all the left and right part elements seperately, and the size is one.
        // assume sum = a + b, a means choosing the first N elements as left part and b means the right part.
        // sum - 2 * left[N][0] = a + b - 2 * a = b - a
        // sum - 2 * right[N][0] = a + b - 2 * b = a - b
        res = std::abs(sum - 2 * left[N][0]);

        //iterating over left part
        for (int sz = 1; sz < N; ++sz) {
            for (auto & a : left[sz]) {
                int b = (sum - 2 * a) / 2 /* same to (sum / 2 - a) */, rsz = N - sz;
                auto & v = right[rsz];
                auto itr = std::lower_bound(v.begin(), v.end(), b); // binary search over right part

                if(itr != v.end()) {
                    res = std::min(res, std::abs(sum- 2 * (a + (*itr))));
                }
                if(itr != v.begin()) {
                    res = std::min(res, std::abs(sum - 2 * (a + (*(--itr)))));
                }
            }
        }
        return res;
    }
};