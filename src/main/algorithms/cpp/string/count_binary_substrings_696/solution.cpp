#include "../../head.h"


class Solution {
public:
    int countBinarySubstrings(std::string const & s) {
        // plagiarizing idea from https://youtu.be/0O2D-AS2-UI
        if (s.empty()) {
            return 0;
        }
        int const sSize = s.size();
        int preCnt = 0;
        int ans = 0;
        for (int idx = 0; idx < sSize; idx++) {
            int curCnt = 1;
            while (idx < sSize - 1 && s[idx] == s[idx + 1]) {
                // we count the number of the contineous letter
                idx++;
                curCnt++;
            }
            // the idx means the last index of the letter (maybe the next will differ from the cur idx, or it's the last)
            ans += std::min(preCnt, curCnt);
            preCnt = curCnt;
        }
        return ans;
    }
};

class Solution {
public:
     int countBinarySubstrings(std::string const & s) {
        int cur = 1, pre = 0, res = 0;
        for (int i = 1; i < s.size(); i++) {
            if (s[i] == s[i - 1]) {
                cur++;
            } else {
                res += std::min(cur, pre);
                pre = cur;
                cur = 1;
            }
        }
        return res + std::min(cur, pre);
    }
};
