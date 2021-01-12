#include "../../head.h"


// #define IGNORE_TLE
class Solution {
public:
    int minimumTimeRequired(std::vector<int> const & jobs, int k) {
        // plagiarizing idea from https://youtu.be/Be4s1gRx7Vc
        int const jobsSize = jobs.size();
        if (jobsSize <= k) {
            return *std::max_element(jobs.begin(), jobs.end());
        }

        if (JUST_SUM == k) {
            return std::accumulate(jobs.begin(), jobs.end(), 0);
        }

        std::vector<int> dpMemo(k, 0);
        int ans = INIT_MAX;
        backTracking(jobs, dpMemo, k, 0, INIT_MIN, ans);
        return ans;
    }
    void backTracking(std::vector<int> const & jobs,
            std::vector<int> & dpMemo,
            int const K, int idx, int curMaxTime, int & ans) {
        if (curMaxTime >= ans) {
            return;
        }
        int const jobsSize = jobs.size();
        if (idx == jobsSize) {
            ans = curMaxTime;
            return;
        }
#ifndef IGNORE_TLE
        std::set<int> timeCostSet;
#endif
        for (int workerIdx = 0; workerIdx < K; workerIdx++) {
#ifndef IGNORE_TLE
            // because the K worker are not different, we have no necessary to distinct them
            if (timeCostSet.find(dpMemo[workerIdx]) == timeCostSet.end()) {
#endif
                dpMemo[workerIdx] += jobs[idx];
                backTracking(jobs, dpMemo, K, idx + 1, std::max(curMaxTime, dpMemo[workerIdx]), ans);
                dpMemo[workerIdx] -= jobs[idx];

#ifndef IGNORE_TLE
                timeCostSet.insert(dpMemo[workerIdx]);
            }
#endif

        }
    }

private:
    static int const JUST_SUM = 1;
    static int const INIT_MAX = INT_MAX;
    static int const INIT_MIN = 0; // the cost will always be greater than 0;
};
