#include "../../head.h"


class Solution {
public:
    int nextGreaterElement(int n) {
        // plagiarizing  from https://youtu.be/nyUJhLxbIDY
        std::string nStr = std::to_string(n);
        int const nStrSize = nStr.size();
        if (JUST_RETURN >= nStrSize) {
            return NOVALID;
        }

        int leftNeedChange = nStrSize - 2;
        while (STOP_IDX < leftNeedChange && nStr[leftNeedChange] >= nStr[leftNeedChange + 1]) {
            leftNeedChange--;
        }
        if (STOP_IDX == leftNeedChange) {
            return NOVALID;
        }
        int rightNeedChange = nStrSize - 1;
        while (nStr[leftNeedChange] >= nStr[rightNeedChange]) {
            rightNeedChange--;
        }
        std::swap(nStr[leftNeedChange], nStr[rightNeedChange]);
        for (leftNeedChange++, rightNeedChange = nStrSize - 1;
                leftNeedChange < rightNeedChange;
                leftNeedChange++, rightNeedChange--) {
            std::swap(nStr[leftNeedChange], nStr[rightNeedChange]);
        }
        long int ans = std::stol(nStr);
        return ans > OVERFLOW_INT ? -1 : ans;


    }
private:
    static int const JUST_RETURN = 1;
    static int const STOP_IDX = -1;
    static int const NOVALID = -1;
    static long const OVERFLOW_INT;
};
long const Solution::OVERFLOW_INT = static_cast<long>((1 << 32) - 1);
