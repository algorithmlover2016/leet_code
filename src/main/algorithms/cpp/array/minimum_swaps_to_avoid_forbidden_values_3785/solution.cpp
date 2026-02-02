#include "../../head.h"



class Solution {
public:
    int minSwaps(vector<int>& nums, vector<int>& forbidden) {
        if (nums.empty() || forbidden.empty() || nums.size() != forbidden.size()) {
            return 0;
        }
        int n = nums.size();
        std::map<int, int> numsFreq, forbFreq, matchingFreq;
        int matchCount = 0;
        int sameNumMatchMaxFreq = 0;
        for (int idx = 0; idx < n; idx++) {
            if (nums[idx] == forbidden[idx]) {
                matchCount++;
                sameNumMatchMaxFreq = std::max(sameNumMatchMaxFreq, ++matchingFreq[nums[idx]]);
            }
            numsFreq[nums[idx]]++; forbFreq[forbidden[idx]]++;
        }
        for (auto & pr : numsFreq) {
            int num = pr.first;
            int freq = pr.second;
            if (freq > n - forbFreq[num]) {
                // there is no enough vacant slot to put num.
                return -1;
            }
        }
        return std::max(sameNumMatchMaxFreq, (matchCount + 1)/2);
    }

};