#include "../../head.h"


class SolutionTLE {
public:
    int numberWays(std::vector<std::vector<int>> const & hats) {
        std::vector<int> used(NUM_LEN, 0);
        for (std::vector<int> const & hat : hats) {
            if (1 == hat.size()) {
                if (used[hat[0]]) {
                    return 0;
                }
                used[hat[0]] = 1;
            }
        }

        int ans = 0;
        backTracking(hats, used, 0, ans);
        return ans;
    }
private:
    void backTracking(std::vector<std::vector<int>> const & hats,
            std::vector<int> & used,
            int index, int & ans) {
        // all the people have the hat
        if (index == hats.size()) {
            ans++;
            return;
        }
        if (1 == hats[index].size()) {
            backTracking(hats, used, index + 1, ans);
        }
        for (int const hat : hats[index]) {
            if (used[hat]) {
                continue;
            }
            used[hat] = 1;
            backTracking(hats, used, index + 1, ans);
            used[hat] = 0;
        }
    }
private:
    int const NUM_LEN = 41;

};

class SolutionDPRecursive {
private:
    // the first element record the index from 1 to 40. the second record the people
    typedef std::tuple<int, int> hatStateKey;
    struct key_hash : public std::unary_function<hatStateKey, std::size_t> {
        std::size_t  operator()(const hatStateKey & kk) const {
            return (std::get<0>(kk) << 20) | (std::get<1>(kk));
        }
    };
    struct key_equal : public std::binary_function<hatStateKey, hatStateKey, bool> {
        bool operator()(hatStateKey const & k1, hatStateKey const & k2) const {
            return (std::get<0>(k1) == std::get<0>(k2) &&
                    std::get<1>(k1) == std::get<1>(k2));
        }
    };
    typedef std::unordered_map<hatStateKey, int, key_hash, key_equal> tupleUnorderedMap;

public:
    int numberWays(std::vector<std::vector<int>> const & hats) {
        // dpRecursive
        // remap the hat -> people
        hats2People.resize(HATS_LEN);
        for (int idx = 0; idx < hats.size(); idx++) {
            for (int const hat : hats[idx]) {
                hats2People[hat].emplace_back(idx);
            }
        }
        int const hatsSize = hats.size();
        return dpRecursive(1, 0, hatsSize);
    }
    int dpRecursive(int idx, int maskState, int const hatsSize) {
        hatStateKey key = std::make_tuple(idx, maskState);
        if (dpMap.find(key) != dpMap.end()) {
            return dpMap[key];
        }

        // when you get a conbination, you get an answer, so we return 1
        if (((1 << hatsSize) - 1) == maskState) {
            return 1;
        }

        // if we use out the hats and we can't find a solution, there is no answer
        if (idx >= HATS_LEN) {
            return 0;
        }

        // if we don't use this hat, idx + 1, and maskState doesn't change
        int ans = dpRecursive(idx + 1, maskState, hatsSize);
        ans %= MOD;

        for (int const people : hats2People[idx]) {
            if (0 == (maskState & (1 << people))) {
                ans += dpRecursive(idx + 1, maskState | (1 << people), hatsSize);
                ans %= MOD;
            }
        }
        return dpMap[key] = ans;
    }

private:
    int const HATS_LEN = 41;
    int const MOD = 1e9 + 7;
    std::vector<std::vector<int>> hats2People;
    tupleUnorderedMap dpMap;
};

class SolutionTwoDemension {
public:
    int numberWays(std::vector<std::vector<int>> const & hats) {
        // plagiarizing from https://www.youtube.com/watch?v=SlwENy96xdE
        // dpRecursive
        // remap the hat -> people
        hats2People.resize(HATS_LEN);
        for (int idx = 0; idx < hats.size(); idx++) {
            for (int const hat : hats[idx]) {
                hats2People[hat].emplace_back(idx);
            }
        }
        int const hatsSize = hats.size();
        int const hatsSizeComb = 1 << hatsSize;
        std::vector<std::vector<int>> dpMemo(2, std::vector<int>(hatsSizeComb, 0));

        // when there is no hats and no people, return 1 for only one answer
        dpMemo[0][0] = 1;
        dpMemo[1] = dpMemo[0];
        // because we use dpMemo[1] to record the new state, so we can change the loop order
        // for example, at the second loop, we first traversal p and then maskState, which means exchange 1(or 3) with 2
        // we can alse initialize the maskState to (hatsSizeCom - 1) and downto zero.
        for (int idx = 1; idx < HATS_LEN; idx++) {
            // for (int maskState = 0; maskState < hatsSizeComb; maskState++) { // 1
            for (int maskState = (hatsSizeComb - 1); maskState >= 0; maskState--) { // 3
                for (int const p : hats2People[idx]) { // 2
                    if (maskState & (1 << p)) {
                        dpMemo[1][maskState] += dpMemo[0][maskState ^ (1 << p)];
                        dpMemo[1][maskState] %= MOD;
                    }
                }
            }
            dpMemo[0] = dpMemo[1];
        }
        return dpMemo[0][hatsSizeComb - 1];
    }

private:
    int const HATS_LEN = 41;
    int const MOD = 1e9 + 7;
    std::vector<std::vector<int>> hats2People;
};

class Solution {
public:
    int numberWays(std::vector<std::vector<int>> const & hats) {
        // plagiarizing from https://leetcode.com/problems/number-of-ways-to-wear-different-hats-to-each-other/discuss/608686/C%2B%2B-Bit-masks-and-Bottom-Up-DP
        hats2People.resize(HATS_LEN);
        for (int idx = 0; idx < hats.size(); idx++) {
            for (int const hat : hats[idx]) {
                hats2People[hat].emplace_back(idx);
            }
        }

        int const hatsSize = hats.size();
        int const hatsSizeComb = 1 << hatsSize;

        std::vector<int> dpMemo(hatsSizeComb, 0);

        dpMemo[0] = 1;

        // at this time, we must decreasing traversal maskState
        // because dpMemo have recorded the last loop message, so we can't modify it if we use its value later
        for (int idx = 1; idx < HATS_LEN; idx++) {
            for (int maskState = (hatsSizeComb - 1); maskState >= 0; maskState--) {
                for (int const p : hats2People[idx]) {
                    if (0 == (maskState & (1 << p))) {
                        dpMemo[maskState | (1 << p)] += dpMemo[maskState];
                        dpMemo[maskState | (1 << p)] %= MOD;
                    }
                }
            }
        }
        return dpMemo[hatsSizeComb - 1];
    }

private:
    int const HATS_LEN = 41;
    int const MOD = 1e9 + 7;
    std::vector<std::vector<int>> hats2People;
};
