#include "../../head.h"


// #define DEBUG
class Solution {
public:
    std::vector<int> maxNumber(std::vector<int> const & nums1, std::vector<int> const & nums2, int k) {
        // plagiarizing from https://leetcode.com/problems/create-maximum-number/discuss/77287/C%2B%2B-16ms-FASTEST-beats-97.
        int const nums1Size = nums1.size();
        int const nums2Size = nums2.size();
        #ifdef DEBUG
        std::cout << "1, 2Size: " << nums1Size << ",\t" << nums2Size << "\n";
        #endif

        int needNums1Min = std::max(0, k - nums2Size);
        int needNums1Max = std::min(k, nums1Size);

        int needNums2Min = k - needNums1Max;
        int needNums2Max = k - needNums1Min;

        std::unordered_map<int, std::vector<int>> nums1DpMemo;
        std::unordered_map<int, std::vector<int>> nums2DpMemo;
        nums1DpMemo[needNums1Max] = getMaxVec(nums1, needNums1Max);
        nums2DpMemo[needNums2Max] = getMaxVec(nums2, needNums2Max);

        getRangeMax(nums1DpMemo, needNums1Max, needNums1Min);
        getRangeMax(nums2DpMemo, needNums2Max, needNums2Min);

        std::vector<int> ans(k, INT_MIN);
        for (int needNums1Len = needNums1Min; needNums1Len <= needNums1Max; needNums1Len++) {
            int needNums2Len = k - needNums1Len;
            #ifdef DEBUG
            std::cout << "nums1Len, nums2Len: " << needNums1Len << ",\t" << needNums2Len << "\t";
            std::cout << "1Len, 2Len: " << nums1DpMemo[needNums1Len].size() << ",\t"
                << nums2DpMemo[needNums2Len].size() << "\n";
            #endif
            std::vector<int> curAns;
            merge(nums1DpMemo[needNums1Len], nums2DpMemo[needNums2Len], curAns);
            if (curAns > ans) {
                ans = curAns;
            }
        }
        return ans;
    }

    void merge(std::vector<int> const & nums1,
            std::vector<int> const & nums2,
            std::vector<int> & ans) {
        int idx1 = 0, idx2 = 0;
        while (idx1 < nums1.size() && idx2 < nums2.size()) {
            if (nums1[idx1] > nums2[idx2]) {
                ans.emplace_back(nums1[idx1++]);
            } else if (nums1[idx1] < nums2[idx2]) {
                ans.emplace_back(nums2[idx2++]);
            } else {
                bool large = !std::lexicographical_compare(nums1.begin() + idx1, nums1.end(),
                                                           nums2.begin() + idx2, nums2.end());
                if (large) {
                    getEqualEle(nums1, idx1, nums1[idx1], ans);
                } else {
                    getEqualEle(nums2, idx2, nums2[idx2], ans);
                }
            }
        }
        if (idx1 < nums1.size()) {
            getLeftEle(nums1, idx1, ans);
        } else if (idx2 < nums2.size()) {
            getLeftEle(nums2, idx2, ans);
        }
    }

    void getLeftEle(std::vector<int> const & nums, int idx, std::vector<int> & ans) {
        for (; idx < nums.size(); idx++) {
            ans.emplace_back(nums[idx]);
        }
    }
    void getEqualEle(std::vector<int> const & nums, int & idx, int const target, std::vector<int> & ans) {
        for (; idx < nums.size() && target == nums[idx]; idx++) {
            ans.emplace_back(nums[idx]);
        }
    }

    void getRangeMax(std::unordered_map<int, std::vector<int>> & numsDpMemo,
            int needNumsMax, int needNumsMin) {
        if (numsDpMemo.find(needNumsMax) == numsDpMemo.end()) {
            return;
        }
        for (int start = needNumsMax; start > needNumsMin; start--) {
            std::list<int> ans(numsDpMemo[start].begin(), numsDpMemo[start].end());

            int pre = INT_MAX;
            std::list<int>::iterator it = ans.begin();
            for (; it != ans.end(); it++) {
                if (pre < *it) {
                    break;
                }
                pre = *it;
            }
            ans.erase(std::prev(it));
            numsDpMemo[start - 1] = std::vector<int>(ans.begin(), ans.end());
        }
    }

    std::vector<int> getMaxVec(std::vector<int> const & nums, int target) {
        if (nums.empty() || 0 == target) {
            return {};
        }

        int const numsSize = nums.size();
        if (target >= numsSize) {
            return nums;
        }

        int const needDelNum = numsSize - target;
        #ifdef DEBUG
        std::cout << "size, target, del: " << numsSize << ",\t" << target << ",\t" << needDelNum << "\n";
        #endif

        std::vector<int> ans; //using as stack
        for (int idx = 0; idx < numsSize; idx++) {
            // idx - ans.size() means util idx(exclude) the number that we have delete
            // if we can do a delete operation, which means ans.pop(),
            // we must let idx - ans.size() < needDelNum
            // ans.size() means the num that we will take
            while (!ans.empty() && ans.back() < nums[idx] && (idx - ans.size() < needDelNum)) {
                ans.pop_back();
            }
            if (idx - ans.size() == needDelNum) {
                for (; idx < numsSize; idx++) {
                    ans.emplace_back(nums[idx]);
                }
                return ans;
            }
            ans.emplace_back(nums[idx]);
        }
        // if all the elements in nums are all the same, according to my code,
        // ans will be nums. then we just need cut the last needDelNum elements with resize
        if (target != ans.size()) {
            ans.resize(target);
        }
        return ans;
    }
};
