#include "../../head.h"


class Solution {
public:
    int maxWidthRamp(std::vector<int> const & A) {
        int ASize = A.size();
        if (2 > ASize) {
            return 0;
        }
        int ans = 0;
        for (int i = 0; i < ASize; i++) {
            // there are some elements that are no need to iterator
            for (int j = ASize - 1; j > i; j--) {
                if (A[j] >= A[i]) {
                    ans = std::max(ans, j - i);
                    break;
                }
            }
            if (ans >= ASize - i) {
                break;
            }
        }
        return ans;
    }
};

class SolutionNlnN {
public:
    int maxWidthRamp(std::vector<int> const & A) {
        // plagiarizing from https://leetcode.com/problems/maximum-width-ramp/discuss/208348/JavaC%2B%2BPython-O(N)-Using-Stack
        int ASize = A.size();
        if (2 > ASize) {
            return 0;
        }
        std::vector<int> descreaseEles;
        int ans = 0;
        for (int index = 0; index < ASize; index++) {
            // store the index of descrease elements
            if (descreaseEles.empty() || A[index] < A[descreaseEles.back()]) {
                // std::cout << "push elements: " << A[index] << "\n";
                descreaseEles.emplace_back(index);
            } else {
                // binary search
                int left = 0, right = descreaseEles.size() - 1, mid = 0;
                while (left < right) {
                    mid = (left + right) >> 1;
                    if (A[descreaseEles[mid]] > A[index]) {
                        left = mid + 1;
                    } else {
                        right = mid;
                    }
                    // std::cout << "left: " << A[descreaseEles[left]] << "\t"
                    //     << "right: " << A[descreaseEles[right]] << "\n";
                }
                ans = std::max(ans, index - descreaseEles[left]);
            }
        }
        return ans;
    }
};


class Solution2N {
public:
    int maxWidthRamp(std::vector<int> const & A) {
        // plagiarizing from https://leetcode.com/problems/maximum-width-ramp/discuss/208348/JavaC%2B%2BPython-O(N)-Using-Stack
        int ASize = A.size();
        if (2 > ASize) {
            return 0;
        }
        std::vector<int> descreaseEles;
        for (int index = 0; index < ASize; index++) {
            // store the index of descrease elements
            if (descreaseEles.empty() || A[index] < A[descreaseEles.back()]) {
                descreaseEles.emplace_back(index);
            }
        }

        int ans = 0;
        for (int index = ASize - 1; index > ans; index--) {
            while (!descreaseEles.empty() && A[index] >= A[descreaseEles.back()]) {
                ans = std::max(ans, index - descreaseEles.back());
                descreaseEles.pop_back();
            }
        }
        return ans;
    }
};
