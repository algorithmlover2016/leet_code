#include "../../head.h"


#define OPTIMIZE_TIME_STILL_TLE
class Solution {
public:
    int numWays(std::vector<std::string> const & words, std::string const & target) {
        if (words.empty() || words[0].empty() || target.empty()) {
            return 0;
        }
        int const wordLen = words.back().size();
        int const targetSize = target.size();

        std::vector<std::vector<int>> dpMemo(wordLen,
                std::vector<int>(targetSize, INIT_FLAG));
        return dfs(words, target, dpMemo, 0, 0);
    }



    int dfs(std::vector<std::string> const & words,
            std::string const & target,
            std::vector<std::vector<int>> & dpMemo,
            int wordIdx, int targetIdx) {
        int const wordLen = words.back().size();
        int const targetSize = target.size();
        if (targetIdx == targetSize) {
            return 1;
        }

        if (wordIdx == wordLen) {
            return 0;
        }

        if (INIT_FLAG != dpMemo[wordIdx][targetIdx]) {
            return dpMemo[wordIdx][targetIdx];
        }

        // not using this character, we just only skip only once.
        int ans = dfs(words, target, dpMemo, wordIdx + 1, targetIdx) % MOD;

#ifdef OPTIMIZE_TIME_STILL_TLE
        int cntTargetLetter = 0;
        int curAns = 0;
        for (int idx = 0; idx < words.size(); idx++) {
            // not using this character
            // if equal, we can use the character
            if (target[targetIdx] == words[idx][wordIdx]) {
                if (0 == cntTargetLetter++) {
                    curAns = dfs(words, target, dpMemo, wordIdx + 1, targetIdx + 1);
                }
            }
        }
        while (cntTargetLetter-- > 0) {
            ans += curAns;
            ans %= MOD;
        }
#else
        for (int idx = 0; idx < words.size(); idx++) {
            // if equal, we can use the character
            if (target[targetIdx] == words[idx][wordIdx]) {
                ans += dfs(words, target, dpMemo, wordIdx + 1, targetIdx + 1);
                ans %= MOD;
            }
        }

#endif
        return dpMemo[wordIdx][targetIdx] = ans;
    }

private:
    static int const MOD = 1e9 + 7;
    int const INIT_FLAG = -1;
};

class SolutionMap {
public:
    int numWays(std::vector<std::string> const & words, std::string const & target) {
        if (words.empty() || words[0].empty() || target.empty()) {
            return 0;
        }
        int const wordLen = words.back().size();
        int const targetSize = target.size();

        // plagiarizing idea from https://youtu.be/udKsbPQu2T8
        std::vector<std::unordered_map<char, int>> colLetterCntMap(wordLen);
        for (int wordIdx = 0; wordIdx < wordLen; wordIdx++) {
            for (auto const & word : words) {
                colLetterCntMap[wordIdx][word[wordIdx]]++;
            }
        }

        std::vector<std::vector<int>> dpMemo(wordLen,
                                             std::vector<int>(targetSize, INIT_FLAG));

        return dfs(words, target, dpMemo, colLetterCntMap, 0, 0);
    }



    int dfs(std::vector<std::string> const & words,
            std::string const & target,
            std::vector<std::vector<int>> & dpMemo,
            std::vector<std::unordered_map<char, int>> const & colLetterCntMap,
            int wordIdx, int targetIdx) {
        int const wordLen = words.back().size();
        int const targetSize = target.size();
        if (targetIdx == targetSize) {
            return 1;
        }

        if (wordIdx == wordLen) {
            return 0;
        }

        if (INIT_FLAG != dpMemo[wordIdx][targetIdx]) {
            return dpMemo[wordIdx][targetIdx];
        }

        // not using this character, we just only skip only once.
        int ans = dfs(words, target, dpMemo, colLetterCntMap, wordIdx + 1, targetIdx) % MOD;

        int cntTargetLetter = 0;
        int curAns = 0;

        char const & targetLetter = target[targetIdx];
        if (colLetterCntMap[wordIdx].find(targetLetter) != colLetterCntMap[wordIdx].end()) {
            curAns = dfs(words, target, dpMemo, colLetterCntMap, wordIdx + 1, targetIdx + 1);
            cntTargetLetter = colLetterCntMap[wordIdx].at(targetLetter);
            ans += static_cast<long long>(curAns) * cntTargetLetter % MOD;
        }
        return dpMemo[wordIdx][targetIdx] = ans % MOD;
    }

private:
    static int const MOD = 1e9 + 7;
    int const INIT_FLAG = -1;
};
