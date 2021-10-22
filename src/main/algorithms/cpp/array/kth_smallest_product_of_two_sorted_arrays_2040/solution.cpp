#include "../../head.h"

// #define DEBUG
class SolutionTLE {
public:
    long long kthSmallestProduct(std::vector<int> const & nums1,
            std::vector<int> const & nums2, long long k) {
        // plagiarizing from https://leetcode.com/problems/kth-smallest-product-of-two-sorted-arrays/discuss/1524312/Python-Binary-Search-O((m%2Bn)log1010) and
        // https://leetcode.com/problems/kth-smallest-product-of-two-sorted-arrays/discuss/1527753/Binary-Search-and-Two-Pointers
        // auto nums1SplitIt = std::upper_bound(std::begin(nums1), std::end(nums1), ZERO_BOUNDARY);
        // auto nums2SplitIt = std::upper_bound(std::begin(nums2), std::end(nums2), ZERO_BOUNDARY);
        std::vector<int> leftPartNums1, rightPartNums1;
        splitArrayByZeroValue(nums1, leftPartNums1, rightPartNums1);
        std::reverse(std::begin(leftPartNums1), std::end(leftPartNums1));

        std::vector<int> leftPartNums2, rightPartNums2;
        splitArrayByZeroValue(nums2, leftPartNums2, rightPartNums2);
        std::reverse(std::begin(leftPartNums2), std::end(leftPartNums2));

        long long leftPartNums1Size = leftPartNums1.size();
        long long rightPartNums1Size = rightPartNums1.size();
        long long leftPartNums2Size = leftPartNums2.size();
        long long rightPartNums2Size = rightPartNums2.size();
        long long negNum = leftPartNums1Size * rightPartNums2Size + rightPartNums1Size * leftPartNums2Size;

        #ifdef DEBUG
        std::cout << "l1, r1: " << leftPartNums1Size << ", " << rightPartNums1Size
            << "; l2, r2: " << leftPartNums2Size << ", " << rightPartNums2Size
            << "; negNum: " << negNum << "\n";
        #endif

        int sign = 1;
        if (negNum < k) {
            k -= negNum;
        } else {
            std::swap(leftPartNums2, rightPartNums2);
            // after change the value of leftPartNums to positive, the product will be in reverse order
            // so if we want to find the kth value, it will be negNum - kth + 1 when changing value to positive.
            k = negNum - k + 1;
            sign = -1;
        }
        long long left = 0, right = MAX_VAL * MAX_VAL;
        while (left < right) {
            long long mid = (left + right) / 2;
            if (count(leftPartNums1, leftPartNums2, mid) + count(rightPartNums1, rightPartNums2, mid) >= k) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return left * sign;
    }

private:
    long long count(std::vector<int> const & left, std::vector<int> & right, long long mid) {
        long long ans = 0;
        for (int leftIdx = 0; leftIdx < left.size(); leftIdx++) {
            for (int rightIdx = right.size() - 1; rightIdx > LEFT_MOST_INDEX_EXCLUDED; rightIdx--) {
                if ((long long)left[leftIdx] * right[rightIdx] <= mid) {
                    ans += rightIdx + 1;
                    break;
                }
            }
        }
        #ifdef DEBUG
        std::cout << "mid: " << mid << ", ans: " << ans << "\n";
        #endif
        return ans;
    }

    void splitArrayByZeroValue(std::vector<int> const & nums,
        std::vector<int> & leftPart,
        std::vector<int> & rightPart,
        int boundary = ZERO_BOUNDARY) {
        if (nums.empty()) {
            return ;
        }
        for (int num : nums) {
            if (boundary > num) {
                num = -num;
                leftPart.emplace_back(num);
            } else {
                rightPart.emplace_back(num);
            }
        }

    }
private:
    static int const ZERO_BOUNDARY = 0;
    static int const LEFT_MOST_INDEX_EXCLUDED = -1;
    static int const LEFT_MOST_INDEX_INCLUDED = 0;
    static long long const MAX_VAL = 1e5;

};

// #define DEBUG
class Solution {
public:
    long long kthSmallestProduct(std::vector<int> const & nums1,
            std::vector<int> const & nums2, long long k) {
        // plagiarizing from https://leetcode.com/problems/kth-smallest-product-of-two-sorted-arrays/discuss/1527753/Binary-Search-and-Two-Pointers
        auto nums1SplitIt = std::upper_bound(std::begin(nums1), std::end(nums1), ZERO_BOUNDARY);
        auto nums2SplitIt = std::upper_bound(std::begin(nums2), std::end(nums2), ZERO_BOUNDARY);

        std::vector<int> neg1(std::begin(nums1), nums1SplitIt), neg2(std::begin(nums2), nums2SplitIt);
        std::vector<int> pos1(nums1SplitIt, std::end(nums1)), pos2(nums2SplitIt, std::end(nums2));

        std::vector<int> pos1_r(std::rbegin(pos1), std::rend(pos1)), pos2_r(std::rbegin(pos2), std::rend(pos2));
        std::vector<int> neg1_r(std::rbegin(neg1), std::rend(neg1)), neg2_r(std::rbegin(neg2), std::rend(neg2));

        int neg_num = neg1.size() * pos2.size() + neg2.size() * pos1.size();
        long long l = -MAX_VAL, r = MAX_VAL;
        while (l < r) {
            long long m = (l + r - 1) / 2, cnt = 0;
            if (m >= 0) {
                cnt = count(neg1_r, neg2_r, m) + count(pos1, pos2, m)
                    + neg_num;
            } else {
                cnt = count(pos2_r, neg1, m) + count(pos1_r, neg2, m);
            }
            if (cnt < k) {
                l = m + 1;
            } else {
                r = m;
            }
        }
        return l;
    }
private:
    long long count(std::vector<int> const & n1, std::vector<int> const & n2, long long m) {
        long long cnt = 0;
        for (int p1 = 0, p2 = n2.size() - 1; p1 < n1.size(); ++p1) {
            while (p2 > LEFT_MOST_INDEX_EXCLUDED && (long long)n1[p1] * n2[p2] > m) {
                --p2;
            }
            cnt += p2 + 1;
        }
        return cnt;
    }

private:
    int const ZERO_BOUNDARY = 0;
    static int const LEFT_MOST_INDEX_EXCLUDED = -1;
    static int const LEFT_MOST_INDEX_INCLUDED = 0;
    static long long const MAX_VAL = 1e10;
};
