#include "../../head.h"


// if a knows b, it will return true; else return false;
bool knows(int a, int b);
class Solution {
public: 
    int findCelebrity(int n) {
        // plagiarizing from https://github.com/grandyang/leetcode/issues/277
        std::vector<bool> people(n, true);
        for (int idx = 0; idx < n; idx++) {
            if (!people[idx]) {
                continue;
            }
            for (int fri = 0; fri < n; fri++) {
                if (fri == idx) {
                    continue;
                }
                if (knows(idx, fri) || (!knows(fri, idx))) {
                    // idx knows fri, or fri don't know idx
                    people[idx] = false;
                } else {
                    // idx don't know fri and fri knows idx
                    people[fri] = false;
                }
            }
            if (people[idx]) {
                return idx;
            }
        }
        return -1;
    }
};

class Solution {
public: 
    int findCelebrity(int n) {
        // plagiarizing from https://github.com/grandyang/leetcode/issues/277
        for (int idx = 0, fri = 0; idx < n; idx++) {
            for (fri = 0; fri < n; fri++) {
                if (fri == idx) {
                    continue;
                }
                if (knows(idx, fri) || (!knows(fri, idx))) {
                    // idx knows fri, or fri don't know idx
                    break;
                }
            }
            if (fir == n) {
                return idx;
            }
        }
        return -1;
    }
};

#define OPTIMIZING_TIME_COMPLEXITY
class Solution {
public: 
    int findCelebrity(int n) {
        // plagiarizing from https://github.com/grandyang/leetcode/issues/277
        int res = 0;
        // assuming res is the celebrity
        for (int idx = 0; idx < n; idx++) {
            if (knows(res, idx)) {
                // there is a assuming that all the people should know the celebrity
                // res knows idx or idx don't know res, it means res not the celebrity
                res = idx;
            }
        }

#ifndef OPTIMIZING_TIME_COMPLEXITY
        // res will meet the result that it knows no body except itself, and all the other people knows him or at the end
        for (int idx = 0; idx < n; idx++) {
            if (res != idx && (knows(res, idx) || (!knows(idx, res)))) {
                return -1;
            }
        }
#else
        for (int idx = 0; idx < res; idx++) {
            if (knows(res, idx) || (!knows(idx, res))) {
                return -1;
            }
        }
        for (int idx = res + 1; idx < n; idx++) {
            if (!knows(idx, res)) {
                return -1;
            }
        }
#endif
        return -1;
    }
};
