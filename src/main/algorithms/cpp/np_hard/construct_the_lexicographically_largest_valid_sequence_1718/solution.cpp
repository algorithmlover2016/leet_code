#include "../../head.h"


// #define DEBUG
class Solution {
public:
    std::vector<int> constructDistancedSequence(int n) {
        // plagiarizing from https://leetcode.com/problems/construct-the-lexicographically-largest-valid-sequence/discuss/1008913/C%2B%2B-Backtracking
        if (JUST_ZERO >= n) {
            return {};
        }
        std::vector<int> ans(2 * n - 1, INIT_MIN);
        std::vector<bool> used(n, false);
        dfs(used, ans, 0);
        return ans;
    }
    bool dfs(std::vector<bool> & used,
             std::vector<int> & ans,
             int idx) {
        int const ansSize = ans.size();
        while (idx < ansSize && INIT_MIN != ans[idx]) {
            idx++;
        }
        if (idx >= ansSize)  {
            return true;
        }
        #ifdef DEBUG
        std::cout << "\nidx: " << idx << "\t";
        #endif
        for (int usedIdx = used.size() - 1; usedIdx > -1; usedIdx--) {
            if (used[usedIdx]) {
                continue;
            }

            int nextIdx = idx + usedIdx + 1;
            #ifdef DEBUG
            std::cout << "nextIdx: " << nextIdx << "\t";
            #endif
            used[usedIdx] = true;
            // we will place 1 element
            if (0 == usedIdx) {
                ans[idx] = usedIdx + 1;
                if (dfs(used, ans, idx + 1)) {
                    return true;
                }
                ans[idx] = INIT_MIN;
            } else if (nextIdx < ansSize && INIT_MIN == ans[nextIdx]) {
                ans[idx] = ans[nextIdx] = usedIdx + 1;
                if (dfs(used, ans, idx + 1)) {
                    return true;
                }
                #ifdef DEBUG
                std::cout << "nextIdx: " << nextIdx << "\tfail \t";
                #endif
                ans[idx] = ans[nextIdx] = 0;
            }
            used[usedIdx] = false;
        }
        return false;
    }
    private:
    static int const JUST_ZERO = 0;
    int const INIT_MIN = 0;
};
