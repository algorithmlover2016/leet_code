#include "../../head.h"


// #define DEBUG
class Solution {
public:
    int visiblePoints(std::vector<std::vector<int>> const & points,
            int angle,
            std::vector<int> const & location) {
        // plagiarizing from https://youtu.be/K2ipSrea1Xs

        int const pointsSize = points.size();
        if (JUST_RETURN_SIZE >= pointsSize) {
            return pointsSize;
        }

        if (POINT_LEN > location.size()) {
            return 0;
        }

        std::vector<double> angles;
        int samePoint = 0;
        for (int idx = 0; idx < pointsSize; idx++) {
            if (POINT_LEN > points[idx].size()) {
                continue;
            }
            if (points[idx] == location) {
                samePoint++;
#ifdef DEBUG
                std::cout << "point: " << points[idx][POINT_Y_IDX] << ",\t" << points[idx][POINT_X_IDX] << "\n";
#endif
                continue;
            }
            double curAngle = atan2(points[idx][POINT_Y_IDX] - location[POINT_Y_IDX],
                    points[idx][POINT_X_IDX] - location[POINT_X_IDX]) * PI_DEGREE / PI;
            angles.emplace_back(curAngle);
        }

        if (angles.empty()) {
            return samePoint;
        }

        std::sort(angles.begin(), angles.end());

        float maxAngle = angles.back();

#ifdef DEBUG
        std::cout << "\n";
#endif
        for (int idx = 0; idx < pointsSize; idx++) {
            float cycAngle = CYCLE_DEGREE + angles[idx];
            if (cycAngle - maxAngle < angle ||
                    std::fabs(cycAngle - maxAngle - angle) < EQUAL_THRESHOLD) {
#ifdef DEBUG
                std::cout << "add cycle: " << cycAngle << "\t";
#endif
                angles.emplace_back(cycAngle);
            } else {
                break;
            }
        }

#ifdef DEBUG
        std::cout << "\nangles.size(): " << angles.size() <<  "\n";
#endif

#ifndef MEMORY_OPTIMIZE
        std::deque<int> storage;
        size_t ans = 0;
        // sliding window
        for (int idx = 0; idx < angles.size(); idx++) {
#ifdef DEBUG
            std::cout << "angle: " << angles[idx] << "\n";
#endif

            storage.emplace_back(idx);
            while (std::fabs(angles[idx] - angles[storage.front()]) > angle) {
                storage.pop_front();
            }
            ans = std::max(ans, storage.size());
        }
#else
        int left = 0;
        int ans = 0;
        // sliding window
        for (int idx = 0; idx < angles.size(); idx++) {
#ifdef DEBUG
            std::cout << "angle: " << angles[idx] << "\n";
#endif

            while (std::fabs(angles[idx] - angles[left]) > angle) {
                left++;
            }
            ans = std::max(ans, idx - left + 1);
        }
#endif
        return ans + samePoint;
    }

private:
    static int const JUST_RETURN_SIZE = 1;
    static double const PI;
    static int const PI_DEGREE = 180;
    static int const CYCLE_DEGREE = 360;

    static int const POINT_LEN = 2;
    static int const POINT_Y_IDX = 1;
    static int const POINT_X_IDX = 0;

    static double const EQUAL_THRESHOLD;
};

double const Solution::PI = 3.141592653;
double const Solution::EQUAL_THRESHOLD = 1e-6;
