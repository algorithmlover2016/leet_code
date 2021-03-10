#include "../../head.h"


// #define DEBUG
class KthLargest {
public:
    KthLargest(int k_, std::vector<int> const & nums_) : k(k_), nums(nums_) {
    }

    int add(int val) {
        nums.emplace_back(val);

        // quickSort(nums, 0, nums.size() - 1);
        quickSortDD(nums, 0, nums.size() - 1);
        #ifdef DEBUG
        for (int idx = 0; idx < nums.size(); idx++) {
            std::cout << nums[idx] << "\t";
        }
        std::cout << "\n";
        #endif
        int targetIdx = nums.size() - k;

        return nums[targetIdx];
    }
private:

    void quickSortDD(std::vector<int> & nums, int left, int right) {
        if (left >= right) {
            return ;
        }
        int low = left, high = right;
        int mid = nums[left + (right - left) / 2];
        while (left < right) {
            while (nums[left] < mid) {
                left++;
            }
            while (nums[right] > mid) {
                right--;
            }
            if (left <= right) {
                std::swap(nums[left++], nums[right--]);
            }
        }
        quickSortDD(nums, low, right);
        quickSortDD(nums, left, high);

    }

    void quickSort(std::vector<int> & nums, int left, int right) {
        if (left >= right) {
            return ;
        }
        int pIdx = partition(nums, left, right);
        // int pIdx = partitionDD(nums, left, right);
        quickSort(nums, left, pIdx - 1);
        quickSort(nums, pIdx + 1, right);
    }
    int partitionDD(std::vector<int> & nums, int left, int right) {
        // can't deal with same elements in nums,
        // which means each element only appear once
        int num = nums[right];
        while (left < right) {
            while (left < right && nums[left] < num) {
                left++;
            }
            while (right > left && nums[right] > num) {
                right--;
            }
            std::swap(nums[left], nums[right]);
        }
        return left;

    }

    int partition(std::vector<int> & nums, int left, int right) {
        int num = nums[right];
        for (int idx = left; idx < right; idx++) {
            if (nums[idx] <= num) {
               std::swap(nums[left++], nums[idx]);
            }
        }
        std::swap(nums[left], nums[right]);
        return left;
    }

private:
    int k = 0;
    std::vector<int> nums;
};

#define DEBUG
class KthLargest {
public:
    KthLargest(int k_, std::vector<int> const & nums) : k(k_) {
        // plagiarizing from https://leetcode.com/problems/kth-largest-element-in-a-stream/discuss/149050/Java-Priority-Queue
        for (int idx = 0; idx < nums.size();  idx++) {
            minHeap.emplace(nums[idx]);
            if (minHeap.size() > k) {
                minHeap.pop();
            }
        }

    }

    int add(int val) {
        minHeap.emplace(val);
        if (minHeap.size() > k) {
            minHeap.pop();
        }
        return minHeap.top();
    }

private:
    int k = 0;
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

};
