#include "../../head.h"


class SolutionDFS {
private:
    static int const LOWER_CASE_LETTERSCNT = 26;
public:
    int findRotateSteps(std::string const & ring, std::string const & key) {
        // plagiarizing from https://leetcode.com/problems/freedom-trail/discuss/98929/Evolve-from-brute-force-to-dp
        // brute force solution with memory
        std::array<std::vector<int>, LOWER_CASE_LETTERSCNT> pos;
        int const ringSize = ring.size(), keySize = key.size();
        for (int index = 0; index < ringSize; index++) {
            // mark each lower case letters' position
            pos[ring[index] - 'a'].emplace_back(index);
        }
        // std::vector<std::vector<int>> memo(keySize, std::vector<int>(ringSize, 0));
        // initialization the memo with the two format is right, just using right array subscript
        // the follor is just easy to understand
        std::vector<std::vector<int>> memo(ringSize, std::vector<int>(keySize, 0));
        return dfsHelper(ring, key, pos, memo, 0, 0);
    }
private:
    int dfsHelper(std::string const & ring, std::string const & key, std::array<std::vector<int>, LOWER_CASE_LETTERSCNT> const & pos,
            std::vector<std::vector<int>> & memo, int const ringStart, int const keyStart) {
        int const ringSize = ring.size();
        if (keyStart >= key.size()) {
            return 0;

        }
        if (0 != memo[ringStart][keyStart]) {
            return memo[ringStart][keyStart];
        }
        int minStep = INT_MAX;
        for (int const next : pos[key[keyStart] - 'a']) {
            int diff = std::abs(ringStart - next);
            minStep = std::min(minStep, std::min(diff, ringSize - diff) +
                               dfsHelper(ring, key, pos, memo, next, keyStart + 1));
        }
        return memo[ringStart][keyStart] = minStep + 1; // plus one for the pressing key operation
    }
};


class SolutionDP {
private:
    static int const LOWER_CASE_LETTERSCNT = 26;
public:
    int findRotateSteps(std::string const & ring, std::string const & key) {
        // plagiarizing from https://leetcode.com/problems/freedom-trail/discuss/98929/Evolve-from-brute-force-to-dp
        // dp
        std::array<std::vector<int>, LOWER_CASE_LETTERSCNT> pos;
        int const ringSize = ring.size(), keySize = key.size();
        for (int index = 0; index < ringSize; index++) {
            // mark each lower case letters' position
            pos[ring[index] - 'a'].emplace_back(index);
        }

        std::vector<std::vector<int>> dp(keySize + 1, std::vector<int>(ringSize, INT_MAX));
        dp[keySize].assign(ringSize, 0);
        for (int index = keySize - 1; index >=0; index--) {
            for (int ringIndex = 0; ringIndex < ringSize; ringIndex++) {
                for (int const next : pos[key[index] - 'a']) {
                    int diff = std::abs(ringIndex - next);
                    dp[index][ringIndex] = std::min(dp[index][ringIndex],
                            std::min(diff, ringSize - diff) + dp[index + 1][next]);
                }
            }
        }
        return dp[0][0] + keySize;
    }

    int findRotateStepsPressButtom(std::string const & ring, std::string const & key) {
        // plagiarizing from https://leetcode.com/problems/freedom-trail/discuss/98929/Evolve-from-brute-force-to-dp
        // dp
        std::array<std::vector<int>, LOWER_CASE_LETTERSCNT> pos;
        int const ringSize = ring.size(), keySize = key.size();
        for (int index = 0; index < ringSize; index++) {
            // mark each lower case letters' position
            pos[ring[index] - 'a'].emplace_back(index);
        }

        std::vector<std::vector<int>> dp(keySize + 1, std::vector<int>(ringSize, INT_MAX));
        dp[keySize].assign(ringSize, 0);
        for (int index = keySize - 1; index >=0; index--) {
            for (int ringIndex = 0; ringIndex < ringSize; ringIndex++) {
                for (int const next : pos[key[index] - 'a']) {
                    int diff = std::abs(ringIndex - next);
                    dp[index][ringIndex] = std::min(dp[index][ringIndex],
                            std::min(diff, ringSize - diff) + 1 + dp[index + 1][next]);
                }
            }
        }
        return dp[0][0];
    }

    int findRotateSteps_ON_(std::string const & ring, std::string const & key) {
        // plagiarizing from https://leetcode.com/problems/freedom-trail/discuss/98929/Evolve-from-brute-force-to-dp
        // dp
        std::array<std::vector<int>, LOWER_CASE_LETTERSCNT> pos;
        int const ringSize = ring.size(), keySize = key.size();
        for (int index = 0; index < ringSize; index++) {
            // mark each lower case letters' position
            pos[ring[index] - 'a'].emplace_back(index);
        }

        std::vector<int> pre(ringSize, 0), cur(ringSize, INT_MAX), *prePtr = &pre, *curPtr = &cur;
        for (int index = keySize - 1; index >=0; index--) {
            for (int ringIndex = 0; ringIndex < ringSize; ringIndex++) {
                for (int const next : pos[key[index] - 'a']) {
                    int diff = std::abs(ringIndex - next);
                    (*curPtr)[ringIndex] = std::min((*curPtr)[ringIndex],
                            std::min(diff, ringSize - diff) + 1 + (*prePtr)[next]);
                }
            }
            std::swap(prePtr, curPtr);
            (*curPtr).assign(ringSize, INT_MAX);
        }
        return (*prePtr)[0];
    }
};
