#include "../../head.h"
#include "solution.cpp"

int main() {
    Solution sol;
    vector<vector<int>> lists = {
        {1, 1, 5},
        {1, 4, 7, 8}
    };
    long long result = sol.minMergeCost(lists);
    cout << "Minimum Merge Cost: " << result << endl;
    return 0;
}