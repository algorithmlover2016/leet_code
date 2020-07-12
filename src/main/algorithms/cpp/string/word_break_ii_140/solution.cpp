#include "../../head.h"


class SolutionTLE {
public:
    std::vector<std::string> wordBreak(std::string const & s, std::vector<std::string> const & wordDict) {
        std::vector<std::string> res;
        if (s.empty()) {
            return res;
        }
        if (wordDict.empty()) {
            return res;
        }
        for (auto const & word : wordDict) {
            fill(word);
        }
        find(s, 0, 0, "", res);
        return res;
    }
private:
    void fill(std::string const & word) {
        if (word.empty()) {
            return ;
        }
        Node * node = &_root;
        for (char const c : word) {
            if (nullptr == node->_c[c - 'a']) {
                node->_c[c - 'a'] = new Node();
            }
            node = node->_c[c - 'a'];
        }
        node->stop = true;
    }

    void find(std::string const & s, int start, int cnt, std::string curRes, std::vector<std::string> & res) {
        if (start >= s.size()) {
            if (cnt > 0) {
                int moveBankLeftSize = curRes.size() - 1;
                res.emplace_back(curRes.substr(0, moveBankLeftSize));
            }
            return ;
        }
        Node * node = &_root;
        for (; start < s.size(); start++) {
            if (nullptr == node->_c[s[start] - 'a']) {
                return ;
            }
            node = node->_c[s[start] - 'a'];
            curRes += s[start];
            if (node->stop) {
                find(s, start + 1, cnt + 1, curRes + " ", res);
            }
        }
    }

private:
    static int const LETTER_CNT = 26;
    struct Node {
        std::array<Node*, LETTER_CNT> _c;
        bool stop {false};
    };
    Node _root;
};

class Solution {
    std::unordered_map<std::string, std::vector<std::string>> m;

    std::vector<std::string> combine(std::string const & word, std::vector<std::string> prev){
        for(int i=0;i<prev.size();++i){
            prev[i]+=" "+word;
        }
        return prev;
    }

public:
    std::vector<std::string> wordBreak(string const & s, std::vector<std::string> const & wordDict) {
        std::unordered_set<std::string> dict(wordDict.begin(), wordDict.end());
        return wordBreak(s, dict);
    }
    std::vector<std::string> wordBreak(string const & s, std::unordered_set<std::string> const & dict) {
        if(m.count(s)) return m[s]; //take from memory
        std::vector<std::string> result;
        if(dict.count(s)){ //a whole string is a word
            result.push_back(s);
        }
        for(int i=1;i<s.size();++i){
            std::string const & word=s.substr(i);
            if(dict.count(word)){
                string const rem=s.substr(0,i);
                std::vector<std::string> prev=combine(word,wordBreak(rem,dict));
                result.insert(result.end(),prev.begin(), prev.end());
            }
        }
        m[s]=result; //memorize
        return result;
    }
};

class Solution {

    std::unordered_map<std::string, std::vector<std::string>> memo;
public:
    std::vector<std::string> wordBreak(std::string const & s, std::vector<std::string> const & wordDict) {
        std::vector<std::string> res;
        if (s.empty()) {
            return res;
        }
        if (wordDict.empty()) {
            return res;
        }
        for (auto const & word : wordDict) {
            fill(word);
        }
        for (int index = s.size() - 1; index >= 0; index--) {
            res.clear();
            find(s.substr(index), "", res);
            memo[s.substr(index)] = res;

        }
        return memo[s];
    }
private:
    void find(std::string const & s, std::string curRes, std::vector<std::string> & res) {
        if (memo.find(s) != memo.end()) {
            curRes = curRes.substr(1);
            for (auto & ele : memo[s]) {
                res.emplace_back(curRes + " " + ele);
                // std::cout << "ele: " << ele << "\t";
            }
            return;
        }
        if (s.empty()) {
            // std::cout << "emplace: " << curRes.substr(1) << "\t";
            res.emplace_back(curRes.substr(1));
            return ;
        }
        Node * node = &_root;
        for (int start = 0; start < s.size(); start++) {
            if (nullptr == node->_c[s[start] - 'a']) {
                return ;
            }
            node = node->_c[s[start] - 'a'];
            if (node->stop) {
                // std::cout << "cut: " << curRes + " " + s.substr(0, start + 1) << "\tleft: " << s.substr(start + 1) << "\t";
                find(s.substr(start + 1), curRes + " " + s.substr(0, start + 1), res);
            }
        }
    }

    void fill(std::string const & word) {
        if (word.empty()) {
            return ;
        }
        Node * node = &_root;
        for (char const c : word) {
            if (nullptr == node->_c[c - 'a']) {
                node->_c[c - 'a'] = new Node();
            }
            node = node->_c[c - 'a'];
        }
        node->stop = true;
    }

    private:
    static int const LETTER_CNT = 26;
    struct Node {
        std::array<Node*, LETTER_CNT> _c;
        bool stop {false};
    };
    Node _root;
};
