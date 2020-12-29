#include "../../head.h"


class Solution {
public:
    int reachNumber(int target) {
        // plagiarizing from https://www.youtube.com/watch?v=K8yXBn4cCQs
        target = std::abs(target);
        int pos = 0;
        int ans = 0;
        while (pos < target || (1 & (pos - target))) {
            ans++;
            pos += ans;
        }
        return ans;
    }
};
