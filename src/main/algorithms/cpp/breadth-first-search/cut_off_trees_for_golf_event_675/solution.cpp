#include "../../head.h"


class SolutionWrongAnswer {
public:
    int cutOffTree(std::vector<std::vector<int>> const & forest) {
        int rowSize = forest.size();
        if (0 == rowSize) {
            return 0;
        }
        int colSize = forest[0].size();
        if (0 == colSize) {
            return 0;
        }
        std::vector<std::vector<bool>> visited(rowSize, std::vector<bool>(colSize, false));
        std::queue<std::pair<int, int>> todo;
        todo.emplace(std::make_pair(0, 0));
        visited[0][0] = true;
        int res = -1;
        while (todo.size()) {
            auto const & curPair = todo.front();
            int row = curPair.first;
            int col = curPair.second;
            todo.pop();
            res++;
            // std::cout << "\nvisited: " << row << "\t" << col << "\t";
            for (int index = 0; index < DIRECTION_SIZE; index++) {
                int nextRow = row + directions[index];
                int nextCol = col + directions[index + 1];
                if (nextRow >= 0 && nextRow < rowSize &&
                        nextCol >= 0 && nextCol < colSize &&
                        0 != forest[nextRow][nextCol] && false == visited[nextRow][nextCol]) {
                    visited[nextRow][nextCol] = true;
                    todo.emplace(std::make_pair(nextRow, nextCol));
                }
            }
        }
        bool complete = true;
        for (int row = 0; row < visited.size(); row++) {
            for (int col = 0; col < visited[row].size(); col++) {
                if (0 != forest[row][col]) {
                    complete &= visited[row][col];
                }

            }
        }
        return complete ? res : -1;
    }
private:
    static int const DIRECTION_ARRAY_SIZE = 5;
    static int const DIRECTION_SIZE = DIRECTION_ARRAY_SIZE - 1;
    static std::array<int, DIRECTION_ARRAY_SIZE> directions;
};
std::array<int, SolutionWrongAnswer::DIRECTION_ARRAY_SIZE> SolutionWrongAnswer::directions = {0, 1, 0, -1, 0};


class SolutionTLE {
public:
    int cutOffTree(std::vector<std::vector<int>> const & forest) {
        // plagiarizing from https://leetcode.com/problems/cut-off-trees-for-golf-event/discuss/107404/Java-solution-PriorityQueue-%2B-BFS
        int rowSize = forest.size();
        if (0 == rowSize) {
            return 0;
        }
        int colSize = forest[0].size();
        if (0 == colSize) {
            return 0;
        }
        std::priority_queue<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>, Cmp> allToDo;
        for (int row = 0; row < rowSize; row++) {
            for (int col = 0; col < colSize; col++) {
                if (1 < forest[row][col]) {
                    allToDo.emplace(std::tuple(forest[row][col], row, col));
                }
            }
        }
        int sum = 0;
        int startRow = 0, startCol = 0;
        while (allToDo.size()) {
            auto const & cur = allToDo.top();
            int endRow = std::get<1>(cur);
            int endCol = std::get<2>(cur);
            // std::cout << "\ncut tree: " << std::get<0>(cur) <<"\t" << endRow << '\t' << endCol << '\t';
            allToDo.pop();
            int curStep = minBFSStep(forest, startRow, startCol, endRow, endCol);
            if (0 > curStep) {
                return curStep;
            }
            sum += curStep;
            startRow = endRow;
            startCol = endCol;
        }
        return sum;
    }
private:
    int minBFSStep(std::vector<std::vector<int>> const & forest,
            int startRow, int startCol, int endRow, int endCol) {
        int rowSize = forest.size();
        int colSize = forest[0].size();
        std::vector<std::vector<bool>> visited(rowSize, std::vector<bool>(colSize, false));
        std::queue<std::pair<int, int>> todo;
        todo.emplace(std::make_pair(startRow, startCol));
        visited[startRow][startCol] = true;
        int res = -1;
        while (todo.size()) {
            int curSize = todo.size();
            res++;
            for (int index = 0; index < curSize; index++) {
                auto const & curPair = todo.front();
                int row = curPair.first;
                int col = curPair.second;
                todo.pop();
                if (row == endRow && col == endCol) {
                    return res;
                }
                for (int index = 0; index < DIRECTION_SIZE; index++) {
                    int nextRow = row + directions[index];
                    int nextCol = col + directions[index + 1];
                    if (nextRow >= 0 && nextRow < rowSize &&
                            nextCol >= 0 && nextCol < colSize &&
                            0 != forest[nextRow][nextCol] && false == visited[nextRow][nextCol]) {
                        visited[nextRow][nextCol] = true;
                        todo.emplace(std::make_pair(nextRow, nextCol));
                    }
                }
            }
        }
        return -1;
    }
    class Cmp {
    public:
        // tuple[0] means the weight (height of the tree)
        bool operator()(std::tuple<int, int, int> const & lhs, std::tuple<int, int, int> const & rhs) {
            return std::get<0>(lhs) > std::get<0>(rhs);
        }
    };

private:
    static int const DIRECTION_ARRAY_SIZE = 5;
    static int const DIRECTION_SIZE = DIRECTION_ARRAY_SIZE - 1;
    static std::array<int, DIRECTION_ARRAY_SIZE> directions;
};
std::array<int, Solution::DIRECTION_ARRAY_SIZE> Solution::directions = {0, 1, 0, -1, 0};
