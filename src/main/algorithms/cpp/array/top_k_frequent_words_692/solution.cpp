#include "../../head.h"


// #define DEBUG
class Solution {
public:
    std::vector<std::string> topKFrequent(std::vector<std::string> const & words, int k) {
        std::unordered_map<std::string, int> wordsCnt;
        std::unordered_map<std::string, std::list<std::string>::iterator> wordIt;
        std::map<int, std::list<std::string>> freqs;
        for (std::vector<std::string>::const_iterator it = words.begin(); it != words.end(); it++) {
            #ifdef DEBUG
            std::cout << *it << "\t";
            #endif
            int curCnt = wordsCnt[*it]++;
            if (0 < curCnt) {
                freqs[curCnt].erase(wordIt[*it]);
            }
            freqs[wordsCnt[*it]].emplace_front(*it);
            wordIt[*it]  = freqs[wordsCnt[*it]].begin();
        }
        std::vector<std::string> ans;
        for (auto /*std::map<int, std::list<std::string>::reverse_iterator*/it = freqs.rbegin(); it != freqs.rend(); it++) {
            std::vector<std::string> curAns;
            for (auto const & word : it->second) {
                curAns.emplace_back(word);
            }
            std::sort(curAns.begin(), curAns.end());
            for (auto const & word : curAns) {
                ans.emplace_back(word);
                if (ans.size() == k) {
                    return ans;
                }
            }
        }
        return ans;
    }
};

// #define DEBUG
class Solution {
public:
    std::vector<std::string> topKFrequent(std::vector<std::string> const & words, int k)  {
        // plagiarizing idea from https://leetcode.com/problems/top-k-frequent-words/discuss/108366/O(nlog(k))-Priority-Queue-C%2B%2B-code
        auto cmp = [&] (std::pair<string, int> const & left, std::pair<string, int> const & right) {
            // minHeap compare function
            return left.second > right.second || (left.second == right.second && left.first <= right.first);
        };
        typedef std::priority_queue<std::pair<std::string, int>, std::vector<std::pair<std::string, int>>, decltype(cmp)> MinHeap;
        MinHeap minHeap(cmp);

        std::unordered_map<std::string, int> wordsCnt;
        for (auto const & word : words) {
            wordsCnt[word]++;
        }
        for (auto const & [word, freq] : wordsCnt) {
            minHeap.emplace(std::make_pair(word, freq));
            if (minHeap.size() > k) {
                minHeap.pop();
            }
        }
        std::vector<std::string> ans(k);
        while (!minHeap.empty()) {
            auto const & ele = minHeap.top();
            ans[--k] = ele.first;
            minHeap.pop();
        }
        return ans;
    }

};
