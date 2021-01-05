#include "../../head.h"


class Solution {
public:
    int maxJumps(std::vector<int> const & arr, int d) {
        // plagiarizing from https://leetcode.com/problems/jump-game-v/discuss/501439/O(N)-Solution-is-Gone
        // https://mp.weixin.qq.com/s/kEQ00_WLqDTG6tbsjQ2Xjw
        if (arr.empty() || JUST_RETURN_ZERO == d) {
            return 0;
        }
        int const arrSize = arr.size();
        std::vector<int> dpMemo(arrSize, DP_INIT_VAL);

        int ans = 0;
        for (int idx = 0; idx < arrSize; idx++) {
            ans = std::max(ans, dfs(arr, dpMemo, idx, d));
        }
        return ans;
    }
    int dfs(std::vector<int> const & arr,
            std::vector<int> & dpMemo,
            int idx,
            int d) {
        int const arrSize = arr.size();
        if (DP_INIT_VAL != dpMemo[idx]) {
            return dpMemo[idx];
        }
        int ans = 1; // means the current idx can be get
        for (auto const direction : directions) {
            int start = idx + direction; // include
            int end = idx + d * direction + direction; // exclude
            if (start > end) {
                end = std::max(end, -1);
                for (int mid = start; mid > end; mid--) {
                    if (arr[mid] < arr[idx]) {
                        ans = std::max(ans, dfs(arr, dpMemo, mid, d) + 1);
                    } else {
                        break;
                    }
                }
            } else {
                end = std::min(end, arrSize);
                for (int mid = start; mid < end; mid++) {
                    if (arr[mid] < arr[idx]) {
                        ans = std::max(ans, dfs(arr, dpMemo, mid, d) + 1);
                    } else {
                        break;
                    }
                }
            }
        }
        return dpMemo[idx] = ans;

    }


private:
    static int const DIRECTION_ARRAY_SIZE = 2;
    static std::array<int, DIRECTION_ARRAY_SIZE> directions;
    static int const JUST_RETURN_ZERO = 0;
    int const DP_INIT_VAL = 0;
};
std::array<int, Solution::DIRECTION_ARRAY_SIZE> Solution::directions{{-1, 1}};

class SolutionSortPair {
public:
    int maxJumps(std::vector<int> arr, int d) {
        // plagiarizing from https://leetcode.com/problems/jump-game-v/discuss/501439/O(N)-Solution-is-Gone
        // https://mp.weixin.qq.com/s/kEQ00_WLqDTG6tbsjQ2Xjw
        if (arr.empty() || JUST_RETURN_ZERO == d) {
            return 0;
        }

        int const arrSize = arr.size();
        std::vector<std::pair<int, int>> arrRebuild(arrSize);
        for (int idx = 0; idx < arrSize; idx++) {
            arrRebuild[idx] = std::make_pair(arr[idx], idx);
        }

        std::sort(arrRebuild.begin(), arrRebuild.end());

        std::vector<int> dpMemo(arrSize, 1);

        int ans = 0;
        for (auto const & point : arrRebuild) {
            for (auto const & direction : directions) {
                int start = point.second + direction; // included
                int end = point.second + direction + d * direction; // excluded
                if (start > end) {
                    end = std::max(end, -1);
                    for (int mid = start; mid > end; mid--) {
                        if (arr[mid] < point.first) {
                            // because arrRebuild has been sorted, the smaller point.first has been computed
                            dpMemo[point.second] = std::max(dpMemo[point.second], dpMemo[mid] + 1);
                        } else {
                            break;
                        }
                    }
                } else {
                    end = std::min(end, arrSize);
                    for (int mid = start; mid < end; mid++) {
                        if (arr[mid] < point.first) {
                            dpMemo[point.second] = std::max(dpMemo[point.second], dpMemo[mid] + 1);
                        } else {
                            break;
                        }
                    }
                }
            }
            ans = std::max(ans, dpMemo[point.second]);
        }
        return  ans;
    }

private:
    static int const DIRECTION_ARRAY_SIZE = 2;
    static std::array<int, DIRECTION_ARRAY_SIZE> directions;
    static int const JUST_RETURN_ZERO = 0;
    int const DP_INIT_VAL = 0;
};
std::array<int, Solution::DIRECTION_ARRAY_SIZE> Solution::directions{{-1, 1}};



class Solution {
public:
    int maxJumps(std::vector<int> arr, int d) {
        // plagiarizing from accept answer, I can't find the author
        if (arr.empty() || JUST_RETURN_ZERO == d) {
            return 0;
        }
        arr.emplace_back(INT_MAX);

        int const arrAddSize = arr.size();

        std::vector<int> dpMemo(arrAddSize, 1);
        std::stack<int> decStack;

        for (int idx = 0; idx < arrAddSize; idx++) {
            while (!decStack.empty() && arr[idx] > arr[decStack.top()]) {
            // the decStack.back() can't jump to idx
                int preIdx = decStack.top(); decStack.pop();
                int end = std::min(idx, preIdx + d + 1);
                // for (int innerIdx = preIdx + 1; innerIdx < end && arr[innerIdx] < arr[preIdx]; innerIdx++) {
                for (int innerIdx = preIdx + 1; innerIdx < end && arr[innerIdx] != arr[preIdx]; innerIdx++) {
                    // from the preIdx jump to its most right
                    // in this internal, there always be true that arr[innerIdx] <= arr[preIdx], so we just remove the case that ==
                    dpMemo[preIdx] = std::max(dpMemo[preIdx], dpMemo[innerIdx] + 1);
                }
                // because all of the number [preIdx + 1, idx) is smaller than dpMemo[preIdx] at least 1
                if (preIdx >= idx - d) {
                    dpMemo[idx] = std::max(dpMemo[idx], dpMemo[preIdx] + 1);
                }
            }
            decStack.emplace(idx);
        }
        return *std::max_element(dpMemo.begin(), std::prev(dpMemo.end()));
    }
private:
    static int const JUST_RETURN_ZERO = 0;
};
