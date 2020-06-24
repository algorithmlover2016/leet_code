#include "../../head.h"


class Solution {
public:
    int balancedString(std::string const & s) {
        int sSize = s.size();
        int const eachLen = sSize / 4;
        if (eachLen * 4 != sSize) {
            return -1;
        }

        std::map<char, int> visited;
        visited.emplace(std::make_pair('Q', eachLen));
        visited.emplace(std::make_pair('R', eachLen));
        visited.emplace(std::make_pair('E', eachLen));
        visited.emplace(std::make_pair('W', eachLen));
        for (int index = 0; index < sSize; index++) {
            visited[s[index]]--;
        }
        int res = INT_MAX, start = 0;
        for (int index = 0; index < sSize; index++) {
            visited[s[index]]++;
            bool flag = true;
            for (std::pair<char, int> const & cur : visited) {
                if (cur.second < 0) {
                    flag = false;
                }
            }
            if (flag) {
                while (flag) {
                    visited[s[start++]]--;
                    for (std::pair<char, int> const & cur : visited) {
                        if (cur.second < 0) {
                            flag = false;
                        }
                    }
                }
                res = std::min(res, index - start + 2);
            }
        }
        return res;
    }
};

class Solution {
public:
    int balancedString(string s) {
        std::unordered_map<int, int> count;
        int n = s.length(), res = n, i = 0, k = n / 4;
        for (int j = 0; j < n; ++j) {
            count[s[j]]++;
        }
        for (int j = 0; j < n; ++j) {
            count[s[j]]--;
            // record from i to j, how many character can be reduced. If all are less than k, then it's a target choice;
            while (i < n && count['Q'] <= k && count['W'] <= k && count['E'] <= k && count['R'] <= k) {
                res = std::min(res, j - i + 1);
                count[s[i++]] += 1;
            }
        }
        return res;
    }
};
