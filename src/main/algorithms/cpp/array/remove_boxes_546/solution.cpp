#include "../../head.h"


class SolutionTLE {
public:
    int removeBoxes(std::vector<int> const & boxes) {
        // plagiarizing from https://leetcode.com/problems/remove-boxes/discuss/101310/Java-top-down-and-bottom-up-DP-solutions
        // and https://leetcode.com/problems/remove-boxes/discuss/101312/Memoization-DFS-C%2B%2B
        // and https://youtu.be/6EfBJX9uLDI
        int const boxesSize = boxes.size();
        // from i to j, at most boxesSize elements, which means the former elements's number is at most boxesSize - 1;
        std::vector<std::vector<std::vector<int>>> dpMemo(boxesSize, std::vector<std::vector<int>>(boxesSize + 1,
                    std::vector<int>(boxesSize + 1, 0)));
        return dfs(boxes, 0, boxesSize, 0, dpMemo);
    }
    int dfs(std::vector<int> const & boxes,
            int start, int end, int pre,
            std::vector<std::vector<std::vector<int>>> & dpMemo) {
        if (start == end) {
            return 0;
        }
        if (0 != dpMemo[start][end][pre]) {
            return dpMemo[start][end][pre];
        }
        for (; start + 1 < end && boxes[start + 1] == boxes[start]; start++, pre++) {
            // only when boxes[start + 1] == boxes[start], we will add one to pre
            // if boxes[start + 1] != boxes[start], we won't add one to pre
            // so latter we compute the size, we need add one to pre
            ;
        }
        int ans = dfs(boxes, start + 1, end, 0, dpMemo) + (pre + 1) * (pre + 1);
        for (int split = start + 1; split < end; split++) {
            if (boxes[split] == boxes[start]) {
                ans = std::max(ans, dfs(boxes, start + 1, split, 0, dpMemo) + dfs(boxes, split, end, pre + 1, dpMemo));
            }
        }
        return dpMemo[start][end][pre] = ans;
    }

};

// #define DEBUG
class Solution {
public:
    int removeBoxes(std::vector<int> const & boxes) {
        // plagiarizing from https://leetcode.com/problems/remove-boxes/discuss/101310/Java-top-down-and-bottom-up-DP-solutions
        int const boxesSize = boxes.size();
        // from i to j, at most boxesSize elements, which means the former elements's number is at most boxesSize - 1;
        std::vector<std::vector<std::vector<int>>> dpMemo(boxesSize, std::vector<std::vector<int>>(boxesSize,
                    std::vector<int>(boxesSize, 0)));

        for (int idx = 0; idx < boxesSize; idx++) {
            for (int pre = 0; pre < boxesSize; pre++) {
                dpMemo[idx][idx][pre] = (pre + 1) * (pre + 1);
            }
        }
        #ifdef DEBUG
        std::cout << "go on\n";
        #endif

        for (int len = 2; len <= boxesSize; len++) {
            // the difference of left and right will at leat one
            for (int right = len - 1; right < boxesSize; right++) {
                int left = right - (len - 1);

            // similar to
            /*
            for (int left = 0; left + len -  1 < boxesSize; left++) {
                int right = left + len - 1;
            */

                /*
                while (left + 1 <= right && boxes[left + 1] == boxes[left]) {
                    left++;
                }
                */

                #ifdef DEBUG
                std::cout << left << ",\t" << right << ";\t";
                #endif

                for (int pre = 0; pre <= left; pre++) {
                    #ifdef DEBUG
                    std::cout << pre << ";\t";
                    #endif
                    // boxes[left] != boxes[left + 1]
                    // it may have pre elements, and pre >= 0 and pre <= left
                    int ans = (pre + 1) * (pre + 1) + dpMemo[left + 1][right][0];
                    for (int split = left + 1; split <= right; split++) {
                        if (boxes[split] == boxes[left]) {
                            ans = std::max(ans, dpMemo[left + 1][split - 1][0] + dpMemo[split][right][pre + 1]);
                        }
                    }
                    dpMemo[left][right][pre] = ans;
                }
                #ifdef DEBUG
                std::cout << "\n";
                #endif
            }
        }
        return dpMemo[0][boxesSize - 1][0];
    }
};
