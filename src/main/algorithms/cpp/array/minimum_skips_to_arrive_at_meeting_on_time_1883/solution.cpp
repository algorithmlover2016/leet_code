#include "../../head.h"


// #define DEBUG

class Solution {
public:
    int minSkips(std::vector<int> const & dist, int speed, int hoursBefore) {
        // plagiarizing from https://leetcode.com/problems/minimum-skips-to-arrive-at-meeting-on-time/discuss/1239980/Python-7-lines-dp-%2B-2liner-explained
        // and https://leetcode.com/problems/minimum-skips-to-arrive-at-meeting-on-time/discuss/1242066/2D-DP
        long long int maxDist = static_cast<long long>(speed) * hoursBefore;
        if (std::accumulate(dist.begin(), dist.end(), 0) > maxDist) {
            return -1;
        }
        #ifdef DEBUG
        std::cout << "can make an answer" << "\n";
        #endif
        int distLen = dist.size();
        std::vector<std::vector<long long int>> dpMemo(distLen, std::vector<long long int>(distLen, 0));
        for (int skip = 0; skip < distLen; skip++) {
            if (dpHelp(dist, distLen - 1, skip, dpMemo, speed) <= maxDist) {
                return skip;
            }
        }
        return -1;
    }
private:
    int dpHelp(std::vector<int> const & dist, int idx, int skip, std::vector<std::vector<long long int>> & dpMemo, int const speed) {
        int const distLen = dist.size();
        if (skip < 0) {
            return INIT_MAX;
        }
        if (idx < 0) {
            return 0;
        }
        if (0 == dpMemo[idx][skip]) {
            // we need compute the result of (idx, skip)
            dpMemo[idx][skip] = dist[idx] +
                    std::min(dpHelp(dist, idx - 1, skip - 1, dpMemo, speed)/*at idx element, we make a skip operation*/,
                            /*if we do not skip the rest, we first need round the costing time to upper bound*/
                            (dpHelp(dist, idx - 1, skip, dpMemo, speed) + speed - 1) / speed * speed /*it means the cost time can make how long if keeping speed all the time*/);
        }
        return dpMemo[idx][skip];
    }
private:
    long long int INIT_MAX = 1e9;
};