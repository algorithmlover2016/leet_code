#include "../../head.h"


// #define DEBUG
class Solution {
public:
    std::vector<int> findClosestElements(std::vector<int> const & arr, int k, int x) {
        int const arrSize = arr.size();
        int targetIdx = std::lower_bound(arr.begin(), arr.end(), x) - arr.begin();
        #ifdef DEBUG
        if (targetIdx < arrSize) {
            std::cout << arr[targetIdx] << "\n";
        }
        #endif

        int upIdx = targetIdx;
        int downIdx = targetIdx - 1;
        while (k-- > 0) {
            if (upIdx < arrSize && (downIdx < 0 || arr[upIdx] - x < x - arr[downIdx])) {
                #ifdef DEBUG
                std::cout << "up: " << arr[upIdx] << "\t";
                #endif
                upIdx++;
            } else if(downIdx >= 0 && (upIdx >= arrSize || x - arr[downIdx] <= arr[upIdx] - x)) {
                #ifdef DEBUG
                std::cout << "down: " << arr[downIdx] << "\t";
                #endif
                downIdx--;
            }
        }
        return std::vector<int>(arr.begin() + downIdx + 1, arr.begin() + upIdx);

    }
};

class Solution {
public:

    std::vector<int> findClosestElements(std::vector<int> const & arr, int k, int x) {
        // plagiarizing idea from https://leetcode.com/problems/find-k-closest-elements/discuss/106426/JavaC%2B%2BPython-Binary-Search-O(log(N-K)-%2B-K)
        int const arrSize = arr.size();
        int left = 0, right = arrSize - k;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (x - arr[mid] > arr[mid + k] - x) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return std::vector<int>(arr.begin() + left, arr.begin() + left + k);


    }
};
