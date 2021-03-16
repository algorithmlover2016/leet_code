#include "../../head.h"


class SolutionWrongAns {
public:
    bool canChoose(std::vector<std::vector<int>> const & groups, std::vector<int> const & nums) {
        if (groups.empty() || groups[0].empty()) {
            return true;
        }
        int row = 0;
        int col = 0;
        for (int idx = 0; idx < nums.size(); idx++) {
            if (groups[row][col] != nums[idx]) {
                // if not set col = 0; no pass [[1, 2]] and [1, 3, 2]
                // if set col = 0; no pass [[21, 22, 21, 22, 21, 30]] and [21, 22, 21, 22, 21, 22, 21, 30]
                continue;
            }
            col++;
            if (col == groups[row].size()) {
                col = 0;
                row++;
            }
            if (row == groups.size()) {
                return true;
            }
        }
        return false;
    }
};
