#include "../../head.h"


#define DEBUG
class SolutionWrong {
public:
    int maxCoins(std::vector<int> const & nums) {
        int const numsSize = nums.size();
        if (nums.empty()) {
            return 0;
        }
        if (JUST_ONE == numsSize) {
            return nums[0];
        }
        std::list<int> numsList(nums.begin(), nums.end());
        numsList.insert(numsList.begin(), 1);
        numsList.insert(numsList.end(), 1);
        int ans = 0;
        while (PRESUDO_SIZE < numsList.size())  {
            auto const curMinIter = std::min_element(std::next(numsList.begin()), std::prev(numsList.end()));
            #ifdef DEBUG
            std::cout << "cur: " << *curMinIter << "\t";
            #endif
            auto const preIter = std::prev(curMinIter);
            #ifdef DEBUG
            std::cout << "pre: " << *preIter << "\t";
            #endif
            auto const nextIter = std::next(curMinIter);
            #ifdef DEBUG
            std::cout << "next: " << *nextIter << "\t";
            #endif
            ans += (*curMinIter) * (*preIter) * (*nextIter);
            numsList.erase(curMinIter);
            #ifdef DEBUG
            std::cout << "\n";
            #endif
            
        }
        return ans;
        
    }
private:
    static int const JUST_ONE = 1;
    static int const PRESUDO_SIZE = 2;
    
};

class SolutionTLE {
public:
    int maxCoins(std::vector<int> const & nums) {
        int const numsSize = nums.size();
        if (nums.empty()) {
            return 0;
        }
        if (JUST_ONE == numsSize) {
            return nums[0];
        }
        std::vector<bool> used(numsSize, false);
        return dfs(nums, used);
    }
    int dfs(std::vector<int> const & nums,
            std::vector<bool> & used) {
        int ans = INIT_MIN;
        int const usedSize = used.size();
        for (int idx = 0; idx < usedSize; idx++) {
            if (used[idx]) {
                continue;
            }

            int left = 1, leftIdx = idx - 1;
            while (MOST_LEFT_IDX < leftIdx && used[leftIdx]) {
                leftIdx--;
            }
            if (MOST_LEFT_IDX < leftIdx) {
                left = nums[leftIdx];
            }

            int right = 1, rightIdx = idx + 1;
            while (usedSize > rightIdx && used[rightIdx]) {
                rightIdx++;
            }
            if (usedSize > rightIdx) {
                right = nums[rightIdx];
            }
            used[idx] = true;
            int curAns = nums[idx] * left * right + dfs(nums, used);
            used[idx] = false;
            ans = std::max(ans, curAns);
        }
        return ans;

    }
private:
    static int const JUST_ONE = 1;
    static int const INIT_MIN = 0;
    static int const MOST_LEFT_IDX = -1;
};
class SolutionDCMEMO {
public:
    int maxCoins(std::vector<int> const & nums) {
        // plagiarizing from https://leetcode.com/problems/burst-balloons/discuss/76228/Share-some-analysis-and-explanations
        int const numsSize = nums.size();
        if (nums.empty()) {
            return 0;
        }
        if (JUST_ONE == numsSize) {
            return nums[0];
        }

        std::vector<int> addLeftRightNums(numsSize + 2, 1);
        for (int idx = 1; idx <= numsSize; idx++) {
            addLeftRightNums[idx] = nums[idx - 1];
        }

        int const addLeftRightNumsSize = addLeftRightNums.size();
        std::vector<std::vector<int>> dpMemo(addLeftRightNumsSize,
                std::vector<int>(addLeftRightNumsSize, INIT_MIN));

        // the last element must be multipy with 1 and 1. and each element can be the last one
        // so we just split the array at any point
        return dfs(addLeftRightNums, dpMemo, 0, addLeftRightNumsSize - 1);
    }

    // not include left and right
    int dfs(std::vector<int> const & nums,
            std::vector<std::vector<int>> & dpMemo,
            int left, int right) {
        if (left + 1 == right) {
            return 0;
        }
        if (INIT_MIN < dpMemo[left][right]) {
            return dpMemo[left][right];
        }
        int ans = INIT_MIN;
        for (int mid = left + 1; mid < right; mid++) {
            ans = std::max(ans, nums[left] * nums[mid] * nums[right] +
                    dfs(nums, dpMemo, left, mid) + dfs(nums, dpMemo, mid, right));
        }
        return dpMemo[left][right] = ans;
    }

private:
    static int const JUST_ONE = 1;
    int const INIT_MIN = -1;
};

class SolutionDP {
public:
    int maxCoins(std::vector<int> const & nums) {
        // plagiarizing from https://leetcode.com/problems/burst-balloons/discuss/76228/Share-some-analysis-and-explanations
        int const numsSize = nums.size();
        if (nums.empty()) {
            return 0;
        }
        if (JUST_ONE == numsSize) {
            return nums[0];
        }

        std::vector<int> addLeftRightNums(numsSize + 2, 1);
        for (int idx = 1; idx <= numsSize; idx++) {
            addLeftRightNums[idx] = nums[idx - 1];
        }

        int const addLeftRightNumsSize = addLeftRightNums.size();
        std::vector<std::vector<int>> dpMemo(addLeftRightNumsSize,
                std::vector<int>(addLeftRightNumsSize, INIT_MIN));

        for (int windowLen = 2; windowLen < addLeftRightNumsSize; windowLen++) {
            for (int left = 0; left < addLeftRightNumsSize - windowLen; left++) {
                int right = left + windowLen;
                for (int mid = left + 1; mid < right; mid++) {
                    dpMemo[left][right] = std::max(dpMemo[left][right],
                            addLeftRightNums[left] * addLeftRightNums[mid] * addLeftRightNums[right] +
                                                    dpMemo[left][mid] + dpMemo[mid][right]);
                }
            }
        }
        return dpMemo[0][addLeftRightNumsSize - 1];
    }

private:
    static int const JUST_ONE = 1;
    int const INIT_MIN = 0;
};
