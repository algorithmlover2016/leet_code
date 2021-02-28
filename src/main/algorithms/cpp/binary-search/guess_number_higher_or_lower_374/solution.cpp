#include "../../head.h"


/** 
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is lower than the guess number
 *			      1 if num is higher than the guess number
 *               otherwise return 0
 * int guess(int num);
 */

class Solution {
public:
    int guessNumber(int n) {
        int left = 1, right = n;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int ans = guess(mid);
            if (0 == ans) {
                return mid;
            } else if (0 > ans) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        // the program will never get here, if pick ranges from 1 to n
        return left;
    }
};

class Solution {
public:
    int guessNumber(int n) {
       int start = 1;
        int end = n;

        while (start <= end) {
            int mid = start + (end -start) / 2;

            int ret = guess(mid);
            if (ret == 1)
                start = mid + 1;
            else if (ret == -1)
                end = mid - 1;
            else
                return mid;
        }
        return -1;
    }
};
