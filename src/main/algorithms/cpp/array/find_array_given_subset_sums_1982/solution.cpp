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

// #define DEBUG
class Solution {
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
        int minVal = *std::min_element(std::begin(sums), std::end(sums));
        for (int & sum : sums) {
            // add an offset for all the sums to make the min sums will be zero
            sum -= minVal;
        }
        #ifdef DEBUG
        std::cout << "sums: ";
        for (int sum : sums) {
            std::cout << sum << ", ";
        }
        std::cout << "\n";
        #endif


        std::multiset<int> pre(std::begin(sums), std::end(sums)), cur;
        std::vector<int> ans;
        for (int idx = 0; idx < n; idx++) {
            int num = *std::next(std::begin(pre)); // the second small sum must be a element which is the closest to zero
            ans.emplace_back(num);
            #ifdef DEBUG
            std::cout << "cur num: " << num;
            #endif
            // remove all the sum which contains num;
            while(pre.size()) {
                // first we get the minimum val and then we remove the two sum of it and it + num;
                auto first = pre.begin();
                int firstVal = *first;
                cur.insert(firstVal);
                pre.erase(first);
                pre.erase(pre.find(firstVal + num));
            }
            std::swap(pre, cur);
            #ifdef DEBUG
            std::cout << "\n";
            #endif
        }
        #ifdef DEBUG
        std::cout << "ans: ";
        for (int num : ans) {
            std::cout << num << ", ";
        }
        std::cout << '\n';
        #endif
        if (dfs(ans, -minVal, 0)) {
            return ans;
        } else {
            return {};
        }
    }
private:
    bool dfs(std::vector<int> & nums, int target, int idx) {
        int const numsSize = nums.size();
        if (idx == numsSize) {
            return 0 == target;
        }
        int curVal = nums[idx];
        // if we do not take the curVal as a part of target
        if (dfs(nums, target, idx + 1)) {
            return true;
        }

        // if we use the element, we need change it to negative
        nums[idx] = -curVal;
        if (dfs(nums, target - curVal, idx + 1)) {
            return true;
        }
        // if there is no answer, we should keep the same unchanged
        nums[idx] = curVal;
        return false;

    }
private:
    static int const ONLY_ONE = 1;
};


int speedup = [] { std::ios::sync_with_stdio(0); std::cin.tie(0); return 0; } ();

class Solution {
private:
    unsigned short cnts[20001], cntb[20001], cur[20001];
private:
    inline int partition(std::vector<int> &v, int p, int i, int target) {
        if (target <= 0) return target == 0 ? p : -1;
        for (; i < v.size(); ++i) {
            std::swap(v[p], v[i]);
            int r = partition(v, p+1, i+1, target - v[p]);
            if (r >= 0)  {
                return r;
            }
            std::swap(v[p], v[i]);
        }
        return -1;
    }

public:
    std::vector<int> recoverArray(int n, std::vector<int>& sums) {
        std::vector<int> res; res.reserve(n);
        std::sort(std::begin(sums), std::end(sums));
        int base = sums[0], sz = sums.back() - base + 1, cp = 0;
        std::fill(cnts, cnts+sz, 0);
        cur[cp++] = 0; ++cnts[0];
        
        for (int i = 1, prev = 0, cnt = 1; i < std::size(sums); ++i) {
            unsigned short v = sums[i] - base;
            if (v == prev) {
                ++cnt;
             } else {
                 prev = v, cnt = 1;
             }
            if (cnts[v] >= cnt) {
                continue;
            }
            res.push_back(v);
            
            for (int j = 0; j < cp; ++j) {
                cntb[j] = cnts[cur[j]];
            }
            for (int j = 0, je = cp; j < je; ++j) {
                unsigned short vv = cur[j] + v;
                if (!cnts[vv]) {
                    cur[cp++] = vv;
                }
                cnts[vv] += cntb[j];
            }
        }
        int pos = partition(res, 0, 0, -base);
        for (int i = 0; i < pos; ++i) {
            res[i] = -res[i];
        }
        return res;
    }
};