#include "../../head.h"


class SolutionMayTLERECURSIVE {
public:
    int stoneGameV(std::vector<int> const & stoneValue) {
        // plagiarizing from https://leetcode.com/problems/stone-game-v/discuss/806761/Python-DP
        if (stoneValue.empty()) {
            return 0;
        }

        int const stoneValueSize = stoneValue.size();
        std::vector<int> preSumStone(stoneValueSize + 1, 0);
        for (int idx = 0; idx < stoneValueSize; idx++) {
            preSumStone[idx + 1] = preSumStone[idx] + stoneValue[idx];
        }

        std::vector<std::vector<int>> dpMemo(stoneValueSize,
                std::vector<int>(stoneValueSize, 0));

        return dpHelp(preSumStone, dpMemo, 0, stoneValueSize - 1);
    }
    int dpHelp(std::vector<int> const & preSumStone,
            std::vector<std::vector<int>> & dpMemo,
            int left,
            int right) {
        if (left == right) {
            return 0;
        }
        if (0 != dpMemo[left][right]) {
            return dpMemo[left][right];
        }
        for (int mid = left; mid < right; mid++) {
            int preSumLeft = preSumStone[mid + 1] - preSumStone[left]; // [left, mid]
            int preSumRight = preSumStone[right + 1] - preSumStone[mid + 1]; // [mid + 1, right]
            if (preSumLeft <= preSumRight) {
                dpMemo[left][right] = std::max(dpMemo[left][right],
                        dpHelp(preSumStone, dpMemo, left, mid) + preSumLeft);
            }
            if (preSumLeft >= preSumRight) {
                dpMemo[left][right] = std::max(dpMemo[left][right],
                        dpHelp(preSumStone, dpMemo, mid + 1, right) + preSumRight);
            }
        }
        return dpMemo[left][right];
    }

};

class SolutionMayTLE_TRAVERSAL {
public:
    int stoneGameV(std::vector<int> const & stoneValue) {
        // plagiarizing from https://leetcode.com/problems/stone-game-v/discuss/806761/Python-DP
        if (stoneValue.empty()) {
            return 0;
        }

        int const stoneValueSize = stoneValue.size();
        std::vector<int> preSumStone(stoneValueSize + 1, 0);
        for (int idx = 0; idx < stoneValueSize; idx++) {
            preSumStone[idx + 1] = preSumStone[idx] + stoneValue[idx];
        }

        std::vector<std::vector<int>> dpMemo(stoneValueSize,
                std::vector<int>(stoneValueSize, 0));

        for (int right = 0; right < stoneValueSize; right++) {
            for (int left = right; left > -1; left--) {
                for (int mid = left; mid < right; mid++) {
                    int preSumLeft = preSumStone[mid + 1] - preSumStone[left]; // [left, mid]
                    int preSumRight = preSumStone[right + 1] - preSumStone[mid + 1]; // [mid + 1, right]
                    if (preSumLeft <= preSumRight) {
                        dpMemo[left][right] = std::max(dpMemo[left][right],
                                dpMemo[left][mid] + preSumLeft);
                    }
                    if (preSumLeft >= preSumRight) {
                        dpMemo[left][right] = std::max(dpMemo[left][right],
                                dpMemo[mid + 1][right] + preSumRight);
                    }
                }
            }
        }
        return dpMemo[0][stoneValueSize - 1];
    }
};

class SolutionBetter {
public:
    int stoneHelper(const int * sums, int i, int j, int * memo, int size) {
      auto & mem = memo[i * size + j];
      if (mem != -1) {
          return mem;
      }
      if (i == j) {
        return mem = 0;
      }
      auto find = std::lower_bound(sums + i, sums + j + 1, (sums[i] + sums[j + 1]) / 2);
      for (int k = find - sums; k <= j; ++k) {
        auto a = sums[k] - sums[i];
        auto b = sums[j + 1] - sums[k];
        if (2 * std::min(a, b) <= mem) break;
        if (a < b) {
          mem = std::max(mem, stoneHelper(sums, i, k - 1, memo, size) + a);
        } else if (a > b) {
          mem = std::max(mem, stoneHelper(sums, k, j, memo, size) + b);
        } else {
          mem = std::max(mem, std::max(stoneHelper(sums, i, k - 1, memo, size),
                                       stoneHelper(sums, k, j, memo, size)) + a);
        }
      }
        for (int k = find - sums - 1; k >= i + 1; --k) {
          auto a = sums[k] - sums[i];
          auto b = sums[j + 1] - sums[k];
          if (2 * std::min(a, b) <= mem) break;
          if (a < b) {
            mem = std::max(mem, stoneHelper(sums, i, k - 1, memo, size) + a);
          } else if (a > b) {
            mem = std::max(mem, stoneHelper(sums, k, j, memo, size) + b);
          } else {
            mem = std::max(mem, std::max(stoneHelper(sums, i, k - 1, memo, size),
                                         stoneHelper(sums, k, j, memo, size)) + a);
          }
        }
      return mem;
    }

    int stoneGameV(std::vector<int> const & stoneValue) {
      const int size = stoneValue.size();
      int sums[size + 1];
      sums[0] = 0;
      for (int i = 1; i < size + 1; ++i) {
        sums[i] = sums[i - 1] + stoneValue[i - 1];
      }
      int memo[size * size];
      std::memset(memo, -1, sizeof memo);
      return stoneHelper(sums, 0, size - 1, memo, size);
    }
};
