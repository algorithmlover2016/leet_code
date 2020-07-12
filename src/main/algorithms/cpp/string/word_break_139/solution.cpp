#include "../../head.h"


class SolutionTLE {
    std::unordered_map<std::string, bool> m;

public:
    bool wordBreak(string const & s, std::vector<std::string> const & wordDict) {
        std::unordered_set<std::string> dict(wordDict.begin(), wordDict.end());
        return wordBreak(s, dict);
    }
    bool wordBreak(string const & s, std::unordered_set<std::string> const & dict) {
        if(m.count(s)) return m[s]; //take from memory
        bool res = false;
        if(dict.count(s)){ //a whole string is a word
            return m[s]= true; //memorize
        }
        for(int i=1;i<s.size();++i){
            std::string const & word=s.substr(i);
            if(dict.count(word)){
                string const rem=s.substr(0,i);
                if (wordBreak(rem, dict)) {
                    return m[s] = true;
                }
            }
        }
        return false;
    }
};

class Solution {
public:
    bool wordBreak(string const & s, std::vector<std::string> const & wordDict) {
        if (s.empty()) {
            return true;
        }
        if (wordDict.empty()) {
            return false;
        }
        std::unordered_set<std::string> dicts(wordDict.begin(), wordDict.end());
        std::vector<bool> dp(s.size() + 1, false);
        dp[0] = true;
        for (int index = 1; index <= s.size(); index++) {
            for (int inner = index - 1; inner >= 0; inner--) {
                if (!dp[inner]) {
                    continue;
                }
                std::string res = s.substr(inner, index - inner);
                if (dicts.find(res) != dicts.end()) {
                    dp[index] = true;
                    break;
                }
            }
        }
        return dp[s.size()];
    }
};
