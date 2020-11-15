#include "../../head.h"


class SolutionWrongAnswer {
public:
    int reversePairs(std::vector<int> const & nums) {
        int const numsSize = nums.size();
        std::vector<int> numsIdx(numsSize);

        for (int idx = 0; idx < numsSize; idx++) {
            numsIdx[idx] = idx;
        }

        int ans = 0;
        mergeSort(nums, numsIdx, ans);
        return ans;
    }

    void mergeSort(std::vector<int> const & nums,
            std::vector<int> & numsIdx,
            int & ans) {
        int const numsIdxSize = numsIdx.size();
        if (numsIdxSize < 2) {
            return;
        }
        std::vector<int>::iterator mid = numsIdx.begin() + (numsIdxSize >> 1);
        std::vector<int> left(numsIdx.begin(), mid);
        std::vector<int> right(mid, numsIdx.end());
        mergeSort(nums, left, ans);
        mergeSort(nums, right, ans);
        // std::cout << "\nnumsSize: " << numsIdxSize << "\n";
        for (int idx = numsIdxSize - 1; idx >= 0; idx--) {
            if (right.empty()) {
                // std::cout << "r left: " << left.back() << "\t" << nums[left.back()] << "\t";
                numsIdx[idx] = left.back();
                left.pop_back();
            } else if (left.empty()) {
                // std::cout << "l right: " << right.back() << "\t" << nums[right.back()] << "\t";
                numsIdx[idx] = right.back();
                right.pop_back();
            } else if (nums[left.back()] > nums[right.back()]){
                // the judgement is wrong,
                // because there is a satuation that right[-2].back() *2 < left.back() < right.back()
                // on this satuation, we just ignore the left.back();

                if (nums[left.back()] > (2 * nums[right.back()])) {
                    // std::cout << "left: " << left.back() << "\t" << nums[left.back()] << "\t";
                    ans += right.size();
                }
                numsIdx[idx] = left.back();
                left.pop_back();
            } else {
                // std::cout << "right: " << right.back() << "\t" << nums[right.back()] << "\t";
                numsIdx[idx] = right.back();
                right.pop_back();
            }
        }
    }
};

class SolutionMerge {
public:
    int reversePairs(std::vector<int> nums) {
        // plagiarizing from https://leetcode.com/problems/reverse-pairs/discuss/97287/C++-with-iterators
        return mergeSort(nums.begin(), nums.end());
    }

private:
    int mergeSort(std::vector<int>::iterator begin, std::vector<int>::iterator end) {
        if (end - begin < 2) {
            return 0;
        }
        auto mid = begin + (end - begin) / 2;
        int ans = mergeSort(begin, mid) + mergeSort(mid, end);
        for (auto iLeft = begin, iRight = mid; iLeft != mid; iLeft++) {
            while (iRight != end && (*iLeft > (JUDGE_NUM * *iRight))) {
                iRight++;
            }
            ans += iRight - mid;
        }
        std::inplace_merge(begin, mid, end);
        return ans;
    }
private:
    long int const JUDGE_NUM = 2;
};

class SolutionWithoutUsing_inplace_merge {
public:
    void merge(int a[], int l, int m, int r) {
        int result[r - l];
        int ind = 0;
        int i1 = l, i2 = m;
        while (i1 < m || i2 < r) {
            if (i1 == m) {
                result[ind++] = a[i2];
                i2++;
            } else if (i2 == r) {
                result[ind++] = a[i1];
                i1++;
            } else if (a[i1] > a[i2]) {
                result[ind++] = a[i2];
                i2++;
            } else {
                result[ind++] = a[i1];
                i1++;
            }
        }
        for (int i = 0; i < r - l; i++) {
            a[l + i] = result[i];
        }
    }
    int merge_sort(int a[], int l, int r) {
        if (l >= r - 1)
            return 0;
        int mid = (l + r) / 2;
        int count = merge_sort(a, l, mid) + merge_sort(a, mid, r);
        int j = mid;
        for (int i = l; i < mid; i++) {
            while (j < r && a[i] > a[j] * 2LL)
                j++;
            count += j - (mid);
        }

        merge(a, l, mid, r);
        return count;
    }

    int reversePairs(std::vector<int> & nums) {
        return merge_sort(nums.data(), 0, nums.size());
    }
};
