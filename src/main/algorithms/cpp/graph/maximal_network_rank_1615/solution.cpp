#include "../../head.h"

// #define DEBUG
class Solution {
public:
    int maximalNetworkRank(int n, std::vector<std::vector<int>> const & roads) {
        // plagirizing from https://leetcode.com/problems/maximal-network-rank/discuss/889001/C%2B%2B-quadratic...-linearithmic...-linear!

        std::vector<int> cntRoads(n, 0); // std::unordered_map but the roads are from 0 to n - 1

        std::unordered_set<int> connected;
        for (auto const & road : roads) {
            if (CONNECTED_ROAD_LEN > road.size()) {
                continue;
            }
            ++cntRoads[road[IDX_ROAD_FIRST]];
            ++cntRoads[road[IDX_ROAD_SECOND]];
            connected.insert((road[IDX_ROAD_FIRST] << FIRST_SHIFT) | (road[IDX_ROAD_SECOND]));
            connected.insert((road[IDX_ROAD_SECOND] << FIRST_SHIFT) | (road[IDX_ROAD_FIRST]));
        }
        int ans = INIT_MIN;

        int const maxIdx = std::max_element(cntRoads.begin(), cntRoads.end()) - cntRoads.begin();
        int maxCnt = std::count(std::begin(cntRoads), std::end(cntRoads), cntRoads[maxIdx]);
        #ifdef DEBUG
        std::cout << "maxIdx, maxCnt: " << maxIdx << ",\t" << maxCnt << "\n";
        #endif
        if (JUST_ONE == maxCnt) {
            for (int idx = 0; idx < n; idx++) {
                if (maxIdx != idx){
                    ans = std::max(ans, cntRoads[maxIdx] + cntRoads[idx]
                            - static_cast<int>(connected.count((maxIdx << FIRST_SHIFT) | idx)));
                }
            }
        } else {
            int connectMaxIdxNum = std::count_if(roads.begin(), roads.end(), [&] (std::vector<int> const & road) {
                    return cntRoads[road[IDX_ROAD_FIRST]] == cntRoads[maxIdx] &&
                            cntRoads[road[IDX_ROAD_SECOND]] == cntRoads[maxIdx];
                    });
            #ifdef DEBUG
            std::cout << "connectMaxIdxNum: " << connectMaxIdxNum << '\n';
            #endif
            // ans = (2 * cntRoads[maxIdx]) - ((cntRoads[maxIdx] * (cntRoads[maxIdx] - 1) / 2 > connectMaxIdxNum) ? 0 : 1);
            // to judge all the idx whose edges is cntRoads[maxIdx] can construct a full graph
            ans = (2 * cntRoads[maxIdx]) - ((maxCnt * (maxCnt - 1) / 2 > connectMaxIdxNum) ? 0 : 1);
        }



        return ans;
    }
private:
    static int const CONNECTED_ROAD_LEN = 2;
    static int const IDX_ROAD_FIRST = 0;
    static int const IDX_ROAD_SECOND = 1;
    static int const INIT_MIN = 0;
    static int const FIRST_SHIFT = 16;
    static int const JUST_ONE = 1;
};

class SolutionSort {
public:
    int maximalNetworkRank(int n, std::vector<std::vector<int>> const & roads) {
        // plagirizing from https://leetcode.com/problems/maximal-network-rank/discuss/889001/C%2B%2B-quadratic...-linearithmic...-linear!

        std::vector<int> cntRoadsIdx(n); // std::unordered_map but the roads are from 0 to n - 1
        std::iota(cntRoadsIdx.begin(), cntRoadsIdx.end(), 0);
        // std::iota(std::begin(cntRoadsIdx), std::end(cntRoadsIdx), initVal);

        std::vector<int> cntRoads(n, 0); // std::unordered_map but the roads are from 0 to n - 1

        std::unordered_set<int> connected;
        for (auto const & road : roads) {
            if (CONNECTED_ROAD_LEN > road.size()) {
                continue;
            }
            ++cntRoads[road[IDX_ROAD_FIRST]];
            ++cntRoads[road[IDX_ROAD_SECOND]];
            connected.insert((road[IDX_ROAD_FIRST] << FIRST_SHIFT) | (road[IDX_ROAD_SECOND]));
            connected.insert((road[IDX_ROAD_SECOND] << FIRST_SHIFT) | (road[IDX_ROAD_FIRST]));
        }
        // according to val in cntRoads sort cntRoadsIdx, so that we just sort the idx
        std::sort(std::begin(cntRoadsIdx), std::end(cntRoadsIdx), [&](int i, int j) {
                return cntRoads[i] > cntRoads[j];
                });
        int ans = INIT_MIN;
        for (int left = 0; left < n; left++) {
            for (int right = left + 1; right < n; right++) {
                if (cntRoads[cntRoadsIdx[left]] + cntRoads[cntRoadsIdx[right]] < ans) {
                    return ans;
                }
                ans = std::max(ans, cntRoads[cntRoadsIdx[left]] + cntRoads[cntRoadsIdx[right]]
                        - static_cast<int>(connected.count((cntRoadsIdx[left] << FIRST_SHIFT) | (cntRoadsIdx[right]))));

            }
        }
        return ans;
    }
private:
    static int const CONNECTED_ROAD_LEN = 2;
    static int const IDX_ROAD_FIRST = 0;
    static int const IDX_ROAD_SECOND = 1;
    static int const INIT_MIN = 0;
    static int const FIRST_SHIFT = 16;
};

class SolutionBruteFS {
public:
    int maximalNetworkRank(int n, std::vector<std::vector<int>> const & roads) {
        // my idea is similar to https://leetcode.com/problems/maximal-network-rank/discuss/888916/Java-simple-O(n2)
        // brute force solution
        std::vector<std::vector<bool>> connected(n,
                std::vector<bool>(n, false));
        std::vector<int> cntRoads(n, 0); // std::unordered_map but the roads are from 0 to n - 1
        for (auto const & road : roads) {
            if (CONNECTED_ROAD_LEN > road.size()) {
                continue;
            }
            ++cntRoads[road[IDX_ROAD_FIRST]];
            ++cntRoads[road[IDX_ROAD_SECOND]];
            connected[road[IDX_ROAD_FIRST]][road[IDX_ROAD_SECOND]] = true;
            connected[road[IDX_ROAD_SECOND]][road[IDX_ROAD_FIRST]] = true;
        }

        int ans = INIT_MIN;
        for (int left = 0; left < n; left++) {
            for (int right = left + 1; right < n; right++) {
                ans = std::max(ans, cntRoads[left] + cntRoads[right] - (connected[left][right] ? 1 : 0));
            }
        }
        return ans;

    }
private:
    static int const CONNECTED_ROAD_LEN = 2;
    static int const IDX_ROAD_FIRST = 0;
    static int const IDX_ROAD_SECOND = 1;
    static int const INIT_MIN = 0;
};
