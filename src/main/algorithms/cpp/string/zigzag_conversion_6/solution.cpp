#include "../../head.h"


// #define DEBUG
class Solution {
public:
    std::string convert(std::string const & s, int numRows) {
        std::string ans;
        int const sSize = s.size();
        if (JUST_RETURN >= sSize || JUST_RETURN >= numRows) {
            return s;
        }
        std::vector<int> deltaVec(2, 0);
        for (int row = 0; row < numRows; row++) {
            // delta = numRows - 1 - idx + numRows - 1 - 1 - idx + 1
            if (0 == row || row + 1 == numRows) {
                deltaVec[0] = deltaVec[1] = 2 * (numRows - 1) - 1;
            } else {
                // deltaIdx = numRows - 1 - idx + numRows - 1 - idx - 1 + 1;
                deltaVec[0] = 2 * (numRows - 1 - row) - 1;
                deltaVec[1] = 2 * row - 1;
            }

#ifdef DEBUG
            std::cout << "\nrow, deltaIdx: " << row << ",\t" << deltaVec[0] << ",\t" << deltaVec[1] << "\n";
#endif
            int deltaIdx = 0;
            for (int idx = row; idx < sSize;) {
#ifdef DEBUG
                std::cout << "idx, val : " << idx << ",\t" << s[idx] << "\t";
#endif
                ans += s[idx];
                idx += deltaVec[deltaIdx] + 1;
                deltaIdx = 1 - deltaIdx;
            }
        }
        return ans;
    }
private:
    static int const JUST_RETURN = 1;
};
