#include "../../head.h"


class Solution {
public:
    int numDecodings(std::string const & s) {
        // plagiarizing from https://www.youtube.com/watch?v=_kg-U4j0gQg
        // Boundary conditions
        if (s.empty() || '0' == s[0]) {
            return 0;
        }
        int const sSize = s.size();
        std::vector<int> dpMemo(sSize + 1, 0);
        // when s is empty, the solution is 1 way which means "" -> ""
        // when s is ["1"-"9"], the solution is 1 way
        dpMemo[0] = dpMemo[1] = 1;

        for (int idx = 2; idx < dpMemo.size(); idx++) {
            // if using one digit to form a solution, the digit can not be zero
            if ('0' != s[idx - 1]) {
                dpMemo[idx] = dpMemo[idx - 1];
            }
            int val = std::stol(s.substr(idx - 2, 2));
            if (val > LOW_BOARDER && val < UP_BOARDER) {
                dpMemo[idx] += dpMemo[idx - 2];
            }
        }
        return dpMemo[sSize];
    }
private:
    static int const LOW_BOARDER = 9;
    static int const UP_BOARDER = 27;
};

class SolutionOptimize {
public:
    int numDecodings(std::string const & s) {
        // plagiarizing from https://www.youtube.com/watch?v=_kg-U4j0gQg
        // the
        if (s.empty()) {
            return 0;
        }
        int const sSize = s.size();
        std::vector<int> dpMemo(sSize + 1, 0);

        // when s is empty, the solution is 1 way which means "" -> ""
        // when s is ["1"-"9"], the solution is 1 way, is s = "0", there is no way
        dpMemo[0] = 1;
        dpMemo[1] = '0' == s[0] ? 0 : 1;

        for (int idx = 2; idx < dpMemo.size(); idx++) {
            // if using one digit to form a solution, the digit can not be zero
            if ('0' != s[idx - 1]) {
                dpMemo[idx] = dpMemo[idx - 1];
            }
            int val = std::stol(s.substr(idx - 2, 2));
            #ifdef DEBUG
            std::cout << idx << "\t" << val << "\t";
            #endif
            if (val > LOW_BOARDER && val < UP_BOARDER) {
                dpMemo[idx] += dpMemo[idx - 2];
            }
        }
        return dpMemo[sSize];
    }
private:
    static int const LOW_BOARDER = 9;
    static int const UP_BOARDER = 27;
};
