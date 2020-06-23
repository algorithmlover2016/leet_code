#include "../../head.h"


class Solution {
public:
    int trap(std::vector<int> const & height) {
        // plagiarizing from https://leetcode.com/problems/trapping-rain-water/discuss/17357/Sharing-my-simple-c%2B%2B-code%3A-O(n)-time-O(1)-space
        int heightSize = height.size();
        if (3 > heightSize) {
            return 0;
        }
        int res = 0;
        int left = 0, right = heightSize - 1;
        int maxLeft = 0, maxRight = 0;
        while (left <= right) { // if there is no =, the last element maybe not count
            if (height[left] <= height[right]) {
                if (height[left] > maxLeft) {
                    maxLeft = height[left];
                } else {
                    res += maxLeft - height[left];
                }
                left++;
            } else {
                if (height[right] > maxRight) {
                    maxRight = height[right];
                } else {
                    res += maxRight - height[right];
                }
                right--;
            }
        }
        return res;
    }
};

class SolutionDiff {
public:
    Solution(){
        ios::sync_with_stdio(false);
        std::cin.tie(nullptr);
        std::cout.tie(nullptr);
    }
    int trap(std::vector<int> const & height) {
        if(height.size() <= 1)
            return 0;
        int left_max=0, right_max=0,result = 0;
        int low = 0, high = height.size() - 1;

        while(low<=high) {
            if(height[low] < height[high]){
                if(height[low] > left_max)
                    left_max = height[low];
                else
                    result+=left_max - height[low];
                low++;
            }
            else{
                if(height[high] > right_max)
                    right_max = height[high];
                else
                    result+=right_max - height[high];
                high--;
            }
        }
        return result;
    }
};

class Solution {
public:
    int trap(std::vector<int> const & height) {
        int heightSize = height.size();
        int left = 0, right = heightSize - 1;
        int res = 0, maxLeft = INT_MIN, maxRight = INT_MIN;
        while (left <= right) {
            maxLeft = std::max(height[left], maxLeft);
            maxRight = std::max(height[right], maxRight);
            if (maxLeft <= maxRight) {
                res += maxLeft - height[left];
                left++;
            } else {
                res += maxRight - height[right];
                right--;
            }
        }
        return res;
    }
};
