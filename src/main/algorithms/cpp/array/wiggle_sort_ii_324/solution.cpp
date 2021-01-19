#include "../../head.h"


// #define DEBUG
class Solution {
public:
    void wiggleSort(std::vector<int> & nums) {
        // plagiarizing idea from https://leetcode.com/problems/wiggle-sort-ii/discuss/77677/O(n)%2BO(1)-after-median-Virtual-Indexing
        int const numsSize = nums.size();
        if (JUST_RETURN == numsSize) {
            return;
        }
        // std::vector<int>::iterator midIt = nums.begin() + (numsSize / 2);
        auto midIt = nums.begin() + (numsSize / 2);
        std::nth_element(nums.begin(), midIt, nums.end());
        #ifdef DEBUG
        std::cout << "\n";
        for (auto const num : nums) {
            std::cout << num << ",\t";
        }
        std::cout << "\n";
        #endif
        // we must get the middle value, because we will change the middle value with exchange
        int const midVal = *midIt;

#define FIND_ELE(idx) nums[(1 + (2 * (idx))) % (numsSize | 1)]

        for ( int left = 0, idx = 0, right = numsSize - 1;
                idx <= right;) {
            // ERROR the value of midIt will be changed // if (FIND_ELE(idx) > (*midIt)) {
            if (FIND_ELE(idx) > (midVal)) {
                std::swap(FIND_ELE(left++), FIND_ELE(idx++));
            // ERROR the value of midIt will be changed // } else if (FIND_ELE(idx) < (*midIt)) {
            } else if (FIND_ELE(idx) < (midVal)) {
                std::swap(FIND_ELE(idx), FIND_ELE(right--));
            } else {
                idx++;
            }
        }
    }
private:
    static int const JUST_RETURN = 1;
};
