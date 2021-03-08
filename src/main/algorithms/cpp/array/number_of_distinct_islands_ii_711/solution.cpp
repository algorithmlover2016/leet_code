#include "../../head.h"


#define DEBUG
class SolutionIdxPair {
public:
    int numDistinctIslands(std::vector<std::vector<int>> const & grid) {
        // plagiarizing from https://leetcode.wenxiaoli.me/15657069520309.html
        // and https://ttzztt.gitbooks.io/lc/content/number-of-distinct-islands.html
        // and https://github.com/grandyang/leetcode/issues/694
        // and https://www.cnblogs.com/grandyang/p/8542820.html

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
                dfs(grid, row, col, visited, curAns);
                ans.insert(normalize(curAns));
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
            int row, int col,
            std::vector<std::vector<bool>> & visited,
            std::vector<std::pair<int, int>> & curAns) {
        int const rowSize = grid.size();
        int const colSize = grid[0].size();
        visited[row][col] = true;
        curAns.emplace_back(row, col);
        for (int idx = 0; idx < DIRECTION_SIZE; idx++) {
            int nextRow = row + directions[idx];
            int nextCol = col + directions[idx + 1];
            if (nextRow > EXCLUDE_MOST_LEFT_IDX && nextRow < rowSize &&
                    nextCol > EXCLUDE_MOST_LEFT_IDX && nextCol < colSize &&
                    ISLAND_FLAG == grid[nextRow][nextCol] && !visited[nextRow][nextCol]) {
                dfs(grid, nextRow, nextCol, visited, curAns);
            }
        }
    }

    std::vector<std::pair<int, int>> normalize(std::vector<std::pair<int, int>> const & curAns) {
        std::vector<std::vector<std::pair<int, int>>> shapes(8);
        for (auto const & ele : curAns) {
            int row = ele.first;
            int col = ele.second;
            shapes[0].emplace_back(std::make_pair(row, col));
            shapes[1].emplace_back(std::make_pair(row, -col));
            shapes[2].emplace_back(std::make_pair(-row, col));
            shapes[3].emplace_back(std::make_pair(-row, -col));
            shapes[4].emplace_back(std::make_pair(col, row));
            shapes[5].emplace_back(std::make_pair(col, -row));
            shapes[6].emplace_back(std::make_pair(-col, row));
            shapes[7].emplace_back(std::make_pair(-col, -row));
        }
        for (auto & shape : shapes) {
            std::sort(std::begin(shape), std::end(shape));
            for (int idx = shape.size() - 1; idx > EXCLUDE_MOST_LEFT_IDX; idx--) {
                shape[idx].first = shape[idx].first - shape[0].first;
                shape[idx].second = shape[idx].second - shape[0].second;
            }
        }
        std::sort(std::begin(shapes), std::end(shapes));
        return shapes[0];
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
                    curAns.emplace_back(std::make_pair(curRow, curCol));
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

                ans.insert(normalize(curAns));

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
    std::vector<std::pair<int, int>> normalize(std::vector<std::pair<int, int>> const & curAns) {
        std::vector<std::vector<std::pair<int, int>>> shapes(8);
        for (auto const & ele : curAns) {
            int row = ele.first;
            int col = ele.second;
            shapes[0].emplace_back(std::make_pair(row, col));
            shapes[1].emplace_back(std::make_pair(row, -col));
            shapes[2].emplace_back(std::make_pair(-row, col));
            shapes[3].emplace_back(std::make_pair(-row, -col));
            shapes[4].emplace_back(std::make_pair(col, row));
            shapes[5].emplace_back(std::make_pair(col, -row));
            shapes[6].emplace_back(std::make_pair(-col, row));
            shapes[7].emplace_back(std::make_pair(-col, -row));
        }
        for (auto & shape : shapes) {
            std::sort(std::begin(shape), std::end(shape));
            for (int idx = shape.size() - 1; idx > EXCLUDE_MOST_LEFT_IDX; idx--) {
                shape[idx].first = shape[idx].first - shape[0].first;
                shape[idx].second = shape[idx].second - shape[0].second;
            }
        }
        std::sort(std::begin(shapes), std::end(shapes));
        return shapes[0];
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
    SolutionIdxPair objIdxPair;
    SolutionBFS objBfs;
    std::vector<std::vector<int>> grid1{{{1, 1, 0, 0, 0}, {1, 1, 0, 0, 0}, {0, 0, 0, 1, 1}, {0, 0, 0, 1, 1}}};
    int ansIdx1 = objIdxPair.numDistinctIslands(grid1);
    int ansBfs1 = objBfs.numDistinctIslands(grid1);

#ifdef PRINT_TO_SCREEN
    std::cout << "grid1: " << ansIdx1 << "\t" << ansBfs1 << "\n";
#endif

    assert(ansIdx1 == 1);
    assert(ansBfs1 == 1);
    std::vector<std::vector<int>> grid2{{{1, 1, 0, 1, 1}, {1, 0, 0, 0, 0}, {0, 0, 0, 0, 1}, {1, 1, 0, 1, 1}}};
    int ansIdx2 = objIdxPair.numDistinctIslands(grid2);
    int ansBfs2 = objBfs.numDistinctIslands(grid2);

#ifdef PRINT_TO_SCREEN
    std::cout << "grid2: " << ansIdx2 << "\t" << ansBfs2 << "\n";
#endif
    assert(ansIdx2 == 2);
    assert(ansBfs2 == 2);


    std::vector<std::vector<int>> grid3{{{1, 1, 0, 0, 0}, {1, 0, 0, 0, 0}, {0, 0, 0, 0, 1}, {0, 0, 0, 1, 1}}};
    int ansIdx3 = objIdxPair.numDistinctIslands(grid3);
    int ansBfs3 = objBfs.numDistinctIslands(grid3);

#ifdef PRINT_TO_SCREEN
    std::cout << "grid3: " << ansIdx3 << "\t" << ansBfs3 << "\n";
#endif
    assert(ansIdx3 == 1);
    assert(ansBfs3 == 1);

    std::cout << "TEST SUCCESSFULLY" << std::endl;
    return 0;
}
#endif
