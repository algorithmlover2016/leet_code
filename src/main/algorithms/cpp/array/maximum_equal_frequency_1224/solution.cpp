#include "../../head.h"


// #define DEBUG
class Solution {
public:
    int maxEqualFreq(std::vector<int> const & nums) {
        // plagiarizing from https://leetcode.com/problems/maximum-equal-frequency/discuss/403743/JavaC%2B%2BPython-Only-2-Cases%3A-Delete-it-or-not
        int const numsSize = nums.size();
        std::unordered_map<int, int> cnts;
        std::unordered_map<int, int> freqs;
        int ans = 0;
        for (int idx = 1; idx <= numsSize; idx++) {
            int num = nums[idx - 1]; // get the cur num
            freqs[cnts[num]]--; // if 0 == cnts[num], just freqs[0]--;
            int c = ++cnts[num]; // cur element appear times
            int freq = ++freqs[c];
            #ifdef DEBUG
            std::cout << num << "\t" << c << "\t" << freq << "\n";
            #endif
            if (freq * c == idx && idx != numsSize) {
                ans = idx + 1;
            } else {
                int d = idx - freq * c; // idx (total number of elements - c * freq)
                if ((1 == d || d == c + 1 /*to make sure we can remove one elment*/) &&
                    /* to make sure the d represent a num */ freqs[d] == 1) {
                    ans = idx;
                }

            }
        }
        return ans;

    }
};

