#include "../../head.h"


// #define USING_MY_NEXT_PERMUTATION
// #define DEBUG
class Solution {
public:
    int getMinSwaps(std::string num, int k) {
        // plagiarizing from https://youtu.be/_83XSvgd_is and
        // https://leetcode.com/problems/minimum-adjacent-swaps-to-reach-the-kth-smallest-number/discuss/1186818/C%2B%2B-Detailed-explanation-using-next_permutation and
        // https://leetcode.com/problems/minimum-adjacent-swaps-to-reach-the-kth-smallest-number/discuss/1187098/Next-Permutation-%2B-Adjacent-Swapping  and
        // https://leetcode.com/problems/minimum-adjacent-swaps-to-reach-the-kth-smallest-number/discuss/1186921/C%2B%2B-next-permutation
        if (num.empty()) {
            return 0;
        }
        std::string oriNum(num);
        while (0 < k--) {
            #ifdef USING_MY_NEXT_PERMUTATION
            myNextPermutation(num);
            #else
            std::next_permutation(num.begin(), num.end());
            #endif
        }
        #ifdef DEBUG
        std::cout << oriNum << ",\t" << num << "\n";
        #endif

        return adjustSwap(oriNum, num);
    }
private:
    int adjustSwap(std::string ori, std::string const & str) {
        int const oriSize = ori.size();
        int const strSize = str.size();
        if (oriSize != strSize) {
            return -1;
        }
        int ans = 0;
        for (int strIdx = 0; strIdx < strSize; strIdx++) {
            int oriIdx = strIdx;
            while (ori[oriIdx] != str[strIdx]) {
                oriIdx++;
            }
            while (oriIdx > strIdx) {
                std::swap(ori[oriIdx], ori[oriIdx - 1]);
                oriIdx--;
                ans++;

            }
        }
        return ans;
    }
    void myNextPermutation(std::string & num) {
        // plagiarizing from https://youtu.be/_83XSvgd_is
        int const numSize = num.size();
        if (1 >= numSize) {
            return;
        }

        int firstInc = - 1;
        for (int idx = numSize - 2; idx > -1; idx--) {
            if (num[idx] < num[idx + 1]) {
                firstInc = idx;
                break;
            }
        }
        if (-1 != firstInc) {
            // we find a reverse order, increasing order
            int firstLarger = - 1;
            for (int idx = numSize - 1; idx > firstInc; idx--) {
                if (num[idx] > num[firstInc]) {
                    firstLarger = idx;
                    std::swap(num[firstLarger], num[firstInc]);
                    break;
                }
            }
            std::reverse(num.begin() + firstInc + 1, num.end());
            #ifdef DEBUG
            std::cout << "\t after iter: " << num << ";\t";
            #endif
        }
    }
};
