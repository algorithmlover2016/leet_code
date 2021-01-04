#include "../../head.h"


// #define DEBUG
class Solution {
public:
    int countArrangement(int n) {
        // plagiarizing from https://youtu.be/wPQ7LOe2jLA
        #ifdef DEBUG
        std::cout << (1 << n) << "\n";
        #endif
#ifdef NO_OPTIMIZE_RUNTIME
        std::vector<std::vector<int>> dpMemo(n + 1,
                std::vector<int>(1 << n, 0));
        for (int mask = 0; mask < dpMemo[0].size(); mask++) {
            dpMemo[0][mask] = 1;
        }
        for (int idx = 1; idx <= n; idx++) {
            for (int mask = 0; mask < dpMemo[idx].size(); mask++) {
#else 
        std::vector<std::vector<int>> dpMemo(n + 1,
                std::vector<int>(1 << n, 1));
        for (int idx = 1; idx <= n; idx++) {
            for (int mask = 0; mask < dpMemo[idx].size(); mask++) {
                dpMemo[idx][mask] = 0;
#endif
                for (int next = 0; next < n; next++) {
                    if ((mask & (1 << next)) &&
                            (0 == idx % (next + 1) || 0 == (next + 1) % idx)) {
                        dpMemo[idx][mask] += dpMemo[idx - 1][mask ^ (1 << next)];
                    }
                }
            }
        }
        return dpMemo[n].back();
    }
};
