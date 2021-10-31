#include "../../head.h"


// #define DEBUG
class SolutionTLE {
public:
    std::vector<int> recoverArray(int n, std::vector<int> sums) {
        // plagiarizing from https://leetcode.com/problems/find-array-given-subset-sums/discuss/1418799/Python-Short-solution-(update)-explained
        // trans from python code to cpp
        if (ONLY_ONE > n) {
            return {};
        }
        int sumsSize = sums.size();
        // firstly, we need check the number of sums is correct.
        assert(sumsSize == (1 << n));
        // secondly, we sort the sums to make it ordered, then we can find the value which is closest to zero easily
        std::sort(std::begin(sums), std::end(sums));
        return dfs(n, sums);
    }
private:
    std::vector<int> dfs(int n, std::vector<int> const & sums) {
        std::vector<int> ans;
        int const sumsSize = sums.size();
        assert(sumsSize == (1 << n));
        std::unordered_map<int, int> cnts;
        for (int sum : sums) {
            cnts[sum]++;
        }

        if (0 == cnts[0]) {
            // sums must contain zero
            return ans;
        }

        if (ONLY_ONE == n && ONLY_ONE <= cnts[0]) {
            ans.emplace_back(*std::max_element(std::begin(sums), std::end(sums), [](int i, int j) {
                // find the max element whose value is not zero.
                return std::abs(i) < std::abs(j);
            }));
            return ans;
        }
        int mostClosestZero = sums[1] - sums[0];
        #ifdef DEBUG:
        std::cout << "mostClosestZero: " << mostClosestZero << '\n';
        #endif

        {
            std::vector<int> newSubSums;
            // firstly, we assume the mostClosestZero value is positive in original array of nums,
            // then we need to find the all sums that excludes mostClosestZero.
            std::unordered_map<int, int> copyCnts(cnts);
            for (int sum : sums) {
                if (0 == copyCnts[sum]) {
                    continue;
                }
                if (0 == copyCnts[sum + mostClosestZero]) {
                    // lack of some necessary sum
                    break;
                }
                copyCnts[sum] -= 1;
                copyCnts[sum + mostClosestZero] -= 1;
                newSubSums.emplace_back(sum);
            }
            #ifdef DEBUG
            std::cout << "positive: ";
            for (int newSubSum : newSubSums) {
                std::cout << newSubSum << ", ";
            }
            std::cout << "\n";
            #endif
            if (newSubSums.size() == (1 << (n - 1))) {
                std::vector<int> nextSubAns = dfs(n - 1, newSubSums);
                nextSubAns.emplace_back(mostClosestZero);
                if (nextSubAns.size() > ans.size()) {
                    std::swap(nextSubAns, ans);
                }
            }
        }

        {
            std::forward_list<int> newSubSums;
            int newSubSumsSize = 0;
            // firstly, we assume the mostClosestZero value is negative in original array of nums,
            // then we need to find the all sums that excludes mostClosestZero.
            mostClosestZero = -mostClosestZero;
            std::unordered_map<int, int> copyCnts(cnts);
            for (std::vector<int>::const_reverse_iterator it = std::crbegin(sums); it != std::crend(sums); it++) {
                int sum = *it;
                if (0 == copyCnts[sum]) {
                    continue;
                }
                if (0 == copyCnts[sum + mostClosestZero]) {
                    // lack of some necessary sum
                    break;
                }
                copyCnts[sum] -= 1;
                copyCnts[sum + mostClosestZero] -= 1;
                newSubSums.emplace_front(sum);
                newSubSumsSize++;
            }
            #ifdef DEBUG
            std::cout << "negative: ";
            for (auto it = newSubSums.begin(); it != newSubSums.end(); it++) {
                std::cout << *it << ", ";
            }
            std::cout << "\n";
            #endif
            if (newSubSumsSize == (1 << (n - 1))) {
                std::vector<int> nextSubAns = dfs(n - 1, std::vector<int>(newSubSums.begin(), newSubSums.end()));
                nextSubAns.emplace_back(mostClosestZero);
                if (nextSubAns.size() > ans.size()) {
                    std::swap(nextSubAns, ans);
                }
            }
        }
        return ans;
    }
private:
    static int const ONLY_ONE = 1;
};