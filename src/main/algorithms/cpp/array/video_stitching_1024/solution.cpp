#include "../../head.h"


class SolutionTLE {
public:
    int videoStitching(std::vector<std::vector<int>> const & clips, int T) {
        std::vector<int> mostJumps(101, -1);
        for (int index = 0; index < clips.size(); index++) {
            if (clips[index][1] > mostJumps[clips[index][0]]) {
                mostJumps[clips[index][0]] = clips[index][1];
            }
        }
        int step = INT_MAX;
        bfs(mostJumps, 0, T, 1, step);
        return step == INT_MAX ? -1 : step;
    }

    void bfs(std::vector<int> const & mostJumps, int start, int target, int cnt, int & step) {
        for (int val = mostJumps[start]; val > start; val--) {
            if (val >= target) {
                if (cnt < step) {
                    step = cnt;
                }
                return;
            }
            bfs(mostJumps, val, target, cnt + 1, step);
        }
    }
};

class SolutionDP {
public:
    int videoStitching(std::vector<std::vector<int>> const & clips, int T) {
        // plagiairizing from https://www.youtube.com/watch?v=4Qho-im90ew
        int const MAX_LEN = 101;
        std::vector<int> mostJumps(MAX_LEN, -1);
        for (int index = 0; index < clips.size(); index++) {
            if (clips[index][1] > mostJumps[clips[index][0]]) {
                mostJumps[clips[index][0]] = clips[index][1];
            }
        }

        std::vector<int> dp(mostJumps.size(), MAX_LEN);
        dp[0] = 0;
        for (int index = 0; index <= T; index++) {
            if (mostJumps[index] < index) {
                continue;
            }
            for (int val = index; val <= mostJumps[index]; val++) {
                dp[val] = std::min(dp[val], dp[index] + 1);
            }
        }
        return MAX_LEN == dp[T] ? -1 : dp[T];
    }
};
