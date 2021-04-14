#include "../../head.h"


class Solution {
public:
    int minSideJumps(std::vector<int> const & obstacles) {
        // plagiarizing from https://leetcode.com/problems/minimum-sideway-jumps/discuss/1152411/PythonC%2B%2B-clean-dp-solution-with-explanation-O(N)
        int const obstaclesSize = obstacles.size();
        if (JUST_THREE > obstaclesSize) {
            return 0;
        }
        // because the last point will not have stone in any lane road,
        // so we just need consider from 0 to before the last one
        std::vector<std::vector<int>> dpMemo(obstaclesSize - 1, std::vector<int>(LANE_ROADS_SIZE, obstaclesSize));
        dpMemo[0][0] = dpMemo[0][2] = 1; dpMemo[0][1] = 0;
        for (int idx = 1; idx < obstaclesSize - 1; idx++) {
            for (int laneRoadIdx = 0; laneRoadIdx < LANE_ROADS_SIZE; laneRoadIdx++) {
                // the cur point at cur lane road has a stone
                // or, the point after this cur point with same lane has a stone
                // they will all lead to the dpMemo[idx] = LANE_ROADS_SIZE,
                // the reason why the next point at the same lane will be INF if the next point at same lane has a stone
                // is that we finally just consider the dpMemo[obstaclesSize - 2] values,
                // no matter the value of the cur point is how much, its next point at same lane will be INF, it can't go
                // to the next point with same lane
                if (obstacles[idx] == laneRoadIdx + 1 || (obstacles[idx + 1] == laneRoadIdx + 1)) {
                    dpMemo[idx][laneRoadIdx] = obstaclesSize;
                } else {
                    dpMemo[idx][laneRoadIdx] = std::min(dpMemo[idx - 1][laneRoadIdx] /*from the former point with same lane, no need to jump*/,
                            1 + std::min(dpMemo[idx - 1][(laneRoadIdx + 1) % 3] /* from the next lane at same point jump to the lane*/,
                                dpMemo[idx - 1][(laneRoadIdx + 2) % 3] /*jump from the next next lane jump to cur lane with same point*/));

                }
            }
        }
        auto const laneOfLastPoint = dpMemo[obstaclesSize - 2];
        return *std::min_element(laneOfLastPoint.begin(), laneOfLastPoint.end());
    }
private:
    static int const JUST_THREE = 3;
    static int const LANE_ROADS_SIZE = 3;
};

// #define DEBUG
class Solution {
public:
    int minSideJumps(std::vector<int> const & obstacles) {
        // plagiarizing from https://leetcode.com/problems/minimum-sideway-jumps/discuss/1152665/JavaC%2B%2BPython-DP-O(1)-space
        int const obstaclesSize = obstacles.size();
        if (JUST_THREE > obstaclesSize) {
            return 0;
        }
        std::vector<int> dpMemo(LANE_ROADS_SIZE, 0);
        dpMemo[0] = dpMemo[2] = 1; dpMemo[1] = 0; // frog is located in lane 1(middle) at point 0;
        for (int idx = 1; idx < obstaclesSize - 1; idx++) {
            #ifdef DEBUG
            std::cout << "\n" << idx << ": "; 
            #endif
            if (0 < obstacles[idx]) {
                // if the lane of cur point is set a stone, it should set its previous point status to be INF.
                // because the precious point at that lane can't go throught to this point in same lane
                dpMemo[obstacles[idx] - 1] = obstaclesSize;
            }
            for (int laneRoadIdx = 0; laneRoadIdx < LANE_ROADS_SIZE; laneRoadIdx++) {
                if (laneRoadIdx != obstacles[idx] - 1) {
                    dpMemo[laneRoadIdx] = std::min(dpMemo[laneRoadIdx] /*the precious point at same lane*/,
                                                   std::min(dpMemo[(laneRoadIdx + 1) % LANE_ROADS_SIZE], dpMemo[(laneRoadIdx + 2) % LANE_ROADS_SIZE]) + 1);
                }
                #ifdef DEBUG
                std::cout << laneRoadIdx << ", " << dpMemo[laneRoadIdx] << "; ";
                #endif
            }

        }
        return *std::min_element(dpMemo.begin(), dpMemo.end());
    }
    private:
    static int const JUST_THREE = 3;
    static int const LANE_ROADS_SIZE = 3;
};

class Solution {
public:
    int minSideJumps(std::vector<int> const & obstacles) {
        int a = 1, b = 0, c = 1;
        for (int obs: obstacles) {
            if (obs == 1) {
                a = INT_MAX / 2;
            }
            if (obs == 2) {
                b = INT_MAX / 2;
            }
            if (obs == 3) {
                c = INT_MAX / 2;
            }

            if (obs != 1) {
                a = std::min(a /*from the same lane road of the previous point*/, std::min(b, c) + 1 /*need a jump*/);
            }
            if (obs != 2) {
                b = std::min(b, std::min(a + 1, c + 1));
            }
            if (obs != 3) {
                c = std::min(c, std::min(a + 1, b + 1));
            }
        }
        return std::min(a, std::min(b, c));
    }
};
