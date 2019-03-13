#include <iostream>
class Solution {
public:
    double soupServings(int N) {
        if (N <= 0) {
            return 1;
        }
        return dp(N, N);
    }
    double dp(int aLeft, int bLeft) {
        static const int TOTAL_DIRECTION = 4;
        if (0 == (aLeft | bLeft)) {
            return 0.5;
        } else if (0 == aLeft) {
            return 1.0;
        } else if (bLeft == 0) {
            return 0;
        } else {
            return 0.25 * (
                dp(aLeft > 100 ? aLeft - 100:0, bLeft > 0 ? bLeft : 0) +
                dp(aLeft > 75 ? aLeft - 75:0, bLeft > 25 ? bLeft - 25 : 0) +
                dp(aLeft > 50 ? aLeft - 50:0, bLeft > 50 ? bLeft - 50 : 0) +
                dp(aLeft > 25 ? aLeft - 25:0, bLeft > 75 ? bLeft - 75: 0));
        }
    }
};
int main() {
    Solution a;

    std::cout << a.soupServings(660295675) << std::endl;
    return 0;
}
// g++ -std=c++11  -o main solution.cpp
