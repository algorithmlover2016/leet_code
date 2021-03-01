#include "../../head.h"


// #define AVOID_OVERFLOW
class SolutionTLE {
public:
    std::vector<int> threeEqualParts(std::vector<int> const & arr) {
        int const arrSize = arr.size();
        if (AT_LEAST_LEN > arrSize) {
            return {-1, -1};
        }
        #ifdef AVOID_OVERFLOW
        std::vector<std::vector<std::string>> dpMemo(arrSize, std::vector<std::string>(arrSize));
        #else
        std::vector<std::vector<long>> dpMemo(arrSize, std::vector<long>(arrSize, 0));
        #endif
        for (int left = 0; left < arrSize; left++) {
            #ifdef AVOID_OVERFLOW
            dpMemo[left][left] = std::to_string(arr[left]);
            #else
            dpMemo[left][left] = arr[left];
            #endif
            for (int right = left + 1; right < arrSize; right++) {
                #ifdef AVOID_OVERFLOW
                if (ZERO_STR == dpMemo[left][right - 1]) {
                    dpMemo[left][right] = std::to_string(arr[right]);
                } else {
                    dpMemo[left][right] = dpMemo[left][right - 1] + std::to_string(arr[right]);
                }
                #else
                dpMemo[left][right] = dpMemo[left][right - 1] * 2 + arr[right];
                #endif
            }
        }
        for (int left = 0; left < arrSize - 1; left++) {
            for (int right = left + 2; right < arrSize; right++) {
                if (dpMemo[0][left] == dpMemo[left + 1][right - 1] &&
                    dpMemo[left + 1][right - 1] == dpMemo[right][arrSize - 1]) {
                    return {left, right};
                }
            }
        }
        return {-1, -1};

    }
private:
    static int const AT_LEAST_LEN = 3;
    #ifdef AVOID_OVERFLOW
    static std::string const ZERO_STR;
    #endif
};
#ifdef AVOID_OVERFLOW
std::string const Solution::ZERO_STR("0");
#endif

class Solution {
public:
    std::vector<int> threeEqualParts(std::vector<int> const & A) {
        // plagiarizing from https://leetcode.com/problems/three-equal-parts/discuss/183922/C%2B%2B-O(n)-time-O(1)-space-12-ms-with-explanation-and-comments
	    // Count no of 1's in the given array
        int countNumberOfOnes = 0;
        for (int c: A) {
            if (c == 1) {
                countNumberOfOnes++;
            }
        }

	    // If no 1 is found, that means we can return ans as {0, size-1}
        if (countNumberOfOnes == 0) {
            return {0, (int)A.size()-1};
        }

        // If no of 1's is not a multiple of 3, then we can never find a possible partition since
        // there will be atkeast one partition that will have different no of 1's and hence
        // different binary representation
        // For example,
        // Given :
        // 0000110  110  110
        //       |  |    |
        //       i       j
        // Total no of ones = 6
        // 0000110         110      110
        //     |           |        |
        //     start       mid      end
        // Match starting from first 1, and putting 2 more pointers by skipping k 1's

        if (countNumberOfOnes % 3 != 0) {
            return {-1, -1};
        }

        // find size of each partition
        int k = countNumberOfOnes / 3;
        int i;

        // find the first 1 in the array
        for (i = 0; i < A.size(); i++) {
            if (A[i] == 1) {
                break;
            }
        }
        int start = i;

        // find (k+1)th 1 in the array
        int count1 = 0;
        for (; i < A.size(); i++) {
            if (A[i] == 1) {
                count1++;
            }
            if (count1 == k + 1) {
                break;
            }
        }
        int mid = i;

        //find (2*k +1)th 1 in the array
        count1 = 0;
        for (;i < A.size(); i++) {
            if(A[i] == 1) {
                count1++;
            }
            if (count1 == k + 1) {
                break;
            }
        }
        int end = i;

        // Match all values till the end of the array
        while(end< A.size() && A[start] == A[mid] && A[mid] == A[end]) {
            start++; mid++; end++;
        }

        // Return appropriate values if all the values have matched till the end
        if (end == A.size()) {
            return {start - 1, mid};
        }

        // otherwise, no such indices found
        return {-1, -1};
    }
};
