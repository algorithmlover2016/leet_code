#include "../../head.h"


class SolutionTLELCS {
public:
    int minOperations(std::vector<int> const & target, std::vector<int> const & arr) {
        // plagiarizing idea from https://leetcode.com/problems/minimum-operations-to-make-a-subsequence/discuss/999153/JavaC%2B%2BPython-LCS-to-LIS
        int const targetSize = target.size();
        int const arrSize = arr.size();
        // lcs
        std::vector<std::vector<int>> dpMemo(targetSize + 1,
                std::vector<int>(arrSize + 1, 0));
        for (int idxTarget = 0; idxTarget < targetSize; idxTarget++) {
            for (int idxArr = 0; idxArr < arrSize; idxArr++) {
                if (target[idxTarget] == arr[idxArr]) {
                    dpMemo[idxTarget + 1][idxArr + 1] = dpMemo[idxTarget][idxArr] + 1;
                } else {
                    dpMemo[idxTarget + 1][idxArr + 1] = std::max(dpMemo[idxTarget + 1][idxArr],
                            dpMemo[idxTarget][idxArr + 1]);
                }
            }
        }
        return targetSize - dpMemo[targetSize][arrSize];
    }
};

class Solution {
public:
    int minOperations(std::vector<int> const & target, std::vector<int> const & arr) {
        // plagiarizing idea from https://leetcode.com/problems/minimum-operations-to-make-a-subsequence/discuss/999153/JavaC%2B%2BPython-LCS-to-LIS
        int const targetSize = target.size();
        std::unordered_map<int, int> val2idx;
        for (int idxTarget = 0; idxTarget < targetSize; idxTarget++) {
            val2idx[target[idxTarget]] = idxTarget;
        }

        // LIS
        std::vector<int> LIS(targetSize, INIT_MAX);
        for (auto const & num : arr) {
            if (val2idx.find(num) == val2idx.end()) {
                continue;
            }
            auto it = std::lower_bound(LIS.begin(), LIS.end(), val2idx[num]);
            *it = val2idx[num];
        }
        while (!LIS.empty() && INIT_MAX == LIS.back()) {
            LIS.pop_back();
        }
        return targetSize - LIS.size();
    }
private:
    int const INIT_MAX = INT_MAX;
};
