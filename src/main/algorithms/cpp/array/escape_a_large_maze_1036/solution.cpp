#include "../../head.h"


// #define DEBUG
#define OPTIMIZE_TIME_FOR_NOT_TLE
class SolutionWrongTLE {
public:
    bool isEscapePossible(std::vector<std::vector<int>> const & blocked,
            std::vector<int> const & source,
            std::vector<int> const & target) {
        if (blocked.empty()) {
            return true;
        }
        if (POS_IDX_LEN != source.size() || POS_IDX_LEN != target.size()) {
            return false;
        }

        #ifndef OPTIMIZE_TIME_FOR_NOT_TLE
        std::set<std::tuple<int, int>> blockedSet;
        #else
        std::set<long long int> blockedSet;
        #endif
        for (auto const & block : blocked) {
            if (POS_IDX_LEN > block.size()) {
                continue;
            }
            #ifndef  OPTIMIZE_TIME_FOR_NOT_TLE
            blockedSet.insert(std::make_tuple(block[X_IDX], block[Y_IDX]));
            #else
            blockedSet.insert(encodeIdx(block[X_IDX], block[Y_IDX]));
            #endif
        }

        std::queue<std::vector<int>> bfsQue;
        bfsQue.push({source[X_IDX], source[Y_IDX]});

        #ifndef OPTIMIZE_TIME_FOR_NOT_TLE
        std::tuple<int, int> sourceTuple(source[X_IDX], source[Y_IDX]);
        std::set<std::tuple<int, int>> seen;
        seen.insert(sourceTuple);
        #else
        std::set<long long int> seen;
        seen.insert(encodeIdx(source[X_IDX], source[Y_IDX]));
        #endif

        // bfsQue.emplace(r0, c0);
        while (!bfsQue.empty()) {
            auto & pos = bfsQue.front();
            if (POS_IDX_LEN > pos.size()) {
                continue;
            }
            int row = pos[X_IDX], col = pos[Y_IDX];
            bfsQue.pop();

            for (int idx = 0; idx < DIRECTIONS_SIZE; idx++) {
                int nextRow = row + directions[idx];
                int nextCol = col + directions[idx + 1];

                #ifndef OPTIMIZE_TIME_FOR_NOT_TLE
                std::tuple<int, int> nextTuple(nextRow, nextCol);
                #else
                int pos = encodeIdx(nextRow, nextCol);
                #endif
                if (nextRow > MIN_IDX && nextRow < MAX_IDX &&
                    nextCol > MIN_IDX && nextCol < MAX_IDX &&
                    #ifndef OPTIMIZE_TIME_FOR_NOT_TLE
                    blockedSet.find(nextTuple) == blockedSet.end() &&
                    seen.find(nextTuple) == seen.end()
                    #else
                    blockedSet.find(pos) == blockedSet.end() &&
                    seen.find(pos) == seen.end()
                    #endif
                    ) {

                    if (nextRow == target[X_IDX] && nextCol == target[Y_IDX]) {
                        return true;
                    }
                    bfsQue.push({nextRow, nextCol});

                        #ifndef OPTIMIZE_TIME_FOR_NOT_TLE
                        seen.insert(nextTuple);
                        #else
                        seen.insert(pos);
                        #endif
                    }
                }
                #ifdef DEBUG
                int bfsQueSize = bfsQue.size();
                if (MAX_BLOCK_AREA <= bfsQueSize) {
                    std::cout << bfsQueSize << "\t";
                }
                #endif
                if (bfsQue.size() > MAX_BLOCK_AREA) {
                    return true;
                }
            }
            return false;
        }
#ifdef OPTIMIZE_TIME_FOR_NOT_TLE
private:
    long long int encodeIdx(long long int row, int col, int const ROWSIZE = MAX_IDX) {
        return static_cast<long long int>(row * ROWSIZE + col);
    }
    bool decodeIdx(long long int pos, int & row, int & col, int const ROWSIZE = MAX_IDX) {
        row = pos / ROWSIZE;
        col = pos % ROWSIZE;
        return true;
    }
#endif

private:
    static int const DIRECTIONS_ARRAY_SIZE = 5;
    static int const DIRECTIONS_SIZE = 4;
    static std::array<int, DIRECTIONS_ARRAY_SIZE> directions;
    static int const X_IDX = 0;
    static int const Y_IDX = 1;
    static int const POS_IDX_LEN = 2;
    static int const MIN_IDX = -1;
    static int const MAX_IDX = 1e6 + 1;
    static int const MAX_BLOCK_AREA = 20000; // 200 * 200 / 2;
};
std::array<int, Solution::DIRECTIONS_ARRAY_SIZE> Solution::directions{{0, 1, 0, -1, 0}};

class Solution {
public:
    bool isEscapePossible(std::vector<std::vector<int>> const & blocked,
            std::vector<int> const & source,
            std::vector<int> const & target) {
        if (blocked.empty()) {
            return true;
        }
        if (POS_IDX_LEN != source.size() || POS_IDX_LEN != target.size()) {
            return false;
        }

        std::set<long long int> blockedSet;
        for (auto const & block : blocked) {
            if (POS_IDX_LEN > block.size()) {
                continue;
            }
            blockedSet.insert(encode(block[X_IDX], block[Y_IDX]));
        }

        std::set<long long int> visited;
        return dfs(visited, blockedSet, source, target) && dfs(visited, blockedSet, target, source);
    }

private:
    bool bfs(std::set<long long int> visited,
            std::set<long long int> const & blockedSet,
            std::vector<int> const & source,
            std::vector<int> const & target) {
        std::vector<std::pair<int, int>> bfsIdx;
        bfsIdx.emplace_back(std::make_pair(source[X_IDX], source[Y_IDX]));
        while (!bfsIdx.empty()) {
            std::vector<std::pair<int, int>> bfsNextIdx;
            for (auto const & xyPos : bfsIdx) {
                for (int idx = 0; idx < DIRECTIONS_SIZE; idx++) {
                    int nextRow = xyPos.first + directions[idx];
                    int nextCol = xyPos.second + directions[idx + 1];

                    int pos = encode(nextRow, nextCol);
                    if (nextRow > MIN_IDX && nextRow < MAX_IDX &&
                            nextCol > MIN_IDX && nextCol < MAX_IDX &&
                            blockedSet.find(pos) == blockedSet.end() &&
                            visited.insert(pos).second) {
                        bfsNextIdx.emplace_back(std::make_pair(nextRow, nextCol));
                    }
                }
            }
            if (MAX_BLOCK_AREA > bfsNextIdx.size()) {
                return true;
            }
            std::swap(bfsIdx, bfsNextIdx);
        }
        return false;
    }

    long long int encode(int row, int col) {
        return ((static_cast<long long>(row)) << SHIFT_LEFT) + col;
    }

    bool decode(long long int pos, int & row, int & col) {
        row = static_cast<int>(pos >> SHIFT_LEFT) & (((long long)1 << SHIFT_LEFT) - 1);
        col = static_cast<int>(pos & ((1 << SHIFT_LEFT) - 1));
        return true;
    }

private:
    static int const DIRECTIONS_ARRAY_SIZE = 5;
    static int const DIRECTIONS_SIZE = 4;
    static std::array<int, DIRECTIONS_ARRAY_SIZE> directions;
    static int const X_IDX = 0;
    static int const Y_IDX = 1;
    static int const POS_IDX_LEN = 2;
    static int const MIN_IDX = -1;
    static int const MAX_IDX = 1e6 + 1;
    static int const MAX_BLOCK_AREA = 20000; // 200 * 200 / 2;
    static int const SHIFT_LEFT = 32;
};
std::array<int, Solution::DIRECTIONS_ARRAY_SIZE> Solution::directions{{0, 1, 0, -1, 0}};

// #define DEBUG
class Solution {
public:
    bool isEscapePossible(std::vector<std::vector<int>> const & blocked,
            std::vector<int> const & source,
            std::vector<int> const & target) {
        // plagiarizing from https://leetcode.com/problems/escape-a-large-maze/discuss/282860/C%2B%2B-Limited-BFS-28-ms
        // why tle, because the using of encode function
        // why wrong answer, becase the MAX_IDX < 10^6(can't be equal)
        if (blocked.empty()) {
            return true;
        }
        if (POS_IDX_LEN != source.size() || POS_IDX_LEN != target.size()) {
            return false;
        }

        /*
        std::set<long long int> blockedSet;
        for (auto const & block : blocked) {
            if (POS_IDX_LEN > block.size()) {
                continue;
            }
            blockedSet.insert(encode(block[X_IDX], block[Y_IDX]));
        }
        */
        std::set<long long int> visitedS;
        std::set<long long int> visitedT;
        for (auto block : blocked) {
            if (POS_IDX_LEN > block.size()) {
                continue;
            }
            if (std::abs(block[X_IDX] - source[X_IDX]) + std::abs(block[Y_IDX] - source[Y_IDX]) < MAX_DIS) {
                visitedS.insert(encode(block[X_IDX], block[Y_IDX]));
            }
            if (std::abs(block[X_IDX] - target[X_IDX]) + std::abs(block[Y_IDX] - target[Y_IDX]) < MAX_DIS) {
                visitedT.insert(encode(block[X_IDX], block[Y_IDX]));
            }
        }
        #ifdef DEBUG
        std::cout << "blockedSize: " << visitedS.size() << ",\t" << visitedT.size() << "\n";
        #endif

        return bfs(visitedS, source, target, visitedS.size()) &&
                bfs(visitedT, target, source, visitedT.size());
    }

private:
    bool bfs(std::set<long long int> visited,
             std::vector<int> const & source,
             std::vector<int> const & target,
             int const blockedSetSize) {
        std::vector<std::pair<int, int>> bfsIdx;
        bfsIdx.emplace_back(std::make_pair(source[X_IDX], source[Y_IDX]));
        visited.insert(((long long)source[X_IDX] << 32) + source[Y_IDX]);
        while (!bfsIdx.empty() && bfsIdx.size() <= blockedSetSize) {
            std::vector<std::pair<int, int>> bfsNextIdx;
            for (auto const & xyPos : bfsIdx) {
                for (int idx = 0; idx < DIRECTIONS_SIZE; idx++) {
                    int nextRow = xyPos.first + directions[idx];
                    int nextCol = xyPos.second + directions[idx + 1];

                    if (nextRow < MIN_IDX || nextRow > MAX_IDX ||
                        nextCol < MIN_IDX || nextCol > MAX_IDX) {
                        continue;
                    }
                    // int pos = encode(nextRow, nextCol);
                    if (nextRow == target[X_IDX] && nextCol == target[Y_IDX]) {
                        return true;
                    }
                    // int pos = ((long long)nextRow << 32) + nextCol;
                    if (visited.insert(((long long)nextRow << 32) + nextCol).second) {
                        #ifdef DEBUG
                        std::cout << nextRow << ",\t" << nextCol << ".\t";
                        #endif
                        bfsNextIdx.emplace_back(std::make_pair(nextRow, nextCol));
                    }
                }
            }
            #ifdef DEBUG
            std::cout << "\n";
            #endif
            std::swap(bfsIdx, bfsNextIdx);
        }
        return !bfsIdx.empty();
    }

    long long int encode(int row, int col) {
        return ((long long)row << SHIFT_LEFT) + col;
    }

    bool decode(long long int pos, int & row, int & col) {
        row = static_cast<int>(pos >> SHIFT_LEFT) & (((long long)1 << SHIFT_LEFT) - 1);
        col = static_cast<int>(pos & ((1 << SHIFT_LEFT) - 1));
        return true;
    }

    private:
    static int const DIRECTIONS_ARRAY_SIZE = 5;
    static int const DIRECTIONS_SIZE = 4;
    static std::array<int, DIRECTIONS_ARRAY_SIZE> directions;

    static int const MIN_IDX = 0;
    static int const MAX_IDX = 1e6 - 1;
    static int const X_IDX = 0;
    static int const Y_IDX = 1;
    static int const POS_IDX_LEN = 2;

    static int const SHIFT_LEFT = 32;
    static int const MAX_DIS = 400;
};
std::array<int, Solution::DIRECTIONS_ARRAY_SIZE> Solution::directions{{0, 1, 0, -1, 0}};
