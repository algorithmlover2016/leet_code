#include "../../head.h"


#define DEBUG
#define TEST_MAIN

/*
#define USING_SORT_METHOD

#ifndef USING_SORT_METHOD
#define USING_MIN_PRIORITY_QUEUE
#endif
*/

#if !defined(USING_SORT_METHOD) && !defined(USING_MIN_PRIORITY_QUEUE)
#define USING_MAP_MARK_POS
#endif

class Interval {
public:
    int start;
    int end;
    Interval(int start_ = 0, int end_ = 0) : start(start_), end(end_) {
    }
};

class Solution {
public:
    std::vector<Interval> employeeFreeTime(std::vector<std::vector<Interval>> const & schedule) {
        // source from https://leetcode.jp/problemdetail.php?id=759
        // plagiarizing idea from https://github.com/grandyang/leetcode/issues/759
        // and https://shibaili.blogspot.com/2019/02/759-employee-free-time.html
        // and https://zxi.mytechroad.com/blog/geometry/leetcode-759-employee-free-time/ or https://github.com/Seanforfun/Algorithm-and-Leetcode/blob/master/leetcode/759.%20Employee%20Free%20Time.md
        // and https://docs.microsoft.com/en-us/cpp/preprocessor/hash-if-hash-elif-hash-else-and-hash-endif-directives-c-cpp?view=msvc-160

        std::vector<Interval> ans;
#ifdef USING_SORT_METHOD
        // O(nlg(n)) time complexity; O(n) space;

#ifdef DEBUG
        std::cout << "USING_SORT_METHOD" << std::endl;
#endif
        std::vector<Interval> allIntervals;
        for (auto const & employeeIntervals : schedule) {
            for (auto const & interval : employeeIntervals) {
                allIntervals.emplace_back(interval);
            }
        }

        if (allIntervals.empty()) {
            return {};
        }

        std::sort(allIntervals.begin(), allIntervals.end(),
                [] (Interval const & left, Interval const & right) {
                return left.start <= right.start;
                });
        int end = allIntervals.front().end; // find the first end of the smallest interval
        for (auto const & interval : allIntervals) {
            if (end < interval.start) {
                ans.emplace_back(Interval(end, interval.start));
            }
            end = std::max(end, interval.end);
        }

#elif defined(USING_MIN_PRIORITY_QUEUE)

#ifdef DEBUG
        std::cout << "USING_MIN_PRIORITY_QUEUE" << std::endl;
#endif

        auto cmp = [] (Interval const & left, Interval const & right) {
            return left.start >= right.start;
        };
        typedef std::priority_queue<Interval, std::vector<Interval>, decltype(cmp)> MaxHeap;
        MaxHeap minHeap(cmp);
        for (auto const & employeeIntervals : schedule) {
            for (auto const & interval : employeeIntervals) {
                minHeap.emplace(interval);
            }
        }
        if (minHeap.empty()) {
            return {};
        }
        auto const & ele = minHeap.top();
        int end = ele.end;
        minHeap.pop();
        while (!minHeap.empty()) {
            auto const & interval = minHeap.top();
            if (interval.start > end) {
                ans.emplace_back(Interval(end, interval.start));
            }
            end = std::max(end, interval.end);
            minHeap.pop();
        }

#else
#ifdef DEBUG
        std::cout << "USING_MAP_MARK_POS" << std::endl;
#endif

        // must use the sorted map, can't using unordered_map
        std::map<int, int> timeStampCnt;
        for (auto const & employeeIntervals : schedule) {
            for (auto const & interval : employeeIntervals) {
                timeStampCnt[interval.start]++;
                timeStampCnt[interval.end]--;
            }
        }

        int cnt = 0;
        for (auto const & [timeStamp, val] : timeStampCnt) {
            cnt += val;
            if (0 == cnt) {
                // we meet a end
                ans.emplace_back(timeStamp, 0); // we record the end point, which means it cloud start a free interval
            }
            if (0 < cnt && !ans.empty() && 0 == ans.back().end) {
                // we meet a new interval.
                ans.back().end = timeStamp;
            }
        }
        ans.pop_back(); // remove the most end interval.
#endif
        return ans;
    }

};

#ifdef TEST_MAIN
#define PRINT_TO_SCREEN
int main() {
    std::vector<std::vector<Interval>> schedule(3);
    schedule[0].resize(2);
    schedule[0][0] = Interval(1, 2);
    schedule[0][1] = Interval(5, 6);

    schedule[1].resize(1);
    schedule[1][0] = Interval(1, 3);

    schedule[2].resize(1);
    schedule[2][0] = Interval(4, 10);

    Solution obj;
    std::vector<Interval> ans = obj.employeeFreeTime(schedule);
#ifdef PRINT_TO_SCREEN
    for (auto const & interval : ans) {
        std::cout << interval.start << ", " << interval.end << "; ";
    }
    std::cout << "\n";
#endif

    schedule[0].resize(2);
    schedule[0][0] = Interval(1, 3);
    schedule[0][1] = Interval(6, 7);

    schedule[1].resize(1);
    schedule[1][0] = Interval(2, 4);

    schedule[2].resize(2);
    schedule[2][0] = Interval(2, 5);
    schedule[2][1] = Interval(9, 12);
    ans = obj.employeeFreeTime(schedule);
#ifdef PRINT_TO_SCREEN
    for (auto const & interval : ans) {
        std::cout << interval.start << ", " << interval.end << "; ";
    }
    std::cout << "\n";
#endif


    std::cout << "TEST DONE" << std::endl;

    return 0;
}
#endif


