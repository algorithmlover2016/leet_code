#include "../../head.h"

#define DEBUG
#define TEST_MAIN
class SolutionTLE {
public:
    int findMaximizedCapital(int k, int W, std::vector<int> const & profits, std::vector<int> const & capital) {
        int const profitsSize = profits.size();
        int const capitalSize = capital.size();
        if (profitsSize == JUST_ZERO || profitsSize != capitalSize) {
            return W;
        }
        std::vector<bool> visited(profitsSize, false);
        int ans = 0;
        dfs(k, W, profits, capital, visited, ans);
        return ans;
    }
    void dfs(int k, int W,
            std::vector<int> const & profits,
            std::vector<int> const & capital,
            std::vector<bool> & visited, int & ans) {
        // when k = 0, we have not compare the W and ans, if k decrease to 0
        if (k < JUST_ZERO) {
            return;
        }
        ans = std::max(W, ans);
        if (k == JUST_ZERO) {
            return;
        }
        for (int idx = 0; idx < capital.size(); idx++) {
            if (visited[idx]) {
                continue;
            }
            if (W < capital[idx]) {
                continue;
            }
            visited[idx] = true;
            dfs(k - 1, W + profits[idx], profits, capital, visited, ans);
            visited[idx] = false;
        }
    }

private:
    static int const JUST_ZERO = 0;

};


class Solution {
public:
    int findMaximizedCapital(int k, int W, std::vector<int> const & profits, std::vector<int> const & capital) {
        int const profitsSize = profits.size();
        int const capitalSize = capital.size();
        if (profitsSize == JUST_ZERO || profitsSize != capitalSize) {
            return W;
        }
        std::vector<int> profitsCapPair(profitsSize);
        std::iota(std::begin(profitsCapPair), std::end(profitsCapPair), 0); // according to profits and capital sort index
        auto cmp = [&] (int const left, int const right) {
            // lambada can't write like this, it will leads to an ERROR: AddressSanitizer: heap-buffer-overflow on address 0x62100002cca0 at pc 0x0000003476bd bp 0x7ffd1c833b00 sp 0x7ffd1c833af8
            // return (capital[left] < capital[right] || (capital[left] == capital[right] && profits[left] >= profits[right]));
            return capital[left] < capital[right];
        };
        std::sort(profitsCapPair.begin(), profitsCapPair.end(), cmp);
        typedef std::priority_queue<int, std::vector<int>, std::greater<int>> MaxHeap;
        MaxHeap minHeap;
        int idx = 0;
        while (k-- > JUST_ZERO) {
            while (idx < profitsCapPair.size() && capital[profitsCapPair[idx]] <= W) {
                minHeap.emplace(-profits[profitsCapPair[idx]]);
                idx++;
            }
            if (!minHeap.empty()) {
                W -= minHeap.top();
                minHeap.pop();
            }
        }
        return W;
    }
private:
    static int const JUST_ZERO = 0;
};

class SolutionMaxHeap {
public:
    int findMaximizedCapital(int k, int W, std::vector<int> const & profits, std::vector<int> const & capital) {
        int const profitsSize = profits.size();
        int const capitalSize = capital.size();
        if (profitsSize == JUST_ZERO || profitsSize != capitalSize) {
            return W;
        }
        std::vector<int> profitsCapPair(profitsSize);
        std::iota(std::begin(profitsCapPair), std::end(profitsCapPair), 0); // according to profits and capital sort index
        auto cmp = [&] (int const left, int const right) {
            // lambada can't write like this, it will leads to an ERROR: AddressSanitizer: heap-buffer-overflow on address 0x62100002cca0 at pc 0x0000003476bd bp 0x7ffd1c833b00 sp 0x7ffd1c833af8
            // return (capital[left] < capital[right] || (capital[left] == capital[right] && profits[left] >= profits[right]));
            return capital[left] < capital[right];
        };
        std::sort(profitsCapPair.begin(), profitsCapPair.end(), cmp);
        // typedef std::priority_queue<int, std::vector<int>, std::greater<int>> MaxHeap;
        std::priority_queue<int> maxHeap;
        int idx = 0;
        while (k-- > JUST_ZERO) {
            while (idx < profitsCapPair.size() && capital[profitsCapPair[idx]] <= W) {
                maxHeap.emplace(profits[profitsCapPair[idx]]);
                idx++;
            }
            if (!maxHeap.empty()) {
                W += maxHeap.top();
                maxHeap.pop();
            }
        }
        return W;
    }
private:
    static int const JUST_ZERO = 0;
};

#define CMP_WITH_LAMDA_AVOID_HEAP_OVERFLOW
class Solution {
public:
    int findMaximizedCapital(int k, int W, std::vector<int> const & profits, std::vector<int> const & capital) {
        int const profitsSize = profits.size();
        int const capitalSize = capital.size();
        if (profitsSize == JUST_ZERO || profitsSize != capitalSize) {
            return W;
        }
        #ifndef CMP_WITH_LAMDA_AVOID_HEAP_OVERFLOW
        std::vector<int> profitsCapPair(profitsSize);
        std::iota(std::begin(profitsCapPair), std::end(profitsCapPair), 0); // according to profits and capital sort index
        auto cmp = [&] (int const left, int const right) {
            // lambada can't write like this, it will leads to an ERROR: AddressSanitizer: heap-buffer-overflow on address 0x62100002cca0 at pc 0x0000003476bd bp 0x7ffd1c833b00 sp 0x7ffd1c833af8
            // return (capital[left] < capital[right] || (capital[left] == capital[right] && profits[left] >= profits[right]));
            return capital[left] < capital[right];
        };
        std::sort(profitsCapPair.begin(), profitsCapPair.end(), cmp);
        std::priority_queue<int> maxHeap;
        int idx = 0;
        while (k-- > JUST_ZERO) {
            while (idx < profitsCapPair.size() && capital[profitsCapPair[idx]] <= W) {
                maxHeap.emplace(profits[profitsCapPair[idx]]);
                idx++;
            }
            if (!maxHeap.empty()) {
                W += maxHeap.top();
                maxHeap.pop();
            }
        }
        #else
        std::vector<std::pair<int, int>> profitsCapPair(profitsSize);
        for (int idx = 0; idx < profitsSize; idx++) {
            profitsCapPair[idx] = std::make_pair(profits[idx], capital[idx]);
        }

        auto cmp = [&] (std::pair<int, int> const & left, std::pair<int, int> const & right) {
            return left.second < right.second || (left.second == right.second && left.first >= right.first);
        };
        std::sort(profitsCapPair.begin(), profitsCapPair.end(), cmp);
        typedef std::priority_queue<int, std::vector<int>, std::greater<int>> MaxHeap;
        MaxHeap minHeap;
        int idx = 0;
        while (k-- > JUST_ZERO) {
            while (idx < profitsCapPair.size() && profitsCapPair[idx].second <= W) {
                minHeap.emplace(-profitsCapPair[idx].first);
                idx++;
            }
            if (!minHeap.empty()) {
                W -= minHeap.top();
                minHeap.pop();
            }
        }
        #endif
        return W;
    }
private:
    static int const JUST_ZERO = 0;
};

#ifdef TEST_MAIN
#define PRINT_TO_SCREEN
int main() {
    Solution obj;
    std::vector<int> profits{{5,5,0,2,5,2,8,0,6,1,10,6,3,0,1,5,9,1,3,5,9,3,5,2,9,3,11,8,5,5,4,0,3,6,2,1,9,3,1,9,0,5,7,8,8,2,0,10,3,2,9,9,2,10,0,5,7,7,2,5,1,7,9,9,2,7,10,7,1,5,5,3,3,3,6,11,4,11,9,1,2,9,0,8,7,11,11,3,5,6,2,6,4,7,5,3,0,2,11,11,4,1,10,2,2,4,0,4,8,3,8,7,8,1,4,10,8,0,1,9,3,11,6,0,0,6,0,3,9,6,3,5,0,6,7,6,3,7,0,9,8,0,6,0,9,10,5,9,6,11,6,10,1,5,6,3,6,9,1,10,11,1,0,6,6,7,10,11,10,3,0,11,8,11,0,0,1,7,9,11,6,4,2,1,0,3,1,3,7,11,5,8,9,0,4,2,1,6,4,5,5,8,0,11,8,5,4,10,5,6,2,9,11,5,9,11,5,11,0,6,9,2,6,11,11,0,8,3,8,2,6,9,4,11,10,8,8,3,8,10,4,3,0,8,2,8,2,0,2,7,11,7,11,7,10,3,0,10,9,0,10,2,9,10,8,6,4,8,6,6,0,10,5,10,10,7,1,2,0,10,10,11,11,4,2,10,4,11,11,6,3,1,10,5,2,1,1,0,5,8,2,3,1,2,10,2,5,7,1,4,6,4,7,2,0,4,2,2,4,8,2,0,7,0,3,5,8,7,8,5,1,11,10,8,11,7,0,0,1,1,1,8,7,1,3,1,1,1,5,9,2,9,8,8,10,9,2,7,9,2,2,3,1,2,0,3,5,0,4,6,7,6,5,3,6,2,0,11,2,5,9,6,6,5,0,3,5,1,10,6,11,9,1,11,9,8,4,0,4,1,7,6,2,8,8,9,6,3,3,2,8,10,11,9,11,5,3,1,1,6,9,8,1,8,10,10,9,8,8,9,8,6,4,8,0,0,9,9,1,4,7,10,6,11,2,3,7,2,2,6,9,1,2,1,2,2,6,4,4,6,4,3,11,8,4,5,8,5,8,0,4,3,1,6,8,8,4,10,10,0,6,9,9,10,7,11,2,8,4,1,3,1,3,2,6,10,10,11,6,7,4,2,9,1,11,2,8,1,8,10,9,11,4,11,0,6,11,2,0,7,0,2,8,4,11,5,1,1,2,9,7,6,10,11,9,1,11,11,5,1,1,10,2,8,6,8,7,5,6,9,11,9,6,7,8,11,6,7,4,0,0,4,5,9,3,6,2,3,8,9,4,9,3,10,9,9,10,4,6,1,7,7,8,4,5,2,11,2,6,4,8,3,11,10,10,11,1,3,10,8,3,6,3,5,8,1,0,7,3,11,0,7,4,11,10,3,8,3,4,10,4,10,0,2,0,0,6,9,1,3,2,0,1,0,11,6,7,6,2,6,3,11,1,1,5,7,0,1,7,3,0,11,11,4,8,5,11,7,4,1,10,11,9,6,0,3,7,9,5,8,7,9,2,11,7,4,1,3,3,9,3,4,6,9,8,10,0,1,8,1,1,10,4,3,0,2,10,10,6,7,11,3,8,2,5,2,9,8,0,10,0,1,2,6,1,7,5,7,1,10,6,0,5,5,5,7,1,7,7,3,3,1,4,9,9,3,7,11,4,8,4,8,2,10,0,7,7,7,5,10,6,1,3,10,0,3,4,1,9,6,8,6,5,1,10,3,3,6,1,4,1,5,10,4,4,5,2,9,3,2,7,9,0,9,8,8,6,2,5,3,11,8,10,10,2,5,9,11,7,10,7,0,2,6,0,10,10,6,4,2,6,6,7,10,5,1,0,5,2,9,7,1,8,7,1,11,6,8,2,1,11,2,6,2,9,9,11,0,3,3,6,7,7,3,10,10,1,11,10,3,10,10,10,8,8,1,9,11,7,7,6,4,5,9,11,10,5,6,4,4,8,10,3,3,2,9,5,11,5,4,5,6,9,8,1,1,5,3,6,0,2,6,1,8,7,0,7,2,10,2,3,6,6,0,9,11,1,3,9,7,3,8,1,9,4,11,6,2,9,8,3,8,0,2,9,2,10,1,11,9,11,4,8,8,8,5,4,7,8,0,2,1,10,2,9,6,9,10,2,0,6,0,10,1,8,3,10,0,6,6,4,8,8,6,8,4,9,11,11,6,6,8,5,9,7,6,3,1,10,10,1,1,8,11,5,0,0,9,7,7,3,6,1,6,6,8,8,7,4,3}};
    std::vector<int> capital{{5,5,0,2,5,2,8,0,6,1,10,6,3,0,1,5,9,1,3,5,9,3,5,2,9,3,11,8,5,5,4,0,3,6,2,1,9,3,1,9,0,5,7,8,8,2,0,10,3,2,9,9,2,10,0,5,7,7,2,5,1,7,9,9,2,7,10,7,1,5,5,3,3,3,6,11,4,11,9,1,2,9,0,8,7,11,11,3,5,6,2,6,4,7,5,3,0,2,11,11,4,1,10,2,2,4,0,4,8,3,8,7,8,1,4,10,8,0,1,9,3,11,6,0,0,6,0,3,9,6,3,5,0,6,7,6,3,7,0,9,8,0,6,0,9,10,5,9,6,11,6,10,1,5,6,3,6,9,1,10,11,1,0,6,6,7,10,11,10,3,0,11,8,11,0,0,1,7,9,11,6,4,2,1,0,3,1,3,7,11,5,8,9,0,4,2,1,6,4,5,5,8,0,11,8,5,4,10,5,6,2,9,11,5,9,11,5,11,0,6,9,2,6,11,11,0,8,3,8,2,6,9,4,11,10,8,8,3,8,10,4,3,0,8,2,8,2,0,2,7,11,7,11,7,10,3,0,10,9,0,10,2,9,10,8,6,4,8,6,6,0,10,5,10,10,7,1,2,0,10,10,11,11,4,2,10,4,11,11,6,3,1,10,5,2,1,1,0,5,8,2,3,1,2,10,2,5,7,1,4,6,4,7,2,0,4,2,2,4,8,2,0,7,0,3,5,8,7,8,5,1,11,10,8,11,7,0,0,1,1,1,8,7,1,3,1,1,1,5,9,2,9,8,8,10,9,2,7,9,2,2,3,1,2,0,3,5,0,4,6,7,6,5,3,6,2,0,11,2,5,9,6,6,5,0,3,5,1,10,6,11,9,1,11,9,8,4,0,4,1,7,6,2,8,8,9,6,3,3,2,8,10,11,9,11,5,3,1,1,6,9,8,1,8,10,10,9,8,8,9,8,6,4,8,0,0,9,9,1,4,7,10,6,11,2,3,7,2,2,6,9,1,2,1,2,2,6,4,4,6,4,3,11,8,4,5,8,5,8,0,4,3,1,6,8,8,4,10,10,0,6,9,9,10,7,11,2,8,4,1,3,1,3,2,6,10,10,11,6,7,4,2,9,1,11,2,8,1,8,10,9,11,4,11,0,6,11,2,0,7,0,2,8,4,11,5,1,1,2,9,7,6,10,11,9,1,11,11,5,1,1,10,2,8,6,8,7,5,6,9,11,9,6,7,8,11,6,7,4,0,0,4,5,9,3,6,2,3,8,9,4,9,3,10,9,9,10,4,6,1,7,7,8,4,5,2,11,2,6,4,8,3,11,10,10,11,1,3,10,8,3,6,3,5,8,1,0,7,3,11,0,7,4,11,10,3,8,3,4,10,4,10,0,2,0,0,6,9,1,3,2,0,1,0,11,6,7,6,2,6,3,11,1,1,5,7,0,1,7,3,0,11,11,4,8,5,11,7,4,1,10,11,9,6,0,3,7,9,5,8,7,9,2,11,7,4,1,3,3,9,3,4,6,9,8,10,0,1,8,1,1,10,4,3,0,2,10,10,6,7,11,3,8,2,5,2,9,8,0,10,0,1,2,6,1,7,5,7,1,10,6,0,5,5,5,7,1,7,7,3,3,1,4,9,9,3,7,11,4,8,4,8,2,10,0,7,7,7,5,10,6,1,3,10,0,3,4,1,9,6,8,6,5,1,10,3,3,6,1,4,1,5,10,4,4,5,2,9,3,2,7,9,0,9,8,8,6,2,5,3,11,8,10,10,2,5,9,11,7,10,7,0,2,6,0,10,10,6,4,2,6,6,7,10,5,1,0,5,2,9,7,1,8,7,1,11,6,8,2,1,11,2,6,2,9,9,11,0,3,3,6,7,7,3,10,10,1,11,10,3,10,10,10,8,8,1,9,11,7,7,6,4,5,9,11,10,5,6,4,4,8,10,3,3,2,9,5,11,5,4,5,6,9,8,1,1,5,3,6,0,2,6,1,8,7,0,7,2,10,2,3,6,6,0,9,11,1,3,9,7,3,8,1,9,4,11,6,2,9,8,3,8,0,2,9,2,10,1,11,9,11,4,8,8,8,5,4,7,8,0,2,1,10,2,9,6,9,10,2,0,6,0,10,1,8,3,10,0,6,6,4,8,8,6,8,4,9,11,11,6,6,8,5,9,7,6,3,1,10,10,1,1,8,11,5,0,0,9,7,7,3,6,1,6,6,8,8,7,4,3}};
    int W = 0, k = 11;
    int ans = obj.findMaximizedCapital(k, W, profits, capital);

#ifdef PRINT_TO_SCREEN
    std::cout << ans << "\n";
#endif

    assert(ans == 0);

    SolutionMaxHeap objMaxHeap;
    assert(ans == objMaxHeap.findMaximizedCapital(k, W, profits, capital));
    std::cout << "TEST SUCCESSFULLY" << std::endl;
    return 0;
}
#endif
