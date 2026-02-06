#include "../../head.h"


class Solution {
private:
    class FenwickTree {
        private:
            std::vector<int> tree;
            int size;
        public:
            FenwickTree(int n = 0) : size(n) {
                tree.resize(size + 1, 0);
            }
            // idx start from 1
            void update(int idx, int delta) {
                for (; idx <= size; idx += idx & -idx) {
                    tree[idx] += delta;
                }
            }
            long long query(int idx) {
                long long sum = 0;
                for (; idx > 0; idx -= idx & -idx) {
                    sum += tree[idx];
                }
                return sum;
            }
    };
    class SLIDING_WINDOW {
    private:
        FenwickTree fenwickTree;
        int windowSize;
        int n;
        long long inversionCount = 0;
        std::deque<int> window;

    public:
        SLIDING_WINDOW(int n_, int windowSize_) : fenwickTree(n_), windowSize(windowSize_), n(n_){}
        void add(int num) {
            // get the inversions caused by num, howmany numbers > num in the current window
            inversionCount += fenwickTree.query(n) - fenwickTree.query(num);
            fenwickTree.update(num, 1);
            window.push_back(num);
        }
        void remove() {
            int num = window.front();
            window.pop_front();
            inversionCount -= fenwickTree.query(num - 1);
            fenwickTree.update(num, -1);
            // get the inversions caused by num, howmany numbers > num in the current window
        }
        long long getInversionCount() {
            return inversionCount;
        }

    };

public:
    long long minInversionCount(std::vector<int> const & nums, int k) {
        int n = nums.size();

        // get all the unique numbers in nums and sort them
        std::set<int> sortedSet(nums.begin(), nums.end());
        #ifdef __DEBUG__
        for (const int num : sortedSet) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
        #endif

        // map the number to its rank, start from 1
        std::map<int, int> rankMap;
        int rank = 1;
        for (const int num : sortedSet) {
            rankMap[num] = rank++;
        }
        std::vector<int> numsMap(n);
        for (int idx = 0; idx < n; idx++) {
            numsMap[idx] = rankMap[nums[idx]];
        }
        #ifdef __DEBUG__
        for (const int num : numsMap) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
        #endif

        /*
        // 离散化
        vector<int> sorted = nums;
        sort(sorted.begin(), sorted.end());
        sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());

        for (int& x : nums) {
            x = lower_bound(sorted.begin(), sorted.end(), x) - sorted.begin() + 1;
            // 树状数组下标从 1 开始
        }
        */

        SLIDING_WINDOW slidingWindow(rankMap.size(), k);
        for (int idx = 0; idx < k; idx++) {
            slidingWindow.add(numsMap[idx]);
            #ifdef __DEBUG__
            std::cout << "After adding " << numsMap[idx] << ", inversion count: " << slidingWindow.getInversionCount() << std::endl;
            #endif
        }
        long long minInversionCount = slidingWindow.getInversionCount();
        for (int idx = k; idx < n; idx++) {
            slidingWindow.remove();
            slidingWindow.add(numsMap[idx]);
            minInversionCount = std::min(minInversionCount, slidingWindow.getInversionCount());
            #ifdef __DEBUG__
            std::cout << "After adding " << numsMap[idx] << " and removing " << numsMap[idx - k] << ", inversion count: " << slidingWindow.getInversionCount() << std::endl;
            #endif
        }
        return minInversionCount;
    }
};