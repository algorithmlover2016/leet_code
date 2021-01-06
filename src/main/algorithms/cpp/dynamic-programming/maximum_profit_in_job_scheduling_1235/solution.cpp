#include "../../head.h"


class Solution {
public:
    int jobScheduling(std::vector<int> const & startTime,
            std::vector<int> const & endTime,
            std::vector<int> const & profit) {
        // plagiarizing from https://leetcode.com/problems/maximum-profit-in-job-scheduling/discuss/409009/JavaC%2B%2BPython-DP-Solution

        int const startTimeSize = startTime.size();
        int const endTimeSize = endTime.size();
        int const profitSize = profit.size();

        if (JUST_RETURN_ZERO == startTimeSize) {
            return 0;
        }
        if (!(startTimeSize == endTimeSize && startTimeSize == profitSize)) {
            return -1;
        }
        if (JUST_RETURN_ONE == startTimeSize) {
            return profit.back();
        }
        std::vector<std::tuple<int, int, int>> jobs;
        for (int idx = 0; idx < endTimeSize; idx++) {
            jobs.emplace_back(std::make_tuple(endTime[idx], startTime[idx], profit[idx]));
        }
        std::sort(jobs.begin(), jobs.end());

        std::map<int, int> dpMemo{{0, 0}};
        for (auto const & job : jobs) {
            if (TUPLE_PROFIX >= std::tuple_size<std::remove_reference<decltype(job)>::type>::value) {
                continue;
            }
            int curProfit = std::prev(dpMemo.upper_bound(std::get<TUPLE_START_TIME>(job)))->second +
                std::get<TUPLE_PROFIX>(job);
            if (curProfit > dpMemo.rbegin()->second) {
                dpMemo[std::get<TUPLE_END_TIME>(job)] = curProfit;
            }
        }

        return dpMemo.rbegin()->second;
    }
private:
    static int const JUST_RETURN_ZERO = 0;
    static int const JUST_RETURN_ONE = 1;
    static int const TUPLE_END_TIME = 0;
    static int const TUPLE_START_TIME = 1;
    static int const TUPLE_PROFIX = 2;
};
