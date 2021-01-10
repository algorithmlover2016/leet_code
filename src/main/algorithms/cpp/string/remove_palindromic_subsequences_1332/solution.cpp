#include "../../head.h"


class Solution {
public:
    int removePalindromeSub(std::string const & s) {
        if (s.empty()) {
            return 0;
        }
        for (int left = 0, right = s.size() - 1; left < right; left++, right--) {
            if (s[left] != s[right]) {
                return 2;
            }
        }
        return 1;
    }
};
