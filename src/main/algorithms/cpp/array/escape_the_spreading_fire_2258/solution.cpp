#include "../../head.h"


// #define DEBUG
// #define DEBUG_DIE
// #define MEM_NO_LIMIT
class SolutionBS {
public:
    int maximumMinutes(std::vector<std::vector<int>> grid) {
        // plagiarizing from https://leetcode.com/problems/escape-the-spreading-fire/discuss/1995289/Python-BFS-Solution
        /*
            Core idea:
                        first, compute the time of each cell be fired.
                        Second, after update the path, find a way from left-up corner to right-buttom corner.
        */
        if (grid.empty() || grid[0].empty()) {
            return MAX_VAL;
        }
        int rowSize= grid.size(), colSize = grid[0].size();

        std::queue<std::tuple<int, int, int>> bfsQue;
        for (int row = 0; row < rowSize; row++) {
            for (int col = 0; col < colSize; col++) {
                switch(grid[row][col]) {
                    case WALL: {
                        // the cell is wall
                        grid[row][col] = REDEFINE_WALL; // which means we can never reach it.
                    };
                    break;
                    case FIRE: {
                        bfsQue.emplace(std::make_tuple(row, col, 0));
                    };
                    case GRASS: {
                        grid[row][col] = MAX_VAL;
                    };
                    default:;break;
                }
            }
        }
        #ifdef DEBUG
        print2D(grid);
        #endif
        // after the upper loop, grid[i][j] == -1 means the cell (i, j) is a wall. Otherwise, it is a cell that Fire can spread.

        std::function<void(std::queue<std::tuple<int, int, int>> &, std::vector<std::vector<int>> &)> bfs = [&] (std::queue<std::tuple<int, int, int>> & bfsQue, std::vector<std::vector<int>> & seen) {
            while(!bfsQue.empty()) {
                auto const & node = bfsQue.front();
                int sRow = std::get<ROW_IDX>(node);
                int sCol = std::get<COL_IDX>(node);
                int sStep = std::get<STEP_IDX>(node);
                bfsQue.pop();
                if (seen[sRow][sCol] < MAX_VAL) {
                    continue;
                }
                seen[sRow][sCol] = sStep;
                for (int dIdx = 0; dIdx < DIRECTION_SIZE; dIdx++) {
                    int nextRow = sRow + directions[dIdx];
                    int nextCol = sCol + directions[dIdx + 1];
                    if (nextRow < rowSize && nextRow >= 0 && // not beyond the boundary of the rows
                        nextCol < colSize && nextCol >= 0 && // not beyond the boundary of the cols
                        sStep + 1 < grid[nextRow][nextCol] // we can use more less step to reach grid[row][col].
                        // grid[row][col] = -1 which will never larger than sStep which starts from 0;
                    ) {
                        bfsQue.emplace(std::make_tuple(nextRow, nextCol, sStep + 1));
                    }
                }
            }
        };
        bfs(bfsQue, grid);
        #ifdef DEBUG
        print2D(grid);
        #endif
        grid.back().back() += 1; // if no this operation, we can not judge == condition.

        #ifdef MEM_NO_LIMIT
        std::vector<int> rangeVal(MAX_ANS + 1);
        std::iota(std::begin(rangeVal), std::end(rangeVal), 0);
        #ifdef DEBUG_RV
        for (int val : rangeVal) {
            std::cout << val << ", ";
        }
        std::cout << "\n";
        #endif
        #endif

        std::function<bool(bool, int)> die = [&] (bool target, int val) -> bool {
            std::vector<std::vector<int>> seen(rowSize, std::vector<int>(colSize, MAX_VAL + 10)); // the initial value must larger than grid init value to know whether we can find a way from start to end
            std::queue<std::tuple<int, int, int>> start;
            start.emplace(std::make_tuple(0, 0, val));
            bfs(start, seen);
            #ifdef DEBUG
            std::cout << "val: " << val << "\n";
                #ifdef DEBUG_DIE
                if (val >= MAX_VAL) {
                    print2D(seen);
                }
                #endif
            #endif
            return seen.back().back() > grid.back().back();
        };
        #ifdef MEM_NO_LIMIT
        return std::upper_bound(std::begin(rangeVal), std::end(rangeVal), true, die) - std::begin(rangeVal) - 1;
        #else
        int left = 0, right = MAX_ANS + 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (die(true, mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        #ifdef DEBUG
        std::cout << "ans: " << left << "\n";
        #endif
        return left - 1;
        
        #endif
    }
    #ifdef DEBUG
private:
    void print2D(std::vector<std::vector<int>> const & grid) {
        for (int row = 0; row < grid.size(); row++) {
            for (int col = 0; col < grid[row].size(); col++) {
                std::cout << grid[row][col] << ", ";
            }
            std::cout << "\n";
        }
    }
    #endif
private:
    int const MAX_VAL = 2 * 1e9;
    static int const MAX_ANS = 1e9;
    static int const ROW_IDX = 0;
    static int const COL_IDX = 1;
    static int const STEP_IDX = 2;
    static int const WALL = 2;
    static int const FIRE = 1;
    static int const GRASS = 0;
    static int const REDEFINE_WALL = -1;

    static int const DIRECTION_SIZE = 4;
    static std::array<int, DIRECTION_SIZE + 1> directions;
};
std::array<int, SolutionBS::DIRECTION_SIZE + 1> SolutionBS::directions = {{1, 0, -1, 0, 1}};


// #define DEBUG
class Solution {
public:
    int maximumMinutes(std::vector<std::vector<int>> const & grid) {
        // plagiarizing from https://leetcode.com/problems/escape-the-spreading-fire/discuss/2016835/No-BS
        if (grid.empty() || grid[0].empty()) {
            return MAX_ANS;
        }
        int rowSize = grid.size(), colSize = grid[0].size();
        std::queue<std::pair<int, int>> fires, persons({{0, 0}});
        for (int row = 0; row < grid.size(); row++) {
            for (int col = 0; col < grid[row].size(); col++) {
                if (FIRE == grid[row][col]) {
                    fires.emplace(std::make_pair(row, col)); // find all the fire points.
                }
            }
        }
        // std::function<std::array<int, RETURN_VAL_LEN>(std::queue<std::pair<int, int>> & bfsQue)> bfsComplete =
        // [&](std::queue<std::pair<int, int>> & bfsQue) -> std::array<int, RETURN_VAL_LEN> {
        //     return std::array<int, RETURN_VAL_LEN>{0, 0, 0};
        // };
        auto bfs = [&](std::queue<std::pair<int, int>> & bfsQue) {
            std::vector<std::vector<int>> remarkSteps(rowSize, std::vector<int>(colSize, INIT_STEP));
            while (!bfsQue.empty()) {
                auto [curRow, curCol] = bfsQue.front(); bfsQue.pop();
                // we can not add one here, because we initialize the initial value as zero which is alread add one at first time.
                // if we initialize the INIT_STEP as -1, then we need add one here.
                for (int dIdx = 0; dIdx < DIRECTION_SIZE; dIdx++) {
                    int nextRow = curRow + directions[dIdx];
                    int nextCol = curCol + directions[dIdx + 1];
                    if (std::min(nextRow, nextCol) >= 0 && nextRow < rowSize && nextCol < colSize &&
                        grid[nextRow][nextCol] == GRASS && INIT_STEP == remarkSteps[nextRow][nextCol] /* the pos has never been visited, bfs, shortest path*/
                    ) {
                        remarkSteps[nextRow][nextCol] = remarkSteps[curRow][curCol] + 1;
                        bfsQue.emplace(std::make_pair(nextRow, nextCol));
                    }
                }
            }
            std::vector<int> ans;
            ans.emplace_back(remarkSteps[rowSize - 1][colSize - 1]);
            if (rowSize > 1) {
                ans.emplace_back(remarkSteps[rowSize - 1][colSize - 2]);
            } else {
                return ans;
            }
            if (colSize > 1) {
                ans.emplace_back(remarkSteps[rowSize - 2][colSize - 1]);
            }
            return ans;
        };
        auto fireAns = bfs(fires), pAns = bfs(persons);
        #ifdef DEBUG
        for (int posNum: fireAns) {
            std::cout << posNum << ", ";
        }
        std::cout << "\n pAns:\n";
        for (int posNum : pAns) {
            std::cout << posNum << ", ";
        }
        std::cout << "\n";
        #endif
        if (RETURN_VAL_LEN > fireAns.size() || RETURN_VAL_LEN > pAns.size()) {
            // it means there is a 1*1 grid
            return grid.back().back() == GRASS ? MAX_ANS : NEVER_REACH;
        }
        if (fireAns[0] == INIT_STEP /*fire can not reach the safehouse*/ && pAns[0] > INIT_STEP /* person can reach to the firHouse*/) {
            return MAX_ANS;
        }
        if (int diff = fireAns[0] - pAns[0]; pAns[0] > 0 /*person can reach safehouse*/ && diff >= 0) {
            return diff - (fireAns[LEFT_IDX] - pAns[LEFT_IDX] <= diff && fireAns[UPPER_IDX] - pAns[UPPER_IDX] <= diff);
        }
        return NEVER_REACH;



    }
private:
    int const INIT_STEP = 0;
    static int const NEVER_REACH = -1;
    static int const MAX_ANS = 1e9;
    static int const FIRE = 1;
    static int const GRASS = 0;
    static int const RETURN_VAL_LEN = 3;
    static int const LEFT_IDX = 1;
    static int const UPPER_IDX = 2;

    static int const DIRECTION_SIZE = 4;
    static std::array<int, DIRECTION_SIZE + 1> directions;
};
std::array<int, Solution::DIRECTION_SIZE + 1> Solution::directions = {{1, 0, -1, 0, 1}};