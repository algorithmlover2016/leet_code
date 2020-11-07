#include "../../head.h"


class SolutionTLE {
public:
    std::vector<int> findNumOfValidWords(std::vector<std::string> const & words,
            std::vector<std::string> const & puzzles) {
        std::vector<int> wordsMap(words.size(), 0);
        std::vector<int> puzzlesMap(puzzles.size(), 0);
        std::vector<int> ans(puzzles.size(), 0);
        getIntegerMap(words, wordsMap);
        std::vector<int> puzzlesFirstMap = getIntegerMap(puzzles, puzzlesMap);
        for (int index = 0; index < wordsMap.size(); index++) {
            for (int pIndex = 0; pIndex < puzzlesMap.size(); pIndex++) {
                // std::cout << wordsMap[index] << "\t" << puzzlesMap[pIndex] << "\t";
                if ((wordsMap[index] | puzzlesMap[pIndex]) == puzzlesMap[pIndex] &&
                        (puzzlesFirstMap[pIndex] | wordsMap[index]) == wordsMap[index]) {
                    // std::cout << "add one" << "\t";
                    ans[pIndex]++;
                }
            }
            // std::cout << "\n";
        }
        return ans;


    }
    std::vector<int> getIntegerMap(std::vector<std::string> const & words,
            std::vector<int> & wordsMap) {
        std::vector<int> ans(words.size(), 0);
        for (int index = 0; index < words.size(); index++) {
            for (char c : words[index]) {
                wordsMap[index] |= (1 << (c - 'a'));
            }
            ans[index] = (1 << (words[index][0] - 'a'));
            // std::cout << wordsMap[index] << "\t" << ans[index] << "\n";
        }
        return ans;
    }
};

class SolutionTLEHashMap {
public:
    std::vector<int> findNumOfValidWords(std::vector<std::string> const & words,
            std::vector<std::string> const & puzzles) {
        std::vector<int> puzzlesMap(puzzles.size(), 0);
        std::unordered_map<int, int> wordsMergeMap;

        getIntegerMap(words, wordsMergeMap);
        std::vector<int> puzzlesFirstMap = getIntegerMap(puzzles, puzzlesMap);

        std::vector<int> ans(puzzles.size(), 0);
        for (std::unordered_map<int, int>::iterator it = wordsMergeMap.begin(); it != wordsMergeMap.end(); it++) {
            for (int pIndex = 0; pIndex < puzzlesMap.size(); pIndex++) {
                // std::cout << wordsMap[index] << "\t" << puzzlesMap[pIndex] << "\t";
                if ((it->first | puzzlesMap[pIndex]) == puzzlesMap[pIndex] &&
                        (puzzlesFirstMap[pIndex] | it->first) == it->first) {
                    // std::cout << "add one" << "\t";
                    ans[pIndex] += it->second;
                }
            }
            // std::cout << "\n";
        }
        return ans;


    }
    std::vector<int> getIntegerMap(std::vector<std::string> const & words,
            std::vector<int> & wordsMap) {
        std::vector<int> ans(words.size(), 0);
        for (int index = 0; index < words.size(); index++) {
            for (char c : words[index]) {
                wordsMap[index] |= (1 << (c - 'a'));
            }
            ans[index] = (1 << (words[index][0] - 'a'));
            // std::cout << wordsMap[index] << "\t" << ans[index] << "\n";
        }
        return ans;
    }

    void getIntegerMap(std::vector<std::string> const & words,
            std::unordered_map<int, int> & wordsMergeMap) {
        for (int index = 0; index < words.size(); index++) {
            int cnt = 0;
            for (char c : words[index]) {
                cnt |= (1 << (c - 'a'));
            }
            wordsMergeMap[cnt] += 1;
        }
    }
};

class SolutionBitCombination {
public:
    std::vector<int> findNumOfValidWords(std::vector<std::string> const & words,
            std::vector<std::string> const & puzzles) {
        std::vector<int> puzzlesMap(puzzles.size(), 0);
        std::unordered_map<int, int> wordsMergeMap;

        getIntegerMap(words, wordsMergeMap);
        std::vector<int> puzzlesFirstMap = getIntegerMap(puzzles, puzzlesMap);

        std::vector<int> ans(puzzles.size(), 0);
        for (int pIndex = 0; pIndex < puzzlesMap.size(); pIndex++) {
            int mask = puzzlesMap[pIndex];
            while (mask) {
                if (wordsMergeMap.find(mask) != wordsMergeMap.end() &&
                    ((mask | puzzlesFirstMap[pIndex]) == mask)) {
                    ans[pIndex] += wordsMergeMap[mask];
                }
                mask = (mask - 1 ) & puzzlesMap[pIndex];
            }
        }
        return ans;


    }
    std::vector<int> getIntegerMap(std::vector<std::string> const & words,
                                   std::vector<int> & wordsMap) {
        std::vector<int> ans(words.size(), 0);
        for (int index = 0; index < words.size(); index++) {
            for (char c : words[index]) {
                wordsMap[index] |= (1 << (c - 'a'));
            }
            ans[index] = (1 << (words[index][0] - 'a'));
        }
        return ans;
    }

    void getIntegerMap(std::vector<std::string> const & words,
                       std::unordered_map<int, int> & wordsMergeMap) {
        for (int index = 0; index < words.size(); index++) {
            int cnt = 0;
            for (char c : words[index]) {
                cnt |= (1 << (c - 'a'));
            }
            wordsMergeMap[cnt] += 1;
        }
    }
};
