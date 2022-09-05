#include "../../head.h"


// #define DEBUG
class SolutionError {
public:
    int minimumWhiteTiles(std::string floor, int numCarpets, int carpetLen) {
        // this solution can not deal with the case of 101, and carpetLen = 3;
        floor += '0';
        auto cmp = [](int const left, int const right) {
            return left < right;
        };
        typedef std::priority_queue<int, std::vector<int>, decltype(cmp)> MaxHeap;
        MaxHeap maxHeap(cmp);
        int internalLen = 0;
        for (char const letter : floor) {
            if (WHITE == letter) {
                internalLen++;
            } else {
                maxHeap.emplace(internalLen);
                internalLen = 0;
            }
        }
        while (!maxHeap.empty() && numCarpets > 0) {
            int maxInternalLen = maxHeap.top(); maxHeap.pop();
            #ifdef DEBUG
            std::cout << maxInternalLen << "\n";
            #endif
            if (maxInternalLen > carpetLen) {
                maxHeap.emplace(maxInternalLen - carpetLen);
            }
            numCarpets--;
        }
        int ans = 0;
        while (!maxHeap.empty()) {
            ans += maxHeap.top(); maxHeap.pop();
        }
        return ans;
    }
private:
    constexpr char static WHITE = '1';
};


class Solution {
public:
    int minimumWhiteTiles(std::string const & floor, int numCarpets, int carpetLen) {
        // plagiarizing from https://leetcode.com/problems/minimum-white-tiles-after-covering-with-carpets/discuss/1863955/JavaC%2B%2BPython-DP-solution
        int floorSize = floor.size();
        if (0 == floorSize) {
            return 0;
        }
        std::vector<std::vector<int>> dpMemo(floorSize + 1, std::vector<int>(numCarpets + 1, 0));
        for (int idx = 1; idx <= floorSize; idx++) {
            for (int carpet = 0; carpet <= numCarpets; carpet++) {
                int skipCur = dpMemo[idx - 1][carpet] + floor[idx - 1] - OFFSET; // this pos keep unchanged
                int coverCur = (carpet > 0 ? dpMemo[std::max(idx - carpetLen, 0)][carpet - 1] : floorSize);
                dpMemo[idx][carpet] = std::min(skipCur, coverCur);
            }
        }
        return dpMemo[floorSize][numCarpets];
    }
private:
    constexpr char static OFFSET = '0';
};

class Solution {
public:
    int minimumWhiteTiles(std::string const & floor, int numCarpets, int carpetLen) {
        // plagiarizing from https://leetcode.com/problems/minimum-white-tiles-after-covering-with-carpets/discuss/1863955/JavaC%2B%2BPython-DP-solution
        int floorSize = floor.size();
        if (0 == floorSize) {
            return 0;
        }
        std::vector<std::vector<int>> dpMemo(floorSize + 1, std::vector<int>(numCarpets + 1, -1));
        for (int idx = 1; idx <= floorSize; idx++) {
            for (int carpet = 0; carpet <= numCarpets; carpet++) {
                int skipCur = dpMemo[idx - 1][carpet] + floor[idx - 1] - OFFSET; // this pos keep unchanged
                int coverCur = (carpet > 0 ? dpMemo[std::max(idx - carpetLen, 0)][carpet - 1] : floorSize);
                dpMemo[idx][carpet] = std::min(skipCur, coverCur);
            }
        }
        return dpMemo[floorSize][numCarpets];
    }
private:
    constexpr char static OFFSET = '0';
};

// #define DEBUG
class Solution {
public:
    int minimumWhiteTiles(std::string const & floor, int numCarpets, int carpetLen) {
        // plagiarizing from https://leetcode.com/problems/minimum-white-tiles-after-covering-with-carpets/discuss/1863967/Memory-Optimized-DP
        int floorSize = floor.size();
        if (0 == floorSize) {
            return 0;
        }
        std::vector<std::vector<int>> dpMemo(2, std::vector<int>(floorSize + 1, 0));

        for (int idx = 0; idx < floor.size(); idx++) {
            dpMemo[0][idx + 1] = dpMemo[0][idx] + (floor[idx] - OFFSET);
        }
        for (int carpet = 1; carpet <= numCarpets; carpet++) {
            for (int idx = 1; idx <= floorSize; idx++) {
                dpMemo[carpet & MOST_RIGHT_BIT][idx] = std::min(dpMemo[carpet & MOST_RIGHT_BIT][idx - 1] + (floor[idx - 1] - OFFSET) /* skip the swaping in this position */,
                 dpMemo[(carpet - 1) & MOST_RIGHT_BIT][std::max(idx - carpetLen, 0)]);
                #ifdef DEBUG
                std::cout << "val: " << dpMemo[carpet & MOST_RIGHT_BIT][idx]  << ", ";
                #endif
            }
            #ifdef DEBUG
            std::cout << "\n";
            #endif
        }
        return dpMemo[numCarpets & MOST_RIGHT_BIT][floorSize];
    }
private:
    constexpr char static OFFSET = '0';
    constexpr int static MOST_RIGHT_BIT = 1;
};