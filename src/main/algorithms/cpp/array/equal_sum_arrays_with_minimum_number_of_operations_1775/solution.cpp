#include "../../head.h"


// #define DEBUG
class Solution {
public:
    int minOperations(std::vector<int> & nums1, std::vector<int> & nums2) {
        // plagiarizing from https://leetcode.com/problems/equal-sum-arrays-with-minimum-number-of-operations/discuss/1086142/C%2B%2BJava-O(n)
        if (nums1.size() * MAX_ELE < nums2.size() ||
                nums2.size() * MAX_ELE < nums1.size()) {
            return -1;
        }
        int sums1 = std::accumulate(nums1.begin(), nums1.end(), 0);
        int sums2 = std::accumulate(nums2.begin(), nums2.end(), 0);
        if (sums1 > sums2) {
            std::swap(nums1, nums2);
        }
        int diff = std::abs(sums1 - sums2);
        std::vector<int> cnt(MAX_ELE, 0);
        for (int const ele : nums1) {
            cnt[MAX_ELE - ele]++;
        }
        for (int const ele : nums2) {
            cnt[ele - MIN_ELE]++;
        }
        int ans = 0;
        for (int change = MAX_ELE - MIN_ELE; change > 0 && diff > 0; change--) {
            int take = std::min(cnt[change], diff / change + (diff % change != 0));
            diff -= take * change;
            #ifdef DEBUG
            std::cout << change << "\t" << take << "\t" << diff << "\n";
            #endif
            ans += take;
        }
        return ans;

    }
private:
    static int const MAX_ELE = 6;
    static int const MIN_ELE = 1;
};

// #define DEBUG
class SolutionWithHeap {
public:
    int minOperations(std::vector<int> & nums1, std::vector<int> & nums2) {
        // plagiarizing from https://leetcode.com/problems/equal-sum-arrays-with-minimum-number-of-operations/discuss/1086142/C%2B%2BJava-O(n)
        if (nums1.size() * MAX_ELE < nums2.size() ||
                nums2.size() * MAX_ELE < nums1.size()) {
            return -1;
        }
        int sums1 = std::accumulate(nums1.begin(), nums1.end(), 0);
        int sums2 = std::accumulate(nums2.begin(), nums2.end(), 0);
        if (sums1 > sums2) {
            std::swap(nums1, nums2);
        }
        int diff = std::abs(sums1 - sums2);
        std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap(nums1.begin(), nums1.end());
        std::priority_queue<int> maxHeap(nums2.begin(), nums2.end());

        int ans = 0;
        while (diff > 0) {
            ans++;
            if (minHeap.empty() || (!maxHeap.empty() && maxHeap.top() - MIN_ELE > MAX_ELE - minHeap.top())) {
                diff -= maxHeap.top() - MIN_ELE;
                maxHeap.pop();
            } else {
                #ifdef DEBUG
                std::cout << "min: " << minHeap.top();
                #endif
                diff -= MAX_ELE - minHeap.top();
                minHeap.pop();
            }

        }
        return ans;

    }
private:
    static int const MAX_ELE = 6;
    static int const MIN_ELE = 1;
};

#define TEST_MAIN
#ifdef TEST_MAIN
#define PRINT_TO_SCREEN
int main() {
    Solution obj;
    std::vector<int> nums1{{1,1,1,1,1,1,1}};
    std::vector<int> nums2{{6}};
    int ans = obj.minOperations(nums1, nums2);
#ifdef PRINT_TO_SCREEN
    std::cout << "ans: " << ans << "\n";
#endif
    assert(ans == -1);
    std::cout << "TEST SUCCESSFULLY" << std::endl;
    return 0;
}
#endif
