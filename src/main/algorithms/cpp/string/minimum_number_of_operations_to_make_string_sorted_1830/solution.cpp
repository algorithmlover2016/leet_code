#include "../../head.h"


#define ACCUMULATE_BY_SUM
class Solution {
public:
    int makeStringSorted(std::string const & s) {
        // plagiarizing from https://www.youtube.com/watch?v=Lfiz6iwp4l8 and
        // https://leetcode.com/problems/minimum-number-of-operations-to-make-string-sorted/discuss/1163050/Python-O(26n)-math-solution-explained and
        // https://leetcode.com/problems/minimum-number-of-operations-to-make-string-sorted/discuss/1164153/C%2B%2B-24-ms

        // accoding to https://en.wikipedia.org/wiki/Fermat%27s_little_theorem
        // if p is a prime number, then (a ^ (p - 1)) % p = 1 % p => (a ^ (p - 2) * a) % p = 1 % p;
        // => ((a ^ (p - 2)) % p) * (a % p) = 1 % p
        static bool initFac = (init(), true);

        int const sSize = s.size();
        if (1 >= sSize) {
            return 0;
        }
        std::vector<int> cnts(LETTERS_CNTS, 0);
        int ans = 0;
        for (int idx = sSize - 1; idx > -1; idx--) {
            int num = s[idx] - OFFSET;
            cnts[num]++;
#ifdef ACCUMULATE_BY_SUM
            long frac = std::accumulate(cnts.begin(), cnts.begin() + num, 0L)  * factorial[sSize - 1 - idx] % MOD;
            for (int denominatorIdx = 0; denominatorIdx < LETTERS_CNTS; denominatorIdx++) {
                frac = frac * invFactorial[cnts[denominatorIdx]] % MOD;
            }

            ans = (ans + frac) % MOD;
#else
            for (int less = 0; less < num; less++) {
                if (0 < cnts[less]) {
                    cnts[less]--;
                    long frac = factorial[sSize - 1 - idx];
                    for (int denominatorIdx = 0; denominatorIdx < LETTERS_CNTS; denominatorIdx++) {
                        frac = frac * invFactorial[cnts[denominatorIdx]] % MOD;
                    }
                    ans = (ans + frac) % MOD;
                    cnts[less]++;
                }
            }
#endif
        }
        return ans;
    }
    private:

    void init() {
        for (int idx = 2; idx < MAX_LEN; idx++) {
            factorial[idx] = ((long)factorial[idx - 1] * idx) % MOD;
            invFactorial[idx] = modPow(factorial[idx], MOD - 2, MOD);
        }
    }

    // plagirizing from https://leetcode.com/problems/minimum-number-of-operations-to-make-string-sorted/discuss/1164153/C%2B%2B-24-ms
    int modPow(int x, unsigned int y, int mod) {
        if (0 == y) {
            return 1;
        }
        long halfAns = modPow(x, y / 2, mod);
        long ans = (halfAns * halfAns) % mod;
        return (y & 0x01) ? (ans * x) % mod: ans;
    }

    private:
    static int const MOD = 1e9 + 7; // it's a prime number
    static int const MAX_LEN = 3000 + 1;
    static int const LETTERS_CNTS = 26;
    static char const OFFSET = 'a';
    static std::vector<int> factorial;
    static std::vector<int> invFactorial;
};
std::vector<int> Solution::factorial(Solution::MAX_LEN, 1);
std::vector<int> Solution::invFactorial(Solution::MAX_LEN, 1);
