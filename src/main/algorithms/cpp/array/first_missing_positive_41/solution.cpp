#include "../../head.h"


// #define DEBUG
class Solution {
public:
    int firstMissingPositive(std::vector<int> & nums) {
        // plagiarizing from https://leetcode.com/problems/first-missing-positive/discuss/17080/Python-O(1)-space-O(n)-time-solution-with-explanation
        // this operation is very important
        nums.emplace_back(0);
        int const numsSize = nums.size();

        for (int idx = 0; idx < numsSize; idx++) {
            if (0 > nums[idx] || nums[idx] >= numsSize) {
                // the first positive number must be larger than 0 and less than or equal to numsSize
                nums[idx] = 0;
            }
        }
        for (int idx = 0; idx < numsSize; idx++) {
            // record the times of appearance of nums[idx] which must be 0 < nums[idx] < numsSize
            // make a val to index map
            nums[nums[idx] % numsSize] += numsSize;
            #ifdef DEBUG
            std::cout << nums[nums[idx] % numsSize] << "\t";
            #endif
            // if nums[idx] exist, then the index whose value is nums[idx] will be a number that is n * numsSize;
            //
        }
        #ifdef DEBUG
        std::cout << "\n";
        #endif
        for (int idx = 1; idx < numsSize; idx++) {
            if (0 == nums[idx] / numsSize) {
                return idx;
            }
        }
        return numsSize;
    }
};

// #define DEBUG
class Solution {
public:
    int firstMissingPositive(std::vector<int> & nums) {
        // plagiarizing from https://leetcode.com/problems/first-missing-positive/discuss/17071/My-short-c%2B%2B-solution-O(1)-space-and-O(n)-time
        int const numsSize = nums.size();

        for (int idx = 0; idx < numsSize; idx++) {
            while (nums[idx] > 0 && nums[idx] <= numsSize && nums[nums[idx] - 1] != nums[idx]) {
                std::swap(nums[nums[idx] - 1], nums[idx]);
            }
        }
        for (int idx = 0; idx < numsSize; idx++) {
            if (nums[idx] != idx + 1) {
                return idx + 1;
            }
        }
        // we have not find the minmum element from 1 to numsSize;
        return numsSize + 1;
    }
};
