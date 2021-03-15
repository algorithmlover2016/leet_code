#include "../../head.h"

// #define DEBUG
#define TEST_MAIN
class SolutionHuaHuaNiu {
public:
    std::vector<int> pourWater(std::vector<int> const & inputHeights, int V, int K) {
        // plagiarizing from https://zxi.mytechroad.com/blog/simulation/leetcode-755-pour-water/
        // and https://github.com/grandyang/leetcode/issues/755
        // I thought there will be better solution which will make time complexity less than O(V * heights.size());
#ifdef DEBUG
        std::cout << typeid(*this).name() << "::" << __func__ << "\n";
#endif
        std::vector<int> heights(inputHeights);
        int const heightsSize = heights.size();
        if (K >= heightsSize) {
            return heights;
        }
        while (V-- > 0) {
            tarversalHelper(heights, K);
        }
        return heights;
    }
    void tarversalHelper(std::vector<int> & heights, int K) {
        int const heightsSize = heights.size();
        if (K >= heightsSize) {
            return; 
        }
        int targetPos = K;
        for (int direction = -1; direction <= 1; direction += 2) {
            // only one line traversal, so there just need a direction -1 or 1 to mark tarversal left or right
            int idx = K + direction;
            // find the interval that all the value of the interval is not larger than heights[K];
            while (idx > EXCLUDE_MOST_LEFT_IDX && idx < heightsSize && heights[idx] <= heights[idx - direction]) {
                // idx means the cur pos, idx - direction means the former pos
                // if traversal to left, idx - direction means idx + 1, otherwise,idx - 1;
                if (heights[idx] < heights[targetPos]) {
                    targetPos = idx;
                }
                idx += direction;
            }
            if (targetPos != K) {
                break;
            }
        }
        heights[targetPos]++;
    }
private:
    static int const EXCLUDE_MOST_LEFT_IDX = -1;
};

class Solution {
public:
    std::vector<int> pourWater(std::vector<int> const & inputHeights, int V, int pos) {
        // plagiarizing from https://shibaili.blogspot.com/2019/03/755-pour-water.html
        // and https://github.com/grandyang/leetcode/issues/755
        // search and rollback
#ifdef DEBUG
        std::cout << typeid(*this).name() << "::" << __func__ << "\n";
#endif
        std::vector<int> ans(inputHeights);
        int const ansSize = ans.size();
        if (pos >= ansSize) {
            return ans;
        }
        while (V-- > 0) {
            int left = pos;
            while (left > 0 && ans[left - 1] <= ans[left]) {
                left--;
            }
            if (ans[left] < ans[pos]) {
                while (left < pos && ans[left + 1] == ans[left]) {
                    left++;
                }
                ans[left]++;
#ifdef DEBUG
                std::cout << "at left idx: " << left << ", " << ans[left] << "; ";
#endif
                continue;
            }
            int right = pos;
            while (right + 1 < ansSize && ans[right] >= ans[right + 1]) {
                right++;
            }
            if (ans[right] < ans[pos]) {
                while (right > pos && ans[right - 1] == ans[right]) {
                    right--;
                }
                ans[right]++;

#ifdef DEBUG
                std::cout << "at right idx: " << right << ", " << ans[right] << "; ";
#endif
            } else {
                ans[pos]++;
#ifdef DEBUG
                std::cout << "at pos idx: " << pos << ", " << ans[pos] << "; ";
#endif
            }
        }
        return ans;
    }
};

class SolutionPos {
public:
    std::vector<int> pourWater(std::vector<int> const & inputHeights, int V, int K) {
        // plagiarizing from https://shibaili.blogspot.com/2019/03/755-pour-water.html
        // and https://github.com/grandyang/leetcode/issues/755
        // search and rollback
#ifdef DEBUG
        std::cout << typeid(*this).name() << "::" << __func__ << "\n";
#endif
        std::vector<int> ans(inputHeights);
        int const ansSize = ans.size();
        if (K >= ansSize) {
            return ans;
        }
        while (V-- > 0) {
            int pos = K;
            int left = pos;
            while (left > 0 && ans[left - 1] <= ans[left]) {
                if (ans[left - 1] < ans[left]) {
                    pos = left - 1;
                }
                left--;
            }
            if (pos != K) {
                ans[pos]++;
                continue;
            }
            int right = K;
            while (right + 1 < ansSize && ans[right] >= ans[right + 1]) {
                if (ans[right + 1] < ans[right]) {
                    pos = right + 1;
                }
                right++;
            }
            ans[pos]++;
        }
        return ans;
    }
};

#ifdef TEST_MAIN
#define PRINT_TO_SCREEN
// #define TEST_SolutionHuaHuaNiu
// #define TEST_SolutionPos

int main() {
#ifdef TEST_SolutionHuaHuaNiu
    SolutionHuaHuaNiu obj;
#elif defined(TEST_SolutionPos)
    SolutionPos obj;
#else 
    Solution obj;
#endif

    std::vector<int> nums{{2, 1, 1, 2, 1, 2, 2}};
    int V = 4, K = 3;
    std::vector<int> acceptAns{{2, 2, 2, 3, 2, 2, 2}};
    std::vector<int> ans = obj.pourWater(nums, V, K);
#ifdef PRINT_TO_SCREEN
    for (int num : ans) {
        std::cout << num << ", ";
    }
    std::cout << "\n";
#endif
    assert(ans == acceptAns);

    nums = std::vector<int>{{1, 2, 3, 4}};
    V = 2; K = 2;
    acceptAns = std::vector<int>{{2, 3, 3, 4}};
    ans = obj.pourWater(nums, V, K);
#ifdef PRINT_TO_SCREEN
    for (int num : ans) {
        std::cout << num << ", ";
    }
    std::cout << "\n";
#endif
    assert(ans == acceptAns);

    nums = std::vector<int>{{3, 1, 3}};
    V = 5; K = 1;
    acceptAns = std::vector<int>{{4, 4, 4}};
    ans = obj.pourWater(nums, V, K);
#ifdef PRINT_TO_SCREEN
    for (int num : ans) {
        std::cout << num << ", ";
    }
    std::cout << "\n";
#endif
    assert(ans == acceptAns);

    std::cout << "TEST SUCCESSFULLY" << std::endl;
    return 0;
}
#endif
