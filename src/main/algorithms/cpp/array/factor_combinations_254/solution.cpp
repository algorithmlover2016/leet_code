#include "../../head.h"


#define TEST_MAIN

#ifndef TEST_SOLUTION_TRAVERSAL_N
#define TEST_SOLUTION_TRAVERSAL_SQRT_N_WITHOUT_REC
#endif

#ifndef TEST_SOLUTION_TRAVERSAL_SQRT_N_WITHOUT_REC
#define TEST_SOLUTION_TRAVERSAL_N
#endif

#ifdef TEST_SOLUTION_TRAVERSAL_SQRT_N_WITHOUT_REC
#undef TEST_SOLUTION_TRAVERSAL_SQRT_N_WITHOUT_REC
#endif
#ifdef TEST_SOLUTION_TRAVERSAL_N
#undef TEST_SOLUTION_TRAVERSAL_N
#endif


#define DEBUG

class Solution {
public:
    std::vector<std::vector<int>> getFactors(int n) {
        // plagiarizing from https://github.com/grandyang/leetcode/issues/254
#ifdef DEBUG
        std::cout << typeid(*this).name() << "->" << __func__ << "call\n";
#endif
        std::vector<std::vector<int>> ans;
        std::vector<int> curAns;
        dfsHelper(n, 2, curAns, ans);
        return ans;
    }
private:
    void dfsHelper(int n, int start, std::vector<int> & curAns, std::vector<std::vector<int>> & ans) {
        if (1 >= start) {
            return;
        }
        if (1 >= n) {
            if (curAns.size() > 1) {
                // skip the situation curAns = {n};
                ans.emplace_back(curAns);
            }
            return;
        }
        for (int idx = start; idx <= n; idx++) {
            if (0 != n % idx) {
                // we should find the factors
                continue;
            }
            curAns.emplace_back(idx);
            // the next factor should not less than idx;
            dfsHelper(n / idx, idx, curAns, ans);
            curAns.pop_back();
        }
    }
};

class SolutionSqrtN {
public:
    std::vector<std::vector<int>> getFactors(int n) {
        // plagiarizing from https://github.com/grandyang/leetcode/issues/254
#ifdef DEBUG
        std::cout << typeid(*this).name() << "->" << __func__ << "call\n";
#endif
        std::vector<std::vector<int>> ans;
        std::vector<int> curAns;
        dfsHelper(n, 2, curAns, ans);
        return ans;
    }
private:
    void dfsHelper(int n, int start, std::vector<int> curAns, std::vector<std::vector<int>> & ans) {
        if (1 >= start) {
            return;
        }
        for (int idx = start; idx * idx <= n; idx++) {
            if (0 != n % idx) {
                // we should find the factors
                continue;
            }
            int quotient = n / idx;
            std::vector<int> nextCurAns(curAns);
            nextCurAns.emplace_back(idx);
            // the next factor should not less than idx; split the quotient into factors appending into the curAns;
            dfsHelper(quotient, idx, nextCurAns, ans);
            nextCurAns.emplace_back(quotient);
            ans.emplace_back(nextCurAns);
        }
    }
};

class SolutionSqrtNRec {
public:
    std::vector<std::vector<int>> getFactors(int n) {
        // plagiarizing from https://github.com/grandyang/leetcode/issues/254
#ifdef DEBUG
        std::cout << typeid(*this).name() << "->" << __func__ << "call\n";
#endif
        std::vector<std::vector<int>> ans;
        for (int start = 2; start * start <= n; start++) {
            if (0 != n % start) {
                continue;
            }
            int quotient = n / start;
            std::vector<int> curAns{start, quotient};
            ans.emplace_back(curAns);
            std::vector<std::vector<int>> quotientAns = getFactors(quotient);
            for (auto & factors : quotientAns) {
                if (!factors.empty() && start <= factors[0]) {
                    factors.insert(factors.begin(), start);
                    ans.emplace_back(factors);
                }
            }
        }
        return ans;
    }
};

#ifdef TEST_MAIN
#define PRINT_TO_SCREEN
int main() {
#ifdef TEST_SOLUTION_TRAVERSAL_N
    Solution obj;
#elif defined(TEST_SOLUTION_TRAVERSAL_SQRT_N_WITHOUT_REC)
    SolutionSqrtN obj;
#else
    SolutionSqrtNRec obj;
#endif

    std::vector<std::vector<int>> ans12 = obj.getFactors(12);
#ifdef PRINT_TO_SCREEN
    for (auto const & v : ans12) {
        for (int const ele : v) {
            std::cout << ele << ", ";
        }
        std::cout << "\n";
    }
#endif

    std::vector<std::vector<int>> ans32 = obj.getFactors(32);
#ifdef PRINT_TO_SCREEN
    for (auto const & v : ans32) {
        for (int const ele : v) {
            std::cout << ele << ", ";
        }
        std::cout << "\n";
    }
#endif

    return 0;
}
#endif
