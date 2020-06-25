#include "../../head.h"


class SolutionTLE {
public:
    int uniqueLetterString(std::string const & s) {
        int const MOD = 1e9 + 7;
        int res = 0;
        for (int index = 0; index < s.size(); index++) {
            std::map<char, int> visited;
            for (int inner = index; inner < s.size(); inner++) {
                visited[s[inner]]++;
                int cnt = 0;
                for (auto elePair : visited) {
                    if (1 == elePair.second) {
                        cnt++;
                    }
                }
                res += cnt;
                if (res > MOD) {
                    res -= MOD;
                }
            }
        }
        return res;

    }
};

class Solution {
public:
    int uniqueLetterString(std::string const & s) {
        int const MOD = 1e9 + 7;
        int res = 0;
        // plagiarizing from https://leetcode.com/problems/count-unique-characters-of-all-substrings-of-a-given-string/discuss/128952/C%2B%2BJavaPython-One-pass-O(N)
        std::vector<std::vector<int>> pos(256, std::vector<int>(2, -1));
        for (int index = 0; index < s.size(); index++) {
            res += (index - pos[s[index]][0]) * (pos[s[index]][0] - pos[s[index]][1]);
            // std::cout << "res: " << res << "\t";
            res %= MOD;
            // std::cout << "mod res: " << res << "\t";
            pos[s[index]][1] = pos[s[index]][0];
            pos[s[index]][0] = index;
        }
        int sSize = s.size();
        for (auto const & subV : pos) {
            res += (sSize - subV[0]) * (subV[0] - subV[1]);
            // std::cout << "res: " << res << "\t";
                res %= MOD;
            // std::cout << "mod res: " << res << "\t";
        }
        return res;
    }
};

class SolutionBetterRuntime {
public:
    int uniqueLetterString(std::string const & S) {
        int index[26][2], res = 0, N = S.length(), mod = std::pow(10, 9) + 7;
        memset(index, -1, sizeof(int) * 52);
        for (int i = 0; i < N; ++i) {
            int c = S[i] - 'A';
            res = (res + (i - index[c][1]) * (index[c][1] - index[c][0]) % mod) % mod;
            index[c][0] = index[c][1];
            index[c][1] = i;
        }
        for (int c = 0; c < 26; ++c)
            res = (res + (N - index[c][1]) * (index[c][1] - index[c][0]) % mod) % mod;
        return res;
    }
};
