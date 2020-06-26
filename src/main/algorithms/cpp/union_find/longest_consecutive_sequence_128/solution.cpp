#include "../../head.h"


class Solution {
public:
    int longestConsecutive(std::vector<int> const & nums) {
        int numsSize = nums.size();
        if (0 == numsSize) {
            return 0;
        }
        std::vector<int> parentIndex(numsSize, -1);
        std::vector<int> cnt(numsSize, 1);
        for (int index = 0; index < numsSize; index++) {
            parentIndex[index] = index;
        }
        std::unordered_map<int, int> valueIndex;
        int res = 1; // at least one node.
        for (int index = 0; index < nums.size(); index++) {
            if (valueIndex.find(nums[index]) != valueIndex.end()) {
                continue;
            }
            int upper = nums[index] + 1;
            int lower = nums[index] - 1;
            valueIndex[nums[index]] = index;
            if (valueIndex.find(upper) != valueIndex.end()) {
                res = std::max(res, unionNode(parentIndex, cnt, valueIndex[upper], index));
            }
            if (valueIndex.find(lower) != valueIndex.end()) {
                res = std::max(res, unionNode(parentIndex, cnt, index, valueIndex[lower]));
            }
        }
        return res;

    }
private:
    int findRoot(std::vector<int> const & parentIndex, int index) {
        while (index >= 0 && index < parentIndex.size() && index != parentIndex[index]) {
            index = parentIndex[index];
        }
        return index;
    }
    int unionNode(std::vector<int> & parentIndex, std::vector<int> & cnt, int left, int right) {
        if (left < 0 || left >= parentIndex.size() ||
                right < 0 || right >= parentIndex.size()) {
            return -1;
        }
        int leftRoot = findRoot(parentIndex, left);
        int rightRoot = findRoot(parentIndex, right);
        if (leftRoot == rightRoot) {
            return cnt[leftRoot];
        }
        int count = cnt[leftRoot] + cnt[rightRoot];
        parentIndex[leftRoot] = rightRoot;
        cnt[rightRoot] = count;
        return count;
    }


};

class SolutionBetterRuntimeIllegal {
public:
    int longestConsecutive(std::vector<int> const & arr) {
        int ans = 0, count = 0;
        std::sort(arr.begin(), arr.end());
        for (int i = 0; i < arr.size(); i++) {
            if (i > 0 && arr[i] == arr[i - 1] + 1) {
                count++;
            } else if (i > 0 && arr[i] == arr[i - 1]) {
                continue;
            } else {
                count = 1;
            }
            ans = std::max(ans, count);
        }
        return ans;

    }
};

class Solution {
public:
    std::unordered_set<int> v;
    int maxlen = 1;
    int longestConsecutive(std::vector<int> const & nums) {
        int curr = 1;
        if (nums.size()) {
            for (auto val : nums) {
                v.insert(val);
            }

            for (int i =0; i<nums.size(); i++) {
                if (v.find(nums[i] - 1) == v.end()) {
                    int val = nums[i] + 1;
                    while(val < INT_MAX && v.find( val++) != v.end()) {
                        curr++;
                    }
                    maxlen = std::max(curr, maxlen);
                    curr = 1;
                }
            }
        } else {
            return 0;
        }

        return maxlen;
    }
};

class Solution {
public:
    int longestConsecutive(std::vector<int> const & nums) {
        // plagiarizing from https://leetcode.com/problems/longest-consecutive-sequence/discuss/41055/My-really-simple-Java-O(n)-solution-Accepted
        std::unordered_map<int, int> visited;
        int res = 0;
        for (int ele : nums) {
            if (visited.find(ele) == visited.end()) {
                // std::cout << "\nele: " << ele << "\t";
                int left = visited.find(ele - 1) == visited.end() ? 0 : visited[ele - 1];
                int right = visited.find(ele + 1) == visited.end() ? 0 : visited[ele + 1];
                int sum = right + left + 1;
                // std::cout << "left: " << left << "\tright: " << right << "\tsum: " << sum << "\t";
                res = std::max(res, sum);
                visited[ele - left] = sum;
                visited[ele + right] = sum;
                visited[ele] = sum;
            }
        }
        return res;
    }
};
static int __ = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    return 0;
}();
