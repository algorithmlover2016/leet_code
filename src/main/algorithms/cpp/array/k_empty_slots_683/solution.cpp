#include "../../head.h"


#define TEST_MAIN
// #define BINARY_SEARCH_BY_SET
class Solution {
public:
    int kEmptySlots(std::vector<int> const & flowers, int k) {
        // plagiarizing from https://zxi.mytechroad.com/blog/simulation/leetcode-683-k-empty-slots/
        // and https://ttzztt.gitbooks.io/lc/content/array/k-empty-slots.html
        // first using set to implement binary-search
        int const flowersSize = flowers.size();
        if (JUST_ZERO == flowersSize || flowersSize <= k) {
            return -1;
        }
#ifdef BINARY_SEARCH_BY_SET
        std::set<int> turnOnDays;
        for (int idx = 0; idx < flowersSize; idx++) {
            int turnOnDay = flowers[idx];
            auto curIt = turnOnDays.insert(turnOnDay).first; // get the insert position
            auto leftIt = curIt;
            auto rightIt = ++curIt;
            if ((rightIt != turnOnDays.end()) && ((*rightIt) == turnOnDay + k + 1)) {
                // its right neightbour is larger k than *curIt
                return idx + 1;
            }
            if ((leftIt != turnOnDays.begin()) && (*(--leftIt) == turnOnDay - k - 1)) {
                return idx + 1;
            }
        }
#else
        // using bucketes;
        k++;
        // 0 as a bucket, 1 -> k as a bucket, k + 1 -> 2k as a bucket,...
        int const bucketsSize = (flowersSize + k - 1) / k;
        std::vector<int> lowers(bucketsSize, INT_MAX);
        std::vector<int> higher(bucketsSize, INT_MIN);
        for (int idx = 0; idx < flowersSize; idx++) {
            int turnOnDay = flowers[idx];
            int bucketIdx = turnOnDay / k;
            if (turnOnDay < lowers[bucketIdx]) {
                lowers[bucketIdx] = turnOnDay;
                if (JUST_ZERO < bucketIdx &&
                        higher[bucketIdx - 1] + k /* the k is larger one than the parameter k */ == turnOnDay) {
                    return idx + 1;
                }
            }
            if (turnOnDay > higher[bucketIdx]) {
                higher[bucketIdx] = turnOnDay;
                if (bucketIdx + 1 < bucketsSize && lowers[bucketIdx + 1] == turnOnDay + k) {
                    return idx + 1;
                }
            }
        }
#endif
        return -1;
    }
private:
    static int const JUST_ZERO = 0;
};

class SolutionBinarySearch {
public:
    int kEmptySlots(std::vector<int> const & flowers, int k) {
        // plagiarizing from https://github.com/grandyang/leetcode/issues/683
        // if we don't get the idea of insert can return a position iterator
        std::set<int> s;
        for (int i = 0; i < flowers.size(); ++i) {
            int cur = flowers[i];
            auto it = s.upper_bound(cur);
            if (it != s.end() && *it - cur == k + 1) {
                return i + 1;
            }
            it = s.lower_bound(cur);
            if (it != s.begin() && cur - *(--it) == k + 1) {
                return i + 1;
            }
            s.insert(cur);
        }
        return -1;
    }
};

#ifdef TEST_MAIN
#define PRINT_TO_SCREEN
int main() {
    Solution obj;
    std::vector<int> flowers{{1, 3, 2}};
    int ans = obj.kEmptySlots(flowers, 1);
#ifdef PRINT_TO_SCREEN
    std::cout << ans << "\n";
#endif
    assert(ans == 2);

    flowers = std::vector<int>{{1, 2, 3}};
    ans = obj.kEmptySlots(flowers, 1);
#ifdef PRINT_TO_SCREEN
    std::cout << ans << "\n";
#endif
    assert(ans == -1);

    std::cout << "TEST SUCCESSFULLY" << std::endl;
    return 0;
}
#endif
