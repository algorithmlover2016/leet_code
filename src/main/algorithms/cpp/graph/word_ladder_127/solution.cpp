#include "../../head.h"

class Solution {
public:
    int ladderLength(std::string beginWord, std::string endWord, std::vector<std::string>& wordList) {
        std::unordered_set<std::string> dict(wordList.begin(),wordList.end());

        if(!dict.count(endWord)) return 0;

        std::unordered_set<std::string> s1({beginWord}), s2({endWord});

        int res = 0;

        while(!s1.empty() && !s2.empty()){
            res++;

            if(s1.size() > s2.size()) {
                swap(s1, s2);
            }

            std::unordered_set<std::string> s3;

            for(std::string cur: s1){
                for(char & c: cur){
                    char tmp = c;
                    for(int i = 0; i < 26; i++){
                        c = i + 'a';

                        if(s2.count(cur)) return res + 1;
                        if(dict.count(cur)) {
                            dict.erase(cur);
                            s3.insert(cur);
                        }
                    }

                    c = tmp;
                }
            }
            std::swap(s1, s3);
        }
        return 0;
    }
};

class SolutionII126 {
public:
    int ladderLength(std::string const & beginWord, std::string const & endWord,
            std::vector<std::string> const & wordList) {
        // plagiarizing from 126. Word Ladder II. answers
        if (beginWord == endWord) {
            return 1;
        }


        std::unordered_set<std::string> wordDict(wordList.begin(), wordList.end());
        if (!wordDict.count(endWord)) {
            return 0;
        }

        size_t wordLen = beginWord.size();
        std::unordered_map<std::string, std::vector<std::string>> childMap;
        std::unordered_set<std::string> q1 = { beginWord };
        std::unordered_set<std::string> q2 = { endWord };

        bool found = false;
        bool reverse = false;
        while (!q1.empty() && !q2.empty() && !found) {

            // remove cur level node from wordDict
            if (q1.size() > q2.size()) {
                std::swap(q1, q2);
                reverse = !reverse;
            }

            for (auto & w : q1) {
                wordDict.erase(w);
            }

            // expand cur level node generate childMap
            std::unordered_set<std::string> qTmp;
            for (const auto & curWord : q1) {
                std::string newWord = curWord;
                for (size_t j = 0; j < wordLen; ++j) {
                    char oldChar = curWord[j];
                    for (char c = 'a'; c <= 'z'; ++c) {
                        if (c == oldChar) continue;
                        newWord[j] = c;
                        if (wordDict.count(newWord)) {
                            if (q2.count(newWord)) {
                                found = true;  // in this case no need to expand
                            } else {
                                qTmp.insert(newWord);
                            }
                            // update childMap
                            if (!reverse) {
                                childMap[curWord].push_back(newWord);
                            } else {
                                childMap[newWord].push_back(curWord);
                            }
                        }
                    }
                    newWord[j] = oldChar;
                }
            }  // expand done

            std::swap(q1, qTmp);
        }
        if (!found) {
            return 0;
        }
        std::vector<std::string> cur = { beginWord };
        std::vector<std::vector<std::string>> res;
        dfs(endWord, cur, res, childMap);
        return res[0].size();
    }

    void dfs(string const & endWord, std::vector<std::string> & cur,
            std::vector<std::vector<std::string>> & res,
            std::unordered_map<std::string,
            std::vector<std::string>> const & childMap) {
        if (cur.back() == endWord) {
            res.push_back(cur);
            return;
        }
        std::string const & curWord = cur.back();
        auto iter = childMap.find(curWord);
        if (iter == childMap.end()) {  // check if curWord has child
            return;
        }
        for (const auto & w : iter->second) {
            cur.push_back(w);
            dfs(endWord, cur, res, childMap);
            cur.pop_back();
        }
    }
};
