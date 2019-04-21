#include <iostream>
#include <sstream>
#include <string>

class Solution {
public:
    int orderOfLargestPlusSign(int N, vector<vector<int>>& mines) {
        // copy solution from https://leetcode.com/problems/largest-plus-sign/discuss/113314/JavaC%2B%2BPython-O(N2)-solution-using-only-one-grid-matrix
        // I got a solution with O(N^4), which must be bad solution, and then I saw the discuss, and I foud this solution, which made inner loop computing four directions to make time complexity reduce to O(N^2)
        std::vector<std::vector<int> > grids(N, vector<int>(N, (N >> 1) + 1));
        for (vector<int> & mine : mines) {
            if (mine.size() != 2) {
                 continue;
            }
            grids[mine[0]][mine[1]] = 0;
        }
        for (int index = 0; index < N; index++) {
            for (int start = 0, end = N - 1, left = 0, right = 0, up = 0, down = 0;
                start < N; start++, end--) {
                grids[index][start] = std::min(grids[index][start],
                                               left = (grids[index][start] == 0 ? 0 : left + 1) );

                grids[index][end] = std::min(grids[index][end],
                                               right = (grids[index][end] == 0 ? 0 : right + 1) );

                grids[start][index] = std::min(grids[start][index],
                                               up = (grids[start][index] == 0 ? 0 : up + 1) );
                grids[end][index] = std::min(grids[end][index],
                                               down = (grids[end][index] == 0 ? 0 : down + 1) );
            }
        }
        int ans = 0;
        for (int index = 0; index < N; index++) {
            for (int subIndex = 0; subIndex < N; subIndex++) {
                ans = std::max(ans, grids[index][subIndex]);
            }
        }
        return ans;
    }
};
// g++ -std=c++11  -o main solution.cpp
