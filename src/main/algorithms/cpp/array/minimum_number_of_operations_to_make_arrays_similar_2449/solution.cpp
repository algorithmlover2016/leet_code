#include "../../head.h"


#define DEBUG
class SolutionWrong {
    // did not differ the odds and evens
public:
    long long makeSimilar(std::vector<int> & nums, std::vector<int> & target) {
        #ifdef DEBUG
        std::cout << "nums.size: " << nums.size() << ", target.size: " << target.size() << "\n";
        #endif
        std::sort(std::begin(nums), std::end(nums));
        #ifdef DEBUG
        printArray(nums);
        #endif
        
        std::sort(std::begin(target), std::end(target));
        #ifdef DEBUG
        printArray(target);
        #endif
        #ifdef DEBUG
        std::cout << "sorted two arrays\n";
        #endif
        long long ans = 0;
        assert(nums.size() == target.size());
        for (int idx = 0; idx < nums.size(); idx++) {
            if (nums[idx] > target[idx]) {
                #ifdef DEBUG
                std::cout << "bigger at " << idx << ",\t and add " << (nums[idx] + 1 - target[idx]) / 2 << "\n";
                #endif
                ans += (nums[idx] + 1 - target[idx]) / 2;
            }
        }
        #ifdef DEBUG
        std::cout << "\n";
        #endif

        return ans;

        
    }
private:
    void printArray(std::vector<int> const & nums) {
        for_each(std::begin(nums), std::end(nums), [](int num) {std::cout << num << "\t";});
        std::cout << "\n";
    }
};

#define USE_ON_MEMORY
class Solution {
    // did not differ the odds and evens. Odd will match odd and even always match even
public:
    long long makeSimilar(std::vector<int> & nums, std::vector<int> & target) {
        // plagiarizing from https://leetcode.com/problems/minimum-number-of-operations-to-make-arrays-similar/solutions/2734189/c-python-sort-odds-and-evens/
        // and https://leetcode.com/problems/minimum-number-of-operations-to-make-arrays-similar/solutions/2734080/odd-even-pointers/
        assert(nums.size() == target.size());
        long long ans = 0;
        #ifdef USE_ON_MEMORY
        std::vector<std::vector<int>> numsSplits(2), targetSplits(2);
        splitByOddAndEven(nums, numsSplits);
        splitByOddAndEven(target, targetSplits);
        std::sort(std::begin(numsSplits[0]), std::end(numsSplits[0])); // the even parts from nums
        std::sort(std::begin(numsSplits[1]), std::end(numsSplits[1])); // the odd parts from nums
        std::sort(std::begin(targetSplits[0]), std::end(targetSplits[0])); // the even parts from target
        std::sort(std::begin(targetSplits[1]), std::end(targetSplits[1])); // the odd parts from target
        for (int idx = 0; idx < numsSplits.size(); idx++)  {
            countDiff(numsSplits[idx], targetSplits[idx], ans);
        }
        #else
        std::sort(std::begin(nums), std::end(nums));
        std::sort(std::begin(target), std::end(target));
        for (int idx = 0, tOdd = 0, tEven = 0; idx < nums.size(); idx++) {
            int & tCur = (nums[idx] % 2 ? tOdd : tEven);
            while (nums[idx] % 2 != target[tCur] % 2) {
                tCur++; // find the first ele that have the same odd or even property
            }
            ans += std::abs(nums[idx] - target[tCur++]) / 2;
        }
        #endif
        return ans / 2; // each time we add and minus 2 at the same time;
    }
private:
    void printArray(std::vector<int> const & nums) {
        for_each(std::begin(nums), std::end(nums), [](int num) {std::cout << num << "\t";});
        std::cout << "\n";
    }
    #ifdef USE_ON_MEMORY
    void splitByOddAndEven(std::vector<int> const & nums, std::vector<std::vector<int>> & ans) {
        for_each(std::begin(nums), std::end(nums), [&ans](int num) {ans[num % 2].emplace_back(num);});
    }
    void countDiff(std::vector<int> const & nums, std::vector<int> const & target, long long & ans) {
        assert(nums.size() == target.size());
        for (int idx = 0; idx < nums.size(); idx++) {
            ans += std::abs(nums[idx] - target[idx]) / 2; // each time, we add or minus 2. So the operation is need divided by 2;
        }
    }
    #endif
};