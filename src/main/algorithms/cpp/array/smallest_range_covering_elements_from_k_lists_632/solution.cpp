#include "../../head.h"


class Solution {
private:
    class cmp {
    public:
        // operator() must be public
        bool operator()(std::tuple<int, int, int> const & lhs, std::tuple<int, int, int> const & rhs) {
            return std::get<0>(lhs) > std::get<0>(rhs);
        }
    };
public:
    std::vector<int> smallestRange(std::vector<vector<int>> const & nums) {
        // plagiarizing from https://leetcode.com/problems/smallest-range-covering-elements-from-k-lists/discuss/104893/Java-Code-using-PriorityQueue.-similar-to-merge-k-array
        int numsSize = nums.size();
        if (0 == numsSize) {
            return {};
        }
        int minDiff = INT_MAX, colMax = INT_MIN;
        std::priority_queue<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>, cmp > todo; // reocord the min element and its row index, its col index
        for (int index = 0; index < numsSize; index++) {
            // if there is a row is empty, then we will never find the range
            if (nums[index].empty()) {
                return {};
            }
            todo.emplace(std::make_tuple(nums[index][0], index, 0));
            colMax = std::max(colMax, nums[index][0]);
        }
        std::vector<int> res(2, 0);
        // if the size equal to numsSize, it means there are numsSize line
        while (todo.size() == numsSize) {
            std::tuple<int, int, int> const & cur = todo.top();
            int curVal = std::get<0>(cur);
            int curRow = std::get<1>(cur);
            int curCol = std::get<2>(cur);
            todo.pop();
            if (colMax - curVal < minDiff) {
                minDiff = colMax - curVal;
                res[0] = curVal;
                res[1] = colMax;
            }
            int newCol = curCol + 1;
            if (newCol < nums[curRow].size()) {
                todo.emplace(std::make_tuple(nums[curRow][newCol], curRow, newCol));
                if (colMax < nums[curRow][newCol]) {
                    colMax = nums[curRow][newCol];
                }
            }
        }
        return res;
    }
};

class SolutionBetterRuntime {
public:
    std::vector<int> smallestRange(std::vector<std::vector<int>> const & nums) {
        // it's the same idea, however it use the properties that map is a min heap, it store the col index in a global vector
        std::map<int, std::vector<int>> mp;
        std::vector<int> pos(nums.size(), 0);

        for (int i = 0; i < nums.size(); ++i) {
            mp[nums[i][0]].push_back(i);
        }

        std::vector<int> res(2, 0);
        int minr = INT_MAX;
        bool found = false;
        while (!found) {
            auto it1 = mp.begin();
            auto it2 = std::prev(mp.end());
            if (it2->first - it1->first < minr) {
                minr = it2->first - it1->first;
                res[0] = it1->first;
                res[1] = it2->first;
            }
            std::vector<int> next = it1->second;
            mp.erase(it1);
            for (int i: next) {
                pos[i]++;
                if (pos[i] == nums[i].size()) {
                    found = true;
                    break;
                }
                mp[nums[i][pos[i]]].push_back(i);
            }
        }

        return res;
    }
};
