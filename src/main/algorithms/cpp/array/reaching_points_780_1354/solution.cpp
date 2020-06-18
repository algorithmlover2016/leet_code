#include "../../head.h"


class SolutionWrong {
public:
    bool reachingPoints(int sx, int sy, int tx, int ty) {
        std::vector<int> start{sx, sy};
        std::vector<int> destination{tx, ty};
        if (start > destination) {
            return false;
        }
        long target = 0;
        int startMin = INT_MAX;
        std::priority_queue<int> todo;
        std::multiset<int> select(start.begin(), start.end());
        for (int index = 0; index < destination.size(); index++) {
            if (startMin > start[index]) {
                startMin = start[index];
            }
            target += destination[index];
            todo.emplace(destination[index]);
        }
        while (!todo.empty()) {
            int cur = todo.top(); todo.pop();
            target -= cur;
            std::cout << "cur: " << cur << "\tother: " << target << "\n";
            if (select.find(cur) != select.end()) {
                select.erase(cur);
                if (select.empty()) {
                    return true;
                } else  if (1 == select.size()) {
                    return cur != 1 && target == *(select.begin()) % cur;
                }
            }
            if (cur < target || (0 < target && target < startMin)) {
                return false;
            }
            if (0 == target) {
                break;
            }
            cur %= target;
            target += cur;
            todo.emplace(cur);
        }
        return select.empty();
    }
};

class Solution {
public:
    bool reachingPoints(int sx, int sy, int tx, int ty) {
        // plagiarizing from https://leetcode.com/problems/reaching-points/discuss/114856/JavaC%2B%2BPython-Modulo-from-the-End
        while (sx < tx && sy < ty) {
            if (tx < ty) {
                ty %= tx;
            } else {
                tx %= ty;
            }
        }
        return (sx == tx && sy <= ty && (0 == (ty - sy) % tx)) ||
            (sy == ty && sx <= tx && (0 == (tx - sx) % ty));

    };
};
