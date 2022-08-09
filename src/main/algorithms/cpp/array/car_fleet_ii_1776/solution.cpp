#include "../../head.h"


class Solution {
public:
    std::vector<double> getCollisionTimes(std::vector<std::vector<int>> const & cars) {
        // plagiarizing from https://leetcode.com/problems/car-fleet-ii/discuss/1085987/JavaC%2B%2BPython-O(n)-Stack-Solution
        int carsSize = cars.size();
        if (0 == carsSize) {
            return {};
        }
        std::vector<double> ans(carsSize, INIT_VAL);
        std::vector<int> lowestStack;
        for (int idx = carsSize - 1; idx > LEFT_EXCLUDE_IDX; idx--) {
            if (CAR_DESC_LEN > cars[idx].size()) {
                continue;
            }
            int curPos = cars[idx][POS_IDX], curSpeed = cars[idx][SPEED_IDX];
            while (!lowestStack.empty()) {
                int nearestLaterLowestIdx = lowestStack.back();
                int nearLaterPos = cars[nearestLaterLowestIdx][POS_IDX];
                int nearLaterSpeed = cars[nearestLaterLowestIdx][SPEED_IDX];
                if (curSpeed <= nearLaterSpeed /*curIdx will not collide the nearest later car*/ ||
                    (ans[nearestLaterLowestIdx] > INIT_VAL /*the nearest later car must collide , for example it must be not the last one*/ &&
                        ((nearLaterPos * 1.0 - curPos) / (curSpeed - nearLaterSpeed) > ans[nearestLaterLowestIdx]) /*the cur car need more time to collide the nearearst later car than the later car collided*/)) {
                    // the cur car will not collide the nearearst later car
                            lowestStack.pop_back();
                } else {
                    // we find the nearest later lowest car that maybe collided with the cur car.
                    break;
                }
            }
            if (!lowestStack.empty()) {
                int nearestLaterLowestIdx = lowestStack.back();
                ans[idx] = (cars[nearestLaterLowestIdx][POS_IDX] * 1.0 - curPos) / (curSpeed - cars[nearestLaterLowestIdx][SPEED_IDX]);
            }
            lowestStack.emplace_back(idx);
        }
        return ans;
        
    }
private:
    int const INIT_VAL = -1;
    static int const LEFT_EXCLUDE_IDX = -1;
    static int const CAR_DESC_LEN = 2;
    static int const POS_IDX = 0;
    static int const SPEED_IDX = 1;
};