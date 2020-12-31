#include "../../head.h"


// #define NO_USING_STD_MAX_ELEMENT
class Solution {
public:
    int maxHeight(std::vector<std::vector<int>> const & cuboids) {
        // plagiarizing idea from https://www.youtube.com/watch?v=W6aB2iM7C8g
        if (cuboids.empty() || cuboids[0].empty()) {
            return 0;
        }
        std::vector<std::vector<int>> orderedCuboids;
        for (auto const & cuboid : cuboids) {
            if (DEMENSION_LEN > cuboid.size()) {
                continue;
            }
            std::vector<int> orderedCuboid(cuboid);
            std::sort(orderedCuboid.begin(), orderedCuboid.end());
            orderedCuboids.emplace_back(orderedCuboid);
        }
        std::sort(orderedCuboids.begin(), orderedCuboids.end());

        int const orderedCuboidsSize = orderedCuboids.size();
        std::vector<int> dpMemo(orderedCuboidsSize);
        #ifdef NO_USING_STD_MAX_ELEMENT
        int ans = INT_MIN;
        #endif

        for (int idx = 0; idx < orderedCuboidsSize; idx++) {
            // if we just use itself to construct the cuboid;
            dpMemo[idx] = orderedCuboids[idx][HEIGHT_IDX];
            for (int preIdx = 0; preIdx < idx; preIdx++) {
                if (orderedCuboids[preIdx][LENGTH_IDX] <= orderedCuboids[idx][LENGTH_IDX] &&
                    orderedCuboids[preIdx][HEIGHT_IDX] <= orderedCuboids[idx][HEIGHT_IDX]) {
                    dpMemo[idx] = std::max(dpMemo[idx], dpMemo[preIdx] + orderedCuboids[idx][HEIGHT_IDX]);
                }
            }
            #ifdef NO_USING_STD_MAX_ELEMENT
            ans = std::max(ans, dpMemo[idx]);
            #endif
        }
        #ifdef NO_USING_STD_MAX_ELEMENT
        return ans;
        #else
        return *std::max_element(dpMemo.begin(), dpMemo.end());
        #endif
    }
    private:
    static int const DEMENSION_LEN = 3;
    static int const WEIGTH_IDX = 0;
    static int const LENGTH_IDX = 1;
    static int const HEIGHT_IDX = 2;
};
