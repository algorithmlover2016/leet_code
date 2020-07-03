#include "../../head.h"


class Solution {
public:
    int shortestPathAllKeys(std::vector<std::string> const & grid) {
        // plagiarizing from https://leetcode.com/problems/shortest-path-to-get-all-keys/discuss/146878/Java-BFS-Solution
        int rowSize = grid.size();
        if (0 == rowSize) {
            return 0;
        }

        int startRow = -1, startCol = -1;
        int allKeys = 0;
        for (int row = 0; row < grid.size(); row++) {
            for (int col = 0; col < grid[row].size(); col++) {
                if ('@' == grid[row][col]) {
                    startRow = row;
                    startCol = col;
                } else if ('a' <= grid[row][col] && 'f' >= grid[row][col]) {
                    allKeys |= 1 << (grid[row][col] - 'a'); // maxKey can not be started from zero;
                }
            }
        }

        if (-1 == startRow || -1 == startCol) {
            return -1;
        }

        std::set<std::tuple<int, int, int>> visited;
        std::queue<std::tuple<int, int, int>> todo;
        std::tuple<int, int, int> startTuple(0, startRow, startCol);
        todo.emplace(startTuple);
        visited.emplace(startTuple);
        int step = 0;
        do {
            step++;
            // std::cout << "\n";
            for (int layerSize = todo.size(); layerSize > 0; layerSize--) {
                auto const & cur = todo.front();
                int keys = std::get<0>(cur);
                int curRow = std::get<1>(cur);
                int curCol = std::get<2>(cur);
                todo.pop();
                // std::cout << "\ncur: " << curRow << "\t" << curCol << "\t";
                for (int index = 0; index < DIRECTION_SIZE; index++) {
                    int nextRow = curRow + directions[index];
                    int nextCol = curCol + directions[index + 1];
                    if (nextRow >= 0 && nextRow < rowSize &&
                            nextCol >= 0 && nextCol < grid[nextRow].size()) {
                        if ('#' == grid[nextRow][nextCol]) {
                            continue;
                        } else if ('a' <= grid[nextRow][nextCol] && 'f' >= grid[nextRow][nextCol]) {
                            int nextKeys = keys | (1 << (grid[nextRow][nextCol] - 'a'));
                            if (allKeys == nextKeys) {
                                return step;
                            } else {
                                std::tuple<int, int, int> next(nextKeys, nextRow, nextCol);
                                if (visited.find(next) == visited.end()) {
                                    // std::cout << "next: " << nextRow << "\t" << nextCol << "\t";
                                    todo.emplace(next);
                                    visited.emplace(next);
                                }
                            }
                        } else if ('A' <= grid[nextRow][nextCol] && 'F' >= grid[nextRow][nextCol]) {
                            if (keys & (1 << (grid[nextRow][nextCol] - 'A'))) {
                                std::tuple<int, int, int> next(keys, nextRow, nextCol);
                                if (visited.find(next) == visited.end()) {
                                    // std::cout << "next: " << nextRow << "\t" << nextCol << "\t";
                                    todo.emplace(next);
                                    visited.emplace(next);
                                }
                            }
                        } else {
                            std::tuple<int, int, int> next(keys, nextRow, nextCol);
                            if (visited.find(next) == visited.end()) {
                                // std::cout << "next: " << nextRow << "\t" << nextCol << "\t";
                                todo.emplace(next);
                                visited.emplace(next);
                            }
                        }
                    }
                }
            }
        } while (todo.size());
        return -1;
    }
private:
    static int const DIRECTION_ARRAY_SIZE = 5;
    static int const DIRECTION_SIZE = DIRECTION_ARRAY_SIZE - 1;
    static std::array<int, DIRECTION_ARRAY_SIZE> directions;
};
std::array<int, Solution::DIRECTION_ARRAY_SIZE> Solution::directions = {0, 1, 0, -1, 0};
static int io = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();

class SolutionOptimise {
public:
    int shortestPathAllKeys(std::vector<std::string> const & grid) {
        // plagiarizing from https://leetcode.com/problems/shortest-path-to-get-all-keys/discuss/146878/Java-BFS-Solution
        int rowSize = grid.size();
        if (0 == rowSize) {
            return 0;
        }
        int colSize = grid[0].size();
        if (0 == colSize) {
            return 0;
        }
        int startRow = -1, startCol = -1;
        int allKeys = 0;
        for (int row = 0; row < grid.size(); row++) {
            for (int col = 0; col < grid[row].size(); col++) {
                if ('@' == grid[row][col]) {
                    startRow = row;
                    startCol = col;
                } else if ('a' <= grid[row][col] && 'f' >= grid[row][col]) {
                    allKeys |= 1 << (grid[row][col] - 'a'); // maxKey can not be started from zero;
                }
            }
        }

        if (-1 == startRow || -1 == startCol) {
            return -1;
        }

        std::set<std::tuple<int, int, int>> visited;
        std::queue<std::tuple<int, int, int>> todo;
        std::tuple<int, int, int> startTuple(0, startRow, startCol);
        todo.emplace(startTuple);
        visited.emplace(startTuple);
        int step = 0;
        do {
            step++;
            // std::cout << "\n";
            for (int layerSize = todo.size(); layerSize > 0; layerSize--) {
                auto const & cur = todo.front();
                int keys = std::get<0>(cur);
                int curRow = std::get<1>(cur);
                int curCol = std::get<2>(cur);
                todo.pop();
                // std::cout << "\ncur: " << curRow << "\t" << curCol << "\t";
                for (int index = 0; index < DIRECTION_SIZE; index++) {
                    int nextRow = curRow + directions[index];
                    int nextCol = curCol + directions[index + 1];
                    int nextKeys = keys;
                    if (nextRow >= 0 && nextRow < rowSize &&
                            nextCol >= 0 && nextCol < grid[nextRow].size()) {
                        if ('#' == grid[nextRow][nextCol]) {
                            continue;
                        } else if ('A' <= grid[nextRow][nextCol] && 'F' >= grid[nextRow][nextCol]) {
                            // need first find the key
                            if (0 == (nextKeys & (1 << (grid[nextRow][nextCol] - 'A')))) {
                                // have not find the key
                                continue;
                            }
                        } else if ('a' <= grid[nextRow][nextCol] && 'f' >= grid[nextRow][nextCol]) {
                            nextKeys |= (1 << (grid[nextRow][nextCol] - 'a'));
                            if (allKeys == nextKeys) {
                                return step;
                            }
                        }
                        std::tuple<int, int, int> next(nextKeys, nextRow, nextCol);
                        if (visited.find(next) == visited.end()) {
                            // std::cout << "next: " << nextRow << "\t" << nextCol << "\t";
                            todo.emplace(next);
                            visited.emplace(next);
                        }
                    }
                }
            }
        } while (todo.size());
        return -1;
    }
private:
    static int const DIRECTION_ARRAY_SIZE = 5;
    static int const DIRECTION_SIZE = DIRECTION_ARRAY_SIZE - 1;
    static std::array<int, DIRECTION_ARRAY_SIZE> directions;
};
std::array<int, Solution::DIRECTION_ARRAY_SIZE> Solution::directions = {0, 1, 0, -1, 0};

class Solution {
public:
    const int d[5] = {0,1,0,-1,0};
    int visited[32][32][70];
    int shortestPathAllKeys(std::vector<std::string> const & grid) {
        memset(visited, 0, sizeof visited);
        int m = grid.size(), n = grid[0].size();
        std::queue<int> queue;
        int keys = 0;
        for(int r = 0; r < m ; r++){
            for(int c = 0; c <n ; c++){
                if(grid[r][c] == '@'){
                    queue.push((r << 16) | (c << 8));
                    visited[r][c][0] = 1;
                }else if (grid[r][c] >= 'a' && grid[r][c] <= 'f'){
                    keys |= (1 << (grid[r][c] - 'a'));
                }
            }
        }
        int dist = 0;
        while(!queue.empty()){
            auto sz = queue.size();
            while(sz--){
                int curr = queue.front(); queue.pop();
                int r = curr >> 16, c = (curr >> 8) & 0xFF, k = curr & 0xFF;
                if (k == keys) return dist;
                for(int i = 0; i < 4; i++){
                    int nr = r + d[i], nc = c + d[i + 1], nkeys = k;
                    if(nr < 0 || nr == m || nc < 0 || nc == n)continue;
                    char loc = grid[nr][nc];
                    if (loc == '#') continue;
                    if (loc >= 'A' && loc <= 'F' && !(k & (1 << (loc - 'A')))) continue;
                    if (loc >= 'a' && loc <= 'f') nkeys |= (1 << (loc - 'a'));
                    if (visited[nr][nc][nkeys]) continue;
                    queue.push((nr << 16) | (nc << 8) | nkeys);
                    visited[nr][nc][nkeys] = 1;
                }
            }
            dist++;
        }
        return -1;
    }
};
