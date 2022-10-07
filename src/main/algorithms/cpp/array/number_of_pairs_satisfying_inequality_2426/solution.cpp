#include "../../head.h"


class Solution {
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