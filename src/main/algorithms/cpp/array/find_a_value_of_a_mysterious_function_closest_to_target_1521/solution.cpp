#include "../../head.h"


class SolutionTLE {
public:
    int closestToTarget(std::vector<int> const & arr, int target) {
        int const arrSize = arr.size();
        std::vector<std::vector<int>> dpMemo(arrSize, std::vector<int>(arrSize, 0));
        
        int ans = INT_MAX;
        for (int row = 0; row < arrSize; row++) {
            dpMemo[row][row] = arr[row];
            ans = std::min(std::abs(dpMemo[row][row] - target), ans);
            for (int col = row + 1; col < arrSize; col++) {
                dpMemo[row][col] = dpMemo[row][col - 1] & arr[col];
                ans = std::min(std::abs(dpMemo[row][col] - target), ans);
            }
        }
        return ans;
    }
};

class SolutionNLogMaxEleSpace {
public:
    int closestToTarget(std::vector<int> const & arr, int target) {
        // plagiarizing from https://leetcode.com/problems/find-a-value-of-a-mysterious-function-closest-to-target/discuss/743741/Detailed-General-Ideasolution-for-such-problems-(-AND-OR-GCD-)-in-O(N-*-log(-max(arri)-)-)
        int const arrSize = arr.size();
        if (arr.empty()) {
            return target;
        }
        std::vector<std::set<int>> dpMemo(arrSize);
        dpMemo[0].insert(arr[0]);
        int ans = INT_MAX;
        for (int idx = 1; idx < arrSize; idx++) {
            dpMemo[idx].insert(arr[idx]);
            ans = std::min(ans, std::abs(arr[idx] - target));
            for (int const preVal : dpMemo[idx -1]) {
                int newVal = preVal & arr[idx];
                dpMemo[idx].insert(newVal);
                ans = std::min(ans, std::abs(newVal - target));
            }
        }
        return ans;
    }
};


class SolutionLessSpaceMoreTime {
public:
    int closestToTarget(std::vector<int> const & arr, int target) {
        // plagiarizing from https://leetcode.com/problems/find-a-value-of-a-mysterious-function-closest-to-target/discuss/743741/Detailed-General-Ideasolution-for-such-problems-(-AND-OR-GCD-)-in-O(N-*-log(-max(arri)-)-)
        int const arrSize = arr.size();
        if (arr.empty()) {
            return target;
        }
        std::vector<std::set<int>> dpMemo(2);
        dpMemo[0].insert(arr[0]);
        int ans = INT_MAX;
        for (int idx = 1; idx < arrSize; idx++) {
            dpMemo[1].insert(arr[idx]);
            ans = std::min(ans, std::abs(arr[idx] - target));
            for (int const preVal : dpMemo[0]) {
                int newVal = preVal & arr[idx];
                dpMemo[1].insert(newVal);
                ans = std::min(ans, std::abs(newVal - target));
            }
            dpMemo[0] = dpMemo[1];
            dpMemo[1].clear();
        }
        return ans;
    }
};

class Solution {
public:
    int closestToTarget(std::vector<int> const & arr, int target) {
        // plagiarizing from https://leetcode.com/problems/find-a-value-of-a-mysterious-function-closest-to-target/discuss/743741/Detailed-General-Ideasolution-for-such-problems-(-AND-OR-GCD-)-in-O(N-*-log(-max(arri)-)-)
        int const arrSize = arr.size();
        if (arr.empty()) {
            return target;
        }
        std::set<int> dpMemo;
        dpMemo.insert(arr[0]);
        int ans = INT_MAX;
        for (int idx = 1; idx < arrSize; idx++) {
            std::set<int> tmpDpMemo;
            tmpDpMemo.insert(arr[idx]);
            ans = std::min(ans, std::abs(arr[idx] - target));
            for (int const preVal : dpMemo) {
                int newVal = preVal & arr[idx];
                tmpDpMemo.insert(newVal);
                ans = std::min(ans, std::abs(newVal - target));
            }
            dpMemo = tmpDpMemo;
        }
        return ans;
    }
};

class Solution {
public:
    int closestToTarget(vector<int>& arr, int target) {
        int tail = 0;
        int segSize = 200;
        vector<int> quick;
        quick.push_back(arr[0]);

        for(int i = 1, index = 0, c = 1; i < arr.size(); ++i) {
            auto val = arr[i];
            if (arr[tail] != val) {
                arr[++tail] = val;

                if (c == 0) {
                    quick.push_back(val);
                } else {
                    quick.back() &= val;
                }

                if (++c == segSize) {
                    c = 0;
                    ++index;
                }
            }
        }

        int ans = abs(arr[0]-target);

        for (int i = 0; i <= tail; ++i) {
            int j = i;
            int val = 0xffffffff;
            while(j <= tail) {
                if (j % segSize == 0) {
                    int tmp = val & quick[j/segSize];

                    if (tmp >= target) {
                        val = tmp;
                        ans = min(ans, abs(val-target));
                        j += segSize;
                        continue;
                    }
                }

                val &= arr[j++];
                ans = min(ans, abs(val-target));

                if (val < target) break;
            }

            if (ans == 0) break;
        }

        return ans;
    }
};
