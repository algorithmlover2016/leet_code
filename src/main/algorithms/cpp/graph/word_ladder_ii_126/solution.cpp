#include "../../head.h"

class SolutionTimeLimit {
public:
    std::vector<std::vector<std::string>> findLadders(std::string const & beginWord,
            std::string const & endWord, std::vector<std::string> const & wordList) {
        std::unordered_map<std::string, std::list<std::string>> graphDict;
        std::unordered_map<std::string, int> shortestDistance;

        std::vector<std::string> oneSolution;
        std::vector<std::vector<std::string>> res;

        BFSConstructGraph(beginWord, endWord, wordList, graphDict, shortestDistance);
        DFS(beginWord, endWord, graphDict, shortestDistance, oneSolution, res);

        return res;
    }

    void BFSConstructGraph(std::string const & beginWord, std::string const & endWord,
            std::vector<std::string> const & wordList,
            std::unordered_map<std::string, std::list<std::string>> & graphDict,
            std::unordered_map<std::string, int> & shortestDistance) {
        std::set<string> wordSet(wordList.begin(), wordList.end());
        std::queue<string> bfsIter;

        bfsIter.emplace(beginWord);
        shortestDistance.emplace(beginWord, 0);
        while(!bfsIter.empty()) {
            int bfsIterSize = bfsIter.size();
            for (int index = 0; index < bfsIterSize; index++) {
                bool findEnd = false;

                std::string cur = bfsIter.front(); bfsIter.pop();
                int curDis = shortestDistance[cur];
                // std::cout << "cur: " << cur << " curDis: " << curDis << "\n";
                std::list<string> neighbors = getNeighbors(cur, wordSet);
                graphDict[cur] = neighbors;
                for (auto const & neighbor : neighbors) {
                    // if neighbor exists in shortestDistance, then this distance is larger than or equal to shortestDistance[neighbor];
                    // because the start elements is the only one, and the node have been visit, and now it be visit by path that go through redundant node
                    if (shortestDistance.find(neighbor) == shortestDistance.end()) {
                        bfsIter.emplace(neighbor);
                        shortestDistance[neighbor] = curDis + 1; // alse mark the node is visited
                        if (neighbor == endWord) {
                            findEnd = true;
                        }
                    }
                }
                if (findEnd) {
                    break;
                }
            }
        }
    }

    std::list<std::string> getNeighbors(std::string const & word, std::set<string> const & wordSet) {
        std::list<std::string> res;
        for (int index = 0; index < word.size(); index++) {
            for (char start = 'a'; start <= 'z'; start++) {
                if (word[index] == start) {
                    continue;
                }
                std::string newWord(word);
                newWord[index] = start;
                if (wordSet.find(newWord) != wordSet.end()) {
                    res.emplace_back(newWord);
                }
            }
        }
        return res;
    }

    void DFS(std::string const & beginWord, std::string const & endWord,
            std::unordered_map<std::string, std::list<std::string>> const & graphDict,
            std::unordered_map<std::string, int> const & shortestDistance,
            std::vector<std::string> & oneSolution,
            std::vector<std::vector<std::string>> & res) {
        oneSolution.emplace_back(beginWord);
        if (beginWord == endWord) {
            res.emplace_back(oneSolution);
        } else {
            int neighborDis = shortestDistance.at(beginWord) + 1;
            for (auto const & neighbor : graphDict.at(beginWord)) {
                if (shortestDistance.at(neighbor) == neighborDis) {
                    DFS(neighbor, endWord, graphDict, shortestDistance, oneSolution, res);
                }
            }
        }
        oneSolution.pop_back();
    }
};

// static int io_opt = []() { ios::sync_with_stdio(false); return 0; }();
class Solution {
public:
    std::vector<std::vector<std::string>> findLadders(std::string const & beginWord, std::string const & endWord,
            std::vector<std::string> const & wordList) {
        if (beginWord == endWord) {
            return { {beginWord} };
        }


        std::unordered_set<std::string> wordDict(wordList.begin(), wordList.end());
        if (!wordDict.count(endWord)) {
            return {};
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
            return {};
        }
        std::vector<std::string> cur = { beginWord };
        std::vector<std::vector<std::string>> res;
        dfs(endWord, cur, res, childMap);
        return res;
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

class SolutionNoDFS {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, unordered_set<string> &wordList) {
        //very interesting problem
        //It can be solved with standard BFS. The tricky idea is doing BFS of paths instead of words!
        //Then the queue becomes a queue of paths.
        vector<vector<string>> ans;
        queue<vector<string>> paths;
        wordList.insert(endWord);
        paths.push({beginWord});
        int level = 1;
        int minLevel = INT_MAX;

        //"visited" records all the visited nodes on this level
        //these words will never be visited again after this level
        //and should be removed from wordList. This is guaranteed
        // by the shortest path.
        unordered_set<string> visited;

        while (!paths.empty()) {
            vector<string> path = paths.front();
            paths.pop();
            if (path.size() > level) {
                //reach a new level
                for (string w : visited) wordList.erase(w);
                visited.clear();
                if (path.size() > minLevel)
                    break;
                else
                    level = path.size();
            }
            string last = path.back();
            //find next words in wordList by changing
            //each element from 'a' to 'z'
            for (int i = 0; i < last.size(); ++i) {
                string news = last;
                for (char c = 'a'; c <= 'z'; ++c) {
                    news[i] = c;
                    if (wordList.find(news) != wordList.end()) {
                    //next word is in wordList
                    //append this word to path
                    //path will be reused in the loop
                    //so copy a new path
                        vector<string> newpath = path;
                        newpath.push_back(news);
                        visited.insert(news);
                        if (news == endWord) {
                            minLevel = level;
                            ans.push_back(newpath);
                        }
                        else
                            paths.push(newpath);
                    }
                }
            }
        }
        return ans;
    }
};
