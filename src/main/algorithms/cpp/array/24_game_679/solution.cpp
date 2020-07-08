#include "../../head.h"


class SolutionBruteFS {
public:
    bool judgePoint24(std::vector<int> const & nums) {
        // plagiarizing from https://leetcode.com/problems/24-game/discuss/107673/JAVA-Easy-to-understand.-Backtracking.
        std::list<double> arr(nums.begin(), nums.end());
        return dfsHelper(arr);
    }
private:
    bool dfsHelper(std::list<double> arr) {
        if (arr.empty()) {
            return false;
        }
        if (1 == arr.size()) {
            return std::abs(arr.front() - TARGET) < eps;
        }
        // std::cout << "\n";
        for (std::list<double>::iterator it = arr.begin(); it != arr.end(); it++) {
            // std::cout << "\n";
            for (std::list<double>::iterator innerIt = arr.begin(); innerIt != it; innerIt++) {
                double fast = *it;
                double slow = *innerIt;
                // std::cout << "fast, slow: " << fast << "\t" << slow << '\t';
                std::list<double> next;
                next.emplace_back(fast + slow);
                next.emplace_back(fast - slow);
                next.emplace_back(slow - fast);
                next.emplace_back(fast * slow);
                if (std::abs(fast) > eps) {
                    next.emplace_back(slow / fast);
                }
                if (std::abs(slow) > eps) {
                    next.emplace_back(fast / slow);
                }
                it = arr.erase(it);
                innerIt = arr.erase(innerIt);
                for (double const ne : next) {
                    arr.emplace_back(ne);
                    // std::cout << "add: " << ne << "\t";
                    if (dfsHelper(arr)) {
                        return true;
                    }
                    // std::cout << "pop_back: " << arr.back() << "\t";
                    arr.pop_back();
                }
                innerIt = arr.emplace(innerIt, slow);
                it = arr.emplace(it, fast);
                // std::cout << "insert: " << *it << "\t" << *innerIt << "\t" << "size: " << arr.size() << "\t";
            }
        }
        return false;
    }
    private:
    static int const TARGET = 24;
    static double const eps;
};

double const SolutionBruteFS::eps = 0.00001;

class Solution {
public:
    bool judgePoint24(std::vector<int> & nums) {
        // plagiarizing from https://leetcode.com/problems/24-game/discuss/107678/C%2B%2B-Concise-code
        // first get The first such-sorted possible permutation
        // (the one that would compare lexicographically smaller to all other permutations) is
        // the one which has all its elements sorted in ascending order,
        // and the largest has all its elements sorted in descending order.
        std::sort(nums.begin(), nums.end());
        do {
            if (valid(nums)) return true;
        } while(std::next_permutation(nums.begin(), nums.end()));
        return false;
    }
private:
    bool valid(std::vector<int> const & nums) {
        if (AT_LEAST_NUMS_SIZE > nums.size()) {
            return false;
        }
        double const a = nums[0], b = nums[1], c = nums[2], d = nums[3];
        if (valid(a+b, c, d) || valid(a-b, c, d) || valid(a*b, c, d) || valid(a/b, c, d)) return true;
        if (valid(a, b+c, d) || valid(a, b-c, d) || valid(a, b*c, d) || valid(a, b/c, d)) return true;
        if (valid(a, b, c+d) || valid(a, b, c-d) || valid(a, b, c*d) || valid(a, b, c/d)) return true;
        return false;
    }
    bool valid(double const a, double const b, double const c) {
        if (valid(a+b, c) || valid(a-b, c) || valid(a*b, c) || (b && valid(a/b, c))) {
            return true;
        }
        if (valid(a, b+c) || valid(a, b-c) || valid(a, b*c) || (c && valid(a, b/c))) {
            return true;
        }
        return false;
    }
    bool valid(double const a, double const b) {
        if (std::abs(a + b-TARGET) < eps ||
                std::abs(a - b - TARGET) < eps ||
                std::abs(a * b - TARGET) < eps ||
                (b && std::abs(a / b-TARGET) < eps)) {
            return true;
        }
        return false;
    }

private:
    static double const eps;
    static int const TARGET = 24;
    static int const AT_LEAST_NUMS_SIZE = 4;
};
double const Solution::eps = 0.00001;
