#include "../../head.h"


#define USING_SORT_INSTEAD_OF_MAP
#ifndef USING_SORT_INSTEAD_OF_MAP
#define USING_ARRAY_INSTEAD_OF_MAP
#endif
// #undef USING_ARRAY_INSTEAD_OF_MAP
class Solution {
public:
    int minIncrementForUnique(std::vector<int> nums) {
        // plagiarizing from https://youtu.be/9Ifuv46fmo4
        if (nums.empty()) {
            return 0;
        }
        int ans = 0;
        int pre = -1;
        // sorting the array of nums and then count the operations
#ifdef USING_SORT_INSTEAD_OF_MAP
        std::sort(nums.begin(), nums.end());
        for (int num : nums) {
            if (pre >= num) {
                ans += pre - num + 1; // update the num to pre + 1;
                num = pre + 1;
            }
            pre = num;
        }
#else
        int maxNum = -1;
        static int const MAX_NUM = 40000 + 1;

#ifdef USING_ARRAY_INSTEAD_OF_MAP
        std::vector<int> numsCnt(MAX_NUM, 0);
#else
        std::map<int, int> numsCnt;
#endif

        for (int num : nums) {
            numsCnt[num]++;
        }
        for (int num = 0; num < MAX_NUM; num++) {
#ifndef USING_ARRAY_INSTEAD_OF_MAP
            int cnt = 0;
            if (numsCnt.find(num) != numsCnt.end()) {
                cnt = numsCnt[num];
            }
#else
            int cnt = numsCnt[num];
#endif
            if (0 < cnt) {
                // there exists one or many num in nums
                // except the first num, the others are all need adding operation
                int totalNeedADDOper = (cnt - 1) * cnt / 2;
                maxNum = std::max(maxNum, num + cnt - 1);

                if (pre >= num) {
                    // the first num alse need update
                    // we should update all the number of num to pre + 1 and then add the left num except the first one;
                    totalNeedADDOper += cnt * (pre - num + 1);
                    maxNum = pre + cnt; // maxNum = pre + 1 + cnt - 1;
                }

                pre = maxNum;
                ans += totalNeedADDOper;
            }
        }
#endif
        return ans;
    }
};
