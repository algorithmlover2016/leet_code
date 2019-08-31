#include "../../head.h"

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // plagiarzing https://leetcode.com/problems/median-of-two-sorted-arrays/discuss/2471/Very-concise-O(log(min(MN)))-iterative-solution-with-detailed-explanation and https://leetcode.com/problems/median-of-two-sorted-arrays/discuss/2481/Share-my-O(log(min(mn)))-solution-with-explanation

        int N1 = nums1.size();
        int N2 = nums2.size();
        if (N1 < N2) {
            // make sure that nums1.size() >= nums2.size()
            return findMedianSortedArrays(nums2, nums1);
        }
        // in this case (N1 >= N2), the cutting line in nums2 can only from 0 to N2
        int left = 0;
        int right = (N2 << 1);
        int N = N1 + N2;
        while (left <= right) {
            int dMid2 = (left + right) >> 1;
            // there is a equation that Mid1 + Mid2 = N1 - Mid1 + N2 - Mid2
            // Mid1 * 2 = dMid1; Mid2 * 2 = dMid2;
            int dMid1 = N - dMid2;
            // if cutting line is on the most left of nums1, there is no elements
            // because we choose the max from the left elements, so initializing with INT_MIN
            double L1 = (dMid1 == 0) ? INT_MIN : nums1[(dMid1 - 1)/2];
            // std::cout << "dMid1: " << dMid1 << "\t" << "L1: " << L1 << "\t";
            // if cutting line is on the most left of nums2, there is no elements
            double L2 = (dMid2 == 0) ? INT_MIN : nums2[(dMid2 - 1)/2];
            // std::cout << "dMid2: " << dMid2 << "\t" << "dMid2: " << L2 << std::endl;

            // if cutting line is on the most right of nums1(only happening when N1 = N2), there is no elements
            // because we choose the min from the right elements, so initializing with INT_MAX
            double R1 = (dMid1 == (N1 << 1)) ? INT_MAX : nums1[dMid1/2];
            // if cutting line is on the most right of nums2, there is no elements
            double R2 = (dMid2 == (N2 << 1)) ? INT_MAX : nums2[dMid2/2];

            if (L1 > R2) {
                // means cutting line in nums1 is too right, and in nums2 is too left
                left = dMid2 + 1;
            } else if (L2 > R1) {
                // means cutting line in nums1 is too left, and in nums2 is too right
                right = dMid2 - 1;
            } else {
                // means the right postion
                return (std::min(R1, R2) + std::max(L1, L2)) / 2.0;
            }
        }
        return -1;
    }
};

class solution_easy_understand {
    // plagiarzing MissMary, url: https://leetcode.com/problems/median-of-two-sorted-arrays/discuss/2481/Share-my-O(log(min(mn)))-solution-with-explanation
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int N1 = nums1.size();
        int N2 = nums2.size();
        if (N1 < N2) {
            // make sure the constraint that nums1.size() >= nums2.size()  is always true
            return findMedianSortedArrays(nums2, nums1);
        }
        
        int lo = 0;
        int hi = N2;
        while (lo <= hi) {
            int mid2 = (lo + hi) / 2;
            // there is a constraint that mid1 + mid2 = N1 - mid1 + N2 - mid2
            // the resion that N1 + N2 + 1 is to make the left part to be larger than right by one
            int mid1 = (N1 + N2 + 1) / 2 - mid2;
            if ((mid2 > 0) && (nums2[mid2 - 1] > nums1[mid1])) {
                hi = mid2 - 1;
            } else if ((mid2 < N2) && (nums1[mid1 - 1] > nums2[mid2])) {
                lo = mid2 + 1;
            } else {
                double max_left = INT_MIN;
                double min_right = INT_MAX;
                if (mid2 == 0) {
                    max_left = nums1[mid1 - 1];
                } else if (mid1 == 0) {
                    max_left = nums2[mid2 - 1];
                } else {
                    max_left = std::max(nums1[mid1 - 1], nums2[mid2 - 1]);
                }
                if ((N1 + N2) & 1) {
                    return max_left;
                }
                if (mid2 == N2) {
                    min_right = nums1[mid1];
                } else if (mid1 == N1) {
                    min_right = nums2[mid2];
                } else {
                    min_right = std::min(nums1[mid1], nums2[mid2]);
                }
                return (max_left + min_right) / 2.0;
            }
        }
        return -1;
    }
};
