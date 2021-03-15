#include "../../head.h"


class SolutionTLE {
public:
    int maxArea(std::vector<int> const & height) {
        int const heightSize = height.size();
        int ans = 0;
        for (int left = 0; left + 1 < heightSize; left++) {
            for (int right = left + 1; right < heightSize; right++) {
                ans = std::max(ans, std::min(height[right], height[left]) * (right - left));
            }
        }
        return ans;
        
    }
};

class Solution {
public:
    int maxArea(std::vector<int> const & height) {
        // plagiarizing from https://leetcode.com/problems/container-with-most-water/discuss/6090/Simple-and-fast-C%2B%2BC-with-explanation
        int const heightSize = height.size();
        int ans = 0;
        for (int left = 0, right = heightSize - 1; left < right;) {
            int minHeight = std::min(height[left], height[right]);
            ans = std::max(ans, minHeight * (right - left));
            // remove the minHeight from left
            while (height[left] <= minHeight && left < right) {
                left++;
            }
            // remove the minHeight from right
            // if height[left] = height[right] = minHeight. we just remove all of them. because if we only remove one of
            // them, the height of next area is nor larget than minHeight, and the width will minus at least one.
            // so the next area will never bigger than the cur area
            // https://leetcode.com/problems/container-with-most-water/discuss/6090/Simple-and-fast-C++C-with-explanation/230471
            while (height[right] <= minHeight && left < right) {
                right--;
            }
        }
        return ans;

    }

};

class Solution {
public:
    int maxArea(std::vector<int> const & height) {
        int i = 0, j = height.size() - 1;
        int max_area = 0;
        while (i < j) {
            int curr_area = (j - i) * std::min(height[i], height[j]);
            max_area = std::max(max_area, curr_area);
            if (height[i] < height[j]) {
                ++i;
            } else {
                --j;
            }
        }
        return max_area;
    }
};
