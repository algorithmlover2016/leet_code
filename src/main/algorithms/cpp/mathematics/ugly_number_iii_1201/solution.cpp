#include "../../head.h"


// #define DEBUG
class SolutionTLE {
public:
    int nthUglyNumber(int n, int a, int b, int c) {
        long long int product = 0;
        while (0 < n--) {
            #ifdef DEBUG
            std::cout << "cur: " << n << "\t";
            #endif
            while (0 != ++product % a && 0 != product % b && 0 != product %c) {
                ;
            }
            #ifdef DEBUG
            std::cout << "product: " << product << "\n";
            #endif
        }
        return product;
        
    }
};

// #define DEBUG
class Solution {
public:

    int nthUglyNumber(int n, int a, int b, int c) {
        // plagiarizing from https://leetcode.com/problems/ugly-number-iii/discuss/387539/cpp-Binary-Search-with-picture-and-Binary-Search-Template
        int lo = 1, hi = 2*(1e9);
        long int along = a, blong = b, clong = c;
        long int ablong = along * blong / __gcd(along, blong);
        long int aclong = along * clong / __gcd(along, clong);
        long int bclong = blong * clong / __gcd(blong, clong);
        // a, b, c 最小公倍数= a 和b * c 的最小公倍数
        long int abclong = along * bclong / __gcd(along, bclong);
        #ifdef DEBUG
        std::cout << along << ",\t" << blong << ",\t" << clong << ",\t"
            << ablong << ",\t" << bclong << ",\t" << aclong << ",\t" << abclong << "\n";
        #endif

        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            int cnt = mid / along + mid / blong + mid / clong - mid / ablong - mid / aclong - mid / bclong + mid /abclong;
            #ifdef DEBUG
            std::cout << lo << ",\t" << hi << ",\t" << mid << ",\t" << cnt << "\n";
            #endif
            if (cnt < n) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
        #ifdef DEBUG
        std::cout << std::endl;
        #endif
        return lo;
    }
};
