#include "../../head.h"


class Solution {
public:
    int minStickers(std::vector<std::string> const & stickers, std::string const & target) {

        // plagiarizing from https://leetcode.com/problems/stickers-to-spell-word/discuss/108318/C%2B%2BJavaPython-DP-%2B-Memoization-with-optimization-29-ms-(C%2B%2B)
        int stickersSize = stickers.size();

        // to count the letter number at each sticker
        std::vector<std::vector<int>> cntStickers(stickersSize, std::vector<int>(LOW_CASE_NUM, 0));
        for (int idx = 0; idx < stickers.size(); idx++) {
            for (char const & c : stickers[idx]) {
                cntStickers[idx][c - 'a']++;
            }
        }

        std::vector<int> cntTarget(LOW_CASE_NUM, 0);
        for (char const & c : target) {
            cntTarget[c - 'a']++;
        }

        std::unordered_map<std::string, int> dpMemo;
        dpMemo[""] = 0;
        return dp(cntStickers, dpMemo, target, cntTarget);
    }

    int dp(std::vector<std::vector<int>> const & cntStickers,
            std::unordered_map<std::string, int> & dpMemo,
            std::string const & target,
            std::vector<int> const & cntTarget) {
        // already has a result
        if (dpMemo.find(target) != dpMemo.end()) {
            return dpMemo[target];
        }

        int ans = INT_MAX;
        for (int idx = 0; idx < cntStickers.size(); idx++) {
            // not using the sticker as a component
            // because we init dpMemo[""]  = 0, which means if program run here, target is not empty
            if (0 == cntStickers[idx][target[0] - 'a']) {
                continue;
            }
            // using the sticker as a component
            std::string leftTarget;
            std::vector<int> cntLeftTarget(LOW_CASE_NUM, 0);
            // if using the sticker, we maybe use other letter in this sticker, so there is a necessary loop
            for (int lowCaseIdx = 0; lowCaseIdx < LOW_CASE_NUM; lowCaseIdx++) {
                // when using the sticker, there still left some letter need composed by other stickers
                int left = cntTarget[lowCaseIdx] - cntStickers[idx][lowCaseIdx];
                if (left > 0) {
                    leftTarget.append(left, 'a' + lowCaseIdx);
                    cntLeftTarget[lowCaseIdx] += left;
                }
            }
            // std::cout << "leftTarget: " << leftTarget << "\n";
            int tmpRes =  dp(cntStickers, dpMemo, leftTarget, cntLeftTarget);
            if (-1 != tmpRes) {
                // using this sticker, we should plus one first, and count the leftTarget.
                ans = std::min(ans, 1 + tmpRes);
            }
        }
        return dpMemo[target] = INT_MAX == ans ? -1 : ans;
    }

private:
    int const LOW_CASE_NUM = 26;
};


class SolutionBetter {
public:
    int minStickers(std::vector<std::string> const & stickers, std::string const & target) {
        int m = stickers.size(), n = target.size();
        std::vector<std::vector<int> > map(m, std::vector<int>(26));
        for (int i = 0; i < m; i++) {
          for (char c : stickers[i]) {
              map[i][c - 'a']++;
          }
        }

        // check if cur_target has been visited
        std::unordered_set<int> vis;

        // BFS
        // store the bit representation of target string
        std::queue<int> q;
        // target at the beginning: all bits set to 1
        q.push((1 << n) - 1);
        int level = 0;
        while (!q.empty()) {
          ++level;
          for (int sz = q.size(); sz > 0; --sz) {
            int cur_target = q.front();
            q.pop();
            // check if cur_target has been visited
            if (vis.count(cur_target)) {
                continue;
            }
            vis.insert(cur_target);

            // the starting point from the right that need to be eliminated
            // because we always try to remove the right most char first (heuristic,
            // see below)
            int start = 0;
            while (start < n) {
              if ((cur_target >> start) & 1) {
                  break;
              }
              ++start;
            }

            for (int i = 0; i < m; ++i) {  // try all stickers
              // heuristic (this is the key speedup, we try stickers with char
              // target[n-1-start] first, so we always can remove the right most
              // char in cur_target)
              if (map[i][target[n - 1 - start] - 'a'] == 0) {
                  continue;
              }
              int next_target = cur_target;
              // try every char in stickers[i], delete it from cur_target
              for (char c : stickers[i]) {
                for (int r = start; r < n; r++) {  // delete from right to left
                  if (target[n - 1 - r] == c && ((next_target >> r) & 1)) {
                    next_target ^= (1 << r);
                    break;
                  }
                }
              }
              if (next_target == 0) {
                  return level;
              }
              q.push(next_target);
            }
          }
        }
        return -1;
    }
};
