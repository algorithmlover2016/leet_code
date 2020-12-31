#include "../../head.h"


// #define DEBUG
class SolutionWrongAnswer {
public:
    int maxStudents(std::vector<std::vector<char>> const & seats) {
        if (seats.empty() || seats[0].empty()) {
            return 0;
        }
        int const seatsRowSize = seats.size();
        int const seatsColSize = seats[0].size();

        std::vector<std::vector<std::vector<int>>> dpMemo(seatsRowSize + 1,
                            std::vector<std::vector<int>>(seatsColSize + 2,
                            std::vector<int>(2, 0)));

        for (int row = 1; row < dpMemo.size();row++) {
            for (int col = 1; col < dpMemo[row].size() - 1; col++) {
                dpMemo[row][col][NO_SIT] = std::max(
                        std::max(dpMemo[row][col - 1][SIT], dpMemo[row][col - 1][NO_SIT]),
                        std::max(
                            std::max(dpMemo[row- 1][col - 1][SIT], dpMemo[row- 1][col - 1][NO_SIT]),
                            std::max(dpMemo[row - 1][col + 1][SIT], dpMemo[row - 1][col + 1][NO_SIT])
                        )
                );
                if (NOTE == seats[row - 1][col - 1]) {
                    dpMemo[row][col][SIT] = std::max(dpMemo[row][col - 1][NO_SIT],
                                            std::max(dpMemo[row - 1][col - 1][NO_SIT],
                                            dpMemo[row - 1][col + 1][NO_SIT])) + 1;

                } else {
                    dpMemo[row][col][SIT] = dpMemo[row][col][NO_SIT];
                }
                #ifdef DEBUG
                std::cout << "row, col: " << row << "\t" << col << "\tSIT: " << dpMemo[row][col][SIT]
                    << "\tNO_SIT: " << dpMemo[row][col][NO_SIT] << "\n";
                #endif
            }
        }
        return std::max(dpMemo[seatsRowSize][seatsColSize][SIT], dpMemo[seatsRowSize][seatsColSize][NO_SIT]);

    }
private:
    static char const NOTE = '.';
    static int const SIT = 0;
    static int const NO_SIT = 1;

};

class Solution {
public:
    int maxStudents(std::vector<std::vector<char>> const & seats) {
        // plagiarizing idea from https://leetcode.com/problems/maximum-students-taking-exam/discuss/503686/A-simple-tutorial-on-this-bitmasking-problem
        if (seats.empty() || seats[0].empty()) {
            return 0;
        }
        int const seatsRowSize = seats.size();
        int const seatsColSize = seats[0].size();
        int const maskTotalState = 1 << seatsColSize;

        std::vector<int> validState(seatsRowSize + 1, 0); // initialize the validState[0] = 0;
        for (int row = 1; row < validState.size(); row++) {
            for (int col = 0; col < seatsColSize; col++) {
                // record each row
                validState[row] =(validState[row] << 1) + (NOTE == seats[row - 1][col] ? 1 : 0);
            }
        }
        std::vector<std::vector<int>> dpMemo(seatsRowSize + 1,
                            std::vector<int>(maskTotalState, INT_MIN));

        dpMemo[0] = std::vector<int>(maskTotalState, 0);
        for (int row = 1; row < dpMemo.size(); row++) {
            for (int curRowState = 0; curRowState <= validState[row]; curRowState++) {
                if (((curRowState & validState[row]) == curRowState) && // we can using curRowState to sit students
                        !(curRowState & (curRowState >> 1))) { // the curRowState has no adjacent neighbours
                    for (int preRowState = 0; preRowState <= validState[row - 1]; preRowState++) {
                        if (!(curRowState & (preRowState >> 1)) && // have no upLeft adjacent
                                !((curRowState >> 1) & preRowState) &&
                            dpMemo[row - 1][preRowState] != INT_MIN) { // have no upRight adjacent neighbours
                            dpMemo[row][curRowState] = std::max(dpMemo[row][curRowState],
                                    dpMemo[row - 1][preRowState] + __builtin_popcount(curRowState));
                        }
                    }
                }
            }
        }
        return *std::max_element(dpMemo[seatsRowSize].begin(), dpMemo[seatsRowSize].end());


    }
private:
    static char const NOTE = '.';
};


class SolutionRecursive {
public:
    int maxStudents(std::vector<std::vector<char>> const & seats) {
        // plagiarizing from https://leetcode.com/problems/maximum-students-taking-exam/discuss/503491/JAVA-Top-Down-DP-Solution
        if (seats.empty() || seats[0].empty()) {
            return 0;
        }

        int const seatsRowSize = seats.size();
        int const seatsColSize = seats[0].size();
        int const maskTotalStates = 1 << seatsColSize;

        std::vector<std::vector<int>> dpMemo(seatsRowSize + 1,
                            std::vector<int>(maskTotalStates, INT_MIN));

        return dpHelp(seats, dpMemo, 0, 0);
    }
private:
    int dpHelp(std::vector<std::vector<char>> const & seats,
               std::vector<std::vector<int>> & dpMemo,
               int curRow,
               int preRowState) {
        if (curRow == seats.size()) {
            return 0;
        }

        if (INT_MIN != dpMemo[curRow][preRowState]) {
            return dpMemo[curRow][preRowState];
        }

        std::vector<int> maskStates;
        backTrackingColumn(maskStates, seats[curRow], 0, 0, preRowState);

        int ans = INT_MIN;
        for (auto const maskState : maskStates) {
            ans = std::max(ans, __builtin_popcount(maskState) + dpHelp(seats, dpMemo, curRow + 1, maskState));

        }
        return dpMemo[curRow][preRowState] = ans;
    }

    void backTrackingColumn(std::vector<int> & maskStates,
                            std::vector<char> const & seatRow,
                            int curCol,
                            int curRowState,
                            int preRowState) {
        if (curCol == seatRow.size()) {
            maskStates.emplace_back(curRowState);
            return;
        }
        // if we don't sit a student at curCol position
        backTrackingColumn(maskStates, seatRow, curCol + 1, curRowState, preRowState);

        // if sitting a student at curCol Position
        if ((NOTE == seatRow[curCol]) &&
            (curCol == 0 || ((curRowState & (1 << (curCol - 1))) == 0 && (preRowState & (1 << (curCol - 1))) == 0)) &&
            (curCol == seatRow.size() - 1 || (preRowState & (1 << (curCol + 1))) == 0)){
            backTrackingColumn(maskStates, seatRow, curCol + 1, curRowState | (1 << curCol), preRowState);
        }
    }
    private:
    static char const NOTE = '.';
};
