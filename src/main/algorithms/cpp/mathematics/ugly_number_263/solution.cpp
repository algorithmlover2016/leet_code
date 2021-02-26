#include "../../head.h"


class Solution {
public:
    bool isUgly(int num) {
        if (JUST_ONE == num) {
            return true;
        }
        if (0 == num) {
            return false;
        }
        static std::vector<int> facs{{2, 3, 5}};
        for (int const fac : facs) {
            while (0 == num % fac) {
                num /= fac;
            }
        }
        return JUST_ONE == num;

    }
private:
    static int const JUST_ONE = 1;
};
