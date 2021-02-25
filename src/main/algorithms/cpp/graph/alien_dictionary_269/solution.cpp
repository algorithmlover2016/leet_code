#include "../../head.h"

#define TEST_MAIN
class Solution {
public:
    std::string alienOrder(std::vector<std::string> const & words) {
        // plagiarizing from https://youtu.be/lyHgGZbLriU
        std::string ans;
        if (words.empty()) {
            return ans;
        }
        std::unordered_map<char, std::unordered_set<char>> graph;
        std::unordered_set<char> letters;
        std::unordered_map<int, int> indegree;
        for (auto const & word : words) {
            for (auto const c : word) {
                // first statistic the total number of all letters
                letters.insert(c);
            }
        }

        int const allLettersNum = letters.size();
        
        for (int idx = 0; idx < words.size() - 1; idx++) {
            for (int later = idx + 1; later < words.size(); later++) {
                std::string const & first = words[idx];
                std::string const & second = words[later];
                int fIdx = 0, sIdx = 0;
                bool found = false;
                while (fIdx < first.size() && sIdx < second.size()) {
                    char const fC = first[fIdx];
                    char const sC = second[sIdx];
                    if (fC == sC) {
                        fIdx++;
                        sIdx++;
                        continue;
                    }
                    if (graph[fC].insert(sC).second) {
                        // sC is after the letter of fC
                        indegree[sC]++;
                        // sC can't be the first element
                        letters.erase(sC);
                    }
                    found = true;
                    break;
                }
                if (!found && second.size() < first.size()) {
                    // abc < ab is exception case
                    return ans;
                }
            }
        }

        std::queue<char> que;
        for (char const c : letters) {
            que.emplace(c);
        }

        while (!que.empty()) {
            char const c = que.front(); que.pop();
            ans += c;
            for (char const sub : graph[c]) {
                if (0 == --indegree[sub]) {
                    que.emplace(sub);
                }
            }
        }
        return ans.size() == allLettersNum ? ans : "";
    }

};

#ifdef TEST_MAIN
#define PRINT_SCREEN
int main() {
    std::vector<std::string> words{{"wrt", "wrf", "er", "ett", "rftt"}};
    Solution obj;
    std::string ans("wertf");
    std::string outAns = obj.alienOrder(words);
#ifdef PRINT_SCREEN
    std::cout << outAns << "\n";
#endif
    assert(ans == outAns);

    std::vector<std::string> words1 = {{"z", "x", "z"}};
    std::string ans1 = "";
    std::string outAns1 = obj.alienOrder(words1);
#ifdef PRINT_SCREEN
    std::cout << outAns1 << "\n";
#endif
    assert(ans1 == outAns1);

#ifdef PRINT_SCREEN
    std::cout << std::endl; 
#endif
}
#endif

