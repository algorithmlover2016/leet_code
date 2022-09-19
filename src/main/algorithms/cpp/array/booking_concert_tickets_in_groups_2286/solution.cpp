#include "../../head.h"

/**
 * Your BookMyShow object will be instantiated and called as such:
 * BookMyShow* obj = new BookMyShow(n, m);
 * vector<int> param_1 = obj->gather(k,maxRow);
 * bool param_2 = obj->scatter(k,maxRow);
 */

// #define DEBUG_INDEX
// #define DEBUG
class BookMyShowSegTree {
public:
    BookMyShowSegTree(int n, int m) : rows(n), cols(m) {
        // plagiarizing from https://leetcode.com/problems/booking-concert-tickets-in-groups/discuss/2083758/Segment-Tree-vs.-BIT
        // segment tree can also be implemented by full binary-tree
        segBTree = std::vector<std::pair<long long, int>>(rows * 4, std::make_pair(0, cols));
        #ifdef DEBUG_INDEX
        std::cout << "segBTree: " << segBTree.size() << "\n";
        #endif
        /*
        let me explain why need resize segBTree to rows * 2 + 1;
        we need construct a binary full tree, whose leafs represent each row. Leafs from left to right means rows from 0 to rows - 1(included)
        Let me assume the height of tree is H (The H start from 1, which means the root node is at height 1)
        if we want rows leafs in the tree. Then for a full binary tree, there must have a equatioin that
        2^(H - 1) = rows <=> H = log2(rows) + 1;
        for a full binary tree, the total nodes in the tree are
        2^(H) - 1 = 2 ^(log2(rows) + 1) - 1 = rows * 2 - 1;
        We just not use the 0 index. The root index is marked as 1;
        However the upper equation requires that the tree must be full.
        So we need 2 ^ ( H + 1) - 1 to make sure which means need 2 ^(log2(rows) + 1 + 1) - 1 = 4 * rows - 1;
        If rows == 2 ^ H - 1 then we can just need apply 2 * rows.
        */
        rowEndIndex = std::vector(rows, 0);

    }

    std::vector<int> gather(int k, int maxRow) {
        maxRow = std::min(maxRow, rows);
        #ifdef DEBUG
        std::cout << "call gather\n";
        #endif
        int row = find_target_row(0, rows - 1, k);
        #ifdef DEBUG
        std::cout << "find row: " << row << "\n";
        #endif
        if (row < 0 || row > maxRow) {
            return {};
        }
        rowEndIndex[row] += k;
        update(0, rows - 1, row, rowEndIndex[row]);
        return {row, rowEndIndex[row] - k};
    }
    
    bool scatter(int k, int maxRow) {
        #ifdef DEBUG
        std::cout << "call scatter begin\n";
        #endif
        maxRow = std::min(maxRow, rows);
        if (query(0, rows - 1, 0, maxRow) + k > ((long long)maxRow + 1) * cols) {
            return false;
        }
        for (int idx = start; k && idx <= maxRow; idx++) {
            if (cols - rowEndIndex[idx]) {
                // rowEndIndex[idx] record the sitted chars. So it will never be negtive.
                int canSit = std::min(cols - rowEndIndex[idx], k);
                k -= canSit;
                rowEndIndex[idx] += canSit;
                update(0, rows - 1, idx, rowEndIndex[idx]);
            } else {
                start = idx + 1;
            }
        }
        #ifdef DEBUG
        std::cout << "call scatter done\n";
        #endif
        return true;
    }
        
private:
    long long query(int tl, int tr, int left, int right, int index = 1) {
        #ifdef DEBUG
        std::cout << "from (" << tl << ", " << tr << ") query (" << left << ", " << right << "), with " << index << "\n";
        #endif
        if (left > right) {
            return 0;
        }
        if (tl == left && tr == right) {
            return segBTree[index].first;
        }
        int tmid = (tl + tr) / 2;
        return query(tl, tmid, left, std::min(tmid, right), index * 2) + query(tmid + 1, tr, std::max(tmid + 1, left) , right, index * 2 + 1);
    }

    void update(int start, int end, int idx, int val, int index = 1) {
        #ifdef DEBUG_INDEX
        std::cout << "(" << start << ", " << end << "), index: " << index << ",\t";
        #endif
        if (start == end) {
            segBTree[index] = {val, cols - val}; // used pos index, and left chars.
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid) {
                update(start, mid, idx, val, index * 2);
            } else {
                update(mid + 1, end, idx, val, index * 2 + 1);
            }
            segBTree[index] = {segBTree[index * 2].first + segBTree[index * 2 + 1].first, std::max(segBTree[index * 2].second, segBTree[index * 2 + 1].second)};
        }
        #ifdef DEBUG
        std::cout << "(" << start << ", " << end << "): (" << segBTree[index].first << ", " << segBTree[index].second << ")\n";
        #endif
    }

    int find_target_row(int startRow, int endRow, int val, int index = 1) {
        // binary search
        if (segBTree[index].second < val) {
            return -1;
        }
        while (startRow < endRow) {
            int mid = startRow + (endRow - startRow) / 2;
            if (segBTree[index * 2].second >= val) {
                index *= 2;
                endRow = mid;
            } else {
                index = index * 2 + 1;
                startRow = mid + 1;
            }
        }
        return startRow;
    }
private:
    int rows = 0;
    int cols = 0;
    int start = 0;
    std::vector<std::pair<long long int, int>> segBTree;
    std::vector<int> rowEndIndex;
};

// #define DEBUG
class BookMyShow {
public:

    BookMyShow(int n, int m) : rows(n), cols(m) {
        // plagiarizing from https://leetcode.com/problems/booking-concert-tickets-in-groups/discuss/2083758/Segment-Tree-vs.-BIT
        segBits = std::vector<long long>(MAX_ROW + 1, 0);
        rowEndIndex = std::vector<int>(MAX_ROW + 1, 0);
    }

    std::vector<int> gather(int k, int maxRow) {
        if (maxRow >= rows) {
            maxRow = rows - 1;
        }
        long long totalSits = prefixSum(maxRow);
        if (totalSits + k > (long long)(maxRow + 1) * cols) {
            // there are not enough chairs left for k persons;
            #ifdef DEBUG
            std::cout << __func__ << " fail because not enough lefts\n";
            #endif
            return {};
        }
        #ifdef DEBUG
        std::cout << "start from " << start << " already sits " << totalSits << "\n";
        #endif
        for (int idx = start; idx <= maxRow; idx++) {
            if (rowEndIndex[idx] + k > cols) {
                // there are not enough chairs left in this row;
                #ifdef DEBUG
                std::cout << __FUNCTION__ << " not enough chairs in row " << idx << ", " << rowEndIndex[idx] << "\n";
                #endif
                continue;
            }
            #ifdef DEBUG
            std::cout << __FUNCTION__ << " sit (" << idx << ")\n";
            #endif
            rowEndIndex[idx] += k;
            add(idx, k);
            return {idx, rowEndIndex[idx] - k};
        }
        #ifdef DEBUG
        std::cout << __FUNCTION__ << " failed although have enough chairs totally\n";
        #endif
        return {};
    }

    bool scatter(int k, int maxRow) {
        if (maxRow >= rows) {
            maxRow = rows - 1;
        }
        long long totalSits = prefixSum(maxRow);
        if (totalSits + k > (long long)(maxRow + 1) * cols) {
            // we have not enough chairs from 0 to maxRow(both included)
            #ifdef DEBUG
            std::cout << __FUNCTION__ << " fail because of out of chairs\n";
            #endif
            return false;
        }
        for (int idx = start; k && idx <= maxRow; idx++) {
            if (cols - rowEndIndex[idx]) {
                // there are some chairs that are not sitted.
                int sitedOnRow = std::min(cols - rowEndIndex[idx], k);
                #ifdef DEBUG
                std::cout << "sit on (" << idx << ", " << sitedOnRow << ")\n";
                #endif
                k -= sitedOnRow;
                rowEndIndex[idx] += sitedOnRow;
                add(idx, sitedOnRow);
            } else {
                start = idx + 1;
            }
        }
        return true;

    }
private:
    long long prefixSum(int index) {
        long long sum = 0;
        for (int idx = index + 1; idx > 0; idx -= idx & (-idx)) {
            sum += segBits[idx];
        }
        return sum;
    }

    void add(int index, int val) {
        for (int idx = index + 1; idx <= MAX_ROW; idx += idx & (-idx)) {
            segBits[idx] += val;
        }
    }

private:
    int rows = 0;
    int cols = 0;
    int start = 0;
    constexpr int static MAX_ROW = 5e4 + 1;
    std::vector<long long> segBits;
    std::vector<int> rowEndIndex;
};