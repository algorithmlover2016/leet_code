#include "../../head.h"


class SolutionAtMost {
public:
    int numberOfSubstrings(std::string const & s) {
        // plagiarizing from https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/discuss/516977/JavaC++Python-Easy-and-Concise
        return atMost(s, 3) - atMost(s, 2);
    }
    int atMost(std::string const & s, int K) {
        int res = 0;
        int start = 0;
        std::unordered_map<char, int> visited; // can be replaced by vector<int>(3, 0) c - 'a';
        for (int index = 0; index < s.size(); index++) {
            if (0 == visited[s[index]]++) {
                K--;
            }
            while (K < 0) {
                if (0 == --visited[s[start]]) {
                    K++;
                }
                start++;
            }
            res += index - start + 1;
        }
        return res;
    }
};

class SolutionExactlyMap {
public:
    int numberOfSubstrings(std::string const & s) {
        // plagiarizing from https://leetcode.com/problems/subarrays-with-k-different-integers/discuss/235235/C%2B%2BJava-with-picture-prefixed-sliding-window
        int const target = 3;
        int res = 0, start = 0, prefix = 0, cnt = 0;
        std::map<char, int> visited;
        for (int index = 0; index < s.size(); index++) {
            if (0 == visited[s[index]]++) {
                cnt++;
            }
            if (cnt > target) {
                visited[s[start++]]--;
                cnt--;
                prefix = 0;
            }
            while (visited[start] > 1) {
                visited[s[start++]]--;
                prefix++;
            }
            if (cnt == target) {
                res += prefix + 1;
            }
        }
        return res;
    }
};

class SolutionExactlyVector {
public:
    int numberOfSubstrings(std::string const & s) {
        // plagiarizing from https://leetcode.com/problems/subarrays-with-k-different-integers/discuss/235235/C%2B%2BJava-with-picture-prefixed-sliding-window
        int const target = 3;
        int res = 0, start = 0, prefix = 0, cnt = 0;
        // std::map<char, int> visited;
        std::vector<int> visited(target, 0);
        for (int index = 0; index < s.size(); index++) {
            if (0 == visited[s[index] - 'a']++) {
                cnt++;
            }
            if (cnt > target) {
                visited[s[start++] - 'a']--;
                cnt--;
                prefix = 0;
            }
            while (visited[s[start] - 'a'] > 1) {
                visited[s[start++] - 'a']--;
                prefix++;
            }
            if (cnt == target) {
                res += prefix + 1;
            }
        }
        return res;
    }
};

class Solution {
public:
    int numberOfSubstringsCombineEnd(std::string const & s) {
        ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
        int as = 0, bs = 0, cs = 0, ind = 0, l = 0, r = 0, ans = 0;
        while (r < s.size()) {
            while (r <s.size() && !(as && bs && cs)) {
                if (s[r]=='a') {
                    as++;
                } else if (s[r]=='b') {
                    bs++;
                } else {
                    cs++;
                }
                r++;
            }
            if (as && bs && cs) {
                while (l < r && as && bs && cs) {
                    if (s[l]=='a') {
                        as--;
                    } else if (s[l]=='b') {
                        bs--;
                    } else {
                        cs--;
                    }
                    // from r to end, all elements can add to this substr(from l to r)
                    ans += s.size() - r + 1;
                    l++;
                }
            }
        }
        return ans;
    }
    int numberOfSubstringsCombineFromStart(std::string const & s) {
        int count[3] = {0, 0, 0},res = 0 , i = 0, n = s.length();
        for (int j = 0; j < n; ++j) {
            ++count[s[j] - 'a'];
            while (count[0] && count[1] && count[2])
                --count[s[i++] - 'a'];
            res += i;
        }
        return res;
    }
};
