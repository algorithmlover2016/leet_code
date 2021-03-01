#include "../../head.h"


class Solution {
public:
    int minimumSize(std::vector<int> const & nums, int maxOperations) {
        // plagiarizing from https://youtu.be/znZ4wT1L8Y0
        int left = INIT_MIN_ELE, right = *std::max_element(nums.begin(), nums.end());
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (helper(nums, maxOperations, mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
private:
    bool helper(std::vector<int> const & nums, int const maxOperations, int mid) { 
        int cnt = 0;
        for (int const num : nums) {
            cnt += (num - 1) / mid;
        }
        return cnt <= maxOperations;
    }
private:
    static int const INIT_MIN_ELE = 1;
};

class Solution {
public:
    int minimumSize(std::vector<int> const & nums, int const maxOperations) {
        int left = 1;
        int right = *std::max_element(nums.begin(), nums.end());
        while (left < right) {
            int mid = left + (right - left) / 2;
            int count = 0;
            for(int x : nums) {
                count += (x + mid - 1) / mid - 1;
            }
            if (count > maxOperations) {
                left = mid + 1;
            } else {
                right = mid;
            }

        }
        return left;
    }
};
