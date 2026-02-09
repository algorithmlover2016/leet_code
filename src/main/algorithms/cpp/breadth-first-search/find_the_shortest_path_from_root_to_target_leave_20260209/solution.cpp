#include <string>
#include <vector>
#include <unordered_set>
#include <queue>

class Solution {
public:
    int findShortestSteps(std::string const & begin, std::string const & target, std::vector<std::string> const & wordlist) {
        std::unordered_set<std::string> wordSet(wordlist.begin(), wordlist.end());
        
        // Target must be in the dictionary
        if (!wordSet.count(target)) {
            return 0;
        }

        if (begin.size() != target.size()) {
            return 0;
        }

        if (begin == target) {
            return 1;
        }

        // BFS Queue: store {currentWord, currentStepCount}
        std::queue<std::pair<std::string, int>> q;
        q.push({begin, 1});
        
        // Remove begin from set to avoid visiting it again
        if (wordSet.count(begin)) {
            wordSet.erase(begin);
        }

        while (!q.empty()) {
            std::pair<std::string, int> curr = q.front();
            q.pop();
            std::string word = curr.first;
            int steps = curr.second;

            // Try changing each character
            for (size_t i = 0; i < word.length(); ++i) {
                char original = word[i];
                for (char c = 'a'; c <= 'z'; ++c) {
                    if (c == original) continue;
                    
                    word[i] = c;
                    
                    if (word == target) {
                        return steps + 1;
                    }

                    if (wordSet.count(word)) {
                        wordSet.erase(word); // Mark as visited by removing from dictionary
                        q.push({word, steps + 1});
                    }
                }
                word[i] = original; // Restore for next iteration
            }
        }

        return 0; // No path found
    }
};