#include "../../head.h"


// #define DEBUG
class SolutionTLE {
public:
    int sumOfFlooredPairs(std::vector<int> & nums) {
        // first. sort the elements in nums in non-descreasing order.
        // second. the later devide the former. the time complexity: n * n
        // third. compute the equal elements. If there are m equal elements, then we need add m * (m - 1) / 2 to the sum.
        if (nums.empty()) {
            return 0;
        }
        int numsSize = nums.size();
        long long int sum = numsSize;
        std::sort(std::begin(nums), std::end(nums));
        int equalNum = 1;
        for (int start = 0; start < numsSize; start++) {
            for (int end = start + 1; end < numsSize; end++) {
                int quotient = nums[end] / nums[start];
                sum += quotient;
            }
            #ifdef DEBUG
            std::cout << "sum: " << sum << "\n";
            #endif
            sum %= MOD;
            if (start > 0) {
                if (nums[start] == nums[start - 1]) {
                    equalNum += 1;
                } else {
                    sum += equalNum * (equalNum - 1LL) / 2;
                    sum %= MOD;
                    equalNum = 1;
                    #ifdef DEBUG
                    std::cout << "after add equal sum: " << sum << "\n";
                    #endif
                }
            }
        }
        // for the last elements, if equalNum = 0, there is no meaning.
        sum += equalNum * (equalNum - 1LL) / 2;
        sum %= MOD;
        return sum;
    }

private:
    int const MOD = 1e9 + 7;
};


class SolutionLessTLE {
public:
    int sumOfFlooredPairs(std::vector<int> const & nums) {
        // plagiarizing from https://leetcode.com/problems/sum-of-floored-pairs/discuss/1210073/C%2B%2B-Short-and-Easy-or-Frequency-Prefix-Sum-Solution-w-Explanation
        static int const MAX_NUM = 1e5;
        std::vector<int> preSumFreq(2 * MAX_NUM + 1, 0);
        int maxEle = 0;
        for (int num : nums) {
            assert(num > 0);
            assert(num <= MAX_NUM);
            preSumFreq[num]++;
            maxEle = std::max(maxEle, num);
            /*
            if (num > maxEle) {
                maxEle = num;
            }
            */

        }
        for (int idx = 1; idx < preSumFreq.size(); idx++) {
            preSumFreq[idx] += preSumFreq[idx - 1];
        }
        int sum = 0;
        for (int num : nums) {
            int left = num, right = 2 * num - 1, quotient = 1;
            while (left <= maxEle) {
                sum += (preSumFreq[right] - preSumFreq[left - 1]) * quotient;
                sum %= MOD;
                // sum = (sum + (preSumFreq[right] - preSumFreq[left - 1]) * quotient) % MOD;
                left += num, right += num, quotient++;
            }
        }
        return sum;
    }

private:
    int const MOD = 1e9 + 7;
};

class SolutionFenwick {
public:
    int sumOfFlooredPairs(std::vector<int> const & nums) {
        // plagiarizing from https://leetcode.com/problems/sum-of-floored-pairs/discuss/1210025/Prefix-Sum-Fenwick-Tree-Sort-and-Sieve
        // solution 2: Fenwick Tree
        int const maxEle = *std::max_element(std::begin(nums), std::end(nums));
        std::vector<int> freqFenwick(MAX_NUM, 0);
        std::unordered_map<int, int> eleCnts;
        for (int const num : nums) {
            eleCnts[num]++;
            freqUpdate(freqFenwick, maxEle + 1, num, 1);
        }

        long ans = 0;
        for (auto & [num, cnt] : eleCnts) {
            for (long quotient = maxEle / num; quotient > 0; quotient--) {
                ans = (ans + cnt * quotient * (freqSum(freqFenwick, (quotient + 1) * num - 1) - freqSum(freqFenwick, quotient * num - 1))) % MOD;

            }
        }
        return ans;


    }
    void freqUpdate(std::vector<int> & freqFenwick, int const maxEle, int ele, int val) {
        for (int start = ele + 1; start <= maxEle; start += (start & (-start))) {
            freqFenwick[start] += val;
        }
    }

    int freqSum(std::vector<int> const & freqFenwick, int ele) {
        int sum = 0;
        for (int start = ele + 1; start > 0; start -= (start & (-start))) {
            sum += freqFenwick[start];
        }
        return sum;
    }
private:
    static int const MOD = 1e9 + 7;
    static int const MAX_NUM = 1e5 + 2;
};

class Solution {
public:
    int sumOfFlooredPairs(std::vector<int> const & nums) {
        // plagiarizing from https://leetcode.com/problems/sum-of-floored-pairs/discuss/1210025/Prefix-Sum-Fenwick-Tree-Sort-and-Sieve
        // solution 2: sieve
        int const maxEle = *std::max_element(std::begin(nums), std::end(nums));
        std::vector<long> sieve(MAX_NUM, 0);
        std::vector<int> cnts(MAX_NUM, 0);
        for (int const num : nums) {
            cnts[num]++;
        }

        for (int idx = 1; idx <= maxEle; idx++) {
            if (cnts[idx] > 0) {
                int quotient = maxEle / idx;
                for (int freq = 1; freq <= quotient; freq++) {
                    sieve[idx * freq] += cnts[idx];
                }
            }
        }
        // compute the presum of the array of sieve and save the result into sieve
        std::partial_sum(std::begin(sieve), std::end(sieve), std::begin(sieve));
        return std::accumulate(std::begin(nums), std::end(nums), 0L, [&] (long sum, int num) {return (sum + sieve[num]) % MOD;});
    }

private:
    static int const MOD = 1e9 + 7;
    static int const MAX_NUM = 1e5 + 1;
};