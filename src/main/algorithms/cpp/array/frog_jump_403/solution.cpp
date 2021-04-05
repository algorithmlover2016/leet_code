#include "../../head.h"


class Solution {
public:
    bool canCross(std::vector<int> const & stones) {
        // plagiarizing idea from https://leetcode.com/problems/frog-jump/discuss/88824/Very-easy-to-understand-JAVA-solution-with-explanations
        // at each position, we find the next pos from the cur pos
        std::unordered_map<int, std::unordered_set<int>> curPosJumpSteps;
        // the first stone will be zero, and its jumping step can only be 1;
        if (stones.empty()) {
            return true;
        }
        curPosJumpSteps[0].insert(1);
        int const stonesSize = stones.size();
        int const lastPos = stones[stonesSize - 1];
        for (int idx = 0; idx < stonesSize - 1; idx++) {
            int stone = stones[idx];
            for (int const step : curPosJumpSteps[stone]) {
                int reach = stone + step;
                if (reach == lastPos) {
                    // because we can jump with step, so if reach > stones[stonesSize - 1], it won't means we can reach
                    return true;
                }
                /*
                if (reach > lastPos) {
                    continue;
                }
                */
                curPosJumpSteps[reach].insert(step);
                curPosJumpSteps[reach].insert(step + 1);
                if (step > 1) {
                    curPosJumpSteps[reach].insert(step - 1);
                }
            }
        }
        return false;
    }
};

class Solution {
public:
    bool canCross(std::vector<int> const & stones) {
        // plagiarizing from https://leetcode.com/problems/frog-jump/discuss/193816/Concise-and-fast-DP-solution-using-2D-array-instead-of-HashMap-with-text-and-video-explanation.
        if (stones.empty()) {
            return true;
        }
        int const stonesSize = stones.size();
        // each time we jump the step larger than the former jumping, then the largest step we can jump is stonesSize
        std::vector<std::vector<bool>> dpMemo(stonesSize, std::vector<bool>(stonesSize + 1, false));
        // at the first idx, we can jump one step
        dpMemo[0][1] = true;
        for (int idx = 1; idx < stonesSize; idx++) {
            for (int from = 0; from < idx; from++) {
                int jump = stones[idx] - stones[from];
                if (jump <= 0 || jump > stonesSize || !dpMemo[from][jump]) {
                    // from from jump to idx is not right
                    continue;
                }
                dpMemo[idx][jump] = true;
                if (jump + 1 <= stonesSize) {
                    dpMemo[idx][jump + 1] = true;
                }
                if (jump > 1) {
                    dpMemo[idx][jump - 1] = true;
                }
                if (stonesSize - 1 == idx) {
                    return true;
                }
            }
        }
        return false;
    }
};

class SolutionTLE {
public:
    bool canCross(std::vector<int> const & stones, int pos = 0, int curStep = 0) {
        // plagiarizing from https://leetcode.com/problems/frog-jump/discuss/88805/Straight-forward-9ms-7-line-c%2B%2B-solution-with-explanation
        for (int idx = pos + 1; idx < stones.size(); idx++) {
            int gap = stones[idx] - stones[pos];
            if (gap < curStep - 1) {
                // we can skip the idx
                continue;
            }
            if (gap > curStep + 1) {
                // we can't jump to or over this idx, it will fail
                return false;
            }
            if (canCross(stones, idx, gap)) {
                return true;
            }
        }
        return pos + 1 == stones.size();
    }
};

class Solution {
public:
    bool canCross(std::vector<int> const & stones, int pos = 0, int curStep = 0) {
        if (pos + 1 == stones.size()) {
            return true;
        }
        // the maximum value of pos will be less than 2000. the maximum value of curStep will be stones.size();
        int code = pos | (curStep << 11);
        if (posJumpSteps.find(code) != posJumpSteps.end()) {
            return posJumpSteps[code];
        }
        // plagiarizing from https://leetcode.com/problems/frog-jump/discuss/88805/Straight-forward-9ms-7-line-c%2B%2B-solution-with-explanation
        for (int idx = pos + 1; idx < stones.size(); idx++) {
            int gap = stones[idx] - stones[pos];
            if (gap < curStep - 1) {
                // we can skip the idx
                continue;
            }
            if (gap > curStep + 1) {
                // we can't jump to or over this idx, it will fail
                return posJumpSteps[code] = false;
            }
            if (canCross(stones, idx, gap)) {
                return posJumpSteps[code] = true;
            }
        }
        return false;
    }
private:
    std::unordered_map<int, bool> posJumpSteps;
};
