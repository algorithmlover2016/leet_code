#include "../../head.h"


// #define DEBUG
class SolutionPlaceError {
public:
    std::string reorganizeString(std::string const & S) {
        int const SSize = S.size();
        int mostLen = (SSize + 1) / 2; // A + A - 1 <= SSize
        std::unordered_map<char, int> lettersCnt;
        for (auto const c : S) {
            if (++lettersCnt[c] > mostLen) {
                return "";
            }
        }
        auto cmp = [&] (std::pair<char, int> const & left, std::pair<char, int> const & right) {
            return left.second <= right.second;
        };
        typedef std::priority_queue<std::pair<char, int>, std::vector<std::pair<char, int>>, decltype(cmp)> MaxHeap;
        
        MaxHeap maxHeap(cmp);
        
        for (auto const & [c, cnt] : lettersCnt) {
            maxHeap.emplace(std::make_pair(c, cnt));
        }
        #ifdef DEBUG
        std::cout << maxHeap.size() << "\t" << SSize << "\n";
        #endif
        std::string ans(SSize, '#');
        while (!maxHeap.empty()) {
            auto & ele = maxHeap.top();
            char c = ele.first;
            int cnt = ele.second;
            maxHeap.pop();
            int idx = 0;
            while (idx < SSize && ans[idx] != '#') {
                idx++;
            }
            for (int num = 0; num < cnt; num++) {
                ans[idx] = c;
                idx += 2;
            }
            #ifdef DEBUG
            std::cout << idx << "\t" << ans << "\n";
            #endif
        }
        return ans;
    }
};

// #define DEBUG
class Solution {
public:
    std::string reorganizeString(std::string const & S) {
        // plagiarizing idea from https://leetcode.com/problems/reorganize-string/discuss/232469/Java-No-Sort-O(N)-0ms-beat-100
        int const SSize = S.size();
        int mostLen = (SSize + 1) / 2; // A + A - 1 <= SSize
        std::unordered_map<char, int> lettersCnt;
        for (auto const c : S) {
            if (++lettersCnt[c] > mostLen) {
                return "";
            }
        }
        auto cmp = [&] (std::pair<char, int> const & left, std::pair<char, int> const & right) {
            return left.second <= right.second;
        };
        typedef std::priority_queue<std::pair<char, int>, std::vector<std::pair<char, int>>, decltype(cmp)> MaxHeap;

        MaxHeap maxHeap(cmp);

        for (auto const & [c, cnt] : lettersCnt) {
            maxHeap.emplace(std::make_pair(c, cnt));
        }
        #ifdef DEBUG
        std::cout << maxHeap.size() << "\t" << SSize << "\n";
        #endif

        int idx = 0;
        std::string ans(SSize, '#');
        while (!maxHeap.empty()) {
            auto & ele = maxHeap.top();
            char c = ele.first;
            int cnt = ele.second;
            maxHeap.pop();
            while (idx < SSize && ans[idx] != '#') {
                idx++;
            }
            for (int num = 0; num < cnt; num++) {
                ans[idx] = c;
                idx += 2;
                if (idx >= SSize) {
                    idx = 1;
                }
            }
            #ifdef DEBUG
            std::cout << idx << "\t" << ans << "\n";
            #endif
        }
        return ans;

    }
};

// #define DEBUG
class Solution {
public:
    std::string reorganizeString(std::string const & S) {
        // plagiarizing from https://leetcode.com/problems/reorganize-string/discuss/232469/Java-No-Sort-O(N)-0ms-beat-100
        int const SSize = S.size();
        int mostLen = (SSize + 1) / 2; // A + A - 1 <= SSize
        std::unordered_map<char, int> lettersCnt;
        for (auto const c : S) {
            if (++lettersCnt[c] > mostLen) {
                return "";
            }
        }

        int maxCnt = 0;
        char letter = ' ';
        for (auto const & [c, cnt] : lettersCnt) {
            if (cnt > maxCnt) {
                letter = c;
                maxCnt = cnt;
            }
        }

        std::string ans(SSize, ' ');
        int idx = 0;
        while (lettersCnt[letter]-- > 0) {
            ans[idx] = letter;
            idx += 2;

        }
        for (auto & [c, cnt] : lettersCnt) {
            while (cnt-- > 0) {
                if (idx >= SSize) {
                    idx = 1;
                }
                ans[idx] = c;
                idx += 2;

            }
        }
        return ans;

    }
};
