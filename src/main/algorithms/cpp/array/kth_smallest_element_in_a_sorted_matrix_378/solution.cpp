#include "../../head.h"


// #define HIGH_GREATER_RIGHT_DOWN_PLUS_ONE
// #define USING_SORTED_MATRIX_ALL_PROPERTY
// #define DEBUG
class Solution {
public:
    int kthSmallest(std::vector<std::vector<int>> const & matrix, int k) {
        // plagiarizing idea from https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/discuss/85173/Share-my-thoughts-and-Clean-Java-Code and https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/discuss/85182/My-solution-using-Binary-Search-in-C%2B%2B
        int const rowSize = matrix.size();
        if (JUST_ZERO == rowSize) {
            return INIT_MIN;
        }
        int const colSize = matrix[0].size();
        if (JUST_ZERO == colSize) {
            return INIT_MIN;
        }

        #ifdef HIGH_GREATER_RIGHT_DOWN_PLUS_ONE
        int low = matrix[0][0], high = matrix.back().back() + 1;
        #else
        int low = matrix[0][0], high = matrix.back().back();
        #endif

        #ifdef DEBUG
        std::cout << "low, high: " << low << ",\t" << high << "\n";
        #endif
        while (low < high) {

            #ifdef HIGH_GREATER_RIGHT_DOWN_PLUS_ONE
            int mid = low + (high - low) / 2;
            #else
            int mid = (high + low) / 2;
            #endif

            #ifdef DEBUG
            std::cout << "\nmid: " << mid << "\t";
            #endif

            int cntSmallerMid = countSmallerInAllRows(mid, matrix);
            if (cntSmallerMid >= k) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        return high;
    }
    int countSmallerInAllRows(int target, std::vector<std::vector<int>> const & matrix) {
        int const rowSize = matrix.size();
        int const colSize = matrix[0].size();
        int cnt = 0;

        #ifdef USING_SORTED_MATRIX_ALL_PROPERTY
        int colIdx = colSize - 1;
        for (int row = 0; row < rowSize; row++) {
            // using this fast than the std::upper_bound,
            // because if matrix[row][colIdx] > mid, matrix[row + i][colIdx] > mid, too when i > 0;
            while (colIdx > EX_MOST_LEFT_INDEX && matrix[row][colIdx] > target) {
                colIdx--;
            }
            cnt += colIdx + 1;
        }
        #else
        for (int row = 0; row < rowSize; row++) {
            int pos = std::upper_bound(matrix[row].begin(), matrix[row].end(), target) - matrix[row].begin();
            cnt += pos;
        }
        #endif

        return cnt;
    }
private:
    static int const INIT_MIN = -1e9 - 1;
    static int const JUST_ZERO = 0;
    static int const EX_MOST_LEFT_INDEX = -1;
};

class Solution {
protected:
    friend class Comp;
    class Comp {
    private:
        bool _reverse;
    public:
        Comp(bool reverse) : _reverse(reverse) {
        }
        bool operator()(std::tuple<int, int, int> const & left, std::tuple<int, int, int> const & right) {
            if (std::get<Solution::VAL_IDX>(left) <= std::get<Solution::VAL_IDX>(right)) {
                return !_reverse;
            } else {
                return _reverse;
            }
        }
    };

public:
    int kthSmallest(std::vector<std::vector<int>> const & matrix, int k) {
        // plagiarizing idea from https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/discuss/85173/Share-my-thoughts-and-Clean-Java-Code
        int const rowSize = matrix.size();
        if (JUST_ZERO == rowSize) {
            return INIT_MIN;
        }
        int const colSize = matrix[0].size();
        if (JUST_ZERO == colSize) {
            return INIT_MIN;
        }
        typedef std::priority_queue<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>, Comp> MaxHeap;
        MaxHeap minHeap(Comp(true));
        for (int col = 0; col < colSize; col++) {
            minHeap.push(std::make_tuple(matrix[0][col], 0, col));
        }
        for (; k > 1; k--) {
            auto const & ele = minHeap.top();
            int row = std::get<ROW_IDX>(ele);
            int col = std::get<COL_IDX>(ele);
            minHeap.pop();
            if (row < rowSize - 1) {
                minHeap.push(std::make_tuple(matrix[row + 1][col], row + 1, col));
            }
        }
        return std::get<VAL_IDX>(minHeap.top());


    }
private:
    static int const INIT_MIN = -1e9 - 1;
    static int const JUST_ZERO = 0;
    static int const EX_MOST_LEFT_INDEX = -1;
    static int const VAL_IDX = 0;
    static int const ROW_IDX = 1;
    static int const COL_IDX = 2;
};
