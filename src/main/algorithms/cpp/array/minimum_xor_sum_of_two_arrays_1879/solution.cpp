#include "../../head.h"


class Solution {
public:
    int minimumXORSum(std::vector<int> const & nums1, std::vector<int> const & nums2, int idx = 0, int mask = 0) {
        // plagiarizing from https://leetcode.com/problems/minimum-xor-sum-of-two-arrays/discuss/1238641/Bit-Mask
        // DFS Memorise
        int const nums1Size = nums1.size();
        int const nums2Size = nums2.size();
        if (idx >= nums1Size) {
            // reach to the end of nums1
            return 0;
        }

        if (dpMem[mask] == INT_MAX) {
            for (int selIdx = 0; selIdx < nums2Size; selIdx++) {
                if (!(mask & ( 1 << selIdx))) {
                    // nums1[idx] has not xor with nums2[selIdx]
                    dpMem[mask] = std::min(dpMem[mask], (nums1[idx] ^ nums2[selIdx]) + minimumXORSum(nums1, nums2, idx + 1, mask | (1 << selIdx)));
                }
            }
        }
        return dpMem[mask];

    }
private:
    static int const MAX_LEN = 14;
private:
    // std::array<int, (1 << MAX_LEN)> dpMem = {[0 ... (1 << MAX_LEN)] = INT_MAX};
    
    int dpMem[(1 << MAX_LEN)] = {[0 ... ((1 << MAX_LEN) - 1)] = INT_MAX};
            
};