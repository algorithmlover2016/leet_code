#include "../../head.h"


// #define USING_LAMBDA_CMP
// #define DEBUG
class Solution {
#ifndef USING_LAMBDA_CMP
protected:
    static bool cmp(std::vector<int> const & left, std::vector<int> const & right) {
        assert(COURSE_SIZE <= left.size());
        assert(COURSE_SIZE <= right.size());
        // increasing order
        return left[END_IDX] < right[END_IDX];
        // reference to https://stackoverflow.com/questions/52745026/heap-overflow-inside-custom-sort-function
    }
#endif
public:
    int scheduleCourse(std::vector<std::vector<int>> courses) {
        // plagiarizing from https://leetcode.com/problems/course-schedule-iii/discuss/104845/Short-Java-code-using-PriorityQueue
        // and https://leetcode.com/problems/course-schedule-iii/discuss/104847/Python-Straightforward-with-Explanation
        #ifdef DEBUG
        std::cout << "start sort\n";
        #endif
        #ifdef USING_LAMBDA_CMP
        auto cmp = [] (std::vector<int> const & left, std::vector<int> const & right) {
            assert(COURSE_SIZE <= left.size());
            assert(COURSE_SIZE <= right.size());
            // increasing order
            return left[END_IDX] < right[END_IDX];
            // reference to https://stackoverflow.com/questions/52745026/heap-overflow-inside-custom-sort-function
        };
        #endif
        std::sort(std::begin(courses), std::end(courses), cmp);

        #ifdef DEBUG
        std::cout << "end sort\n";
        #endif
        #ifdef DEBUG
        for (auto const & course : courses) {
            std::cout << course[INTERNAL_IDX] << ", " << course[END_IDX] << ";\t";
        }
        std::cout << "\n";
        #endif
        std::priority_queue<int> maxHeap;
        // start means the smallest time point at cur course
        int start = 0;
        for (auto const & course : courses) {
            if (COURSE_SIZE > course.size()) {
                continue;
            }
            start += course[INTERNAL_IDX];
            maxHeap.emplace(course[INTERNAL_IDX]);
            if (start > course[END_IDX]) {
                // the former endtime point must be less than or equal to the cur endtime point
                // because the cur course can't be add to the heap, we must pop one from the heap.
                // we choose pop the maximum time internal from the heap which is its max elements
                // then start must meet the condition that start <= course[END_IDX]
                // beause if the cur intermal is max, we just remove it from start, so start <= course[END_IDX]
                // otherwise, start - maxEle + curInternalTime < course[maxEle_Endtime] <= course[END_IDX]
                start -= maxHeap.top();
                maxHeap.pop();
            }
        }
        return maxHeap.size();
    }

private:
    static int const COURSE_SIZE = 2;
    static int const INTERNAL_IDX = 0;
    static int const END_IDX = 1;
};
