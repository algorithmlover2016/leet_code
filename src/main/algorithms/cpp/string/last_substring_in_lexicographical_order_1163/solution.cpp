#include "../../head.h"


class SolutionTLE {
public:
    std::string lastSubstring(std::string const & s) {
        if (JUST_RETURN >= s.size()) {
            return s;
        }
        int const sSize = s.size();

        std::string ans;
        for (int idx = 0; idx < sSize; idx++) {
            dfs(s, idx, "", ans);
        }
        return ans;
    }
    void dfs(std::string const & s, int idx, std::string next, std::string & ans) {
        int const sSize = s.size();
        if (next > ans) {
            ans = next;
        }
        if (idx >= sSize) {
            return;
        }
        dfs(s, idx + 1, next.append(1, s[idx]), ans);
    }
private:
    static int const JUST_RETURN = 1;
};

class Solution {
public:
    std::string lastSubstring(std::string const & s) {
        int const sSize = s.size();
        if (JUST_RETURN >= sSize) {
            return s;
        }
        // plagiarizing from https://leetcode.com/problems/last-substring-in-lexicographical-order/discuss/363662/Short-python-code-O(n)-time-and-O(1)-space-with-proof-and-visualization
        int idxLeft = 0, idxRight = idxLeft + 1;
        int delta = 0;
        while (idxRight < sSize) {
            if (s[idxLeft + delta] == s[idxRight + delta]) {
                delta++;
            } else if (s[idxLeft + delta] > s[idxRight + delta]) {
                idxRight +=  delta + 1;
                delta = 0;
            } else {
                idxLeft = std::max(idxLeft + delta + 1, idxRight);
                idxRight = idxLeft + 1;
                delta = 0;
            }
        }
        return s.substr(idxLeft);
    }

private:
    static int const JUST_RETURN = 1;
};
