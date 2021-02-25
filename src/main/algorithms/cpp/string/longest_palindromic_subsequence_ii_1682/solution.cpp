#include "../../head.h"

#define TEST_MAIN
class Solution {
public:
    int longestPalindromeSubseq(std::string const & s) {
        // plagiarizing idea from https://leetcode.ca/2020-07-08-1682-Longest-Palindromic-Subsequence-II/
        if (s.empty()) {
            return 0;
        }
        int const sSize = s.size();
        std::vector<std::vector<std::vector<int>>> dpMemo(sSize,
                std::vector<std::vector<int>>(sSize,
                    std::vector<int>(LOWCASE_LETTER_NUMS, 0)));
        for (int idx = 1; idx < sSize; idx++) {
            if (s[idx - 1] == s[idx]) {
                // normally, we should define the dpMemo[idx][idx][s[idx] - LOWCASE_OFFSET] = 1;
                // to make sure all the answer is even
                dpMemo[idx - 1][idx][s[idx] - LOWCASE_OFFSET] = 2;
            }
        }

        for (int interval = 3; interval <= sSize; interval++) {
            for (int start = 0; start + interval - 1 < sSize; start++) {
                int incEnd = start + interval - 1;
                for (int k = 0; k < LOWCASE_LETTER_NUMS; k++) {
                    // only s[start] == s[incEnd] and the inner is not end with s[incEnd]
                    if (s[start] == s[incEnd] && s[start] - LOWCASE_OFFSET == k) {
                        for (int diffK = 0; diffK < LOWCASE_LETTER_NUMS; diffK++) {
                            if (diffK != k) {
                                dpMemo[start][incEnd][k] = std::max(dpMemo[start][incEnd][k],
                                        dpMemo[start + 1][incEnd - 1][diffK] + 2);
                            }
                        }
                    }
                    dpMemo[start][incEnd][k] = std::max(dpMemo[start][incEnd][k], dpMemo[start + 1][incEnd][k]);
                    dpMemo[start][incEnd][k] = std::max(dpMemo[start][incEnd][k], dpMemo[start][incEnd - 1][k]);
                    
                }
            }
        }
        return *std::max_element(dpMemo[0][sSize - 1].begin(), dpMemo[0][sSize - 1].end());
    }
private:
    static int const LOWCASE_LETTER_NUMS = 26;
    static char const LOWCASE_OFFSET = 'a';
};

#ifdef TEST_MAIN
#define PRINT_SCREEN
int main() {
    std::string in("bbabab");
    Solution obj;
    int ans = obj.longestPalindromeSubseq(in);
#ifdef PRINT_SCREEN
    std::cout << ans << "\n";
#endif
    assert(ans == 4);

    std::string in1("dcbccacdb");
    int ans1 = obj.longestPalindromeSubseq(in1);
#ifdef PRINT_SCREEN
    std::cout << ans1 << "\n";
#endif
    assert(ans1 == 4);

#ifdef PRINT_SCREEN
    std::cout << std::endl;
#endif
}
#endif
