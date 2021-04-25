#include "../../head.h"


// #define DEBUG
#define COMPUTE_NO_USING_MULTIPLY_AVOID_OVERFLOWING
class Solution {
public:
    int getXORSum(std::vector<int> const & arr1, std::vector<int> const & arr2) {
        // plagiarizing from https://youtu.be/n1rMJWTuqBU
        int const MAX_BITS = sizeof(int) * BYTE_BITS;
        #ifdef DEBUG
        std::cout << MAX_BITS << "\n";
        #endif
        std::vector<int> arr1Bits(MAX_BITS, 0);
        std::vector<int> arr2Bits(MAX_BITS, 0);
        int ans = 0;
        for (int idx = 0; idx < MAX_BITS; idx++) {
            for (int num : arr1) {
                if (num & (1 << idx)) {
                    arr1Bits[idx]++;
                }
            }
            for (int num : arr2) {
                if (num & (1 << idx)) {
                    arr2Bits[idx]++;
                }
            }
            #ifdef DEBUG
            std::cout << arr1Bits[idx] << ", " << arr2Bits[idx] << "\n";
            #endif

#ifdef COMPUTE_NO_USING_MULTIPLY_AVOID_OVERFLOWING
            ans |= (1 & arr2Bits[idx] & arr1Bits[idx]) ? (1 << idx) : 0;
#else
            ans |= 1 & ((long)arr2Bits[idx] * (long)arr1Bits[idx]) ? (1 << idx) : 0;
#endif
        }
        return ans;
    }
private:
    static int const BYTE_BITS = 8;
};

class Solution {
public:
    int getXORSum(std::vector<int> const & arr1, std::vector<int> const & arr2) {
        // plagiarizing from https://youtu.be/n1rMJWTuqBU
        int xorArr1Ans = 0;
        int xorArr2Ans = 0;
        for (int num : arr1) {
            xorArr1Ans ^= num;
        }
        for (int num : arr2) {
            xorArr2Ans ^= num;
        }
        return xorArr1Ans & xorArr2Ans;
    }
};
