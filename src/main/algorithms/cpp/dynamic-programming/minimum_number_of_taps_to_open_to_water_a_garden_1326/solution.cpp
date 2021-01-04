#include "../../head.h"


// #define DEBUG
class SolutionMyAnswer {
public:
    int minTaps(int n, std::vector<int> const & ranges) {
        if (0 == n) {
            return 0;
        }

        if (ranges.empty()) {
            return -1;
        }

        int const rangesSize = ranges.size();
        std::vector<int> dpMemo(rangesSize, n);
        dpMemo[0] = 1;

        int maxFar = INT_MIN;
        int ans = INT_MAX;

        for (int idx = 0; idx < rangesSize; idx++) {
            int mostLeft = idx - ranges[idx];
            #ifdef DEBUG
            std::cout << "idx, mostLeft: " << idx << ",\t" << mostLeft << "\t";
            #endif
            for (int left = 0; left < idx; left++) {
                // idx and left can combine together directly
                if (mostLeft <= 0) {
                    dpMemo[idx] = 1;
                } else if (mostLeft <= left + ranges[left]) {
                    dpMemo[idx] = std::min(dpMemo[idx], dpMemo[left] + 1);
                }
            }

            #ifdef DEBUG
            std::cout << "dpMemo: " << dpMemo[idx] << "\n";
            #endif
            if (dpMemo[idx] < n) {
                maxFar = std::max(maxFar, idx + ranges[idx]);
                if (maxFar >= n) {
                    ans = std::min(ans, dpMemo[idx]);
                }
            }
        }
        return INT_MAX == ans ? -1 : ans;
    }
};

class SolutionBetter {
public:
    int minTaps(int n, std::vector<int> & ranges) {

        for (int i = 1; i < ranges.size(); i++) {
            if(ranges[i] == 0) {
                ranges[i]=i;
            } else {
                int range = std::max(0, i - ranges[i]);
                ranges[range] = std::max(i + ranges[i], ranges[range]);
            }
        }

        int maxIdx = 0;
        int pos = 0;
        int jump = 0;

        for (int i = 0; i < n; i++) {
            if (maxIdx < i) {
                return -1;
            }
            maxIdx = std::max(maxIdx, ranges[i]);

            if (i == pos) {
                jump++;
                pos = maxIdx;
            }
        }
        return maxIdx >= n ? jump : -1;
    }
};
