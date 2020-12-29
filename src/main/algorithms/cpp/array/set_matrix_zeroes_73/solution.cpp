#include "../../head.h"


class Solution {
public:
    void setZeroes(std::vector<std::vector<int>> & matrix) {
        if (matrix.empty() || matrix[0].empty()) {
            return;
        }
        std::set<int> rows; // we can also use vector, which size will be equal to matrix.size()
        std::set<int> cols; // we can alse use vector, which size will be eqaal to matrix[0].size()
        for (int row = 0; row < matrix.size(); row++) {
            for (int col = 0; col < matrix[row].size(); col++) {
                if (RESET == matrix[row][col]) {
                    rows.emplace(row);
                    cols.emplace(col);
                }
            }
        }
        for (int const row : rows) {
            for (int col = 0; col < matrix[row].size(); col++) {
                matrix[row][col] = RESET;
            }
        }

        for (int const col : cols) {
            for (int row = 0; row < matrix.size(); row++) {
                matrix[row][col] = RESET;
            }
        }
    }
private:
    static int const RESET = 0;
};

class SolutionBetter {
public:
    void setZeroes(std::vector<std::vector<int>> & A) {
        // plagiarizing from the accept answers
        if (A.empty() || A[0].empty()) {
            return;
        }

        int const ARowSize = A.size();
        int const AColSize = A[0].size();

        // because we will use the first row and first col to record the answer,
        // so we should preprocess the first row and first col
        bool row0 = false;
        bool col0 = false;

        for (int row = 0; row < ARowSize; row++) {
            if (RESET == A[row][PREPROCESS_COL]) {
                col0 = true;
                break;
            }
        }

        for (int col = 0; col < AColSize; col++) {
            if (RESET == A[PREPROCESS_ROW][col]) {
                row0 = true;
                break;
            }
        }

        for (int row = PREPROCESS_ROW; row < ARowSize; row++) {
            for (int col = PREPROCESS_COL; col < AColSize; col++) {
                if (RESET == A[row][col]) {
                    A[row][PREPROCESS_COL] = A[PREPROCESS_ROW][col] = RESET;
                }
            }
        }


        for (int row = PREPROCESS_ROW + 1; row < ARowSize; row++) {
            if (RESET == A[row][PREPROCESS_COL]) {
                for (int col = PREPROCESS_COL + 1; col < AColSize; col++) {
                    A[row][col] = RESET;
                }
            }
        }

        for (int col = PREPROCESS_COL + 1; col < AColSize; col++) {
            if (RESET == A[PREPROCESS_ROW][col]) {
                for (int row = PREPROCESS_ROW; row < ARowSize; row++) {
                    A[row][col] = RESET;
                }
            }
        }
        if (row0) {
            for (int col = PREPROCESS_COL + 1; col < AColSize; col++) {
                A[PREPROCESS_ROW][col] = RESET;
            }
        }
        if (col0) {
            for (int row = PREPROCESS_ROW + 1; row < ARowSize; row++) {
                A[row][PREPROCESS_COL] = RESET;
            }
        }
    }
    private:
    static int const RESET = 0;
    static int const PREPROCESS_ROW = 0;
    static int const PREPROCESS_COL = 0;
};
