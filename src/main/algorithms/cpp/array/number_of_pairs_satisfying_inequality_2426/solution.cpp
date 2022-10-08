#include "../../head.h"


class SolutionTLE {
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

class SolutionTLE {
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