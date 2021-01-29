#include "../../head.h"


class Solution {
public:
    bool isPossible(std::vector<int> const & nums) {
        // plagiarizing idea from https://leetcode.com/problems/split-array-into-consecutive-subsequences/discuss/106514/C%2B%2BPython-Esay-Understand-Solution
        int const numsSize = nums.size();
        if (JUST_LEN_TWO >= numsSize)  {
            return false;
        }

        std::unordered_map<int, int> left, end;
        for (int const num : nums) {
            left[num]++;
        }
        for (int const num : nums) {
            if (JUST_ZERO == left[num]) {
                // no need to arrange this item
                continue;
            } else {
                // we need find a position for this item, which means we are going to use this item
                left[num]--;
            }
            if (JUST_ZERO < end[num - 1]) {
                // this item can be added at the end of existing subsequence
                // we add the num to as the end of num - 1 (which already is construct a subsequence whose length > 3;
                end[num - 1]--;
                end[num]++;
            } else if (JUST_ZERO < left[num + 1] && JUST_ZERO < left[num + 2]) {
                // this item need construct a new subsequence
                left[num + 1]--;
                left[num + 2]--;
                end[num + 2]++;
            } else {
                return false;
            }
        }
        return true;

    }
private:
    static int const JUST_LEN_TWO = 2;
    static int const JUST_ZERO = 0;

};

// #define DEBUG
class Solution {
public:
    bool isPossible(std::vector<int> const & nums) {
        // plagiarizing idea from https://leetcode.com/problems/split-array-into-consecutive-subsequences/discuss/106495/Java-O(n)-time-and-O(1)-space-solution-greedily-extending-shorter-subsequence
        int const numsSize = nums.size();
        if (JUST_LEN_TWO >= numsSize)  {
            return false;
        }

        int pre = INIT_MIN;
        int preLen1 = 0, preLen2 = 0, preLen3 = 0;

        int cur = 0;
        int curCnt = 0;
        int curLen1 = 0, curLen2 = 0, curLen3 = 0;
        for (int idx = 0; idx < numsSize; pre = cur, preLen1 = curLen1, preLen2 = curLen2, preLen3 = curLen3) {
            for (cur = nums[idx], curCnt = 0; idx < numsSize && cur == nums[idx]; idx++) {
                curCnt++;
            }
            if (cur != pre + 1) { // can't construct a subsequence with its previous element
                if (JUST_ZERO != preLen1 || JUST_ZERO != preLen2) {
                    return false;
                } else {
                    curLen1 = curCnt;
                    curLen2 = 0;
                    curLen3 = 0;
                }
            } else {
                if (curCnt < preLen1 + preLen2) {
                    //this must be met to go though
                    return false;
                }
                curLen1 = std::max(JUST_ZERO, curCnt - preLen1 - preLen2 - preLen3);
                curLen2 = preLen1;
                curLen3 = preLen2 + std::min(preLen3, curCnt - preLen1 - preLen2);
                // if (curLen3 < preLen2) {
                //     return false;
                // }
                #ifdef DEBUG
                std::cout << "cur: " << cur << ",\t" << curLen1 << ",\t" << curLen2 << ",\t" << curLen3 << "\n";
                #endif

            }
        }
        return (JUST_ZERO == preLen1 && JUST_ZERO == preLen2);
    }

    private:
    static int const JUST_LEN_TWO = 2;
    static int const JUST_ZERO = 0;
    static int const INIT_MIN = INT_MIN;
};
