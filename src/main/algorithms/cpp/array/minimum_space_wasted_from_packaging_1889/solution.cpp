#include "../../head.h"


// #define DEBUG
class SolutionTLE {
public:
    int minWastedSpace(std::vector<int> & packages, std::vector<std::vector<int>> & boxes) {
        // idea from mine.
        // sorted the packages and each boxes supplier and use upper_bound to find the first one that not less than the package
        // time: O(sort(packages) + sort(box) for each box in boxes + package.size() * log(box.size()))
        // space: O(packages) + O(boxes) + O(1)
        std::sort(std::begin(packages), std::end(packages));
        #ifdef DEBUG
        print(packages);
        #endif
        
        int ans = INT_MAX;
        for (auto & box : boxes) {
            std::sort(std::begin(box), std::end(box));
            #ifdef DEBUG
            print(box);
            #endif
            int curAns = findWaste(packages, box);
            if (INVALID_RET != curAns && curAns < ans) {
                ans = curAns;
            }
        }
        return (INT_MAX == ans) ? INVALID_RET : ans;
    }
private:
    int findWaste(std::vector<int> const & packages, std::vector<int> const & box) {
        if (packages.empty()) {
            return 0;
        }
        if (box.empty() || (packages.back() > box.back())) {
            return INVALID_RET;
        }
        int ans = 0;
        for (int package : packages) {
            auto const & it = std::lower_bound(std::begin(box), std::end(box), package);
            ans += (*it - package);
            ans %= MOD;
        }
        return ans;
    }
#ifdef DEBUG
private:    
    void print(std::vector<int> const & eles) {
        for (auto ele : eles) {
            std::cout << ele << "\t";
        }
        std::cout << "\n";
    }
    
#endif
private:
    int const MOD = 1e9 + 7;
    int const INVALID_RET = -1;
};

class Solution {
public:
    int minWastedSpace(std::vector<int> & packages, std::vector<std::vector<int>> & boxes) {
        // plagiarizing from https://leetcode.com/problems/minimum-space-wasted-from-packaging/discuss/1254116/JavaC%2B%2BPython-Binary-Search-should-not-use-prefix-sum
        if (packages.empty()) {
            return 0;
        }
        std::sort(std::begin(packages), std::end(packages));
        long long int pSum = 0;
        pSum = std::accumulate(std::begin(packages), std::end(packages), pSum);
        // pSum = std::accumulate(std::begin(packages), std::end(packages), 0LL);
        long long int ans = LONG_MAX;
        for (auto & box : boxes) {
            if (box.empty()) {
                continue;
            }
            std::sort(std::begin(box), std::end(box));
            if (box.back() < packages.back()) {
                continue;
            }
            long long int curAns = 0, leftIdx = 0, rightIdx = 0;
            for (auto & ele : box) {
                int rightIdx = std::upper_bound(packages.begin() + leftIdx, packages.end(), ele) - packages.begin();
                curAns += (rightIdx - leftIdx) * ele;
                leftIdx = rightIdx;
            }
            ans = std::min(ans, curAns);
        }
        return LONG_MAX > ans ? (ans - pSum) % MOD : -1;

    }
private:
    int const MOD = 1e9 + 7;
};