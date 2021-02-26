#include "../../head.h"

#define TEST_MAIN

#define DEBUG
// #define DEBUG_DETAIL
class Solution {
public:
    std::vector<int> waysToFillArray(std::vector<std::vector<int>> const & queries) {
        // plagiarizing from https://leetcode.com/problems/count-ways-to-make-array-with-product/discuss/1035607/C%2B%2BPython-Precompute
        // and https://leetcode.com/problems/count-ways-to-make-array-with-product/discuss/1031331/C%2B%2B-prime-factorization-and-combinatorics-solution-beats-100-with-explanation-and-comments
        if (!initDone) {

#ifdef DEBUG
            std::cout << "init static data member in non-static function: " << __func__ << '\n';
#endif

            init();
        }
        int const queriesSize = queries.size();
        std::vector<int> ans(queriesSize, 1);
        for (int idx = 0; idx < queriesSize; idx++) {
            if (QUERY_LEN > queries[idx].size()) {
                continue;
            }
            int n = queries[idx][QUERY_FIRST_IDX], k = queries[idx][QUERY_SECOND_IDX];
            for (auto const p : primes) {
                int cnt = 0;
                while (0 == k % p) {
                    cnt++;
                    k /= p;
                }
                ans[idx] = (long)ans[idx] * comb[n + cnt - 1][cnt] % MOD;
            }
            if (1 != k) {
                ans[idx] = (long)ans[idx] * n % MOD;
            }
        }
        return ans;
    }

    static void init() {
        std::vector<bool> tmpPrimes(MAX_LEN, true);
        tmpPrimes[0] = false;
        tmpPrimes[1] = false;
        for (int idx = 2; idx * idx < MAX_LEN; idx++) {
            if (tmpPrimes[idx]) {
                for (int next = idx * idx; next < MAX_LEN; next += idx) {
                    tmpPrimes[next] = false;
                }
                primes.emplace_back(idx);
                #ifdef DEBUG
                std::cout << primes.back() << "\t";
                #endif
            }
        }
        #ifdef DEBUG
        std::cout << "\n";
        #endif
        std::vector<bool>().swap(tmpPrimes);
        // tmpPrimes.swap(std::vector<bool>());

        int const primesSize = primes.size();
        comb.resize(MAX_LEN + primesSize, std::vector<int>(primesSize, 0));
        comb[0][0] = 1;
        for (int n = 1; n < comb.size(); n++) {
            for (int k = 0; k < primesSize; ++k) {
                comb[n][k] = (0 == k) ? 1 : (comb[n - 1][k - 1] + comb[n - 1][k]) % MOD;
                #if defined(DEBUG_DETAIL) && defined(DEBUG)
                if (n < 3) {
                    std::cout << comb[n][k] << ",\t";
                }
                #endif
            }
            #if defined(DEBUG_DETAIL) && defined(DEBUG)
            if (n < 3) {
                std::cout << "\n";
            }
            #endif

        }
        initDone = true;
    }

private:
    static int const MAX_LEN = 1e4 + 1;
    static int const MOD = 1e9 + 7;
    static int const QUERY_LEN = 2;
    static int const QUERY_FIRST_IDX = 0;
    static int const QUERY_SECOND_IDX = 1;

    static bool initDone;
    static std::vector<int> primes;
    static std::vector<std::vector<int>> comb;
};

bool Solution::initDone = false;
std::vector<int> Solution::primes;
std::vector<std::vector<int>> Solution::comb;

#ifdef TEST_MAIN
#define PRINT_TO_SCREEN
#define INIT_DEPENDENDS_ON_OBJ
#undef INIT_DEPENDENDS_ON_OBJ
int main() {
    std::vector<std::vector<int>> queries{{{2, 6}, {5, 1}, {73, 660}, {5, 5}, {4, 4}, {3, 3}, {2, 2}}};
#ifndef INIT_DEPENDENDS_ON_OBJ
    Solution::init();
#endif
    Solution obj;
    std::vector<int> ans = obj.waysToFillArray(queries);
#ifdef PRINT_TO_SCREEN
    for (int const ele : ans) {
        std::cout << ele << ",\t";
    }
    std::cout << "\n";
#endif
    std::vector<int> ansCorrect{{4,1,50734910, 5, 10, 3, 2}};
    assert(ans == ansCorrect);
#ifdef PRINT_TO_SCREEN
    std::cout << "TEST SUCCESSFULLY" << std::endl;
#endif
}
#endif
