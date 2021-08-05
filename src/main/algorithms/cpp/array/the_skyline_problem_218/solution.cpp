#include "../../head.h"\n\n\n

// #define DEBUG
class Solution {
public:
    std::vector<std::vector<int>> getSkyline(std::vector<std::vector<int>> const & buildings) {
        // reference to https://leetcode.com/problems/the-skyline-problem/discuss/61193/Short-Java-solution
        std::vector<std::vector<int>> ans;
        std::vector<std::vector<int>> heights;
        for (auto const & build : buildings) {
            if (build.size() < BUILD_SIZE) {
                continue;
            }
            heights.emplace_back(std::vector<int>{build[BUILD_LEFT_IDX], -build[BUILD_HEIGHT_IDX]});
            heights.emplace_back(std::vector<int>{build[BUILD_RIGHT_IDX], build[BUILD_HEIGHT_IDX]});
        }
        #ifdef DEBUG
        std::cout << "construct heights vector done, and heights.size() is " << heights.size() << "\n"; 
        #endif
        
        
        std::sort(heights.begin(), heights.end(), [&](std::vector<int> const & left, std::vector<int> const & right){
            assert(left.size() >= INNER_HEIGHT_SIZE);
            assert(right.size() >= INNER_HEIGHT_SIZE);
            if (left[INNER_HEIGHT_AXIS_IDX] != right[INNER_HEIGHT_AXIS_IDX]) {
                return left[INNER_HEIGHT_AXIS_IDX] < right[INNER_HEIGHT_AXIS_IDX];
            }
            return left[INNER_HEIGHT_HEIGHT_IDX] < right[INNER_HEIGHT_HEIGHT_IDX];
        });
        #ifdef DEBUG
        std::cout << "sort heights vector done\n"; 
        for (auto const & height : heights) {
            std::cout << height[INNER_HEIGHT_AXIS_IDX] << ' ' << height[INNER_HEIGHT_HEIGHT_IDX] << '\n';
        }
        #endif
        std::multiset<int> maxHeap;
        maxHeap.emplace(0);
        int pre = 0;
        for (auto const & height : heights) {
            if (height.size() < INNER_HEIGHT_SIZE) {
                continue;
            }
            #ifdef DEBUG
            std::cout << "cur ele: " << height[INNER_HEIGHT_AXIS_IDX] << ' ' << height[INNER_HEIGHT_HEIGHT_IDX] << '\n';
            #endif
            if (height[INNER_HEIGHT_HEIGHT_IDX] < 0) {
                // means the ele_height is start;
                maxHeap.emplace(-height[INNER_HEIGHT_HEIGHT_IDX]);
            } else {
                std::pair<It, It> it = maxHeap.equal_range(height[INNER_HEIGHT_HEIGHT_IDX]);
                maxHeap.erase(it.first);
            }
            #ifdef DEBUG
            std::cout << "Begin to get Max element in maxHeap\n"; 
            #endif
            int curMax = *maxHeap.rbegin();
            if (pre != curMax) {
                ans.emplace_back(std::vector<int>{height[INNER_HEIGHT_AXIS_IDX], curMax});
                pre = curMax;
            }
        }
        return ans;

    }
private:
    static int const BUILD_SIZE = 3;
    static int const BUILD_LEFT_IDX = 0;
    static int const BUILD_RIGHT_IDX = 1;
    static int const BUILD_HEIGHT_IDX = 2;

    static int const INNER_HEIGHT_SIZE = 2;
    static int const INNER_HEIGHT_AXIS_IDX = 0;
    static int const INNER_HEIGHT_HEIGHT_IDX = 1;
    typedef std::multiset<int>::iterator It;
};

class SolutionBetterRT {
public:
    std::vector<std::vector<int>> getSkyline(std::vector<std::vector<int>> & buildings) {
        std::vector<std::vector<int>> res;
        int cur = 0, cur_X, cur_H = -1,  len = buildings.size();
        std::priority_queue<std::pair<int, int>> liveBlg; // first: height, second: end time
        while(cur < len || !liveBlg.empty()) {
            // if either some new building is not processed or live building queue is not empty
            
            cur_X = liveBlg.empty() ? buildings[cur][0] : liveBlg.top().second; // next timing point to process

            if(cur >= len || buildings[cur][0] > cur_X) {
                //first check if the current tallest building will end before the next timing point
                // pop up the processed buildings, i.e. those  have height no larger than cur_H and end before the top one
                while(!liveBlg.empty() && (liveBlg.top().second <= cur_X)) {
                    liveBlg.pop();   
                }
            } else {
                // if the next new building starts before the top one ends, process the new building in the vector
                cur_X = buildings[cur][0];
                while(cur < len && buildings[cur][0] == cur_X) {
                    // go through all the new buildings that starts at the same point
                    // just push them in the queue
                    liveBlg.push(std::make_pair(buildings[cur][2], buildings[cur][1]));
                    cur++;
                }
            }
            cur_H = liveBlg.empty() ? 0 : liveBlg.top().first; // outut the top one
            if (res.empty() || (res.back()[1] != cur_H)) {
                res.push_back({cur_X, cur_H});   
            }
        }
        return res;
    }
};
