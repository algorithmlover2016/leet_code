#include "../../head.h"

// #define DEBUG
#define TEST_MAIN
class Solution {
public:
    std::string rearrangeString(std::string const & s, int k) {
        int maxCnt = 0;
        std::unordered_map<char, int> lettersCnt;
        for (char const letter : s) {
            maxCnt = std::max(maxCnt, ++lettersCnt[letter]);
        }
        int sSize = s.size();
        if (maxCnt + (maxCnt - 1) * (k - 1) > sSize) {
            return "";
        }
        auto cmp = [&] (std::pair<char, int> const & left, std::pair<char, int> const & right) {
            return left.second < right.second || (left.second == right.second && left.first > right.first);
        };
        typedef std::priority_queue<std::pair<char, int>, std::vector<std::pair<char, int>>, decltype(cmp)> MaxHeap;
        MaxHeap maxHeap(cmp);
        for (auto const & [key, cnt] : lettersCnt) {
            maxHeap.emplace(std::make_pair(key ,cnt));
        }
        std::string ans(sSize, '#');
        int idx = 0;
        while (!maxHeap.empty()) {
            auto const & ele = maxHeap.top();
            char letter = ele.first;
            int cnt = ele.second;
#ifdef DEBUG
            std::cout << letter << ", " << cnt << "\n";
#endif
            maxHeap.pop();
            for (int num = 0; num < cnt; num++) {
                ans[idx] = letter;
                idx += k;
                if (idx >= sSize) {
                    idx = idx % k + 1;
                }

#ifdef DEBUG
            std::cout << letter << ", " << idx << "\t" << ans << "\t" ;
#endif
            }
#ifdef DEBUG
            std::cout << "\n";
#endif
        }

        return ans;
    }
};

class SolutionSortDepends {
public:
    std::string rearrangeString(std::string const & s, int k) {
        int maxCnt = 0;
        std::unordered_map<char, int> lettersCnt;
        for (char const letter : s) {
            maxCnt = std::max(maxCnt, ++lettersCnt[letter]);
        }
        int sSize = s.size();
        if (maxCnt + (maxCnt - 1) * (k - 1) > sSize) {
            return "";
        }
        auto cmp = [&] (char const & left, char const & right) {
            return lettersCnt[left] < lettersCnt[right] || (lettersCnt[left] == lettersCnt[right] && left > right);
        };
        typedef std::priority_queue<char, std::vector<char>, decltype(cmp)> MaxHeap;
        MaxHeap maxHeap(cmp);
        for (auto const & [key, cnt] : lettersCnt) {
            maxHeap.emplace(key);
        }
        std::string ans;
        std::queue<char> que;
        int idx = 0;
        while (!maxHeap.empty()) {
            char letter = maxHeap.top();maxHeap.pop();
#ifdef DEBUG
            std::cout << letter << ", " << "\n";
#endif
            ans += letter;
            lettersCnt[letter]--;
            que.emplace(letter);
            if (que.size() == k) {
                char frontLetter = que.front(); que.pop();
                if (lettersCnt[frontLetter] > 0) {
                    maxHeap.emplace(frontLetter);
                }
            }
        }
        // return ans.size() == sSize ? ans : "";
        return ans;
    }
};

#ifdef TEST_MAIN
#define PRINT_TO_SCREEN
// #define TEST_SolutionSortDepends
int main() {
#ifdef TEST_SolutionSortDepends
    SolutionSortDepends obj;
    std::string s1("aabbcc");
    std::string ans1 = obj.rearrangeString(s1, 3);
#ifdef PRINT_TO_SCREEN
    std::cout << ans1 << "\n";
#endif
    assert("abcabc" == ans1);

    std::string s2("aaabc");
    std::string ans2 = obj.rearrangeString(s2, 3);
#ifdef PRINT_TO_SCREEN
    std::cout << ans2 << "\n";
#endif
    assert("" == ans2);

    std::string s3("aaadbbcc");
    std::string ans3 = obj.rearrangeString(s3, 2);
#ifdef PRINT_TO_SCREEN
    std::cout << ans3<< "\n";
#endif
    assert("abacabcd" == ans3); // the order is not right
#else
    Solution obj;
    std::string s1("aabbcc");
    std::string ans1 = obj.rearrangeString(s1, 3);
#ifdef PRINT_TO_SCREEN
    std::cout << ans1 << "\n";
#endif
    assert("abcabc" == ans1);

    std::string s2("aaabc");
    std::string ans2 = obj.rearrangeString(s2, 3);
#ifdef PRINT_TO_SCREEN
    std::cout << ans2 << "\n";
#endif
    assert("" == ans2);

    std::string s3("aaadbbcc");
    std::string ans3 = obj.rearrangeString(s3, 2);
#ifdef PRINT_TO_SCREEN
    std::cout << ans3<< "\n";
#endif
    assert("abacabcd" == ans3); // the order is not right
#endif
    std::cout << "TEST SUCCESSFULLY" << std::endl;
}
#endif
