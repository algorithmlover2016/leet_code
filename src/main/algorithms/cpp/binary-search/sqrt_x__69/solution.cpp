#include "../../head.h"


#define DEBUG
class Solution {
public:
    int mySqrt(int x) {
        if (JUST_ONE >= x) {
            return x;
        }
        long long left = 1;
        long long right = x / 2;
        #ifdef DEBUG
        int loopCnt = 0;
        #endif
        while (left < right) {
            long long mid = left + (right - left) / 2;
            long long m = multiplySelf(mid);
            #ifdef DEBUG
            std::cout << left << ", " << right << ", " << mid << "\n";
            #endif
            if (m >= x) {
                right = mid;
            } else {
                left = mid + 1;
            }
            #ifdef DEBUG
            loopCnt++;
            #endif
        }
        #ifdef DEBUG
        std::cout << loopCnt << "\n";
        #endif
        return left * left <= x ? left : left - 1;
    }
private:
    long long multiplySelf(long long x) {
        return x * x;
    }
private:
    static int const JUST_ONE = 1;
};

class Solution {
public:
    int mySqrt(int x) {
        if (x <= 1) {
            return x;
        }
        int left = 1, right = x;
        int mid;
        while (left < right) {
            mid = left + (right - left) / 2;
            if (x / mid == mid) {
                return mid;
            } else if (x / mid < mid) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return right - 1;
    }
};

#define DEBUG
class Solution {
public:
    int mySqrt(int x) {
        if (JUST_ONE >= x) {
            return x;
        }
        // plagiarizing from https://leetcode.com/problems/sqrtx/discuss/25057/3-4-short-lines-Integer-Newton-Every-Language
        //  we assume that x > 0 ans y > 0; then there is a inequality x^2 + y^2 >= 2*x*y
        long long int ans = x;
        #ifdef DEBUG
        int loopCnt = 0;
        #endif
        while (ans * ans > x) {
            ans = (ans + x / ans) / 2;
            #ifdef DEBUG
            loopCnt++;
            #endif
        }
        #ifdef DEBUG
        std::cout << loopCnt << "\n";
        #endif
        return ans;
    }
private:
    static int const JUST_ONE = 1;
};
