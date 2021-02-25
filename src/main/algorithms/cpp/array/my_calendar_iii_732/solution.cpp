#include "../../head.h"


class MyCalendarThree {
public:
    // plagiarizing from https://leetcode.com/problems/my-calendar-iii/discuss/109556/JavaC%2B%2B-Clean-Code
    MyCalendarThree() {

    }

    int book(int start, int end) {
        timeLines[start]++; // at start, do a new booking
        timeLines[end]--;  // at end, done
        int concurrent = 0;
        int ans = 0;
        for (auto const & [key, val] : timeLines) {
            ans = std::max(ans, concurrent += val);
        }

        return ans;
    }
private:
    std::map<int, int> timeLines; // must be sorted map, can't be unordered_map
};

class MyCalendarThree {
public:
    // plagiarizing from https://leetcode.com/problems/my-calendar-iii/discuss/176950/C%2B%2B-Map-Solution-beats-95%2B
    MyCalendarThree() {
        count[-1] = 0;
    }

    int book(int s, int e) {
        // find the start point
        auto start = count.emplace(s, (--count.upper_bound(s))->second);
        // find the end point
        auto end = count.emplace(e, std::prev(count.upper_bound(e))->second);
        for (auto i = start.first; i != end.first; ++i) {
            // from start to end(exclude), at each time point,
            // the concurrent events will add 1 according to its original value
            // end point will keep zero or not changed
            res = std::max(res, ++(i->second));
        }
        return res;
    }
private:
    std::map<int, int> count; // must be sorted map, can't be unordered_map
    int res = 0;
};
