#include "../../head.h"


class Solution {
public:
    int const COLSIZE = 1e6;
    int const ROWSIZE = 1e6;
    bool isEscapePossible(std::vector<std::vector<int>> const & blocked,
            std::vector<int> const & source, std::vector<int> const & target) {
        std::set<long long int> b;
        for (auto const & p : blocked) {
            if (2 != p.size()) {
                return false;
            }
            b.emplace(mark(p[0], p[1], COLSIZE));
        }
        if (b.empty()) {
            return true;
        }

        if (2 != source.size() || 2 != target.size()) {
            return false;
        }
        std::set<long long int> visited;
        std::queue<std::pair<int, int>> todo;
        todo.emplace(std::make_pair(source[0], source[1]));
        visited.emplace(mark(source[0], source[1], COLSIZE));
        int res = 0;
        while (todo.size()) {
            auto const & curPair = todo.front();
            int row = curPair.first;
            int col = curPair.second;
            todo.pop();
            res++;
            for (int index = 0; index < DIRECTION_SIZE; index++) {
                int nextRow = row + directions[index];
                int nextCol = col + directions[index + 1];
                if (nextRow == target[0] && nextRow == target[1]) {
                    return true;
                }
                long long int next = mark(nextRow, nextCol, COLSIZE);
                if (nextRow >= 0 && nextRow < ROWSIZE &&
                        nextCol >= 0 && nextCol < COLSIZE &&
                        b.find(next) == b.end() && visited.end() == visited.find(next)) {
                    visited.emplace(next);
                    todo.emplace(std::make_pair(nextRow, nextCol));
                }
            }
        }
        return false;
    }
private:
    long long int mark(int row, int col, int colSize) {
        return row * static_cast<long long int>(colSize) + col;
    }
    void deMark(long long int num, int & row, int & col, int colSize) {
        row = num / colSize;
        col = num % colSize;
    }

private:
    static int const DIRECTION_ARRAY_SIZE = 5;
    static int const DIRECTION_SIZE = DIRECTION_ARRAY_SIZE - 1;
    static std::array<int, DIRECTION_ARRAY_SIZE> directions;
};
std::array<int, Solution::DIRECTION_ARRAY_SIZE> Solution::directions = {0, 1, 0, -1, 0};
