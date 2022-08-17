#include "../../head.h"


class Solution {
public:
    int shortestSequence(std::vector<int> const & rolls, int k) {
        // Find a shortest subsequence that can not be taken from rolls.
        // We can remove some roll but can not change the order.
        // plagiarizing from https://leetcode.com/problems/shortest-impossible-sequence-of-rolls/discuss/2322280/JavaC%2B%2BPython-One-Pass-O(K)-Space
        std::set<int> visited;
        int ans = 1;
        for (int const roll : rolls) {
            visited.insert(roll);
            if (visited.size() == k) {
                // it means we find a circle of all the numbers from 1 to k
                ans++; // after increament 1, ans will be the next length that need find a circle.
                visited.clear();
            }
        }
        return ans;
        
    }
};