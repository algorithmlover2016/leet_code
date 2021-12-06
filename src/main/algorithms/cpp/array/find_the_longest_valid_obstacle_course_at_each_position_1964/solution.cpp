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

class SolutionFenwickTree {
private:
    class MaxBitByFenwickTree {
    private:
        std::vector<int> bits;
    public:
        MaxBitByFenwickTree(int size) {
            bits.resize(size + 1);
        }
        int get(int idx) {
            int ans = 0;
            for (; idx > 0; idx -= idx & (-idx)) {
                ans = std::max(ans, bits[idx]);
            }
            return ans;
        }
        void update(int idx, int val) {
            for (; idx < bits.size(); idx += idx & (-idx)) {
                bits[idx] = std::max(bits[idx], val);
            }
        }

    };
public:
    std::vector<int> longestObstacleCourseAtEachPosition(std::vector<int> const & obstacles) {
        // plagiarizing from https://leetcode.com/problems/find-the-longest-valid-obstacle-course-at-each-position/discuss/1390159/C%2B%2BPython-Same-with-Longest-Increasing-Subsequence-problem-Clean-and-Concise
        // Fenwick Tree with Compression
        std::vector<int> obstaclesIdx(obstacles);
        std::vector<int> ans(obstacles.size());
        int uniqCompressSize = compress(obstaclesIdx);
        MaxBitByFenwickTree maxBitObj(uniqCompressSize);
        for (int idx = 0; idx < obstaclesIdx.size(); idx++) {
            int order = obstaclesIdx[idx];
            int subLongest = maxBitObj.get(order) + 1;
            ans[idx] = subLongest;
            maxBitObj.update(order, subLongest);
        }
        return ans;
    }

private:
    int compress(std::vector<int> & obstaclesIdx) {
        std::vector<int> strictlyIncObstacles(obstaclesIdx);
        std::sort(std::begin(strictlyIncObstacles), std::end(strictlyIncObstacles));
        strictlyIncObstacles.erase(std::unique(strictlyIncObstacles.begin(), strictlyIncObstacles.end()), strictlyIncObstacles.end());
        // change val from value of obstacles into index order after sorted increasing
        for (int & val : obstaclesIdx) {
            val = std::lower_bound(std::begin(strictlyIncObstacles), std::end(strictlyIncObstacles), val) - std::begin(strictlyIncObstacles) + 1;
        }
        return strictlyIncObstacles.size();
    }
};