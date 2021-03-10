#include "../../head.h"


class Solution {
public:
    std::vector<int> topKFrequent(std::vector<int>& nums, int k) {
        auto cmp = [&] (std::pair<int, int> const & left, std::pair<int, int> const & right) {
            return left.second > right.second || (left.second == right.second && left.first < right.first);
        };
        typedef std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(cmp)> MinHeap;
        std::unordered_map<int, int> numsCnt;
        MinHeap minHeap(cmp);
        for (int const num : nums) {
            numsCnt[num]++;
        }
        for (auto const & [num, cnt] : numsCnt) {
            minHeap.emplace(std::make_pair(num, cnt));
            if (minHeap.size() > k) {
                minHeap.pop();
            }
        }
        std::vector<int> ans(k);
        while (!minHeap.empty()) {
            auto const & ele = minHeap.top();
            ans[--k] = ele.first;
            minHeap.pop();
        }
        return ans;
    }
};
