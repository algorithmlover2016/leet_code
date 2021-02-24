#include "../../head.h"


class Solution {
public:
    std::vector<int> corpFlightBookings(std::vector<std::vector<int>> const & bookings, int n) {
        // plagiarizing from https://leetcode-cn.com/problems/number-of-subarrays-with-bounded-maximum/solution/xi-fa-dai-ni-xue-suan-fa-yi-ci-gao-ding-qian-zhu-2/
        // difference array
        std::vector<int> ans(n + 1, 0);
        for (auto const & booking : bookings) {
            if (BOOK_LEN > booking.size()) {
                continue;
            }
            ans[booking[START_IDX] - 1] += booking[VAL_IDX];
            ans[booking[END_IDX]] -= booking[VAL_IDX];
        }
        ans.pop_back();
        for (int idx = 1; idx < ans.size(); idx++) {
            ans[idx] += ans[idx - 1];
        }
        return ans;

    }
private:

    static int const BOOK_LEN = 3;
    static int const START_IDX = 0;
    static int const END_IDX = 1;
    static int const VAL_IDX = 2;
};
