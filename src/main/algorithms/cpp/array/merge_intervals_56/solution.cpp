#include "../../head.h"


class Solution {
public:
    std::vector<std::vector<int>> merge(std::vector<std::vector<int>> const & intervals) {
        // plagiarizing idea from employee_free_time_759
        std::vector<std::vector<int>> ans;
        std::map<int, int> timeStampsCnt;
        for (auto const & interval : intervals) {
            if (INTERVAL_LEN > interval.size()) {
                continue;
            }
            timeStampsCnt[interval[INTERVAL_START_IDX]]++;
            timeStampsCnt[interval[INTERVAL_END_IDX]]--;
        }

        int cnt = 0;
        int start = 0;
        int end = 0;
        for (auto const & [timeStamp, curCnt] : timeStampsCnt) {
            if (0 == cnt) {
                start = timeStamp;
                end = timeStamp;
            }
            cnt += curCnt;
            if (0 == cnt) {
                end = timeStamp;
                ans.emplace_back(std::vector<int>{start, end});
            }
        }
        return ans;
    }
private:
    static int const INTERVAL_LEN = 2;
    static int const INTERVAL_START_IDX = 0;
    static int const INTERVAL_END_IDX = 1;
};


class Solution {
public:
    std::vector<std::vector<int>> merge(std::vector<std::vector<int>> const & intervals) {
        // plagiarizing idea from employee_free_time_759
        // using minHeap
        auto cmp = [] (std::pair<int, int> const & left, std::pair<int, int> const & right) {
            // construct a minHeap
            return left.first >= right.first;
        };
        typedef std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(cmp)> MaxHeap;
        MaxHeap minHeap(cmp);
        for (auto const & interval : intervals) {
            if (INTERVAL_LEN > interval.size()) {
                continue;
            }
            minHeap.emplace(std::make_pair(interval[INTERVAL_START_IDX], interval[INTERVAL_END_IDX]));
        }
        std::vector<std::vector<int>> ans;
        if (minHeap.empty()) {
            return ans;
        }
        auto const & firstMinEle = minHeap.top();
        int start = firstMinEle.first;
        int end = firstMinEle.second;
        minHeap.pop();
        while (!minHeap.empty()) {
            auto const cur = minHeap.top(); minHeap.pop();
            if (cur.first <= end) { // if we want a contineous interval, the cur start should be not larger than cur end
                // the end should be the maximum number of cur.second and end
                end = std::max(end, cur.second);
            } else {
                ans.emplace_back(std::vector<int>{start, end});
                start = cur.first;
                end = cur.second;
            }
        }
        ans.emplace_back(std::vector<int>{start, end});
        return ans;
    }
private:
    static int const INTERVAL_LEN = 2;
    static int const INTERVAL_START_IDX = 0;
    static int const INTERVAL_END_IDX = 1;
};
