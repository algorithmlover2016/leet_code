#include "../../head.h"


class Solution {
public:
    int maxBuilding(int n, std::vector<std::vector<int>> restrictions) {
        // plagiarizing from https://leetcode.com/problems/maximum-building-height/discuss/1175269/C%2B%2B-with-picture-2-passes
        // according to the id_i sort the restrictions, to make sure the id_i is ordered (increasing or decreasing)
        restrictions.insert(std::end(restrictions), {{1, 0}, {n, n - 1}} /*this is a tmp vector*/);
        std::sort(std::begin(restrictions), std::end(restrictions));
        shadePass(restrictions);
        std::reverse(std::begin(restrictions), std::end(restrictions));
        return shadePass(restrictions);
    }
private:
    int shadePass(std::vector<std::vector<int>> & restrictions) {
        int const restrictionsSize = restrictions.size();
        if (AT_LEAST_RESTRICTIONS_SIZE > restrictionsSize) {
            return 0;
        }
        int ans = 0;
        for (int idx = 0; idx < restrictionsSize - 1; idx++) {
            if (RESTRICTION_SIZE > restrictions[idx].size() || RESTRICTION_SIZE > restrictions[idx + 1].size()) {
                continue;
            }
            int curHeight = restrictions[idx][HEIGHT_IDX];
            int nextHeight = restrictions[idx + 1][HEIGHT_IDX];
            // if we add step from cur idx, then the max height will be curHeight + (the difference from cur to next)
            int maxHeightFromCurHeight = curHeight +
                std::abs(restrictions[idx + 1][ID_IDX] - restrictions[idx][ID_IDX]);
            if (maxHeightFromCurHeight > nextHeight) {
                // assuming the real maxHeight is finalH, the difference between finalH and maxHeightFromCurHeght is h;
                // then there is a formula that finalH + h = maxHeightFromCurHeight and finalH - h = nextHeight
                // so finalH = (maxHeightFromCurHeight + nextHeight) / 2 ( because the / is divide floor to smaller)
                // finalH = nextHeight + (maxHeightFromCurHeight - nextHeigt) / 2
                maxHeightFromCurHeight = nextHeight + (maxHeightFromCurHeight - nextHeight) / 2;
            }
            ans = std::max(ans, maxHeightFromCurHeight);
            // then the nextHeight will be restricted by the maxHeightFromHeight and restriction (nextHeight);
            restrictions[idx + 1][HEIGHT_IDX] = std::min(maxHeightFromCurHeight, nextHeight);
        }
        return ans;
    }
private:
    static int const AT_LEAST_RESTRICTIONS_SIZE = 2;
    static int const RESTRICTION_SIZE = 2;
    static int const ID_IDX = 0;
    static int const HEIGHT_IDX = 1;
};

class Solution {
public:
    int maxBuilding(int n, std::vector<std::vector<int>> arr) {
        // plagiarizing from https://leetcode.com/problems/maximum-building-height/discuss/1175047/PythonC%2B%2B-greedy-solution-with-visual-explanation-O(MlogM)
        arr.push_back({1, 0});
        arr.push_back({n, n - 1});
        std::sort(arr.begin(), arr.end());
        int m = arr.size();

        for (int i = 1; i < m; ++i) {
            arr[i][1] = std::min(arr[i][1], arr[i - 1][1] + arr[i][0] - arr[i - 1][0]);
        }
        for (int i = m - 2; i >= 0; --i) {
            arr[i][1] = std::min(arr[i][1], arr[i + 1][1] + arr[i + 1][0] - arr[i][0]);
        }

        int ans = 0, l, h1, r, h2;
        for (int i = 1; i < m; ++i) {
            l = arr[i - 1][0], r = arr[i][0], h1 = arr[i - 1][1], h2 = arr[i][1];
            // r - l is the max steps we can take, and std::abs(h1 - h2) is the min steps we need take to adapt the change
            // if r - l is smaller, then we need a minus operation, otherwise, we can make a plus operation
            ans = std::max(ans, std::max(h1, h2) + (r - l - std::abs(h1 - h2)) / 2);
        }
        return ans;
    }
};

class Solution {
public:
  int maxBuilding(int n, std::vector<std::vector<int>> & res) {
      std::vector<std::pair<int, int>> a;
      a.emplace_back(1, 0);
      a.emplace_back(n, n - 1);
      for (auto & x: res) {
          assert(RESTRICTIONS_SIZE <= x.size());
          a.emplace_back(x[0], x[1]);
      }
      std::sort(a.begin(), a.end());
      int m = a.size(), ans = 0;
      for (int i = 0; i < m - 1; i++) {
          int d = a[i + 1].first - a[i].first;
          a[i + 1].second = std::min(a[i + 1].second, a[i].second + d);
      }
      for (int i = m; --i; ) {
          int d = a[i].first - a[i - 1].first;
          a[i - 1].second = std::min(a[i - 1].second, a[i].second + d);
          // left is h1, d is the difference of index, right is h2;
          // no matter h1 is larger or smaller than h2, let's assume that
          // the max height from h1 to h2 is h. the delta from h to h2 + d is x
          // h2 + d = h + x;
          // h1 = h - x;
          // h = (h1 + h2 + d) / 2;
          ans = std::max(ans, (a[i - 1].second + a[i].second + d) >> 1);
      }
      return ans;
  }
private:
    static int const RESTRICTIONS_SIZE = 2;

};
