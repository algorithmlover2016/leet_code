#include "../../head.h"


// #define DEBUG
class SolutionTLE {
public:
    int createSortedArray(std::vector<int> const & instructions) {
        int const instructionsSize = instructions.size();
        std::list<int> nums;
        int ans = 0;
        for (int const i : instructions) {
            int leftIdx = -1;
            int numsSize = nums.size();
            int rightIdx = numsSize;
            std::list<int>::iterator rightIt = nums.end();
            int idx = 0;
            for (std::list<int>::iterator it = nums.begin(); it != nums.end(); it++) {
                if (*it < i) {
                    leftIdx = idx;
                } else if (*it > i) {
                    rightIdx = idx;
                    rightIt = it;
                    break;
                }
                #ifdef DEBUG
                std::cout << leftIdx << ", " << rightIdx << ": " << *it << "\n";
                #endif
                idx++;
            }
            ans += std::min(leftIdx + 1, numsSize - rightIdx);
            ans %= MOD;
            nums.insert(rightIt, i);
        }
        return ans;
    }

private:
    static int const MOD = 1e9 + 7;
};



class SolutionBinaryIndexTree {
public:
    Solution() {
        cntBIT = std::vector<int>(MAX_VAL_UPPER_BOUNDARY, 0);
    }

    int createSortedArray(std::vector<int> const & instructions) {
        // plagiarizing idea from https://leetcode.com/problems/create-sorted-array-through-instructions/discuss/927531/JavaC%2B%2BPython-Binary-Indexed-Tree
        int ans = 0;
        for (int idx = 0; idx < instructions.size(); idx++) {
            // for the left side, we just compute how many numbers are less than instructions[idx];
            // for the right side, when loop idx, there are already idx elements inserted into container,
            //  if we compute the number of not larger than  instructions[idx], we have the total number.
            //  Just need do a minus op
            ans = (ans + std::min(getNumbers(instructions[idx] - 1, cntBIT),
                                  idx - getNumbers(instructions[idx], cntBIT))) % MOD;
            update(instructions[idx], cntBIT);

        }
        return ans;
    }

private:
    void update(int num, std::vector<int> & cntBIT) {
        while (num < MAX_VAL_UPPER_BOUNDARY) {
            // the cur idx(num) add one, and then it will add the binaryIndexTree
            cntBIT[num]++;
            num += num & (-num);
        }
    }
    int getNumbers(int num, std::vector<int> & cntBIT) {
        int ans = 0;
        while (num > MIN_VAL_BOUNDARY) {
            ans += cntBIT[num];
            num -= num & (-num);
        }
        return ans;
    }
private:
    static int const MOD = 1e9 + 7;
    static int const MAX_VAL = 1e5;
    static int const MAX_VAL_UPPER_BOUNDARY = MAX_VAL + 1;
    static int const MIN_VAL_BOUNDARY = 0;

    std::vector<int> cntBIT;
};
