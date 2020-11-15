#include "../../head.h"


class SolutionTLE {
public:
    std::vector<int> countSmaller(std::vector<int> const & nums) {
        int numsSize = nums.size();
        std::vector<int> res(numsSize, 0);
        for (int i = 0; i < numsSize; i++) {
            for (int j = i + 1; j < numsSize; j++) {
                if (nums[j] < nums[i]) {
                    res[i]++;
                }
            }
        }
        return res;
    }
};

class Solution {
private:
    typedef std::vector<std::pair<int, int>> pValIdx;
    typedef std::vector<std::pair<int, int>>::iterator pValIdxIt;

public:
    std::vector<int> countSmaller(std::vector<int> const & nums) {
        // plagiarizing from https://leetcode.com/problems/count-of-smaller-numbers-after-self/discuss/76584/Mergesort-solution

        int const numsSize = nums.size();
        pValIdx numsIdxPair(numsSize);
        for (int idx = 0; idx < nums.size(); idx++) {
            numsIdxPair[idx] = std::make_pair(nums[idx], idx);
        }

        std::vector<int> res(numsSize);
        mergeSort(numsIdxPair.begin(), numsIdxPair.end(), res);
        return res;
    }
    void mergeSort(pValIdxIt begin,
                   pValIdxIt end,
                   std::vector<int> & res) {
        // plagiarizing from https://leetcode.com/problems/count-of-smaller-numbers-after-self/discuss/76584/Mergesort-solution/184423
        // there is only one or zero nums left;

        // if (end <= begin + 1) {
        /*
           when numsIdxPair is empty, then the begin() and end() all return null pointer, which can't add 1
            Line 851: Char 45: runtime error: applying non-zero offset 8 to null pointer (stl_iterator.h) 
SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior /usr/bin/../lib/gcc/x86_64-linux-gnu/9/../../../../include/c++/9/bits/stl_iterator.h:860:45

            */
        if (end - begin <= 1) {
            return;
        }
        pValIdxIt mid = begin + (end - begin) / 2;
        mergeSort(begin, mid, res);
        mergeSort(mid, end, res);
        for (auto iLeft = begin, jRight = mid; iLeft != mid; iLeft++) {
            while (jRight != end && iLeft->first > jRight->first) {
                jRight++;
            }
            res[iLeft->second] += jRight - mid;
        }
        std::inplace_merge(begin, mid, end);
    }
};

class Solution {
public:
    std::vector<int> countSmaller(std::vector<int> const & nums) {
        // plagiarizing from https://leetcode.com/problems/count-of-smaller-numbers-after-self/discuss/76584/Mergesort-solution

        int const numsSize = nums.size();
        std::vector<int> numsIdx(numsSize);

        std::vector<int> res;
        mergeSort(nums, numsIdx, res);
        return res;
    }
    std::vector<int> mergeSort(std::vector<int> const & nums,
            std::vector<int> & numsIdx,
            int start,
            int end,
            std::vector<int> & res) {
        std::vector<int> ans(numsIdx);
        if (end - start <= 1) {
            return ans;
        }
        int mid = (start + end) / 2;
        mergeSort(nums, numsIdx, start, mid, res);
        mergeSort(nums, numsIdx, mid, end, res);
        for (auto left = start, right = mid, idx = left; left < mid || right < end;) {
            if (right == end || (left < mid && nums[numsIdx[left]] < nums[numsIdx[right]])) {
                ans[idx] = numsIdx[left];
                res[numsIdx[left]] += right - mid;
            } else {
                ans[idx] = numsIdx[right];
            }
        }
        for (int idx = start; idx < end; idx++) {
            numsIdx[idx] = ans[idx];
        }
    }
};

class SolutionNoMultiProcess {
public:
    std::vector<int> countSmaller(std::vector<int> const & nums) {
        // plagiarizing from https://leetcode.com/problems/count-of-smaller-numbers-after-self/discuss/76584/Mergesort-solution

        int const numsSize = nums.size();
        std::vector<int> numsIdx(numsSize);
        for (int idx = 0; idx < numsSize; idx++) {
            numsIdx[idx] = idx;
        }

        std::vector<int> res(numsSize);
        mergeSort(nums, numsIdx, 0, numsSize, res);
        return res;
    }
    void mergeSort(std::vector<int> const & nums,
            std::vector<int> & numsIdx,
            int start,
            int end,
            std::vector<int> & res) {
        if (end - start <= 1) {
            return;
        }
        std::vector<int> ans(end - start);
        int mid = (start + end) / 2;
        mergeSort(nums, numsIdx, start, mid, res);
        mergeSort(nums, numsIdx, mid, end, res);
        for (int left = start, right = mid, idx = 0; idx < ans.size(); idx++) {
            if (right == end || (left < mid && nums[numsIdx[left]] <= nums[numsIdx[right]])) {
                ans[idx] = numsIdx[left];
                res[numsIdx[left]] += right - mid;
                left++;
            } else {
                ans[idx] = numsIdx[right];
                right++;
            }
        }
        for (int idx = 0; idx < ans.size(); idx++) {
            numsIdx[idx + start] = ans[idx];
        }
    }
};

class SolutionMultiProcess {
public:
    std::vector<int> countSmaller(std::vector<int> const & nums) {
        // plagiarizing from https://leetcode.com/problems/count-of-smaller-numbers-after-self/discuss/76584/Mergesort-solution

        int const numsSize = nums.size();
        std::vector<int> numsIdx(numsSize);
        for (int idx = 0; idx < numsSize; idx++) {
            numsIdx[idx] = idx;
        }

        std::vector<int> res(numsSize);
        mergeSort(nums, numsIdx, res);
        return res;
    }
    void mergeSort(std::vector<int> const & nums,
            std::vector<int> & numsIdx,
            std::vector<int> & res) {
        int const numsIdxSize = numsIdx.size();
        if (numsIdxSize <= 1) {
            return;
        }
        std::vector<int>::iterator mid = numsIdx.begin() + (numsIdxSize / 2);
        std::vector<int> left(numsIdx.begin(), mid);
        std::vector<int> right(mid, numsIdx.end());
        mergeSort(nums, left, res);
        mergeSort(nums, right, res);
        for (int idx = numsIdxSize - 1; idx >= 0; idx--) {
            if (right.empty() || (!left.empty() && nums[left.back()] > nums[right.back()])) {
                numsIdx[idx] = left.back();
                res[left.back()] += right.size();
                left.pop_back();
            } else {
                numsIdx[idx] = right.back();
                right.pop_back();
            }
        }
    }
};

class SolutionBST {
private:
    struct Node {
        int val, dup, smallerSum;
        Node *left, *right;
        Node(int val_, int smallerSum_ = 0) :
            val(val_), smallerSum(smallerSum_), dup(1), left(nullptr), right(nullptr) {
        }
    };

public:
    std::vector<int> countSmaller(std::vector<int> const & nums) {
        // plagiarizing from https://leetcode.com/problems/count-of-smaller-numbers-after-self/discuss/76580/9ms-short-Java-BST-solution-get-answer-when-building-BST
        int const numsSize = nums.size();
        std::vector<int> ans(numsSize);
        Node * root = nullptr;
        for (int idx = numsSize - 1; idx >= 0; idx--) {
            root = insert(nums[idx], root, ans, idx);
        }
        return ans;
    }
private:
    Node* insert(int const num, Node* node, std::vector<int> & ans, int idx, int preSum = 0) {
        if (nullptr == node) {
            // if at the leaf, we need construct a new node
            // at this time, preSum is the answer;
            node = new Node(num);
            ans[idx] = preSum;
            return node;
        } else if (node->val == num) {
            node->dup++;
            ans[idx] = preSum + node->smallerSum;
        } else if (node->val > num) {
            node->smallerSum++;
            node->left = insert(num, node->left, ans, idx, preSum);
        } else {
            node->right = insert(num, node->right, ans, idx, preSum + node->smallerSum + node->dup);
        }
        return node;
    }
};
