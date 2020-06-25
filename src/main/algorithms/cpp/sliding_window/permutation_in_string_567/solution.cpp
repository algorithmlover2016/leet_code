#include "../../head.h"


class Solution {
public:
    bool checkInclusion(std::string const & s1, std::string const & s2) {
        std::unordered_map<char, int> visited;
        int s1Size = s1.size();
        for (char const c : s1) {
            visited[c]++;
        }
        int start = 0, cnt = 0;
        for (int index = 0; index < s2.size(); index++) {
            // std::cout << "\nvisit: " << s2[index] << "\t";
            if (--visited[s2[index]] >= 0) {
                cnt++;
                if (cnt == s1Size) {
                    return true;
                }
            } else {
                while (visited[s2[index]] < 0) {
                    if (++visited[s2[start++]] > 0) {
                        cnt--;
                    }
                }
            }
        }
        return false;
    }
};

static const auto ____ = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    return 0;
}();
class SolutionMaintainFixedLength {
public:
    bool checkInclusion(std::string const & s1, std::string const & s2) {
        std::vector<int> s1_freq(26, 0);
        for (char c: s1) {
            s1_freq[c-'a']++;
        }

        int l = 0, r = 0, cnt = s1.size();
        while (r < s2.size()) {
            if (--s1_freq[s2[r++]-'a'] >= 0) {
                cnt--;
            }

            if (cnt == 0) {
                return true;
            }

            if (r - l == s1.size()) {
                if (s1_freq[s2[l++]-'a']++ >= 0) cnt++;
            }
        }
        return false;
    }
};
