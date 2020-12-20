#include "../../head.h"


class SolutionWrongAnswer {
public:
    bool increasingTriplet(std::vector<int> const & nums) {
        // can't solve the input
        // 1, 0, 0, 10, 0, 1000
        // backStack
        std::vector<int> incStack;
        for (int const num : nums) {
            while (!incStack.empty() && incStack.back() >= num) {
                incStack.pop_back();
            }
            incStack.emplace_back(num);
            if (LEN < incStack.size()) {
                return true;
            }
        }
        return false;
    }
private:
    static int const LEN = 3 - 1; // to avoid equal comparation
};

class Solution {
public:
    bool increasingTriplet(std::vector<int> const & nums) {
        // dp
        std::vector<int> dp;
        std::vector<int>::iterator lowIt;
        for (int const num : nums) {
            lowIt = std::lower_bound(dp.begin(), dp.end(), num);
            if (lowIt == dp.end()) {
                dp.emplace_back(num);
            } else {
                *lowIt = num;
            }

            if (LEN < dp.size()) {
                return true;
            }
        }
        return false;
    }
private:
    static int const LEN = 3 - 1; // to avoid equal comparation
};

class Solution {
public:
    bool increasingTriplet(std::vector<int> const & nums) {
        // plagiarizing from https://www.youtube.com/watch?v=QBiEJul9bUk
        int smallest = INT_MAX, secondSmallest = INT_MAX;
        for (int const num : nums) {
            if (num <= smallest) {
                smallest = num;
            } else if (num <= secondSmallest) {
                secondSmallest = num;
            } else {
                return true;
            }
        }
        return false;
    }
};
