#include "../../head.h"


// #define DEBUG
class Solution {
protected:
    struct Rectangle {
    public:
        int left;
        int top;
        int right;
        int buttom;
        // we must define the default constructor because we will use this type in map
        // map's operator[key] will invoke Rectangle() constructor
        Rectangle(int left_ = 0, int top_ = 0, int right_ = 0, int buttom_ = 0) :
        left(left_), top(top_), right(right_), buttom(buttom_) {
        }
    };

public:
    bool isPrintable(std::vector<std::vector<int>> const & targetGrid) {
        // plagiarizing from https://youtu.be/fBFv075BvOY
        // print from the smallest area rectangle
        std::unordered_set<int> colors;
        std::unordered_map<int, Rectangle> col2Rec;
        for (int row = 0; row < targetGrid.size(); row++) {
            for (int col = 0; col < targetGrid[row].size(); col++) {
                int color = targetGrid[row][col];
                colors.insert(color);
                if (col2Rec.find(color) == col2Rec.end()) {
                    // left, top, right, buttom
                    Rectangle rec(col, row, col, row);
                    col2Rec[color] = rec;
                    // col2Rec.insert(std::make_pair(color, rec));
                } else {
                    col2Rec[color].left = std::min(col2Rec[color].left, col);
                    col2Rec[color].top = std::min(col2Rec[color].top, row);
                    col2Rec[color].right = std::max(col2Rec[color].right, col);
                    col2Rec[color].buttom = std::max(col2Rec[color].buttom, row);
                }
            }
        }

        std::unordered_set<int> printed;
        std::unordered_set<int> printing;
        for (int const color : colors) {
            if (!dfs(color, printed, printing, targetGrid, col2Rec)) {
                return false;
            }
        }
        return true;
    }
    bool dfs(int const color,
            std::unordered_set<int> & printed,
            std::unordered_set<int> & printing,
            std::vector<std::vector<int>> const & targetGrid,
            std::unordered_map<int, Rectangle> const & col2Rec) {
        #ifdef DEBUG
        std::cout << "print: " << color << "\t";
        #endif

        if (printed.find(color) != printed.end()) {
            return true;
        }

        if (printing.find(color) != printing.end()) {
            #ifdef DEBUG
            std::cout << "print printing: " << color << "\n";
            #endif

            return false;
        }

        #ifdef DEBUG
        std::cout << "color: " << color << ",\t" << col2Rec.at(color).top << ",\t" << col2Rec.at(color).buttom
            << ",\t" << col2Rec.at(color).left << ",\t" << col2Rec.at(color).right << "\t";
        #endif

        for (int row = col2Rec.at(color).top; row <= col2Rec.at(color).buttom; row++) {
            for (int col =  col2Rec.at(color).left; col <= col2Rec.at(color).right; col++) {
                if (targetGrid[row][col] != color) {
                    // not add targetGrid[row][col], we next print it. now we print color
                    // need turn to print it.
                    printing.insert(color);
                    if (!dfs(targetGrid[row][col], printed, printing, targetGrid, col2Rec)) {
                        #ifdef DEBUG
                        std::cout << "print fail: " << targetGrid[row][col] << "\n";
                        #endif
                        return false;
                    }
                    printing.erase(color);
                }
            }
        }
        #ifdef DEBUG
        std::cout << "\n";
        #endif
        printed.insert(color);
        return true;
    }
};

// #define DEBUG
class Solution {
protected:
    struct Rectangle {
    public:
        int left;
        int top;
        int right;
        int buttom;
        // we must define the default constructor because we will use this type in map
        // map's operator[key] will invoke Rectangle() constructor
        Rectangle(int left_ = 0, int top_ = 0, int right_ = 0, int buttom_ = 0) :
        left(left_), top(top_), right(right_), buttom(buttom_) {
        }
    };

public:
    bool isPrintable(std::vector<std::vector<int>> targetGrid) {
        // plagiarizing from https://leetcode.com/problems/strange-printer-ii/discuss/854193/Python-Straight-Forward
        // print from the smallest area rectangle
        std::unordered_set<int> colors;
        std::unordered_map<int, Rectangle> col2Rec;
        for (int row = 0; row < targetGrid.size(); row++) {
            for (int col = 0; col < targetGrid[row].size(); col++) {
                int color = targetGrid[row][col];
                colors.insert(color);
                if (col2Rec.find(color) == col2Rec.end()) {
                    // left, top, right, buttom
                    Rectangle rec(col, row, col, row);
                    col2Rec[color] = rec;
                    // col2Rec.insert(std::make_pair(color, rec));
                } else {
                    col2Rec[color].left = std::min(col2Rec[color].left, col);
                    col2Rec[color].top = std::min(col2Rec[color].top, row);
                    col2Rec[color].right = std::max(col2Rec[color].right, col);
                    col2Rec[color].buttom = std::max(col2Rec[color].buttom, row);
                }
            }
        }

        while (!colors.empty()) {
            std::unordered_set<int> failColors;
            for (int const color : colors) {
                if (!printOp(color, targetGrid, col2Rec)) {
                    #ifdef DEBUG
                    std::cout << "insert: " << color << "\n";
                    #endif
                    failColors.insert(color);
                }
            }
            if (failColors.size() == colors.size()) {
                return false;
            }
            std::swap(colors, failColors);
        }
        return true;
    }
    
private:
    bool printOp(int const color,
            std::vector<std::vector<int>> & targetGrid,
            std::unordered_map<int, Rectangle> const & col2Rec) {
#ifdef DEBUG
        std::cout << "print: " << color << "\t";
#endif

#ifdef DEBUG
        std::cout << "color: " << color << ",\t" << col2Rec.at(color).top << ",\t" << col2Rec.at(color).buttom
            << ",\t" << col2Rec.at(color).left << ",\t" << col2Rec.at(color).right << "\t";
#endif

        for (int row = col2Rec.at(color).top; row <= col2Rec.at(color).buttom; row++) {
            for (int col =  col2Rec.at(color).left; col <= col2Rec.at(color).right; col++) {
                if (JUST_ZERO < targetGrid[row][col] && targetGrid[row][col] != color) {
                    // in this region, there is some other color;
                    return false;
                }
            }
        }
        
        for (int row = col2Rec.at(color).top; row <= col2Rec.at(color).buttom; row++) {
            for (int col =  col2Rec.at(color).left; col <= col2Rec.at(color).right; col++) {
                targetGrid[row][col] = JUST_ZERO;
            }
        }

#ifdef DEBUG
        std::cout << "\n";
#endif
        return true;
    }

private:
    static int const JUST_ZERO = 0;
    
};
