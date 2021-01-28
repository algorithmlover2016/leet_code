#include "../../head.h"


class Solution {
public:
    int longestWPI(std::vector<int> const & hours) {
        // find the max window that sums larger than 0;
        // first plagiarizing idea from https://leetcode.com/problems/longest-well-performing-interval/discuss/334565/JavaC%2B%2BPython-O(N)-Solution-Life-needs-996-and-669
        int score = 0;
        int ans = 0;
        std::unordered_map<int, int> seenScore;
        for (int idx = 0; idx < hours.size(); idx++) {
            score += hours[idx] > 8 ? 1 : -1;
            if (0 < score) {
                ans = idx + 1; // from 0 to idx
            } else {
                if (seenScore.find(score) == seenScore.end()) {
                    seenScore[score] = idx;
                }
                if (seenScore.find(score - 1) != seenScore.end()) {
                    ans = std::max(ans, idx - seenScore[score - 1]);
                }
            }
        }
        return ans;
    }
};


class SolutionTLE {
public:
    int longestWPI(std::vector<int> const & hours) {
        int const hoursSize = hours.size();
        std::vector<int> preSum(hoursSize + 1, 0);
        int ans = 0;
        for (int idx = 0; idx < hoursSize; idx++) {
            preSum[idx + 1] = preSum[idx] + (hours[idx] > 8 ? 1 : -1);
            for (int innerIdx = idx; innerIdx > -1; innerIdx--) {
                if (preSum[idx + 1] - preSum[innerIdx] > 0) {
                    ans = std::max(ans, idx - innerIdx + 1);
                }
            }
        }
        return ans;
    }
};

#define DEBUG
class SolutionWrongAnswer {
public:
    int longestWPI(std::vector<int> const & hours) {
        int const hoursSize = hours.size();
        std::vector<int> preSum(hoursSize + 1, 0);
        int ans = 0;
        std::vector<int> decStack;
        for (int idx = 0; idx < hoursSize; idx++) {
            preSum[idx + 1] = preSum[idx] + (hours[idx] > 8 ? 1 : -1);
            #ifdef DEBUG
            std::cout << "\npreSum: " << preSum[idx + 1] << '\t';
            #endif
            if (preSum[idx + 1] > 0) {
                ans = idx + 1;
            } else {
                while (!decStack.empty() && preSum[decStack.back()] < preSum[idx + 1]) {
                    #ifdef DEBUG
                    std::cout << "pop: " << decStack.back() << ",\t" << idx << '\t';
                    #endif
                    // the wrong reason is that we should find the first pos that is smaller than the preSum[idx + 1]
                    ans = std::max(ans, idx + 1 - decStack.back());
                    decStack.pop_back();
                }
            }
            decStack.emplace_back(idx + 1);

        }
        return ans;
    }
};

#define DEBUG
class Solution {
public:
    int longestWPI(std::vector<int> const & hours) {
        int const hoursSize = hours.size();
        std::vector<int> preSum(hoursSize + 1, 0);
        std::vector<int> decStack;
        for (int idx = 0; idx < hoursSize; idx++) {
            preSum[idx + 1] = preSum[idx] + (hours[idx] > 8 ? 1 : -1);
            // find the smaller preSum that first appear
            if (decStack.empty() || preSum[decStack.back()] > preSum[idx + 1]) {
                decStack.emplace_back(idx + 1);
            }
        }

        int ans = 0;
        for (int idx = hoursSize - 1; idx >= ans; idx--) {
            if (preSum[idx + 1] > 0) {
                // ans = std::max(ans, idx + 1);
                ans = idx + 1;
                break;
            }
            while (!decStack.empty() && preSum[decStack.back()] < preSum[idx + 1]) {
                ans = std::max(ans, idx + 1 - decStack.back());
                decStack.pop_back();
            }
        }

        return ans;
    }
};
