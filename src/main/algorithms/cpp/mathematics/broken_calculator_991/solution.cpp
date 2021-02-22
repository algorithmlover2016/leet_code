#include "../../head.h"


// #define DEBUG
class Solution {
public:
    int brokenCalc(int X, int Y) {
        // plagiarizing from https://youtu.be/XIiLnBV664A
        #ifdef DEBUG
        static int step = 0;
        std::cout << X << ",\t" << Y << ",\t" << step << "\n";
        step++;
        #endif
        if (X >= Y) {
            // if X >= Y, we can only execute decrement operation, which means substracting X from 1
            return X - Y;
        } else if (JUDGE_ODD == (Y & JUDGE_ODD)) {
            // Y + 1 or Y - 1 will make Y become even, however X become bigger more easily
            return brokenCalc(X, Y + 1) + 1;
        } else {
            return brokenCalc(X, Y / 2) + 1;
        }
        
    }
private:
    static int const JUDGE_ODD = 0x01;
};
