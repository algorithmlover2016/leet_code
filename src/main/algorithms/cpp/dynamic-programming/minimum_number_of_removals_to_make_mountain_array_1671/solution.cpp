#include "../../head.h"


class SolutionTLE {
public:
    int minimumMountainRemovals(std::vector<int> const & nums) {
        // plagiarizing from https://leetcode.com/problems/minimum-number-of-removals-to-make-mountain-array/discuss/952053/Python-3-solutions%3A-LIS-dp-O(n-log-n)-explained
        int const numsSize = nums.size();
        if (JUST_RETURN_TWO >= numsSize) {
            return numsSize;
        }
        int maxLen = 0;
        for (int idx = 0; idx < numsSize; idx++) {
            std::vector<int> left;
            std::vector<int> right;
            for (int start = 0; start < idx;  start++) {
                if (nums[start] < nums[idx]) {
                    left.emplace_back(nums[start]);
                }
            }
            left.emplace_back(nums[idx]);
            for (int start = numsSize - 1; start > idx; start--) {
                if (nums[start] < nums[idx]) {
                    right.emplace_back(nums[start]);
                }
            }

            right.emplace_back(nums[idx]);
            int longestLeftLen = longestIncreaseArray(left);
            int longestRightLen = longestIncreaseArray(right);
            if (AT_LEAST_LEN <= longestLeftLen && AT_LEAST_LEN <= longestRightLen) {
                maxLen = std::max(maxLen, longestLeftLen + longestRightLen - 1);

            }
        }
        return numsSize - maxLen;
    }
private:
    int longestIncreaseArray(std::vector<int> const & nums) {
        int const numsSize = nums.size();
        if (JUST_RETURN_ONE >= numsSize) {
            return numsSize;
        }
        std::vector<int> increaseArray(numsSize + 1, INT_MAX);
        int len = 0;
        for (int const num : nums) {
            #ifdef STD_LOWER_BOUND
            auto it = std::lower_bound(increaseArray.begin(), increaseArray.end(), num);
            *it = num;
            // len = std::max(len, static_cast<int>(it - increaseArray.begin()) + 1);
            len = std::max(len, static_cast<int>(std::distance(increaseArray.begin(), it)) + 1);
            #else
            int idx = binarySearch(increaseArray, num) + 1;
            increaseArray[idx] = num;
            len = std::max(len, idx + 1);

            #endif

        }
        return len;

    }
    int binarySearch(std::vector<int> const & nums, int target) {
        if (nums.empty()) {
            return -1;
        }
        int const numsSize = nums.size();
        int left = 0;
        int right = numsSize - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (nums[mid] >= target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return right;
    }

private:
    static int const JUST_RETURN_ONE = 1;
    static int const JUST_RETURN_TWO = 2;
    static int const AT_LEAST_LEN = 2;
};

// #define DEBUG
class Solution {
public:
    int minimumMountainRemovals(std::vector<int> const & nums) {
        // plagiarizing from https://leetcode.com/problems/minimum-number-of-removals-to-make-mountain-array/discuss/952053/Python-3-solutions%3A-LIS-dp-O(n-log-n)-explained
        int const numsSize = nums.size();
        if (JUST_RETURN_TWO >= numsSize) {
            return numsSize;
        }
        std::vector<int> increaseDpMemo(numsSize, INITIAL_VAL);
        std::vector<int> mountainDpMemo(numsSize, INITIAL_VAL);
        for (int idx = 0; idx < numsSize; idx++) {
            for (int pre = 0; pre < idx; pre++) {
                #ifdef DEBUG
                std::cout << "idx, pre: " << idx << ",\t" << pre << "\t";
                #endif
                if (nums[pre] < nums[idx]) {
                    // we can add this pre-th index
                    increaseDpMemo[idx] = std::max(increaseDpMemo[idx], 1 + increaseDpMemo[pre]);
                }
                if (nums[pre] > nums[idx]) {
                    // first we construct a moutain that using pre's increase list with idx-th element
                    if (INITIAL_VAL < increaseDpMemo[pre]) {
                        mountainDpMemo[idx] = std::max(mountainDpMemo[idx], 1 + increaseDpMemo[pre]);
                    }
                    // second we can construct a moutain that using pre's mountain with idx-th element
                    if (INITIAL_VAL < mountainDpMemo[pre]) {
                        mountainDpMemo[idx] = std::max(mountainDpMemo[idx], 1 + mountainDpMemo[pre]);
                    }
                }
            }
        }
        return numsSize - (*std::max_element(mountainDpMemo.begin(), mountainDpMemo.end()));

    }
private:
    static int const JUST_RETURN_TWO = 2;
    int const INITIAL_VAL = 1;
};

// #define TEST_DEC
class Solution {
public:
    int minimumMountainRemovals(std::vector<int> const & nums) {
        int const numsSize = nums.size();
        if (JUST_LEN_TWO >= numsSize) {
            return numsSize;
        }
        std::vector<int> incArray = longestIncArray(nums);
        std::vector<int> decArray(nums);

        #ifdef TEST_DEC
        std::cout << "\nTEST_DEC BEGIN\n";
        for (auto const & num : longestDecArray(decArray)) {
            std::cout << num << "\t";
        }
        std::cout << "\nTEST_DEC END\n";

        #endif
        std::reverse(decArray.begin(), decArray.end());
        decArray = longestIncArray(decArray);
        std::reverse(decArray.begin(), decArray.end());

        int maxLen = 0;
        for (int idx = 0; idx < numsSize; idx++) {
            if (JUST_LEN_TWO <= incArray[idx] && JUST_LEN_TWO <= decArray[idx]) {
                maxLen = std::max(maxLen, incArray[idx] + decArray[idx] - 1);
            }
        }
        return numsSize - maxLen;
    }
private:
    std::vector<int> longestIncArray(std::vector<int> const & nums) {
        int const numsSize = nums.size();
        if (JUST_LEN_ONE == numsSize) {
            return std::vector<int>(nums);
        }
        int const INC_INITIAL_VAL = INT_MAX;
        std::vector<int> increaseArray(numsSize, INC_INITIAL_VAL);
        std::vector<int> lens(numsSize, 0);
        for (int idx = 0; idx < numsSize; idx++) {
            auto it = std::lower_bound(increaseArray.begin(), increaseArray.end(), nums[idx]);
            *it = nums[idx];
            lens[idx] = static_cast<int>(std::distance(increaseArray.begin(), it)) + 1;
        }
        return lens;
    }
    std::vector<int> longestDecArray(std::vector<int> const & nums) {
        int const numsSize = nums.size();
        if (JUST_LEN_ONE == numsSize) {
            return std::vector<int>(nums);
        }
        int const INC_INITIAL_VAL = INT_MIN;
        std::vector<int> decreaseArray(numsSize, INC_INITIAL_VAL);
        int maxLen = 0;
        for (auto const num : nums) {
            int idx = binarySearchDec(decreaseArray, num);
            decreaseArray[idx] = num;
            maxLen = std::max(maxLen, idx + 1);
        }
        while (!decreaseArray.empty() and INC_INITIAL_VAL == decreaseArray.back()) {
            decreaseArray.pop_back();
        }
        return decreaseArray;
    }
    int binarySearchDec(std::vector<int> const & nums, int target) {
        int const numsSize = nums.size();
        if (nums.empty()) {
            return -1;
        }
        int left = 0;
        int right = nums.size() - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (nums[mid] >= target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return left;
    }
private:
    static int const JUST_LEN_ONE = 1;
    static int const JUST_LEN_TWO = 2;
};
