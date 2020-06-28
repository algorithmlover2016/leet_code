#include "../../head.h"


class SolutionTLE {
public:
    void solve(std::vector<std::vector<char>> & board) {
        int rowSize = board.size();
        if (0 == rowSize) {
            return ;
        }
        int colSize = board[0].size();
        if (0 == colSize) {
            return ;
        }

        int totalIndex = rowSize * colSize + 1;
        std::vector<int> parentIndex(totalIndex, 0);
        for (int index = 0; index < parentIndex.size(); index++) {
            parentIndex[index] = index;
        }

        std::vector<int> cnt(totalIndex, 1);
        for (int row = 0; row < rowSize; row++) {
            for (int col = 0; col < colSize; col++) {
                if ('O' == board[row][col]) {
                    unionAround(board, row, col, parentIndex, cnt);
                }
            }
        }
        int ORoot = findRoot(parentIndex, 0);

        for (int row = 0; row < rowSize; row++) {
            for (int col = 0; col < colSize; col++) {
                int p = findRoot(parentIndex, mark(colSize, row, col));
                // std::cout << "\nrow, col\t" << row << "\t" << col << "\t" << p << "\t";
                if ('O' == board[row][col] && ORoot != p) {
                    board[row][col] = 'X';
                }
            }
        }
    }
private:

    void unionAround(std::vector<std::vector<char>> const & board, int row, int col,
            std::vector<int>  & parentIndex, std::vector<int> & cnt) {
        int mapIndex = mark(board[row].size(), row, col);
        // std::cout << "\nmapIndex: " << row << "\t" << col << "\t" << mapIndex << "\t";
        for (int index = 0; index < DIRECTION_SIZE; index++) {
            int nextRow = row + directions[index];
            int nextCol = col + directions[index + 1];
            if (nextRow >= 0 && nextRow < board.size() &&
                    nextCol >= 0 && nextCol < board[row].size() &&
                    'O' == board[nextRow][nextCol]) {
                // std::cout << "union: " << nextRow << "\t" << nextCol << "\t";
                unionAndCnt(parentIndex, cnt, mapIndex, mark(board[nextRow].size(), nextRow, nextCol));
            }
        }
        if (0 == row || row == board.size() - 1 ||
                0 == col || col == board[row].size() - 1) {
            unionAndCnt(parentIndex, cnt, 0, mapIndex);
        }
        // std::cout << "parent: " << findRoot(parentIndex, mapIndex) << "\t";
    }


    int mark(int colSize, int row, int col) {
        return row * colSize + col + 1;
    }

    int findRoot(std::vector<int> const & parentIndex, int index) {
        while (index != parentIndex[index]) {
            index = parentIndex[index];
        }
        return index;
    }

    int unionAndCnt(std::vector<int> & parentIndex, std::vector<int> & cnt, int left, int right) {
        int leftRoot = findRoot(parentIndex, left);
        int rightRoot = findRoot(parentIndex, right);
        // std::cout << "root: " << right << "\tleftRoot, rightRoot: " << leftRoot << "\t" << rightRoot << "\t";
        if (leftRoot == rightRoot) {
            return cnt[leftRoot];
        }

        int count = cnt[leftRoot] + cnt[rightRoot];
        parentIndex[leftRoot] = rightRoot;
        cnt[rightRoot] = count;
        return count;
    }

private:
    static int const DIRECTION_ARRAY_SIZE = 3;
    // static int const DIRECTION_ARRAY_SIZE = 5;
    static int const DIRECTION_SIZE = DIRECTION_ARRAY_SIZE - 1;
    static std::array<int, DIRECTION_ARRAY_SIZE> const directions;
};
std::array<int, Solution::DIRECTION_ARRAY_SIZE> const Solution::directions = {0, 1, 0};
// std::array<int, Solution::DIRECTION_ARRAY_SIZE> const Solution::directions = {0, 1, 0, -1, 0};

class Solution {
public:
	void solve(std::vector<std::vector<char>> & board) {
        // plagiarizing from https://leetcode.com/problems/surrounded-regions/discuss/41612/A-really-simple-and-readable-C%2B%2B-solutionuff0conly-cost-12ms
        int i,j;
        int row = board.size();
        if (!row) {
        	return;
        }
        int col = board[0].size();

		for (i = 0; i < row; i++) {
			check(board, i, 0, row, col);
			if (col > 1) {
				check(board, i, col - 1, row, col);
            }
		}
		for (j = 1; j + 1 < col; j++) {
			check(board, 0, j, row, col);
			if (row > 1) {
				check(board, row - 1, j, row, col);
            }
		}
		for (i = 0; i < row; i++) {
			for (j = 0; j < col; j++) {
				if (board[i][j] == 'O') {
					board[i][j] = 'X';
                } else if(board[i][j]=='1') {
					board[i][j]='O';
                }
            }
        }
    }

	void check(std::vector<std::vector<char> >&vec, int i, int j, int row, int col) {
		if (vec[i][j] == 'O') {
			vec[i][j] = '1';
			if (i>1) {
				check(vec, i-1, j, row, col);
            }
			if (j > 1) {
				check(vec, i, j - 1, row, col);
            }
			if (i + 1 < row) {
				check(vec, i + 1, j, row, col);
            }
			if (j + 1 < col) {
				check(vec, i, j + 1, row, col);
            }
		}
	}
};
