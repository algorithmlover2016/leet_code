#include "../../head.h"


// #define BINARY_TRAVERSAL
class Solution {
protected:
    friend class Comp;
    class Comp {
    private:
        bool _reverse;
    public:
        Comp(bool reverse = false) : _reverse(reverse) {
        }
        bool operator()(std::vector<int> const & left, std::vector<int> const & right) {
            assert(Solution::COMP_LEN <= left.size());
            assert(Solution::COMP_LEN <= right.size());
            int leftDiff = left[Solution::COMP_SECOND] - left[Solution::COMP_FIRST];
            int rightDiff = right[Solution::COMP_SECOND] - right[Solution::COMP_FIRST];
            if (leftDiff > rightDiff) {
                return _reverse;
            } else if (leftDiff < rightDiff) {
                return !_reverse;
            } else {
                return left[Solution::COMP_SECOND] > right[Solution::COMP_SECOND] ? _reverse : !_reverse;
            }
        }
    };

public:
    int minimumEffort(std::vector<std::vector<int>> tasks) {
        // plagiarizing idea from https://youtu.be/ja76NVaneC8
        // assuming minimum_i >= actual_i;
        Comp compObj(true);
        // according to tasks[idx]'s minimum - actual descreasing order
        std::sort(tasks.begin(), tasks.end(), compObj);

#ifndef BINARY_TRAVERSAL
        int ans = 0;
        int curLeft = 0;
        for (auto const & task : tasks) {
            if (COMP_LEN > task.size()) {
                continue;
            }
            if (task[COMP_SECOND] > curLeft) {
                int needAdded = task[COMP_SECOND] - curLeft;
                curLeft +=needAdded;
                ans += needAdded;
            }
            curLeft -= task[COMP_FIRST];
        }
        return ans;

#else
        int left = 0;
        int right = 0;
        for (auto const & task : tasks) {
            left += task[COMP_FIRST];
            right += task[COMP_SECOND];
        }
        while (left < right) {
            int mid = (right + left) / 2;
            if (done(tasks, mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return left;

#endif
    }

#ifdef BINARY_TRAVERSAL
private:
    bool done(std::vector<std::vector<int>> const & tasks, int mid) {
        for (auto const & task : tasks) {
            if (COMP_LEN > task.size()) {
                continue;
            }
            if (task[COMP_SECOND] > mid) {
                return false;
            }
            mid -= task[COMP_FIRST];
        }
        return true;
    }
#endif

private:
    static int const COMP_LEN = 2;
    static int const COMP_FIRST = 0;
    static int const COMP_SECOND = 1;
};
