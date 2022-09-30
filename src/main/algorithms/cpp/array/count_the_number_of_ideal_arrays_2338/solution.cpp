#include "../../head.h"

// #define DEBUG
#define LAMBDA_INIT
class Solution {
public:
    int idealArrays(int n, int maxValue) {
        if (n >= MAX_ROWS || maxValue >= MAX_VAL) {
            return -1;
        }
        #ifdef LAMBDA_INIT
        auto InitOnce = [&]() {
            combs = std::vector<std::vector<int>>(MAX_ROWS, std::vector<int>(MAX_VAL_BITS, 0));
            combs[0][0] = 1;
            cnts = std::vector<std::vector<int>>(MAX_VAL, std::vector<int>(MAX_VAL_BITS, 0));
            #ifdef DEBUG
            std::cout << "combs.size: (" << combs.size() << ", " << combs.back().size() << "), cnts.size: (" << cnts.size() << ", " << cnts.back().size()  << ")\n";
            #endif

            /*
            get the memorized array to storage the combination results
            */

            for (int nCr = 1; nCr < MAX_ROWS; nCr++) {
                for (int r = 0; r < MAX_VAL_BITS; r++) {
                    combs[nCr][r] = (0 == r) ? 1 : (combs[nCr - 1][r] + combs[nCr - 1][r - 1]) % MOD;
                    #ifdef DEBUG_COMB
                    std::cout << combs[nCr][r] << ", ";
                    #endif
                }
                #ifdef DEBUG_COMB
                std::cout << "\n";
                #endif
            }
            #ifdef DEBUG
            std::cout << "Init combs done\n";
            #endif

            for (int div = 1; div < MAX_VAL; div++) {
                ++cnts[div][0]; // init all the elements as div, so there is one combination which is [div, div, ..., div]
                for (int last = 2 * div; last < MAX_VAL; last += div) { // for each combination which is end with div, we can add last at the most right.
                    for (int bars = 0; cnts[div][bars]; bars++) {
                        cnts[last][bars + 1] += cnts[div][bars];
                    }
                }
            }
            #ifdef DEBUG
            std::cout << "Init cnts done\n";
            #endif
        };
        static bool INIT_FLAG = (InitOnce(), true);
        #else
        static bool INIT_FLAG = (InitOnce(), true);
        #endif
        #ifdef DEBUG
        std::cout << "Init done\n";
        #endif
        int ans =0;
        for (int lastVal = 1; lastVal <= maxValue; lastVal++) {
            for (int bars = 0; bars < std::min(MAX_VAL_BITS, n) && cnts[lastVal][bars]; bars++) {
                ans = (1LL * cnts[lastVal][bars] * combs[n - 1][bars] + ans) % MOD;
            }
        }
        return ans;
    }

#ifndef LAMBDA_INIT
private:
    void InitOnce() {

        combs = std::vector<std::vector<int>>(MAX_ROWS, std::vector<int>(MAX_VAL_BITS, 0));
        combs[0][0] = 1;
        cnts = std::vector<std::vector<int>>(MAX_VAL, std::vector<int>(MAX_VAL_BITS, 0));
        #ifdef DEBUG
        std::cout << "combs.size: (" << combs.size() << ", " << combs.back().size() << "), cnts.size: (" << cnts.size() << ", " << cnts.back().size()  << ")\n";
        #endif

        /*
            get the memorized array to storage the combination results
        */

        for (int nCr = 1; nCr < MAX_ROWS; nCr++) {
            for (int r = 0; r < MAX_VAL_BITS; r++) {
                combs[nCr][r] = (0 == r) ? 1 : (combs[nCr - 1][r] + combs[nCr - 1][r - 1]) % MOD;
                #ifdef DEBUG_COMB
                std::cout << combs[nCr][r] << ", ";
                #endif
            }
            #ifdef DEBUG_COMB
            std::cout << "\n";
            #endif
        }
        #ifdef DEBUG
        std::cout << "Init combs done\n";
        #endif

        for (int div = 1; div < MAX_VAL; div++) {
            ++cnts[div][0]; // init all the elements as div, so there is one combination which is [div, div, ..., div]
            for (int last = 2 * div; last < MAX_VAL; last += div) { // for each combination which is end with div, we can add last at the most right.
                for (int bars = 0; cnts[div][bars]; bars++) {
                    cnts[last][bars + 1] += cnts[div][bars];
                }
            }
        }
        #ifdef DEBUG
        std::cout << "Init cnts done\n";
        #endif

    }
#endif

private:
    constexpr int static MAX_ROWS = 1e4 + 1;
    constexpr int static MAX_VAL_BITS = 14;
    constexpr int static MAX_VAL = 2 << (MAX_VAL_BITS - 1);

    constexpr int static MOD = 1e9 + 7;
    std::vector<std::vector<int>> combs;
    std::vector<std::vector<int>> cnts;
};