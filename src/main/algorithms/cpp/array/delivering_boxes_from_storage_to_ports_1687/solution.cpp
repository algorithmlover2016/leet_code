#include "../../head.h"


class Solution {
public:
    int boxDelivering(std::vector<std::vector<int>> const & boxes,
            int portsCount, int maxBoxes, int maxWeight) {
        // plagiarizing idea from https://youtu.be/OkOK8dyOmd8
        if (boxes.empty()) {
            return 0;
        }

        int const boxesSize = boxes.size();
        std::vector<int> dpMemo(boxesSize + 1, INT_MAX);

        dpMemo[0] = 0;

        int left = 0;
        int windowWeight = 0;
        int windowTrip = 2;
        for (int cur = 0; cur < boxesSize; cur++) {
            if (BOX_SIZE > boxes[cur].size()) {
                continue;
            }

            windowWeight += boxes[cur][BOX_WEIGHT_IDX]; // add this item to the window, so we need add its weight

            // if we add the item, we should know whether should add a trip or not
            if ((0 < cur) && (boxes[cur][BOX_PORT_IDX] != boxes[cur - 1][BOX_PORT_IDX])) {
                windowTrip++;
            }

            // maintain the window size
            while (((cur - left) >= maxBoxes) || // [left, cur] so the window size is cur - left + 1
                   (windowWeight > maxWeight) || // weight is over

                   // can't be (left < cur && boxes[left][BOX_PORT_IDX] == boxes[left + 1][BOX_PORT_IDX])) {
                   // because if uing this as judgement, we just consider the port changement, not the maxWeight

                   // the left-th element can be splitted to former part
                   (left < cur && dpMemo[left] == dpMemo[left + 1])) {
                windowWeight -= boxes[left][BOX_WEIGHT_IDX];
                if (boxes[left][BOX_PORT_IDX] != boxes[left + 1][BOX_PORT_IDX]) {
                    windowTrip--;
                }
                left++;
            }
            dpMemo[cur + 1] = std::min(dpMemo[cur + 1], dpMemo[left] + windowTrip);
        }
        return dpMemo[boxesSize];

    }
private:
    static int const BOX_SIZE = 2;
    static int const BOX_PORT_IDX = 0;
    static int const BOX_WEIGHT_IDX = 1;
};

// #define DEBUG
class Solution {
public:
    int boxDelivering(std::vector<std::vector<int>> const & boxes,
            int portsCount, int maxBoxes, int maxWeight) {
        // plagiarizing idea from https://leetcode.com/problems/delivering-boxes-from-storage-to-ports/discuss/969723/JavaC%2B%2BPython-Sliding-Window-O(N)-Solution
        if (boxes.empty()) {
            return 0;
        }

        int const boxesSize = boxes.size();
        
        // can not initialize the value to INT_MAX, overflow.
        // because dpMemo[windowEndIdx] will depend on its former idx which has not be computed
        // namely, windowEndIdx is start from some position not zero and it is updated discontinuously
        // std::vector<int> dpMemo(boxesSize + 1, INT_MAX);
        std::vector<int> dpMemo(boxesSize + 1, 2e5);
        dpMemo[0] = 0;

        int windowEndIdx = 0;
        int windowPortLastChange = 0;
        int windowTrip = 0;

        for (int cur = 0; cur < boxesSize; cur++) {
            if (BOX_SIZE > boxes[cur].size()) {
                continue;
            }
            // first add elements as many as possible with greedy
            while (windowEndIdx < boxesSize &&
                    maxBoxes > 0 &&
                    maxWeight >= boxes[windowEndIdx][BOX_WEIGHT_IDX]) {
                maxBoxes--;
                maxWeight -= boxes[windowEndIdx][BOX_WEIGHT_IDX];
                if (0 == windowEndIdx ||
                        boxes[windowEndIdx - 1][BOX_PORT_IDX] != boxes[windowEndIdx][BOX_PORT_IDX]) {
                    windowTrip++; // when windowEndIdx == 0, windowTrip++ means from storage to the first port
                    windowPortLastChange = windowEndIdx; // at windowEndIdx we need adding a trip because port changes;
                }
                windowEndIdx++;
            }

            #ifdef DEBUG
            std::cout << "cur: " << cur << ",\tdp: " << dpMemo[cur] << "\n";
            #endif
            // +1 means needing a return trip to arrive storage
            dpMemo[windowEndIdx] = std::min(dpMemo[windowEndIdx], dpMemo[cur] + windowTrip + 1);

            dpMemo[windowPortLastChange] = std::min(dpMemo[windowPortLastChange], dpMemo[cur] + windowTrip);

            // sliding the window to the right, which means remove the cur-th element
            maxBoxes++;
            maxWeight += boxes[cur][BOX_WEIGHT_IDX];

            if (cur != boxesSize - 1 && boxes[cur][BOX_PORT_IDX] != boxes[cur + 1][BOX_PORT_IDX]) {
            // if (cur == boxesSize - 1 || boxes[cur][BOX_PORT_IDX] != boxes[cur + 1][BOX_PORT_IDX]) {
                // we remove a element, who is not the most right elemnt, and it need a trip from cur to cur + 1;
                windowTrip--;
            }
        }
        return dpMemo[boxesSize];
    }
private:
    static int const BOX_SIZE = 2;
    static int const BOX_PORT_IDX = 0;
    static int const BOX_WEIGHT_IDX = 1;
};
