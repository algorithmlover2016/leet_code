#include "../../head.h"


class Solution {
public:
    int maxValue(int n, int index, int maxSum) {
        // plagiarizing from https://leetcode.com/problems/maximum-value-at-a-given-index-in-a-bounded-array/discuss/1119708/C%2B%2B-Binary-Search-O(log-n) and
        // https://leetcode.com/problems/maximum-value-at-a-given-index-in-a-bounded-array/discuss/1119801/JavaC%2B%2BPython-Binary-Search
        // I just add some comment for formula
        if (1 > n /*size of the array is at least 1 */ ||
                n > maxSum /*each element in the array is at least 1*/ ||
                index >= n /*the index must be smaller than n*/) {
            // error input
            return 0;
        }
        int left = 0, right = maxSum;
        int leftPart = index; // it record the number of elements, starting from 1
        int rightPart = n - 1 - index;
        int maxSumExceptOnes = maxSum - n;
        while (left < right) {
            long mid = (left + right + 1) / 2;
            // int mid = left + (right - left) / 2;
            /*
               Notice we have remove the basic 1 by maxSumExceptOnes = maxSum - n;
               mid * mid =
               for leftPart:
               if we think there is enough elements, which means leftPart >= mid:
               then the leftPartSum will be: 1 + 2 + ... + mid = (mid + 1) * mid / 2 = (mid ^ 2 + mid) / 2
               for rightPart:
               if we alse think there is enough elements, which means rightPart >= mid:
               then the rightPartSum will be: mid - 1 + mid - 2 + ... + 1 =
                                            (1 + mid - 1) * (mid - 1) / 2 = (mid ^ 2 - mid) / 2
               because we have consider the mid in the leftPart, so the rightPart starts from mid - 1;
               we add the two items, (mid ^ 2 + mid + mid ^ 2 - mid) / 2 = mid ^ 2 = mid * mid

               if mid > leftPart, which means we don't have enough elements to set value, the left most value will be
               mid - index = mid - leftPart, so when we accumulate the sum in above step, we should minus the sum of
               (1 + 2 + ... + mid - leftPart - 1) = (mid - leftPart - 1 + 1) * (mid - leftPart - 1) / 2 =
               (mid - leftPart) * (mid - leftPart - 1) / 2;
               the reason why the left most value will be mid - leftPart, because from the index of mid position, we
               move to left, when we arrive the 0-th element, we need leftPart step.
               same reason to rightPart
               if mid > rightPart, which also means we can't set the right most value to be 1, the right most value will
               be mid - rightPart, so we should minus the sum of (1 + 2 + ... + mid - rightPart - 1) =
               (mid - rightPart - 1 + 1) * (mid - rightPart - 1) / 2 = (mid - rightPart) * (mid - rightPart - 1) / 2
               the reason why the right most value is mid - rightPart is that there are rightPart elements from index(excluded,
               index belongs to mid), so at index + 1 position, we will set the value with mid - 1, and so on, when we arrive at
               index + rightPart (which is the last element, whose index is n - 1), the value will be mid - rightPart
            */
            long need = mid * mid - (
                    ((mid > leftPart) ? (mid - leftPart - 1) * (mid - leftPart) : 0) +
                    ((mid > rightPart) ? (mid - rightPart - 1) * (mid - rightPart) : 0)) / 2;
            if (need <= maxSumExceptOnes) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }
        return left + 1; /*because we compute the mid exclude the original 1 set in each pos*/
    }
};
