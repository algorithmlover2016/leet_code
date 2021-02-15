#include "../../head.h"


// #define DEBUG

class SolutionPriorityQueue { // minHeap
protected:
    friend class Comp;
    class Comp {
    private:
        bool _reverse;
        std::vector<int> const & _arr;
    public:
        Comp(std::vector<int> const & arr, bool reverse = false) : _arr(arr), _reverse(reverse) {
        }
        bool operator()(std::pair<int, int> const & left, std::pair<int, int> const & right) {
            // x / y < w / z (x, y, w, z > 0) => x * z < y * w
            if (_arr[left.first] * _arr[right.second] <= _arr[left.second] * _arr[right.first]) {
                return !_reverse;
            } else {
                return _reverse;
            }
        }
    };

public:
    std::vector<int> kthSmallestPrimeFraction(std::vector<int> const & arr, int k) {
        // plagiarizing idea from https://leetcode.com/problems/k-th-smallest-prime-fraction/discuss/115819/Summary-of-solutions-for-problems-%22reducible%22-to-LeetCode-378
        // similar to https://leetcode.com/problems/k-th-smallest-prime-fraction/discuss/115486/Java-AC-O(max(nk)-*-logn)-Short-Easy-PriorityQueue
        int const arrSize = arr.size();
        if (JUST_ONE >= arrSize) {
            return {};
        }

        typedef std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, Comp> MaxHeap;

        Comp comp(arr, true);
        MaxHeap minHeap(comp);

        for (int idx = 0; idx < arrSize - 1; idx++) {
            #ifdef DEBUG
            std::cout << "add: " << arr[idx] << ",\t" << arr[arrSize - 1] << "\n";
            #endif
            minHeap.push(std::make_pair(idx, arrSize - 1));
        }

        while (k-- > 1) {
            auto const & ele = minHeap.top();
            int numeratorIdx = ele.first;
            int denominatorIdx = ele.second;
            minHeap.pop();

            #ifdef DEBUG
            std::cout << arr[numeratorIdx] << ",\t" << arr[denominatorIdx] << "\t";
            #endif

            // MOST_LEFT_IDX_EXCLUDE
            if (--denominatorIdx > numeratorIdx) {

                #ifdef DEBUG
                std::cout << "add: " << arr[numeratorIdx] << ",\t" << arr[denominatorIdx] << "\n";
                #endif

                minHeap.push(std::make_pair(numeratorIdx, denominatorIdx));
            }
        }
        auto const & ans = minHeap.top();
        return {arr[ans.first], arr[ans.second]};
    }

    private:
    static int const JUST_ONE = 1;
    // static int const MOST_LEFT_IDX_EXCLUDE = -1;
    // static int const NUMERATOR_IDX = 0;
    // static int const DENOMINATOR_IDX = 1;
};

// #define DEBUG

class SolutionBinarySearch {
public:
    std::vector<int> kthSmallestPrimeFraction(std::vector<int> const & arr, int k) {
        // plagiarizing idea from https://leetcode.com/problems/k-th-smallest-prime-fraction/discuss/115819/Summary-of-solutions-for-problems-%22reducible%22-to-LeetCode-378
        int const arrSize = arr.size();
        if (JUST_ONE >= arrSize) {
            return {};
        }

        double low = 0, high = 1;
        int curMinNumerator = 0, curMaxDenominator = 1; // record the cur Max fraction

        for (int cnt = 0; true; cnt = 0, curMinNumerator = 0) {
            // double mid = low + (high - low) / 2;
            double mid = (high + low) / 2;

            // should use arrSize - 1 - rightIdx to represent the right ele
            for (int leftIdx = 0, rightIdx = arrSize - 1; leftIdx < arrSize; leftIdx++) {
                while (rightIdx > MOST_LEFT_IDX_EXCLUDE && arr[leftIdx] > mid * arr[arrSize - 1 - rightIdx]) {
                    rightIdx--;
                }
                cnt += 1 + rightIdx;

                #ifdef DEBUG
                std::cout << "left, right: " << leftIdx << ",\t" << rightIdx + 1 << ",\tmid: " << mid << "\n";
                #endif

                // curMinNumerator / curMaxDenominator < arr[leftIdx] / arr[1 + rightIdx]
                if (rightIdx > MOST_LEFT_IDX_EXCLUDE &&
                    curMinNumerator * arr[arrSize - 1 - rightIdx] < curMaxDenominator * arr[leftIdx]) {
                    curMinNumerator = arr[leftIdx];
                    curMaxDenominator = arr[arrSize - 1 - rightIdx];
                }
            }



            if (cnt > k) {
                high = mid;
            } else if (cnt < k) {
                low = mid;
            } else {
                return {curMinNumerator, curMaxDenominator};
            }
        }
    }
    private:
    static int const JUST_ONE = 1;
    static int const MOST_LEFT_IDX_EXCLUDE = -1;
};


// #define DEBUG
class SolutionZigzagSearch {
public:
    std::vector<int> kthSmallestPrimeFraction(std::vector<int> const & arr, int k) {
        // plagiarizing idea from https://leetcode.com/problems/k-th-smallest-prime-fraction/discuss/115819/Summary-of-solutions-for-problems-%22reducible%22-to-LeetCode-378
        int const arrSize = arr.size();
        if (JUST_ONE >= arrSize) {
            return {};
        }

        int curMinNumerator = 0, curMaxDenominator = arrSize - 1; // record the cur Max fraction
        // curMaxDenominator from n - 1 to 0, traverse arr from 0 to n - 1

        for (int leCnt = 0, ltCnt = 0; true; leCnt = 0, ltCnt = 0) {
            // should use arrSize - 1 - rightIdx to represent the right ele
            for (int leftIdx = 0, leIdx = arrSize - 1, ltIdx = arrSize - 1; leftIdx < arrSize; leftIdx++) {
                while (leIdx > MOST_LEFT_IDX_EXCLUDE &&
                        // arr[leftIdx] / arr[arrSize - 1 - leIdx] > arr[curMinNumerator] / arr[arrSize - 1 - curMaxDenominator]
                        arr[leftIdx] * arr[arrSize - 1 - curMaxDenominator] > arr[curMinNumerator] * arr[arrSize - 1 - leIdx]) {
                    leIdx--;
                }
                leCnt += 1 + leIdx;

                while (ltIdx > MOST_LEFT_IDX_EXCLUDE &&
                        // arr[leftIdx] / arr[arrSize - 1 - ltIdx] >= arr[curMinNumerator] / arr[arrSize - 1 - curMaxDenominator]
                        arr[leftIdx] * arr[arrSize - 1 - curMaxDenominator] >= arr[curMinNumerator] * arr[arrSize - 1 - ltIdx]) {
                    ltIdx--;
                }
                ltCnt += 1 + ltIdx;
            }

            #ifdef DEBUG
            std::cout << "leCnt, ltCnt: " << leCnt << ",\t" << ltCnt << ",\t"
                << arr[curMinNumerator] << ",\t" << arr[arrSize - 1 - curMaxDenominator] << "\n";
            #endif

            if (leCnt < k) {
                curMinNumerator++;
            } else if (ltCnt >= k) {
                curMaxDenominator--;
            } else {
                return {arr[curMinNumerator], arr[arrSize - 1 - curMaxDenominator]};
            }
        }
    }
private:
    static int const JUST_ONE = 1;
    static int const MOST_LEFT_IDX_EXCLUDE = -1;
};
