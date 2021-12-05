#include "../../head.h"


class Solution {
public:
    std::vector<int> longestObstacleCourseAtEachPosition(std::vector<int> const & obstacles) {
        // plagiarizing from https://leetcode.com/problems/find-the-longest-valid-obstacle-course-at-each-position/discuss/1390603/Straightup-LIS
        std::vector<int> ans;
        std::vector<int> nonDecreasingSequences;
        for (int const obstacle : obstacles) {
            auto it = std::upper_bound(std::begin(nonDecreasingSequences), std::end(nonDecreasingSequences), obstacle);
            if (it == std::end(nonDecreasingSequences)) {
                nonDecreasingSequences.emplace_back(obstacle);
                it = std::prev(std::end(nonDecreasingSequences));
            } else {
                *it = obstacle;
            }
            ans.emplace_back(it - std::begin(nonDecreasingSequences) + 1);
        }
        return ans;
    }
};

class SolutionSetSizeAtInit {
public:
    std::vector<int> longestObstacleCourseAtEachPosition(std::vector<int> const & obstacles) {
        // plagiarizing from https://leetcode.com/problems/find-the-longest-valid-obstacle-course-at-each-position/discuss/1390603/Straightup-LIS
        std::vector<int> ans(obstacles.size());
        std::vector<int> nonDecreasingSequences;
        for (int idx = 0; idx < obstacles.size(); idx++) {
            int obstacle = obstacles[idx];
            auto it = std::upper_bound(std::begin(nonDecreasingSequences), std::end(nonDecreasingSequences), obstacle);
            if (it == std::end(nonDecreasingSequences)) {
                nonDecreasingSequences.emplace_back(obstacle);
                it = std::prev(std::end(nonDecreasingSequences));
            } else {
                *it = obstacle;
            }
            ans[idx] = it - std::begin(nonDecreasingSequences) + 1;
        }
        return ans;
    }
};