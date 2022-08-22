#include "../../head.h"


// #define DEBUG
// #define REVER_ORDER
class Solution {
public:
    int carFleet(int target, std::vector<int> const & position, std::vector<int> const & speed) {
        // plagiarizing from https://leetcode.com/problems/car-fleet/discuss/139850/C%2B%2BJavaPython-Straight-Forward
        // and https://leetcode.com/problems/car-fleet/discuss/139875/C%2B%2B-5-lines
        if (position.size() != speed.size()) {
            return INVALID;
        }
        std::map<int, double> sortedPos;
        for (int idx = 0; idx < position.size(); idx++) {
            // we need get a sorted order that all the postion are sorted in non-descreasing order.
            // the datastructure of map is storaged the key with the smallest at the top (not unordered_map)
            #ifdef REVER_ORDER
            sortedPos[-position[idx]] = (double(target) - position[idx]) / speed[idx]; // get the costing time need from the position to the target
            #else
            sortedPos[position[idx]] = (double(target) - position[idx]) / speed[idx]; // get the costing time need from the position to the target
            #endif
        }
        #ifdef DEBUG
        for (auto it = sortedPos.begin(); it != sortedPos.end(); it++) {
            std::cout << it->first << ", " << it->second << "\n";
        }
        #endif
        int ans =0;
        double curCostTime = -1;
        #ifdef REVER_ORDER
        for (auto it = sortedPos.begin(); it != sortedPos.end(); it++) {
        // }  for coding indent, can not uncomment
        #else
        for (auto it = sortedPos.rbegin(); it != sortedPos.rend(); it++) {
        #endif
            // Iter all the elements from the end to the start.
            // if the previous cost time is larger than the current cost time, it means the current car will catch the previous (from the end to the start)
            if (curCostTime < it->second) {
                curCostTime = it->second;
                ans++;
            }
        }
        return ans;
    }
private:
    static int const INVALID = -1;
};