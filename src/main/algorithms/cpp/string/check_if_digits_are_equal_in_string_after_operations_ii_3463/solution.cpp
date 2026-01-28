#include "../../head.h"

class Solution {
private:
    // Precomputed binomial coefficients modulo 5 for n, k < 5
    // C(n, k) % 5
    const int C_MOD_5[5][5] = {
        {1, 0, 0, 0, 0},
        {1, 1, 0, 0, 0},
        {1, 2, 1, 0, 0},
        {1, 3, 3, 1, 0},
        {1, 4, 1, 4, 1}  // Note: 6 % 5 = 1
    };

    // Lucas theorem to compute nCr % 5
    int lucasMod5(int n, int k) {
        if (k == 0) return 1;
        return (lucasMod5(n / 5, k / 5) * C_MOD_5[n % 5][k % 5]) % 5;
    }

    // Lucas theorem equivalent for nCr % 2
    // nCr is odd if and only if (n & k) == k
    int nCrMod2(int n, int k) {
        return ((n & k) == k) ? 1 : 0;
    }

    // Compute nCr % 10 using Chinese Remainder Theorem
    int nCrMod10(int n, int k) {
        int mod2 = nCrMod2(n, k);
        int mod5 = lucasMod5(n, k);
        
        // We need x such that:
        // x = mod2 (mod 2)
        // x = mod5 (mod 5)
        // Formula: x = (5 * mod2 + 6 * mod5) % 10
        return (5 * mod2 + 6 * mod5) % 10;
    }

public:
    bool hasSameDigits(std::string s) {
        int n = s.size();
        if (n == 2) {
            return s[0] == s[1];
        }

        // We want to reduce n digits to 2 digits.
        // This takes m = n - 2 operations.
        // The coefficients follow the m-th row of Pascal's triangle.
        int m = n - 2;
        int leftSum = 0;
        int rightSum = 0;

        for (int i = 0; i <= m; ++i) {
            int coeff = nCrMod10(m, i);
            int d1 = s[i] - '0';
            int d2 = s[i + 1] - '0';

            leftSum = (leftSum + coeff * d1) % 10;
            rightSum = (rightSum + coeff * d2) % 10;
        }

        return leftSum == rightSum;
    }
};