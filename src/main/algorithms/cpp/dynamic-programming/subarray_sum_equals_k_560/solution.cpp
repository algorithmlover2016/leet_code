#include "../../head.h"


class SolutionTimeLimit {
public:
    int subarraySum(std::vector<int> const & nums, int const k) {
        int numsSize = nums.size();
        if (0 == numsSize) {
            return k == 0;
        }
        std::vector<int> preSums(numsSize + 1, 0);
        for (int index = 0; index < numsSize; index++) {
            preSums[index + 1] = nums[index] + preSums[index];
        }

        int res = 0;
        for (int start = 1; start < preSums.size(); start++) {
            for (int end = start; end < preSums.size(); end++) {
                if (k == preSums[end] - preSums[start - 1]) {
                    res++;
                }
            }
        }
        return res;

    }
};


class SolutionBetterRunTime {
public:
    int subarraySum(std::vector<int> const & nums, int const k) {
        // plagiarizing from https://leetcode.com/problems/subarray-sum-equals-k/discuss/102106/Java-Solution-PreSum-%2B-HashMap
        int numsSize = nums.size();
        if (0 == numsSize) {
            return k == 0;
        }
        std::unordered_map<int, int> sumPair{{0, 1}};
        int res = 0;
        int sum = 0;
        for (int index = 0; index < numsSize; index++) {
            sum += nums[index];
            res += sumPair.find(sum - k) != sumPair.end() ? sumPair[sum - k] : 0;
            sumPair[sum]++;
        }
        return res;

    }
};

class SolutionMuchBetter {
public:
    int subarraySum(std::vector<int> const & nums, int k) {
        int prefixsum = 0;
        static int const size = 56000;
        uint16_t sprefixsum[size*2] = {};
        int count= 0;
        sprefixsum[0+size] = 1;
        for (int i=0;i<nums.size();++i) {
            prefixsum+=nums[i];
            auto lookfor = prefixsum-k;
            count+=sprefixsum[lookfor+size];
            sprefixsum[prefixsum+size]++;
        }
        return count;
    }
};
