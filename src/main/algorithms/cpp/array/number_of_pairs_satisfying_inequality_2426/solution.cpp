#include "../../head.h"


class SolutionBruteForceTLE {
public:
    long long numberOfPairs(std::vector<int> const & nums1, std::vector<int> const & nums2, int diff) {
        if (nums1.size() != nums2.size()) {
            return -1;
        }
        long long ans = 0;
        for (int left = 0; left < nums1.size(); left++) {
            for (int right = left + 1; right < nums2.size(); right++) {
                if (nums1[left] - nums1[right] <= nums2[left] - nums2[right] + diff) {
                    ans++;
                }
            }
        }
        return ans;
    }
};

class SolutionBSTLE {
public:
    long long numberOfPairs(std::vector<int> const & nums1, std::vector<int> const & nums2, int diff) {
        // plagiarizing from https://leetcode.com/problems/number-of-pairs-satisfying-inequality/solutions/2646606/python-reverse-pairs/
        /*
            nums1[i] - nums1[j] <= nums2[i] - nums2[j] + diff =>
            nums1[i] - nums2[i] <= nums1[j] - nums2[j] + diff =>
            diffs[i] <= diffs[j] + diff if diffs[i] = nums1[i] - nums2[i] for 0 <= i < nums1.size()
        */
        if (nums1.size() != nums2.size()) {
            return -1;
        }
        long long ans = 0;
        std::multiset<int> diffs;
        for (int idx = 0; idx < nums1.size(); idx++) {
            auto it = std::upper_bound(std::begin(diffs), std::end(diffs), nums1[idx] - nums2[idx] + diff);
            int pairNums = std::distance(std::begin(diffs), it);
            ans += pairNums;
            diffs.insert(nums1[idx] - nums2[idx]);
        }
        return ans;
    }
};

// #define DEBUG
class SolutionFenwick {
public:
    long long numberOfPairs(std::vector<int> const & nums1, std::vector<int> const & nums2, int diff) {
        // plagiarizing from https://leetcode.com/problems/number-of-pairs-satisfying-inequality/solutions/2648104/2-O(nlogn)-solutions-or-Merge-Sort-and-BIT-or-Java/
        if (nums1.size() != nums2.size()) {
            return -1;
        }
        FenwickTree obj(SHIFTS * 2 + 2);
        long long ans = 0;
        for (int idx = 0; idx < nums1.size(); idx++) {
            int curDiff = nums1[idx] - nums2[idx] + SHIFTS;
            #ifdef DEBUG
            std::cout << "curDiff: " << curDiff - SHIFTS << "\n";
            #endif
            ans += obj.get(curDiff + diff); // we should first compute the number and then insert the cur diff
            obj.add(curDiff);
        }
        return ans;
    }
private:
    class FenwickTree {
    public:
        FenwickTree(int size) {
            bits = std::vector(size, 0);
            #ifdef DEBUG
            std::cout << "Fenwick Tree size: " << bits.size() << "\n";
            #endif
        }
    void add(int idx, int val = 1) {
        if (idx <= 0) {
            return;
        }
        for (idx += 1; idx < bits.size(); idx += idx & (-idx) ) {
            bits[idx] += val;
        }
    }
    long long get(int idx) {
        long long ans = 0;
        for (idx += 1; idx > 0; idx -= idx & (-idx)) {
            ans += bits[idx];
        }
        return ans;
    }

    private:
        std::vector<int> bits;
    };
private:
    int constexpr static SHIFTS = 1e4 * 3; // minimum(nums1) - maximum(nums2) + minimum(diff) = -1e4 - 1e4 - 1e4
};

class SolutionMergeSort {
public:
    long long numberOfPairs(std::vector<int> const & nums1, std::vector<int> const & nums2, int diff) {
        // plagiarizing from https://leetcode.com/problems/number-of-pairs-satisfying-inequality/solutions/2648104/2-O(nlogn)-solutions-or-Merge-Sort-and-BIT-or-Java/
        if (nums1.size() != nums2.size()) {
            return -1;
        }
        std::vector<int> diffs(nums1.size(), 0);
        for (int idx = 0; idx < diffs.size(); idx++) {
            diffs[idx] = nums1[idx] - nums2[idx];
        }
        std::vector<int> sortedUsed(diffs.size());
        return mergeSorted(diffs, sortedUsed, 0, diffs.size() - 1, diff);
    }
private:
    long long mergeSorted(std::vector<int> & nums, std::vector<int> & copied, int left, int right, int diff) {
        if (left == right) {
            return 0; // there is only one elements in this sub-array, no need to sort and no pairs;
        }
        int mid = left + (right - left) / 2;
        long long ans = 0;
        ans += mergeSorted(nums, copied, left, mid, diff);
        ans += mergeSorted(nums, copied, mid + 1, right, diff);
        ans += merge(nums, copied, left, mid, right, diff);
        return ans;
    }
    long long merge(std::vector<int> & nums, std::vector<int> & copied, int left, int mid, int right, int diff) {
        long long ans = 0;
        for (int l = left, r = mid + 1; l <= mid && r <= right; l++) {
            while (r <= right && (nums[l] > nums[r] + diff)) {
                // find the first pos that nums[l] <= nums[j] + diff
                // for all the left l', they are all meeted the requirements that nums[l'] > nums[r] + diff
                // because nums[l'] > nums[l] for all l < l' <= mid
                r++;
            }
            ans += right - r + 1;
        }
        for (int l = left, r = mid + 1, k = left; l <= mid || r <= right; k++) {
            if (r > right /* There are no elements left in the right part, so we just append all the left parts left */ ||
                ((l <= mid) && (nums[l] <= nums[r]) /* There are still some nums in the two sides and left num is less than the right pos num */)) {
                copied[k] = nums[l++];
            } else {
                copied[k] = nums[r++];
            }
        }
        std::copy(std::begin(copied) + left, std::begin(copied) + right + 1, std::begin(nums) + left);
        return ans;
    }
};