#include "../../head.h"


class Solution {
public:
    int findBestValue(std::vector<int> const & arr, int target) {
        int arrSize = arr.size();
        if (0 == arrSize) {
            return 0;
        }
        // long long int sum = std::accumulate(arr.begin(), arr.end(), 0);
        long long int sum = 0;
        int maxEle = INT_MIN;
        for (int index = 0; index < arrSize; index++) {
            sum += arr[index];
            if (arr[index] > maxEle) {
                maxEle = arr[index];
            }
        }

        int start = std::min(static_cast<int>(sum / arrSize), target / arrSize);
        int end = std::min(maxEle, target);
        int diff = INT_MAX;
        int res = start;
        for (; start <= end; start++) {
            long long int tmpSum = 0;
            // std::cout << "start: " << start << "\n";
            for (int index = 0; index < arrSize; index++) {
                if (arr[index] > start) {
                    tmpSum += start;
                } else {
                    tmpSum += arr[index];
                }
            }
            int tmpDiff = std::abs(tmpSum - target);
            // std::cout << "tmpSum: " << tmpSum << "\t"
            //     << "tmpDiff: " << tmpDiff <<
            //     "\tCurDiff: " << diff << "\n";
            if (tmpDiff < diff) {
                diff = tmpDiff;
                res = start;
            } else {
                break;
            }
        }
        return res;

    }
};

class Solution {
public:
    int findBestValue(std::vector<int>& A, int target) {
        // plagiarizing from https://leetcode.com/problems/sum-of-mutated-array-closest-to-target/discuss/463306/JavaC%2B%2BPython-Just-Sort-O(nlogn)
        std::sort(A.begin(), A.end());
        int n = A.size(), i = 0;
        while (i < n && target > A[i] * (n - i)) {
            target -= A[i++];
        }
        return i == n ? A[n - 1] : int(std::round((target - 0.0001) / (n - i)));
    }
};
