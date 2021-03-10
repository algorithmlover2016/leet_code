#include "../../head.h"


class Solution {
protected:
    class Comp {
    private:
        bool reverse_;
    public:
        Comp(bool reverse = false) : reverse_(reverse) {
        }
        bool operator()(std::tuple<int, int, int, int> const & left, std::tuple<int, int, int, int> const & right) {
            if (std::get<SUM_IDX>(left) <= std::get<SUM_IDX>(right)) {
                return !reverse_;
            } else {
                return reverse_;
            }
        }
    };

public:
    int kthSmallest(std::vector<std::vector<int>> const & mat, int k) {
        // plagiarizing idea from https://leetcode.com/problems/find-the-kth-smallest-sum-of-a-matrix-with-sorted-rows/discuss/609678/Python-O(k-*-logk-*-len(mat))-with-detailed-explanations-%2B-4-lines-python.
        if (mat.empty() || mat[0].empty()) {
            return 0;
        }
        std::vector<int> ans(mat[0]);
        for (int idx = 1; idx < mat.size(); idx++) {
            ans = kthSmallestPair(ans, mat[idx], k);
        }
        return k >= ans.size() ? ans[k - 1] : 0;
    }

    std::vector<int> kthSmallestPair(std::vector<int> const & nums1, std::vector<int> const & nums2, int k) {
        std::vector<int> ans;
        typedef std::priority_queue<std::tuple<int, int, int, int>, std::vector<std::tuple<int, int, int, int>>, Comp> MaxHeap;
        MaxHeap minHeap(true);
        for (int idx = 0; idx < nums1.size() && idx < k; idx++) {
            std::tuple<int, int, int, int> tupEle = std::make_tuple(nums1[idx] + nums2[0], nums1[idx], nums2[0], 0);
            minHeap.emplace(tupEle);
        }
        while (k-- > 0) {
            auto const & curMinEle = minHeap.top();
            ans.emplace_back(std::get<SUM_IDX>(curMinEle));
            int curNums1 = std::get<FIRST_IDX>(curMinEle);
            int curNums2 = std::get<SECOND_IDX>(curMinEle);
            int curNums2Idx = std::get<SECOND_IDX_IDX>(curMinEle);
            minHeap.pop();
            int nextNUms2Idx = curNums2Idx + 1;
            if (nextNUms2Idx < nums2.size() && minHeap.size() < k) {
                std::tuple<int, int, int, int> tupEle = std::make_tuple(curNums1 + nums2[nextNUms2Idx], curNums1, nums2[nextNUms2Idx], nextNUms2Idx);
                minHeap.emplace(tupEle);
            }
        }
        return ans;
    }

private:
    static int const SUM_IDX = 0;
    static int const FIRST_IDX = 1;
    static int const SECOND_IDX = 2;
    static int const SECOND_IDX_IDX = 3;
};

class Solution {
public:
    int kthSmallest(std::vector<std::vector<int>> const & mat, int k) {
        if (mat.empty() || mat[0].empty()) {
            return 0;
        }
        std::vector<int> ans(mat[0]);
        for (int idx = 1; idx < mat.size(); idx++) {
            auto const & rowVecs = mat[idx];
            std::vector<int> curAns;
            for (int idxAns = 0; idxAns < ans.size(); idxAns++) {
                for (int const val : rowVecs) {
                    curAns.emplace_back(ans[idxAns] + val);
                }
            }
            std::sort(std::begin(curAns), std::end(curAns));
            if (k < curAns.size()) {
                curAns.resize(k);
            }
            std::swap(ans, curAns);
            std::vector<int>().swap(curAns);
        }
        return k >= ans.size() ? ans[k - 1] : 0;
    }
};

class Solution {
public:
    int kthSmallest(std::vector<std::vector<int>> const & mat, int k) {
        // plagiarizing idea from https://leetcode.com/problems/find-the-kth-smallest-sum-of-a-matrix-with-sorted-rows/discuss/610701/JavaC%2B%2BPython-Binary-Search-and-Prune-Backtracking-O(m*k*log(m*5000))-~-4ms
        if (mat.empty() || mat[0].empty()) {
            return 0;
        }
        int const rowSize = mat.size();
        int const colSize = mat[0].size();
        int left = rowSize; /*because 1 <= mat[row][col] <= 5000*/
        int right = MAX_ELE * rowSize;
        // binary search the target
        while (left < right) {
            int mid = left + (right - left) / 2;
            int cnt = dfsFindNoMoreThan(mat, mid, 0, 0, k);
            if (cnt >= k) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }

private:
    int dfsFindNoMoreThan(std::vector<std::vector<int>> const & mat, int target, int rowIdx, int sum, int k) {
        if (sum > target) {
            // our target is to find a combination from each row whose sum is <= target, after using all rows
            return 0;
        }
        if (rowIdx == mat.size()) {
            return 1;
        }
        int const colSize = mat[rowIdx].size();
        int ans = 0;
        for (int col = 0; col < colSize; col++) {
            int cnt = dfsFindNoMoreThan(mat, target, rowIdx + 1, sum + mat[rowIdx][col], k - ans);
            if (0 == cnt) {
                // we can't find a combination who meets the sum is not larger than target.
                // because mat[rowIdx][col] < mat[rowIdx][col + 1];
                break;
            }
            ans += cnt;
            if (ans > k) {
                // we just need find k elements, there is no need go on if we have find k elements;
                break;
            }
        }
        return ans;
    }
private:
    static int const MAX_ELE = 5000;
};
