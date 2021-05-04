#include "../../head.h"


// #define DEBUG
class Solution {
public:
    int maxHappyGroups(int batchSize, std::vector<int> const & groups) {
        // plagiarizing from https://leetcode.com/problems/maximum-number-of-groups-getting-fresh-donuts/discuss/1140548/Python-dfs-with-optimizations-explained and
        // https://leetcode.com/problems/maximum-number-of-groups-getting-fresh-donuts/discuss/1140644/C%2B%2B-0-ms%3A-Greedy-%2B-DP
        std::vector<int> cnts(batchSize, 0);
        int ans = 0;
        for (int group : groups) {
            int mod = group % batchSize;
            if (0 == mod) {
                // the group will always be happy
                ans++;
            } else if (0 < cnts[batchSize - mod]) {
                // the group will be happy if it is with batchSize - mod
                --cnts[batchSize - mod];
                ans++;
            } else {
                ++cnts[mod];
            }
        }
        return ans + dfs(cnts, 0);
    }
private:
    int dfs(std::vector<int> & cnts, int left) {
        #ifdef DEBUG
        std::cout << __func__ << "."  << __LINE__ << ":\n";
        #endif
        auto it = dpMemo.find(cnts);
        if (it != std::end(dpMemo)) {
            return it->second;
        }
        int ans = 0;
        int const batchSize = cnts.size();
        for (int idx = 1; idx < batchSize; idx++) {
            if (cnts[idx]-- > 0) {
                ans = std::max(ans, (0 == left/*it means the idx group will be happy*/) +
                        dfs(cnts, (batchSize + left - idx) % batchSize));
            }
            ++cnts[idx];
        }
        return dpMemo[cnts] = ans;

    }
private:
    std::map<std::vector<int>, int> dpMemo;
};
