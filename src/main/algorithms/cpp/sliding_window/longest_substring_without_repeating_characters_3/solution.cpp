#include "../../head.h"


class Solution {
public:
    int lengthOfLongestSubstring(std::string const & s) {
        int res  = 0, start = 0;
        std::unordered_map<char, int> visited;
        for (int index = 0; index < s.size(); index++) {
            if (0 < visited[s[index]]++) {
                while (1 < visited[s[index]]) {
                    visited[s[start++]]--;
                }
            }
            res = std::max(res, index - start + 1);
        }
        return res;

    }
};

class SolutionMapTovector {
public:
    int lengthOfLongestSubstring(std::string const & s) {
        // base case
        int length = s.length();
        int i(0), j(0);
        if (length == 0) {
            return 0;
        }

        // case
        // the container: will use vector
        std::vector<int> window(300, 0); // intialize all to zero
        // set the first i pointer to 1
        window[s[0]]++;
        // set ans to 1 so far
        int ans = 1;
        // moving the window
        while (j < length - 1) {
            if (window[s[j+1]] == 0) {
                j++;
                window[s[j]] = 1;
                ans = max(ans, j-i+1);
            }else{
                window[s[i]]--;
                i++;
            }
        }
        return ans;
    }
};
