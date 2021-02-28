#include "../../head.h"


class Solution {
public:
    int makeArrayIncreasing(std::vector<int> const & arr1, std::vector<int> arr2) {
        // plagiarizing from https://leetcode.com/problems/make-array-strictly-increasing/discuss/377403/Python-DP-solution-with-explanation.
        std::sort(arr2.begin(), arr2.end()); // make arr2 to be a no decrreament array
        std::unordered_map<int, int> curLayerDpMemo{{{-1, 0}}};
        int ans = INIT_MAX;
        for (int const num : arr1) {
            std::unordered_map<int, int> nextLayerDpMemo;
            int curMin = INIT_MAX;
            for (auto const & [key, cnt] : curLayerDpMemo) {
                if (num > key) {
                    // we can add this element who is num to next layer directly
                    if (nextLayerDpMemo.find(num) == nextLayerDpMemo.end()) {
                        nextLayerDpMemo[num] = INIT_MAX;
                    }
                    nextLayerDpMemo[num] = std::min(nextLayerDpMemo[num], cnt);
                    curMin = std::min(curMin, nextLayerDpMemo[num]);
                }
                // we won't take num as a valid number, so we just need find a ele in arr2 who is greater than key
                auto it = std::upper_bound(arr2.begin(), arr2.end(), key);
                if (it != arr2.end()) {
                    if (nextLayerDpMemo.find(*it) == nextLayerDpMemo.end()) {
                        nextLayerDpMemo[*it] = INIT_MAX;
                    }
                    nextLayerDpMemo[*it] = std::min(nextLayerDpMemo[*it], cnt + 1);
                    curMin = std::min(curMin, nextLayerDpMemo[*it]);
                }
            }
            nextLayerDpMemo.swap(curLayerDpMemo);
            ans = curMin;
        }
        if (curLayerDpMemo.empty()) {
            return -1;
        }
        return ans;
    }

private:
    static int const INIT_MAX = INT_MAX;
};
