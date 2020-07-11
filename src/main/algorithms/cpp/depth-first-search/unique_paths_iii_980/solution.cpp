#include "../../head.h"


class Solution {
public:
    int uniquePathsIII(std::vector<std::vector<int>> grid) {
        // plagiarizing from https://www.youtube.com/watch?v=Dny7JhfvJ0o
        int const rowSize = grid.size();
        if (0 == rowSize) {
            return 0;
        }
        int const colSize = grid[0].size();
        if (0 == colSize) {
            return 0;
        }
        int startRow = 0, startCol = 0, emptyNode = 1;
        for (int row = 0; row < rowSize; row++) {
            for (int col = 0; col < colSize; col++) {
                if (0 == grid[row][col]) {
                    emptyNode++;
                } else if (1 == grid[row][col]) {
                    startRow = row;
                    startCol = col;
                }
            }
        }
        int res = 0;
        dfs(grid, startRow, startCol, endRow, endCol, emptyNode, res);
        return res;
    }
    void dfs(std::vector<std::vector<int>> & grid,
            int const startRow, int const startCol,
            int emptyNode, int & res) {
        if (!checkValid(grid, startRow, startCol)) {
            return ;
        }
        if (2 == grid[startRow][startCol]) {
            // if visited endRow and endCol, if emptyNode is not zero, there is no
            // need to traversal the others empty nodes
            if (0 == emptyNode) {
                res++;
            }
            return ;
        }
        grid[startRow][startCol] = -2; // empty node but has been visited
        emptyNode--;
        dfs(grid, startRow + 1, startCol, emptyNode, res);
        dfs(grid, startRow - 1, startCol, emptyNode, res);
        dfs(grid, startRow, startCol + 1, emptyNode, res);
        dfs(grid, startRow, startCol - 1, emptyNode, res);
        grid[startRow][startCol] = 0; // empty node recovery
        emptyNode++;
    }

    bool checkValid(std::vector<std::vector<int>> const & grid, int const startRow, int const startCol) {
        if (startRow >= 0 && startRow < grid.size() &&
                startCol >= 0 && startCol < grid[startRow].size() &&
                0 <= grid[startRow][startCol]) {
            return true;
        }
        return false;
    }

};

class SolutionDFSReturnVal {
public:
    int a[4] = {0, 1, 0, -1};
    int b[4] = {1, 0, -1, 0};
    int m=0;
    int n=0;
    bool check(int x, int y, std::vector<std::vector<bool>> const & visited){
        return ((0<=x && x<m) && (0<=y && y<n) && (!visited[x][y]));
    }

    int travel(int i, int j, std::vector<std::vector<int>> const & grid, std::vector<std::vector<bool>>& visited, int zeroCnt, int level){
        if (grid[i][j]==2) {
            if(zeroCnt==(level-1)) return 1;
            else return 0;
        }
        int ans = 0;
        visited[i][j] = true;
        for(int k=0 ; k<4 ; k++){
            int x = i+a[k], y = j+b[k];
            if(check(x, y, visited))
                if(grid[x][y]!=-1 && grid[x][y]!=1) ans+=travel(x, y, grid, visited, zeroCnt, level+1);
        }
        visited[i][j] = false;
        return ans;
    }

    int uniquePathsIII(vector<vector<int>>& grid) {
        m = grid.size();
        if(m==0) return 0;
        n = grid[0].size();
        int x=0, y=0, zeroCnt=0;
        std::vector<std::vector<bool>> visited(m, std::vector<bool> (n, false));
        for(int i=0 ; i<m ; i++){
            for(int j=0 ; j<n ; j++){
                if(grid[i][j]==1){ x=i; y=j;}
                if(grid[i][j]==0) zeroCnt++;
            }
        }
        return travel(x, y, grid, visited, zeroCnt, 0);
    }
};

class SolutionUltimate {
public:
    int uniquePathsIII(std::vector<std::vector<int>> grid) {
        // plagiarizing from https://www.youtube.com/watch?v=Dny7JhfvJ0o
        int const rowSize = grid.size();
        if (0 == rowSize) {
            return 0;
        }
        int const colSize = grid[0].size();
        if (0 == colSize) {
            return 0;
        }
        int startRow = 0, startCol = 0, emptyNode = 1;
        for (int row = 0; row < rowSize; row++) {
            for (int col = 0; col < colSize; col++) {
                if (0 == grid[row][col]) {
                    emptyNode++;
                } else if (1 == grid[row][col]) {
                    startRow = row;
                    startCol = col;
                }
            }
        }
        return dfs(grid, startRow, startCol, emptyNode);
    }

private:
    int dfs(std::vector<std::vector<int>> & grid,
            int const startRow, int const startCol,
            int emptyNode) {
        if (!checkValid(grid, startRow, startCol)) {
            return 0;
        }
        if (2 == grid[startRow][startCol]) {
            // if visited endRow and endCol, if emptyNode is not zero, there is no
            // need to traversal the others empty nodes
            if (0 == emptyNode) {
                return 1;
            }
            return 0;
        }
        grid[startRow][startCol] = -2; // empty node but has been visited
        emptyNode--;
        int ans = 0;
        for (int index = 0; index < DIRECTION_SIZE; index++) {
            ans += dfs(grid,
                       startRow + directions[index], startCol + directions[index + 1],
                       emptyNode);
        }
        grid[startRow][startCol] = 0; // empty node recovery
        emptyNode++;
        return ans;
    }

    bool checkValid(std::vector<std::vector<int>> const & grid, int const startRow, int const startCol) {
        if (startRow >= 0 && startRow < grid.size() &&
                startCol >= 0 && startCol < grid[startRow].size() &&
                0 <= grid[startRow][startCol]) {
            return true;
        }
        return false;
    }
private:
    static int const DIRECTION_ARRAY_SIZE = 5;
    static int const DIRECTION_SIZE = DIRECTION_ARRAY_SIZE - 1;
    static std::array<int, DIRECTION_ARRAY_SIZE> directions;
};
std::array<int, Solution::DIRECTION_ARRAY_SIZE> Solution::directions = {0, 1, 0, -1, 0};
