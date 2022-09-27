#include "../../head.h"


// #define DEBUG
class SolutionMySelf {
public:
    int validSubarraySize(std::vector<int> const & nums, int threshold) {
        // similar to https://leetcode.com/problems/subarray-with-elements-greater-than-varying-threshold/discuss/2259557/Monostack
        if (nums.empty()) {
            return 0;
        }
        std::vector<int> nonDescreasings;
        for (int idx = 0, left = 0; idx < nums.size(); idx++) {
            while (!nonDescreasings.empty() && nums[idx] <= nums[nonDescreasings.back()]) {
                #ifdef DEBUG
                std::cout << "pop_back " << nums[nonDescreasings.back()] << ",\t";
                #endif
                nonDescreasings.pop_back();
            }
            #ifdef DEBUG
            std::cout << "\nEmplace_back " << nums[idx] << "\n";
            #endif
            nonDescreasings.emplace_back(idx);
            for (int left = 0; left < nonDescreasings.size(); left++) {
                int start = 0; 
                if (left > 0) {
                    start = nonDescreasings[left - 1] + 1;
                }
                #ifdef DEBUG
                std::cout << "nonDesc: (" << start << " [" << nums[nonDescreasings[left]] << "]), cur idx: (" << idx << " ["<< nums[idx] << "]), " << " len: " << idx - start + 1 << ", q: " << threshold / (idx - start + 1) << ";\t";
                #endif
                if (threshold / (idx - start + 1) < nums[nonDescreasings[left]]) {
                    #ifdef DEBUG
                    std::cout << "find the answer: " << start << ", " << nonDescreasings[left] << " cur idx: " << idx << "; with " << threshold / (idx - nonDescreasings[left] + 1) << " < " << nums[nonDescreasings[left]]  << "\n";
                    #endif
                    return idx - start + 1;
                }
            }
            #ifdef DEBUG
            std::cout << "\n";
            #endif
        }
        return -1;
    }
};

class Solution {
public:
    int validSubarraySize(std::vector<int> nums, int threshold) {
        // plagiarizing from https://leetcode.com/problems/subarray-with-elements-greater-than-varying-threshold/discuss/2259557/Monostack
        std::vector<int> nonDescreasings;
        nums.emplace_back(0); // add a minimum element into nums to compute all the internal
        for (int idx = 0; idx < nums.size(); idx++) {
            while (!nonDescreasings.empty() && nums[idx] < nums[nonDescreasings.back()]) {
                // we find a element at idx which is less than the previous element marked in nonDescreasings
                int val = nums[nonDescreasings.back()]; nonDescreasings.pop_back();
                int leftIdx = nonDescreasings.empty() ? -1 : nonDescreasings.back();
                // The minimum num of these elements from leftIdx + 1(included) to idx - 1(included) is val;
                if (threshold / (idx - leftIdx - 1) < val) {
                    return idx - leftIdx - 1;
                }
            }
            nonDescreasings.emplace_back(idx);
        }
        return -1;
    }
};



// #define DEBUG
class SolutionTLE {
public:
    int validSubarraySize(std::vector<int> const & nums, int threshold) {
        if (nums.empty()) {
            return 0;
        }
        std::vector<int> nonDescreasings;
        for (int idx = 0, left = 0; idx < nums.size(); idx++) {
            while (!nonDescreasings.empty() && nums[idx] < nums[nonDescreasings.back()]) {
                #ifdef DEBUG
                std::cout << "pop_back " << nums[nonDescreasings.back()] << ",\t";
                #endif
                nonDescreasings.pop_back();
            }
            #ifdef DEBUG
            std::cout << "\nEmplace_back " << nums[idx] << "\n";
            #endif
            nonDescreasings.emplace_back(idx);
            for (int left = 0; left <= idx; left++) {
                auto it = std::lower_bound(std::begin(nonDescreasings), std::end(nonDescreasings), left); // it will never be the std::end(nonDescreasings);
                #ifdef DEBUG
                std::cout << "nonDesc: (" << nums[left] << " [" << nums[left] << "]), cur idx: (" << idx << " ["<< nums[idx] << "]), " << " len: " << idx - left + 1 << ", q: " << threshold / (idx - left + 1) << ";\t";
                #endif
                if (threshold / (idx - left + 1) < nums[*it]) {
                    #ifdef DEBUG
                    std::cout << "find the answer: " << left << ", " << nonDescreasings[left] << idx << "; with " << threshold / (idx - nonDescreasings[left] + 1) << " < " << nums[*it]  << "\n";
                    #endif
                    return idx - left + 1;
                }
            }
            #ifdef DEBUG
            std::cout << "\n";
            #endif
        }
        return -1;
    }
};