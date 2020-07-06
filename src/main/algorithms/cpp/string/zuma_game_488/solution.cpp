#include "../../head.h"


class Solution {
public:
    int findMinStep(std::string const & board, std::string const & hand) {
        // plagiarizing from https://leetcode.com/problems/zuma-game/discuss/97010/%22short%22-java-solution-beats-98
        /*
           std::string ss("aaabbbbccddffsfsfgfsffa");
           std::regex re("(.)\\1{2,}");
           std::cout << std::regex_replace(ss, re, "") << "\n";
         */
        std::vector<int> cnt(UPPER_ALPHA_NUM, 0);
        for (char const c : hand) {
            cnt[c - 'A']++;
        }
        return dfsHelper(board + "#", cnt);
    }
private:
    int dfsHelper(std::string board, std::vector<int> & cnt) {
        // std::cout << "board: " << board << "\n";
        if ("#" == board) {
            return 0;
        }
        int res = INT_MAX;
        for (int start = 0, end = 0; end < board.size(); end++) {
            if (board[end] == board[start]) {
                continue;
            }
            int needInsert = 3 - end + start;
            if (0 > needInsert) {
                needInsert = 0;
            }
            if (needInsert <= cnt[board[start] - 'A']) {
                // std::cout << "needInsert: " << needInsert << "\t" << board[start] << "\t";
                cnt[board[start] - 'A'] -= needInsert;
                int forther = dfsHelper(board.substr(0, start) + board.substr(end), cnt);
                if (forther >= 0) {
                    res = std::min(res, needInsert + forther);
                }
                cnt[board[start] - 'A'] += needInsert;
            }
            start = end;
            // std::cout << "\n";
        }
        return INT_MAX == res ? -1 : res;

    }

private:
    int const UPPER_ALPHA_NUM = 26;
};
