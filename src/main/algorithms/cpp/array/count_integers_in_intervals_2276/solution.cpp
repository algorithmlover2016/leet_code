#include "../../head.h"


// TLE solution
class CountIntervals {
public:
    CountIntervals() {
    }

    void add(int left, int right) {
        for (int start = left; start <= right; start++) {
            nums.insert(start);
        }
    }

    int count() {
        return nums.size();
    }
private:
    std::set<int> nums;
};

/**
 * Your CountIntervals object will be instantiated and called as such:
 * int main() {
 *  CountIntervals* obj = new CountIntervals();
 *  obj->add(left,right);
 *  int param_2 = obj->count();
 * }
 */
// #define DEBUG
class CountIntervals {
    // https://leetcode.com/problems/count-integers-in-intervals/discuss/2039706/Merge-Intervals
public:
    CountIntervals(): cnts(0) {
    }

    void add(int left, int right) {
        #ifdef DEBUG
        std::cout << "deal: " << left << ", " << right << "\n";
        #endif
        auto it = internals.upper_bound(left); // find the first element key which is larger than left;
        // The new internal [left, right] should be insert before it;
        if (it != internals.begin() && std::prev(it)->second >= left) {
            // the previous element is part included in [left, right]
            it  = std::prev(it);
            left = std::min(left, it->first);
        }
        #ifdef DEBUG
        std::cout << "[" << it->first << ", " << it->second << "]\n";
        #endif
        for (;it != internals.end() && it->first <= right; internals.erase(it++)) {
            // deal with the internal of intersection
            right = std::max(right, it->second);
            cnts -= it->second - it->first + 1;
            #ifdef DEBUG
            std::cout << "left: " << left << ", right: " << right << "\n";
            std::cout << "remove: " << it->first << ", " << it->second << "\n";
            #endif
        }
        internals.insert({left, right});
        // internals[left] = right;
        cnts += right - left + 1;
        #ifdef DEBUG
        std::cout << "insert: [" << left << ", " << right << "]\n";
        for (auto [key, val] : internals) {
            std::cout << "[" << key << ", " << val << "]\t";
        }
        std::cout << "\n";
        #endif
        

    }

    int count() {
        return cnts;
    }
private:
    std::map<int, int> internals;
    int cnts;
};