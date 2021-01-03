#include "../../head.h"



#define DEBUG
class Solution {
private:
    static std::set<char> rangeSet;

private:

    template<bool caseSensitive = false>
    static char toAsterisk(char const c) {
        char cc = caseSensitive ? c : tolower(c);
        if (rangeSet.find(cc) != rangeSet.end()) {
#ifdef DEBUG
        std::cout << "replace: " << cc << "\n";
#endif
            return '*';
        } else {
            return c;
        }
    }

public:
    std::vector<std::string> spellchecker(std::vector<std::string> const & wordList,
            std::vector<std::string> const & queries) {

        if (wordList.empty() || queries.empty()) {
            return {};
        }
        std::set<std::string> wordSet;
        std::unordered_map<std::string, std::string> wordMaps;

        for (auto const & word : wordList) {
            wordSet.insert(word);

            std::string wordLowcase(word);
            // std::transform(word.begin(), word.end(), wordLowcase.begin(), tolower);
            std::transform(word.begin(), word.end(), wordLowcase.begin(), tolower);
            if (wordMaps.find(wordLowcase) == wordMaps.end()) {
#ifdef DEBUG
                std::cout << "add MapKV: " << wordLowcase << ",\t" << word << "\n";
#endif
                wordMaps[wordLowcase] = word;
            }

            std::string wordAsterisk(wordLowcase);
            std::transform(wordLowcase.begin(), wordLowcase.end(), wordAsterisk.begin(), toAsterisk<>);
            if (wordMaps.find(wordAsterisk) == wordMaps.end()) {
#ifdef DEBUG
                std::cout << "add MapKV: " << wordAsterisk << ",\t" << word << "\n";
#endif
                wordMaps[wordAsterisk] = word;
            }

        }

        std::vector<std::string> ans;
        for (auto const & query : queries) {
            if (wordSet.find(query) != wordSet.end()) {
                ans.emplace_back(query);
                continue;
            }
            std::string queryLowcase(query);
            std::transform(query.begin(), query.end(), queryLowcase.begin(), tolower);
            if (wordMaps.find(queryLowcase) != wordMaps.end()) {
                ans.emplace_back(wordMaps[queryLowcase]);
                continue;
            }

            std::string queryAsterisk(queryLowcase);
            std::transform(queryLowcase.begin(), queryLowcase.end(), queryAsterisk.begin(), toAsterisk<>);
            if (wordMaps.find(queryAsterisk) != wordMaps.end()) {
                ans.emplace_back(wordMaps[queryAsterisk]);
            } else {
                ans.emplace_back("");
            }
        }
        return ans;
    }
};

std::set<char> Solution::rangeSet{{'a', 'e', 'i', 'o', 'u'}};

class SolutionBetterRunTime {
public:
    unordered_map<string, string> regexMap;
    unordered_map<string, bool> seen;
    unordered_map<string, string> smallcase;
    bool isVowel(char c) {
        if (c == 'a' || c == 'A') return true;
        if (c == 'e' || c == 'E') return true;
        if (c == 'i' || c == 'I') return true;
        if (c == 'o' || c == 'O') return true;
        if (c == 'u' || c == 'U') return true;
        return false;
        
    }
    void to_lower(string &s) {
        for(auto& c : s){
            c = tolower(c);
        }
    }
    vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries) {
        for (string word : wordlist) {
            string tmp = word;
            to_lower(tmp);
            for (int i = 0; i < word.size(); i++) {
                if (isVowel(tmp[i])) tmp[i] = '*';
            }
            //cout << word<< " "<<tmp<< "\t";
            if (!regexMap.count(tmp)) regexMap[tmp] = word;
            seen[word] = true;
            tmp = word;
            to_lower(tmp);
            //cout << tmp<<"\n";
            if (!smallcase.count(tmp))smallcase[tmp] = word;
        }
        vector<string> ret;
        for (string query : queries) {
            string tmp = query;
            to_lower(tmp);
            for (int i = 0; i < query.size(); i++) {
                if (isVowel(tmp[i])) tmp[i]  = '*';
            }
            if (!regexMap.count(tmp)) ret.push_back("");
            else {
                if (seen.count(query)) ret.push_back(query);
                else {
                    to_lower(query);
                    if (smallcase.count(query)) ret.push_back(smallcase[query]);
                    else ret.push_back(regexMap[tmp]);
                }
            }
        }
        return ret;
    }
};

int main() {
    Solution obj;


    std::vector<std::string> const wordList{{"KiTe","kite","hare","Hare"}};

    std::vector<std::string> const queries{{"kite","Kite","KiTe","Hare","HARE","Hear","hear","keti","keet","keto"}};
    std::vector<std::string> ans = obj.spellchecker(wordList, queries);
    for (auto const & str : ans) {
        std::cout << "\"" << str << "\",\t";
    }
    std::cout << "\n";
    return 0;
}

/*
   // self implement transform
   #define DEBUG
class Solution {
private:
    static std::set<char> rangeSet;

private:

    template<bool caseSensitive = false>
    static char toAsterisk(char const c) {
        char cc = caseSensitive ? c : tolower(c);
        if (rangeSet.find(cc) != rangeSet.end()) {
#ifdef DEBUG
        std::cout << "replace: " << cc << "\n";
#endif
            return '*';
        } else {
            return c;
        }
    }

public:
    std::vector<std::string> spellchecker(std::vector<std::string> const & wordList,
            std::vector<std::string> const & queries) {

        if (wordList.empty() || queries.empty()) {
            return {};
        }
        std::set<std::string> wordSet;
        std::unordered_map<std::string, std::string> wordMaps;

        for (auto const & word : wordList) {
            wordSet.insert(word);

            std::string wordLowcase(word);
            // std::transform(word.begin(), word.end(), wordLowcase.begin(), tolower);
            std::transform(word.begin(), word.end(), wordLowcase.begin(), tolower);
            if (wordMaps.find(wordLowcase) == wordMaps.end()) {
#ifdef DEBUG
                std::cout << "add MapKV: " << wordLowcase << ",\t" << word << "\n";
#endif
                wordMaps[wordLowcase] = word;
            }

            std::string wordAsterisk(wordLowcase);
            std::transform(wordLowcase.begin(), wordLowcase.end(), wordAsterisk.begin(), toAsterisk<>);
            if (wordMaps.find(wordAsterisk) == wordMaps.end()) {
#ifdef DEBUG
                std::cout << "add MapKV: " << wordAsterisk << ",\t" << word << "\n";
#endif
                wordMaps[wordAsterisk] = word;
            }

        }

        std::vector<std::string> ans;
        for (auto const & query : queries) {
            if (wordSet.find(query) != wordSet.end()) {
                ans.emplace_back(query);
                continue;
            }
            std::string queryLowcase(query);
            std::transform(query.begin(), query.end(), queryLowcase.begin(), tolower);
            if (wordMaps.find(queryLowcase) != wordMaps.end()) {
                ans.emplace_back(wordMaps[queryLowcase]);
                continue;
            }

            std::string queryAsterisk(queryLowcase);
            std::transform(queryLowcase.begin(), queryLowcase.end(), queryAsterisk.begin(), toAsterisk<>);
            if (wordMaps.find(queryAsterisk) != wordMaps.end()) {
                ans.emplace_back(wordMaps[queryAsterisk]);
            } else {
                ans.emplace_back("");
            }
        }
        return ans;
    }
};

std::set<char> Solution::rangeSet{{'a', 'e', 'i', 'o', 'u'}};
   */
