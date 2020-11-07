#include "../../head.h"


class Solution {
public:
    int maxScoreWords(std::vector<std::string> const & words,
            std::vector<char> const & letters,
            std::vector<int> const & score) {
        // plagiarizing from https://leetcode.com/problems/maximum-score-words-formed-by-letters/discuss/426045/C%2B%2B-DFS-(optional-memo)
        int const LETTER_NUM = 26;
        std::vector<int> cnt(LETTER_NUM, 0);
        for (char c : letters) {
            cnt[c - 'a']++;
        }
        // return backTracing(words, cnt, score, 0);
        return backTracingTraversal(words, cnt, score, 0);
    }
    int backTracing(std::vector<std::string> const & words,
            std::vector<int> & cnt,
            std::vector<int> const & score,
            int index) {
        if (index == words.size()) {
            return 0;
        }
        int skipCur = backTracing(words, cnt, score, index + 1);
        int gain = 0;
        bool isValid = true;
        for (int innerIndex = 0; innerIndex < words[index].size(); innerIndex++) {
            if (--cnt[words[index][innerIndex] - 'a'] < 0) {
                isValid = false;
            }
            gain += score[words[index][innerIndex] - 'a'];
        }
        if (isValid) {
            gain += backTracing(words, cnt, score, index + 1);
        }
        for (int innerIndex = 0; innerIndex < words[index].size(); innerIndex++) {
            cnt[words[index][innerIndex] - 'a']++;
        }
        return isValid ? std::max(skipCur, gain) : skipCur;
    }

    int backTracingTraversal(std::vector<std::string> const & words,
            std::vector<int> & cnt,
            std::vector<int> const & score,
            int index = 0) {

        // plagiarizing from https://leetcode.com/problems/maximum-score-words-formed-by-letters/discuss/425129/java-backtrack-similar-to-78.-Subsets-1ms-beats-100
        int ans = 0;
        for (int i = index; i < words.size(); i++) {
            int gain = 0;
            bool isValid = true;
            for (char c : words[i]) {
                if (--cnt[c - 'a'] < 0) {
                    isValid = false;
                }
                gain += score[c - 'a'];
            }
            if (isValid) {
                gain += backTracingTraversal(words, cnt, score, i + 1);
                ans = std::max(ans, gain);
            }
            for (char c : words[i]) {
                ++cnt[c - 'a'];
            }
        }
        return ans;
    }
};
