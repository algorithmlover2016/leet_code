#include "../../head.h"
#define __DEBUG__
#include "solution.cpp"
int main() {
    Solution sol;
    std::vector<std::string> grid = {
        "..."
    };
    int d = 2;
    int result = sol.numberOfRoutes(grid, d);
    std::cout << "Number of routes: " << result << std::endl;
    return 0;
}