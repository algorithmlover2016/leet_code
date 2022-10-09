#include "../../head.h"


// #define DEBUG
class SolutionTLE {
public:
    int minOperations(std::vector<int> const & nums, std::vector<int> const & numsDivide) {
        if (nums.empty() || numsDivide.empty()) {
            return -1;
        }
        int smallest = INIT_MAX, secSmall = smallest;
        for (int idx = 0; idx < numsDivide.size(); idx++) {
            if (numsDivide[idx] < smallest) {
                #ifdef DEBUG
                std::cout << "make one exchange at " << idx << ", ";
                #endif
                secSmall = smallest;
                smallest = numsDivide[idx];
            } else if (numsDivide[idx] > smallest && numsDivide[idx] < secSmall) {
                #ifdef DEBUG
                std::cout << "make sec exchange at " << idx << ", ";
                #endif
                secSmall = numsDivide[idx];
            }
        }
        #ifdef DEBUG
        std::cout << "\n";
        #endif
        if (secSmall == INIT_MAX) {
            secSmall = smallest;
        }
        #ifdef DEBUG
        std::cout << "INT_MAX: " << INIT_MAX << ", smallest: " << smallest << ", secSmall: " << secSmall << "\n";
        #endif
        int maxNum = *std::max_element(std::begin(nums), std::end(nums));
        #ifdef DEBUG
        std::cout << "maxNum: " << maxNum << "\n";
        #endif
        std::set<int> facs = factors(smallest, secSmall, maxNum);
        facs.insert(1);
        for (int idx = 0; idx < numsDivide.size(); idx++) {
            if (numsDivide[idx] == smallest || numsDivide[idx] == secSmall) {
                continue;
            }
            getCommonDivide(numsDivide[idx], facs);
        }
        #ifdef DEBUG
        std::cout << "facs\n";
        for (auto it = facs.begin(); it != facs.end(); it++) {
            std::cout << *it << ", ";
        }
        std::cout << "\n";
        
        #endif

        std::set<int> numsSet(nums.begin(), nums.end());
        int minFac = INIT_MAX;
        for (auto it = facs.begin(); it != facs.end(); it++) {
            if (numsSet.find(*it) != numsSet.end()) {
                minFac = *it;
                break;
            }
        }
        if (minFac != INIT_MAX) {
            int ans = 0;
            for (int num : nums) {
                if (num < minFac) {
                    ans++;
                }
            }
            return ans;

        };
        return -1;
    }
private:

    std::set<int> factors(int left, int right, int maxNum = INIT_MAX) {
        std::set<int> ans;
        if (left > right) {
            std::swap(left, right);
        }
        maxNum = std::min(left, std::min(right / 2, maxNum));
        for (int factor = 2; factor <= maxNum; factor++) {
            if (0 == left % factor && 0 == right % factor) {
                ans.insert(factor);
            }
        }
        return ans;
    }

    void getCommonDivide(int num, std::set<int> & facs) {
        if (facs.empty()) {
            return;
        }
        for (auto it = facs.begin(); it != facs.end();) {
            if (0 != num % (*it)) {
                facs.erase(it++);
            } else {
                it++;
            }
        }
    }
private:
    int constexpr static INIT_MAX = INT_MAX;
};

#define USE_SORT
class Solution {
public:
    int minOperations(std::vector<int> & nums, std::vector<int> const & numsDivide) {
        // plggiarizing from https://leetcode.com/problems/minimum-deletions-to-make-array-divisible/solutions/2292651/java-c-python-gcd-o-n-m-log/
        // and https://leetcode.com/problems/minimum-deletions-to-make-array-divisible/solutions/2292612/gcd/
        if (nums.empty() || numsDivide.empty()) {
            return -1;
        }
        int gcdNum = std::reduce(std::begin(numsDivide), std::end(numsDivide), numsDivide[0], [&](int a, int b) {return std::gcd(a, b);});
        #ifdef USE_SORT
        std::sort(nums.begin(), nums.end());
        for (int idx = 0; idx < nums.size() && nums[idx] <= gcdNum; idx++) {
            if (0 == gcdNum % nums[idx]) {
                return idx;
            }
        }
        return -1;
        #else
        int minNum = INIT_MAX;
        for (int num : nums) {
            minNum = std::min(minNum, 0 == gcdNum % num ? num : minNum);
        }
        return INIT_MAX == minNum ? -1 : std::count_if(std::begin(nums), std::end(nums), [&](int a) {return a < minNum;});

        #endif
    }
#ifndef USE_SORT
private:
    int constexpr static INIT_MAX = INT_MAX;
#endif
};