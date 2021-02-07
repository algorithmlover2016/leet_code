#include "../../head.h"


class Solution {
protected:
    friend class Comp;
    class Comp {
    private:
        bool _reverse;
    public:
        Comp(bool reverse = false) : _reverse(reverse) {
        }
        bool operator()(std::tuple<int, int, int> const & left, std::tuple<int, int, int> const & right) {
            if (std::get<Solution::VAL_IDX>(left) <= std::get<Solution::VAL_IDX>(right)) {
                return !_reverse;
            } else {
                return _reverse;
            }
        }
    };

public:
    std::vector<std::vector<int>> kSmallestPairs(std::vector<int> const & nums1, std::vector<int> const & nums2, int k) {
        // plagiarizing idea from https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/discuss/85173/Share-my-thoughts-and-Clean-Java-Code
        std::vector<std::vector<int>> ans;
        int const nums1Size = nums1.size();
        if (JUST_ZERO == nums1Size) {
            return ans;
        }
        int const nums2Size = nums2.size();
        if (JUST_ZERO == nums2Size) {
            return ans;
        }
        typedef std::priority_queue<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>, Comp> MaxHeap;
        MaxHeap minHeap(Comp(true));
        minHeap.push(std::make_tuple(nums1[0] + nums2[0], 0, 0));
        
        std::vector<std::vector<bool>> seen(nums1Size, std::vector<bool>(nums2Size, false));
        
        while (k-- > 0 && !minHeap.empty()) {
            auto const & ele = minHeap.top();
            int nums1Idx = std::get<ROW_IDX>(ele);
            int nums2Idx = std::get<COL_IDX>(ele);
            minHeap.pop();
            ans.push_back({nums1[nums1Idx], nums2[nums2Idx]});
            // ans.push_back({nums1Idx, nums2Idx});
            if (nums1Idx < nums1Size - 1 && !seen[nums1Idx + 1][nums2Idx]) {
                seen[nums1Idx + 1][nums2Idx] = true;
                minHeap.push(std::make_tuple(nums1[nums1Idx + 1] + nums2[nums2Idx], nums1Idx + 1, nums2Idx));
            }
            if (nums2Idx < nums2Size - 1 && !seen[nums1Idx][nums2Idx + 1]) {
                seen[nums1Idx][nums2Idx + 1] = true;
                minHeap.push(std::make_tuple(nums1[nums1Idx] + nums2[nums2Idx + 1], nums1Idx, nums2Idx + 1));
            }
        }
        return ans;
    }

private:
    static int const JUST_ZERO = 0;
    static int const EX_MOST_LEFT_INDEX = -1;
    static int const VAL_IDX = 0;
    static int const ROW_IDX = 1;
    static int const COL_IDX = 2;
};
