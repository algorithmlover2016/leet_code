#include "../../head.h"


class Solution {
public:
    int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
        // why not find 2^x = buckets; return x?
        if (0 == minutesToDie) {
            return 0;
        }
        if (2 > buckets) {
            return buckets;
        }
        int nums = minutesToTest / minutesToDie;
        int start = 0; end = buckets - 1;
        int res = 0;
        while (start < end) {
            int mid = (start + end) >> 1;
            res++;
            end = start;
        }
        return static_cast<int>(<ceil(res / nums));
        
    }
};

class Solution {
public:
    int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
        // plagiarizing from https://leetcode.com/problems/poor-pigs/discuss/94266/Another-explanation-and-solution
        if (0 == minutesToDie){
            return 0;
        }
        int nums = minutesToTest / minutesToDie + 1;
        int pigs = 0;
        while (static_cast<int>(std::pow(nums, pigs)) < buckets) {
            pigs++;
        }
        return pigs;
    }
};
