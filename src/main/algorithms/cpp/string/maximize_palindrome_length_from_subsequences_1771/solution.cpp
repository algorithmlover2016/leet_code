#include "../../head.h"


class SolutionWrongAns {
public:
    int longestPalindrome(std::string const & word1, std::string const & word2) {
        std::string rWord2(word2.rbegin(), word2.rend());
        int lcsLen = lcs(word1, rWord2);
        if (word1.back() != word2.front()) {
            return 0 == lcsLen ? 0 : lcsLen * 2 + 1;
        } else {
            return lcsLen * 2;
        }


    }
private:
    int lcs(std::string const & word1, std::string const & word2) {
        int const word1Size = word1.size();
        int const word2Size = word2.size();
        std::vector<std::vector<int>> dpMemo(word1Size + 1, std::vector<int>(word2Size + 1, 0));
        for (int idx1 = 0; idx1 < word1Size; idx1++) {
            for (int idx2 = 0; idx2 < word2Size; idx2++) {
                if (word1[idx1] == word2[idx2]) {
                    dpMemo[idx1 + 1][idx2 + 1] = dpMemo[idx1][idx2] + 1;
                } else {
                    dpMemo[idx1 + 1][idx2 + 1] = std::max(dpMemo[idx1][idx2 + 1], dpMemo[idx1 + 1][idx2]);
                }
            }
        }
        return dpMemo[word1Size][word2Size];
    }
};

class Solution {
public:
    int longestPalindrome(std::string const & word1, std::string const & word2) {
        // plagiarizing idea from https://youtu.be/wObLRAMXxoE
        int const word1Size = word1.size();
        int const word2Size = word2.size();
        std::string word(word1 + word2);
        int const wordSize = word.size();
        std::vector<std::vector<int>> dpPalindrome(wordSize, std::vector<int>(wordSize, 0));
        for (int left = wordSize - 1; left > EXCLUDE_LEFT_MOST_IDX; left--) {
            for (int right = left; right < wordSize; right++) {
                if (word[left] == word[right]) {
                    dpPalindrome[left][right] =
                        (right - left < 2) ? right - left + 1 : dpPalindrome[left + 1][right - 1] + 2;
                } else {
                    dpPalindrome[left][right] = std::max(dpPalindrome[left + 1][right], dpPalindrome[left][right - 1]);
                }
            }
        }

        int ans = 0;
        for (int idx1 = 0; idx1 < word1Size; idx1++) {
            for (int idx2 = 0; idx2 < word2Size; idx2++) {
                if (word1[idx1] == word2[idx2]) {
                    // idx1 + 1 should be in [0, word1Size), and word1Size + idx2 - 1 should be in [wrod1Size, wordSize)
                    // if idx1 == word1Size - 1, and idx2 = 0, it will break the constraint,
                    if (idx1 + 1 == word1Size && 0 == idx2) {
                        // dpPalindrome[idx1 + 1][word1Size + idx2 - 1] = dpPalindrome[word1Size][word1Size - 1]
                        // which is meaningless
                        ans = std::max(ans, 2);
                    } else {
                        ans = std::max(ans, 2 + dpPalindrome[idx1 + 1][word1Size + idx2 - 1]);
                    }
                }
            }
        }
        return ans;
    }
private:
    static int const EXCLUDE_LEFT_MOST_IDX = -1;
};
