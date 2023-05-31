#include "../../head.h"



class Solution {
public:
    int minimumObstacles(std::vector<std::vector<int>> const & grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }
        
    }
private:
    static int const DIRECT_SIZE = 4;
    static std::array<int, DIRECT_SIZE + 1> const DIRECT;
};
std::array<int, Solution::DIRECT_SIZE + 1> const Solution::DIRECT = {0, 1, 0, -1, 0};