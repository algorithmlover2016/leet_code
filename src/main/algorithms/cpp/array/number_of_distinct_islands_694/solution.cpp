#include "../../head.h"


#define DEBUG
class Solution {
public:
    int numDistinctIslands(std::vector<std::vector<int>> const & grid) {
        // plagiarizing from https://leetcode.wenxiaoli.me/15657069520309.html
        // and https://ttzztt.gitbooks.io/lc/content/number-of-distinct-islands.html
        // and https://github.com/grandyang/leetcode/issues/694
        // first using std::string as shape
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }
        int const rowSize = grid.size();
        int const colSize = grid[0].size();
        std::vector<std::vector<bool>> visited(rowSize, std::vector<bool>(colSize, false));
        std::set<std::string> ans;
        for (int row = 0; row < rowSize; row++) {
            for (int col = 0; col < colSize; col++) {
                if (ISLAND_FLAG != grid[row][col] || visited[row][col]) {
                    continue;
                }
                std::string curAns;
                dfs(grid, row, col, visited, curAns);
                ans.insert(curAns);
#ifdef DEBUG
                std::cout << curAns << "\n";
#endif
            }

        }
        return ans.size();
    }
    void dfs(std::vector<std::vector<int>> const & grid,
            int row, int col,
            std::vector<std::vector<bool>> & visited,
            std::string & curAns) {
        int const rowSize = grid.size();
        int const colSize = grid[0].size();
        visited[row][col] = true;

        curAns += std::to_string(grid[row][col]);
        for (int idx = 0; idx < DIRECTION_SIZE; idx++) {
            int nextRow = row + directions[idx];
            int nextCol = col + directions[idx + 1];
            if (nextRow > EXCLUDE_MOST_LEFT_IDX && nextRow < rowSize &&
                    nextCol > EXCLUDE_MOST_LEFT_IDX && nextCol < colSize &&
                    ISLAND_FLAG == grid[nextRow][nextCol] && !visited[nextRow][nextCol]) {
                dfs(grid, nextRow, nextCol, visited, curAns);
            } else {
                curAns += '#';
            }
        }
    }
private:
    static int const ISLAND_FLAG = 1;
    static int const DIRECTION_ARRAY_SIZE = 5;
    static int const DIRECTION_SIZE = DIRECTION_ARRAY_SIZE - 1;
    static std::array<int, DIRECTION_ARRAY_SIZE> directions;
    static int const EXCLUDE_MOST_LEFT_IDX = -1;
};
std::array<int, Solution::DIRECTION_ARRAY_SIZE> Solution::directions = {0, 1, 0, -1, 0};

class SolutionIdxPair {
public:
    int numDistinctIslands(std::vector<std::vector<int>> const & grid) {
        // plagiarizing from https://leetcode.wenxiaoli.me/15657069520309.html
        // and https://ttzztt.gitbooks.io/lc/content/number-of-distinct-islands.html
        // and https://github.com/grandyang/leetcode/issues/694
        // first using std::string as shape
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }
        int const rowSize = grid.size();
        int const colSize = grid[0].size();
        std::vector<std::vector<bool>> visited(rowSize, std::vector<bool>(colSize, false));
        std::set<std::vector<std::pair<int, int>>> ans;
        for (int row = 0; row < rowSize; row++) {
            for (int col = 0; col < colSize; col++) {
                if (ISLAND_FLAG != grid[row][col] || visited[row][col]) {
                    continue;
                }
                std::vector<std::pair<int, int>> curAns;
                dfs(grid, row, col, row, col, visited, curAns);
                ans.insert(curAns);
#ifdef DEBUG
                std::cout << "\nIdx Pair CurLayerResult\n";
                for (auto const ele : curAns) {
                    std::cout << ele.first << ", " << ele.second << "\t";
                }
                std::cout << "\n";
#endif
            }

        }
        return ans.size();
    }
    void dfs(std::vector<std::vector<int>> const & grid,
            int rowStart, int colStart, int row, int col,
            std::vector<std::vector<bool>> & visited,
            std::vector<std::pair<int, int>> & curAns) {
        int const rowSize = grid.size();
        int const colSize = grid[0].size();
        visited[row][col] = true;
        curAns.emplace_back(std::make_pair(row - rowStart, col - colStart));
        for (int idx = 0; idx < DIRECTION_SIZE; idx++) {
            int nextRow = row + directions[idx];
            int nextCol = col + directions[idx + 1];
            if (nextRow > EXCLUDE_MOST_LEFT_IDX && nextRow < rowSize &&
                    nextCol > EXCLUDE_MOST_LEFT_IDX && nextCol < colSize &&
                    ISLAND_FLAG == grid[nextRow][nextCol] && !visited[nextRow][nextCol]) {
                dfs(grid, rowStart, colStart, nextRow, nextCol, visited, curAns);
            }
        }
    }
private:
    static int const ISLAND_FLAG = 1;
    static int const DIRECTION_ARRAY_SIZE = 5;
    static int const DIRECTION_SIZE = DIRECTION_ARRAY_SIZE - 1;
    static std::array<int, DIRECTION_ARRAY_SIZE> directions;
    static int const EXCLUDE_MOST_LEFT_IDX = -1;
};
std::array<int, SolutionIdxPair::DIRECTION_ARRAY_SIZE> SolutionIdxPair::directions = {0, 1, 0, -1, 0};

class SolutionBFS {
public:
    int numDistinctIslands(std::vector<std::vector<int>> grid) {
        // plagiarizing from https://leetcode.wenxiaoli.me/15657069520309.html
        // and https://ttzztt.gitbooks.io/lc/content/number-of-distinct-islands.html
        // and https://github.com/grandyang/leetcode/issues/694
        // first using std::string as shape
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }
        int const rowSize = grid.size();
        int const colSize = grid[0].size();
        std::set<std::vector<std::pair<int, int>>> ans;
        for (int row = 0; row < rowSize; row++) {
            for (int col = 0; col < colSize; col++) {
                if (ISLAND_FLAG != grid[row][col]) {
                    continue;
                }
#ifdef DEBUG
                std::cout << __func__ << ":" << __LINE__ << " root: " << row << "\t" << col << "\n";
#endif
                std::vector<std::pair<int, int>> curAns;
                std::queue<std::pair<int, int>> que;
                que.emplace(std::make_pair(row, col));
                while (!que.empty()) {
                    auto const & ele = que.front();
                    int curRow = ele.first;
                    int curCol = ele.second;
                    que.pop();
                    curAns.emplace_back(std::make_pair(curRow - row, curCol - col));
                    grid[curRow][curCol] = -1;
                    for (int idx = 0; idx < DIRECTION_SIZE; idx++) {
                        int nextRow = curRow + directions[idx];
                        int nextCol = curCol + directions[idx + 1];
                        if (nextRow > EXCLUDE_MOST_LEFT_IDX && nextRow < rowSize &&
                                nextCol > EXCLUDE_MOST_LEFT_IDX && nextCol < colSize &&
                                ISLAND_FLAG == grid[nextRow][nextCol]) {
                            que.emplace(std::make_pair(nextRow, nextCol));
                        }
                    }
                }

                ans.insert(curAns);

#ifdef DEBUG
                std::cout << "\nBFS CurLayerResult\n";
                for (auto const ele : curAns) {
                    std::cout << ele.first << ", " << ele.second << "\t";
                }
                std::cout << "\n";
#endif
            }

        }
        return ans.size();
    }
private:
    static int const ISLAND_FLAG = 1;
    static int const DIRECTION_ARRAY_SIZE = 5;
    static int const DIRECTION_SIZE = DIRECTION_ARRAY_SIZE - 1;
    static std::array<int, DIRECTION_ARRAY_SIZE> directions;
    static int const EXCLUDE_MOST_LEFT_IDX = -1;
};
std::array<int, SolutionBFS::DIRECTION_ARRAY_SIZE> SolutionBFS::directions = {0, 1, 0, -1, 0};


#define TEST_MAIN
#ifdef TEST_MAIN
#define PRINT_TO_SCREEN
int main() {
    Solution obj;
    SolutionIdxPair objIdxPair;
    SolutionBFS objBfs;
    std::vector<std::vector<int>> grid1{{{1, 1, 0, 0, 0}, {1, 1, 0, 0, 0}, {0, 0, 0, 1, 1}, {0, 0, 0, 1, 1}}};
    int ans1 = obj.numDistinctIslands(grid1);
    int ansIdx1 = objIdxPair.numDistinctIslands(grid1);
    int ansBfs1 = objBfs.numDistinctIslands(grid1);

#ifdef PRINT_TO_SCREEN
    std::cout << ans1 << "\t" << ansIdx1 << "\t" << ansBfs1 << "\n";
#endif

    assert(ans1 == 1);
    assert(ansIdx1 == 1);
    assert(ansBfs1 == 1);
    std::vector<std::vector<int>> grid2{{{1, 1, 0, 1, 1}, {1, 0, 0, 0, 0}, {0, 0, 0, 0, 1}, {1, 1, 0, 1, 1}}};
    int ans2 = obj.numDistinctIslands(grid2);
    int ansIdx2 = objIdxPair.numDistinctIslands(grid2);
    int ansBfs2 = objBfs.numDistinctIslands(grid2);

#ifdef PRINT_TO_SCREEN
    std::cout << ans2 << "\t" << ansIdx2 << "\t" << ansBfs2 << "\n";
#endif
    assert(ans2 == 3);
    assert(ansIdx2 == 3);
    assert(ansBfs2 == 3);


    std::vector<std::vector<int>> grid3{{{1, 1, 0, 0, 0}, {1, 0, 0, 0, 0}, {0, 0, 0, 0, 1}, {0, 0, 0, 1, 1}}};
    int ans3 = obj.numDistinctIslands(grid3);
    int ansIdx3 = objIdxPair.numDistinctIslands(grid3);
    int ansBfs3 = objBfs.numDistinctIslands(grid3);

#ifdef PRINT_TO_SCREEN
    std::cout << ans3 << "\t" << ansIdx3 << "\t" << ansBfs3 << "\n";
#endif
    assert(ans3 == 2);
    assert(ansIdx3 == 2);
    assert(ansBfs3 == 2);

    std::cout << "TEST SUCCESSFULLY" << std::endl;
    return 0;
}
#endif
