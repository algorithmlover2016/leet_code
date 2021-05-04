#include "../../head.h"


class Solution {
public:
    std::vector<int> minInterval(std::vector<std::vector<int>> intervals, std::vector<int> const & queries) {
        // plagirizing from https://youtu.be/4O7baTU2ZeQ
        // sort the interval of intervals in increasing order
        std::sort(intervals.begin(), intervals.end());
        int const intervalSize = intervals.size();
        int const queriesSize = queries.size();
        std::vector<int> ans(queriesSize);
        if (0 == queriesSize) {
            return ans;
        }

        std::vector<int> queriesIdx(queriesSize);
        std::iota(std::begin(queriesIdx), std::end(queriesIdx), 0);

        // sort the queriesIdx in increasing order according to the value of queries
        auto cmpQuery = [&] (int const left, int const right) {
            return queries[left] < queries[right];
        };
        std::sort(std::begin(queriesIdx), std::end(queriesIdx), cmpQuery);
        auto cmpMinHeap = [&] (std::vector<int> const & left, std::vector<int> const & right) {
            assert(HEAP_ELE_SIZE <= left.size());
            assert(HEAP_ELE_SIZE <= right.size());
            return left[HEAP_ELE_INTERVAL_IDX] > right[HEAP_ELE_INTERVAL_IDX];
        };
        typedef std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, decltype(cmpMinHeap)> MaxHeap;
        MaxHeap minHeap(cmpMinHeap);

        for (int idx = 0, intervalIdx = 0; idx < queriesSize; idx++) {
            int queryIdx = queriesIdx[idx];
            int queryVal = queries[queryIdx];
            // each interval is traversal only once
            while (intervalIdx < intervalSize && intervals[intervalIdx][INTERVAL_LEFT_IDX] <= queryVal) {
                auto & interval = intervals[intervalIdx];
                int left = interval[INTERVAL_LEFT_IDX];
                int right = interval[INTERVAL_RIGHT_IDX];
                if (right >= queryVal) {
                    minHeap.push({right - left + 1, right});
                }
                intervalIdx++;
            }
            while (!minHeap.empty() && (minHeap.top()[HEAP_ELE_MOST_RIGHT_IDX] < queryVal)) {
                minHeap.pop();
            }

            if (minHeap.empty()) {
                ans[queryIdx] = -1;
            } else {
                ans[queryIdx] = minHeap.top()[HEAP_ELE_INTERVAL_IDX];
            }
        }
        return ans;
    }

private:
    static int const HEAP_ELE_SIZE = 2;
    static int const HEAP_ELE_INTERVAL_IDX = 0;
    static int const HEAP_ELE_MOST_RIGHT_IDX = 1;
    static int const INTERVAL_LEFT_IDX = 0;
    static int const INTERVAL_RIGHT_IDX = 1;
};

class Solution {
public:
    std::vector<int> minInterval(std::vector<std::vector<int>> const & intervals, std::vector<int> const & queries) {
        int n = intervals.size();
        std::vector<std::pair<int, int>> v(n);
        for (int i = 0; i < n ; i++) {
            v[i] = {intervals[i][0], intervals[i][1]};
        }
        std::sort(v.begin(), v.end());

        std::vector<std::pair<int, int>> q(queries.size());
        for (int i = 0; i < queries.size() ; i++) {
            q[i] = {queries[i], i};
        }
        std::sort(q.begin(), q.end());

        std::vector<int> ans(q.size());

        std::set<std::pair<int, int>> s;       // length, end, similar to priority_queue minHeap
        int ind = 0;

        for (auto x : q) {
            int val = x.first;
            while (ind < n && v[ind].first <= val) {
                s.insert({v[ind].second - v[ind].first + 1, v[ind].second});
                ind++;
            }

            ////////////////////////////
            // important !!
            while (!s.empty() && (*s.begin()).second < val ) {
                s.erase(s.begin());
            }
            ////////////////////////////

            if (s.empty()) {
                ans[x.second] = -1;
            } else {
                ans[x.second] = ((*s.begin()).first);
            }
        }
        return ans;
    }
};

static const auto io_sync_off = [] () {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
}();
