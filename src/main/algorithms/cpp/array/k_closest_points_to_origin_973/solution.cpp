#include "../../head.h"


class Solution {
public:
    std::vector<std::vector<int>> kClosest(std::vector<std::vector<int>> const & points, int k) {
        // need a maxHeap with size k, always pop top elements
        auto cmp = [] (std::pair<int, int> const & left, std::pair<int, int> const & right) {
            return left.first <= right.first;
        };
        typedef std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(cmp)> MaxHeap;
        MaxHeap maxHeap(cmp);
        for (int idx = 0; idx < points.size(); idx++) {
            auto const & point = points[idx];
            if (POINT_SIZE > point.size()) {
                continue;
            }
            int disSqu = point[X_IDX] * point[X_IDX] + point[Y_IDX] * point[Y_IDX];
            maxHeap.emplace(std::make_pair(disSqu, idx));
            if (maxHeap.size() > k) {
                maxHeap.pop();
            }
        }

        std::vector<std::vector<int>> ans(k);
        while (k-- > 0) {
            auto const & ele = maxHeap.top();
            ans[k] = points[ele.second];
            maxHeap.pop();
        }
        return ans;
    }
private:
    static int const POINT_SIZE = 2;
    static int const X_IDX = 0;
    static int const Y_IDX = 1;
};


class Solution {
public:
    std::vector<std::vector<int>> kClosest(std::vector<std::vector<int>> & points, int K) {
        auto cmp = [](const auto & a, const auto & b) {
            return a[0] * a[0] + a[1] * a[1] < b[0] * b[0] + b[1] * b[1];
        };
        std::nth_element(points.begin(), points.begin() + K, points.end(), cmp);
        points.erase(points.begin() + K, points.end());
        return points;
    }
};
