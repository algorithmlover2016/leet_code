#include "../../head.h"



class SolutionTLE {
private:
    const int FLIP_FLAG = 1;
    const int NEED_ANS = 2;
public:
    vector<int> minDeletions(string s, vector<vector<int>>& queries) {
        std::vector<char> sChars(s.begin(), s.end());
        std::vector<int> ans;
        for (const auto & query : queries) {
            if (query.empty()) {
                continue;
            }
            if (query[0] == FLIP_FLAG && query.size() > FLIP_FLAG) {
                sChars[query[1]] = ((sChars[query[1]] - 'A') ^ 1) + 'A';
                continue;
            } else if (query[0] == NEED_ANS && query.size() > NEED_ANS) {
                int left = query[1], right = query[2];
                ans.push_back(helper(sChars, left, right));
            }
        }
        return ans;
    }
private:
    int helper(std::vector<char> & sChars, int left, int right) {
        int count = 0;
        char prevChar = sChars[left];
        for (int idx = left+1; idx <= right; idx++) {
            if (sChars[idx] != prevChar) {
                prevChar = sChars[idx];
                continue;
            } else {
                count++;
            }
        }
        return count;
    }

};