#include "../../head.h"


class Solution {
public:
    double findMaxAverage(std::vector<int> const & nums, int k) {
        double ans = -100000;
        int const numsSize = nums.size();
        if (numsSize < k) {
            return ans;
        }
        
        double windSum = 0;
        for (int idx = 0; idx < numsSize; idx++) {
            windSum += nums[idx];
            if (idx >= k - 1) {
                ans = std::max(ans, windSum / k);
                windSum -= nums[idx - k + 1];
            }
        }
        return ans;
    }
private:
    static int const JUST_ONE = 1;
};


class Solution {
public:
    double findMaxAverage(std::vector<int> const & nums, int k) {
        // plagiarizing from https://leetcode.com/problems/maximum-average-subarray-i/discuss/105432/Java-solution-Sum-of-Sliding-window
        double ans = -100000 * k;
        int const numsSize = nums.size();
        if (numsSize < k) {
            return ans;
        }
        
        double windSum = 0;
        for (int idx = 0; idx < numsSize; idx++) {
            windSum += nums[idx];
            if (idx >= k - 1) {
                ans = std::max(ans, windSum);
                windSum -= nums[idx - k + 1];
            }
        }
        return ans / k;
    }
private:
    static int const JUST_ONE = 1;
};

class Solution {
public:
    double findMaxAverage(std::vector<int> const & nums, int k) {
        int max = 0,sum = 0,n = nums.size();
        for (int i = 0; i < k; i++) {
            sum += nums[i];
        }
        max = sum;
        for (int i = k; i < n; i++) {

            sum += nums[i] - nums[i - k];

            if (sum > max) {
                max = sum;
            }
        }
        return max / (k * 1.00);
    }
};
