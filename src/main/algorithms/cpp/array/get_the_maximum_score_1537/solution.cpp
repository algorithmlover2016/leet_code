#include "../../head.h"


// #define DEBUG
class SolutionTLE {
public:
    int maxSum(std::vector<int> const & nums1, std::vector<int> const & nums2) {
        int const nums1Size = nums1.size();
        int const nums2Size = nums2.size();
        std::vector<std::unordered_map<int, int>> val2Idx(2);
        for (int idx = 0; idx < nums1Size; idx++) {
            val2Idx[0][nums1[idx]] = idx;
        }

        for (int idx = 0; idx < nums2Size; idx++) {
            val2Idx[1][nums2[idx]] = idx;
        }

        int ans = INIT_MIN;
        dfsMaxSum(nums1, nums2, 0, -1, true, 0, ans, val2Idx);
        std::swap(val2Idx[0], val2Idx[1]);
        dfsMaxSum(nums2, nums1, 0, -1, true, 0, ans, val2Idx);
        return ans;
    }

    void dfsMaxSum(std::vector<int> const & nums1,
            std::vector<int> const & nums2,
            int idx1, int idx2, bool useIdx1, int sum, int & ans,
            std::vector<std::unordered_map<int, int>> const & val2Idx) {
        int const nums1Size = nums1.size();
        int const nums2Size = nums2.size();

        if (idx1 == nums1Size) {
            if (sum > ans) {
                ans = sum;
            }
            return;
        }
        #ifdef DEBUG
        std::cout << idx1 << ",\t" << idx2 << ",\t" << sum << "\n";
        #endif

        if (useIdx1) {
            int curVal = nums1[idx1];
            if (val2Idx[1].find(curVal) != val2Idx[1].end() && (val2Idx[1].at(curVal) > idx2)) {
                dfsMaxSum(nums1, nums2, idx1, val2Idx[1].at(curVal), !useIdx1, sum, ans, val2Idx);
            }
            dfsMaxSum(nums1, nums2, idx1 + 1, idx2, useIdx1, sum + nums1[idx1], ans, val2Idx);
        } else {
            if (idx2 == nums2Size) {
                if (sum > ans) {
                    ans = sum;
                }
                return;
            }
            int curVal = nums2[idx2];
            if (val2Idx[0].find(curVal) != val2Idx[0].end() && (val2Idx[0].at(curVal) > idx1)) {
                dfsMaxSum(nums1, nums2, val2Idx[0].at(curVal), idx2, !useIdx1, sum, ans, val2Idx);
            }
            dfsMaxSum(nums1, nums2, idx1, idx2 + 1, useIdx1, sum + nums2[idx2], ans, val2Idx);
        }
    }
private:
    static int const INIT_MIN = 0;
};

#define DEBUG
class SolutionWrongAnswer {
public:
    int maxSum(std::vector<int> const & nums1, std::vector<int> const & nums2) {
        return std::max(maxSumImp(nums1, nums2), maxSumImp(nums2, nums1));
    }
    int maxSumImp(std::vector<int> const & nums1, std::vector<int> const & nums2) {
        // must start from nums1 and end at nums1.end();
        int const nums1Size = nums1.size();
        int const nums2Size = nums2.size();

        int ans = 0;

        int nums1Idx = 0, nums2Idx = 0;
        int nums1Sum = 0, nums2Sum = 0;
        bool firstMeet = false;
        for (;nums1Idx < nums1Size && nums2Idx < nums2Size;) {
            if (nums1[nums1Idx] == nums2[nums2Idx]) {
                if (!firstMeet) {
                    ans += nums1Sum + nums1[nums1Idx];
                    firstMeet = true;
                } else {
                    ans += std::max(nums1Sum, nums2Sum) + nums1[nums1Idx];
                }
                #ifdef DEBUG
                std::cout << "idx1, idx2: " << nums1Idx << ",\t" << nums2Idx << ",\t" << ans << "\n";
                #endif
                nums1Sum = 0;
                nums2Sum = 0;
                nums1Idx++;
                nums2Idx++;
            } else if (nums1[nums1Idx] < nums2[nums2Idx]) {
                nums1Sum += nums1[nums1Idx++];
            } else {
                nums2Sum += nums2[nums2Idx++];
            }
        }

        while (nums1Idx < nums1Size) {
            nums1Sum += nums1[nums1Idx++];
        }
        ans += nums1Sum;
        return ans;
    }
};

// #define DEBUG
class Solution {
public:
    int maxSum(std::vector<int> const & nums1, std::vector<int> const & nums2) {
        // plagiarizing idea from https://leetcode.com/problems/get-the-maximum-score/discuss/767987/JavaC%2B%2BPython-Two-Pointers-O(1)-Space
        int const nums1Size = nums1.size();
        int const nums2Size = nums2.size();

        long long ans = 0;

        int nums1Idx = 0, nums2Idx = 0;
        long long nums1Sum = 0, nums2Sum = 0;
        for (;nums1Idx < nums1Size && nums2Idx < nums2Size;) {
            if (nums1[nums1Idx] == nums2[nums2Idx]) {
                ans += std::max(nums1Sum, nums2Sum) + nums1[nums1Idx];
                ans %= MOD;
                #ifdef DEBUG
                std::cout << "idx1, idx2: " << nums1Idx << ",\t" << nums2Idx << ",\t" << ans << "\n";
                #endif
                nums1Sum = 0;
                nums2Sum = 0;
                nums1Idx++;
                nums2Idx++;
            } else if (nums1[nums1Idx] < nums2[nums2Idx]) {
                nums1Sum += nums1[nums1Idx++];
            } else {
                nums2Sum += nums2[nums2Idx++];
            }
        }
        while (nums1Idx < nums1Size) {
            nums1Sum += nums1[nums1Idx++];
        }
        while (nums2Idx < nums2Size) {
            nums2Sum += nums2[nums2Idx++];
        }
        ans += std::max(nums1Sum, nums2Sum);
        ans %= MOD;
        return ans;
    }

    int maxSumLee215(std::vector<int> const & A, std::vector<int> const & B) {
        int i = 0, j = 0, n = A.size(), m = B.size();
        long a = 0, b = 0;
        while (i < n || j < m) {
            if (i < n && (j == m || A[i] < B[j])) {
                a += A[i++];
            } else if (j < m && (i == n || A[i] > B[j])) {
                b += B[j++];
            } else {
                a = b = std::max(a, b) + A[i];
                i++, j++;
            }
        }
        return std::max(a, b) % MOD;
    }
private:
    static int const MOD = 1e9 + 7;
};
