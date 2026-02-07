#include "../../head.h"


class SolutionMoMultiSet {
private:
    struct Query {
        public:
        int l;
        int r;
        int idx;
        Query(int l, int r, int idx) : l(l), r(r), idx(idx) {}
    };
    vector<Query> queriesVec;
    class SlidingMedian {
    private:
        std::multiset<int> leftSet; 
        std::multiset<int> rightSet;
        long long leftSum = 0;
        long long rightSum = 0;
    public:
        long long getMedian() {
            return *leftSet.rbegin();
        }
        int leftSize() {
            return leftSet.size();
        }
        int rightSize() {
            return rightSet.size();
        }
        long long leftTotal() {
            return leftSum;
        }
        long long rightTotal() {
            return rightSum;
        }
        void add(int val) {
            if (leftSet.empty() || val <= *leftSet.rbegin()) {
                leftSet.insert(val);
                leftSum += val;
            } else {
                rightSet.insert(val);
                rightSum += val;
            }
            balance();
        }
        void remove(int val) {
            if (leftSet.find(val) != leftSet.end()) {
                leftSet.erase(leftSet.find(val));
                leftSum -= val;
            } else {
                rightSet.erase(rightSet.find(val));
                rightSum -= val;
            }
            balance();
        }
        void balance() {
            while (leftSet.size() > rightSet.size() + 1) {
                auto it = std::prev(leftSet.end());
                int val = *it;
                leftSet.erase(it);
                leftSum -= val;
                rightSet.insert(val);
                rightSum += val;
            }
            while (rightSet.size() > leftSet.size()) {
                int val = *rightSet.begin();
                rightSet.erase(rightSet.begin());
                rightSum -= val;
                leftSet.insert(val);
                leftSum += val;
            }
        }
    };

public:
    vector<long long> minOperations(vector<int>& nums, int k, vector<vector<int>>& queries) {
        // refer to https://leetcode.com/problems/minimum-operations-to-equalize-subarrays/solutions/7382847/mos-algorithm-sliding-median-two-multise-0bex/
        int n = nums.size();
        int qSize = queries.size();
        std::vector<long long> ans(qSize, 0);

        std::vector<int> right2LeftMatch(n);
        right2LeftMatch[n - 1] = n - 1;
        for (int i = n - 2; i >= 0; i--) {
            if (nums[i] % k == nums[i + 1] % k) {
                right2LeftMatch[i] = right2LeftMatch[i + 1];
            } else {
                right2LeftMatch[i] = i;
            }
        }
        for (int i = 0; i < qSize; i++) {
            int l = queries[i][0], r = queries[i][1];
            if (right2LeftMatch[l] < r) {
                ans[i] = -1;
                continue;
            }
            queriesVec.emplace_back(l, r, i);
        }
        const int BLOCK_SIZE = max(1, (int)(n / sqrt(queriesVec.size() + 1)));

        auto cmp = [&](const Query &a, const Query &b) {
            int blockA = a.l / BLOCK_SIZE;
            int blockB = b.l / BLOCK_SIZE;
            if (blockA != blockB) {
                return blockA < blockB;
            }
            return a.r < b.r;
        };
        std::sort(queriesVec.begin(), queriesVec.end(), cmp);
        int currL = 0, currR = -1;
        SlidingMedian slidingMedian;
        for (const Query &query : queriesVec) {
            int l = query.l, r = query.r;
            while (currR < r) {
                currR++;
                slidingMedian.add(nums[currR]);
            }
            while (currR > r) {
                slidingMedian.remove(nums[currR]);
                currR--;
            }
            while (currL < l) {
                slidingMedian.remove(nums[currL]);
                currL++;
            }
            while (currL > l) {
                currL--;
                slidingMedian.add(nums[currL]);
            }
            long long median = slidingMedian.getMedian();
            long long totalOps = (slidingMedian.leftSize() * median - slidingMedian.leftTotal()
                              + slidingMedian.rightTotal() - slidingMedian.rightSize() * median) / k;
            ans[query.idx] = totalOps;
        }
        return ans;
        
    }
};

class Solution {
private:
    class NODE {
    public:
        std::vector<int> vals;
        std::vector<long long> prefixSums;
    };
    class SegmentTree {
    private:
        int size;
        std::vector<NODE> tree;
    private:
        void mergeNodes(const NODE &leftNode, const NODE &rightNode, NODE &parentNode) {
            int leftSize = leftNode.vals.size();
            int rightSize = rightNode.vals.size();
            parentNode.vals.resize(leftSize + rightSize);
            /*
            int leftIdx = 0, rightIdx = 0, parentIdx = 0;
            while(leftIdx < leftSize && rightIdx < rightSize) {
                if (leftNode.vals[leftIdx] <= rightNode.vals[rightIdx]) {
                    parentNode.vals[parentIdx++] = leftNode.vals[leftIdx++];
                } else {
                    parentNode.vals[parentIdx++] = rightNode.vals[rightIdx++];
                }
            }
            while (leftIdx < leftSize) {
                parentNode.vals[parentIdx++] = leftNode.vals[leftIdx++];
            }
            while (rightIdx < rightSize) {
                parentNode.vals[parentIdx++] = rightNode.vals[rightIdx++];
            }
            */
            std::merge(leftNode.vals.begin(), leftNode.vals.end(),
                       rightNode.vals.begin(), rightNode.vals.end(),
                       parentNode.vals.begin());
            parentNode.prefixSums.resize(leftSize + rightSize);
            parentNode.prefixSums[0] = parentNode.vals[0];
            for (int i = 1; i < parentNode.vals.size(); i++) {
                parentNode.prefixSums[i] = parentNode.prefixSums[i - 1] + parentNode.vals[i];
            }
        }
    public:
        SegmentTree(int size) : size(size) {
            // the size of segment tree is 4 times of the input size
            // why 4 times? refer to https://cp-algorithms.com/data_structures/segment_tree.html#implementation
            // and https://stackoverflow.com/questions/19996455/why-do-we-need-4n-size-for-segment-tree
            tree.resize(4 * size);
        }
        void build(const std::vector<int> &nums, int node, int start, int end) {
            if (start == end) {
                tree[node].vals.push_back(nums[start]);
                tree[node].prefixSums.push_back(nums[start]);
            } else {
                int mid = start + (end - start) / 2;
                build(nums, 2 * node + 1, start, mid);
                build(nums, 2 * node + 2, mid + 1, end);
                mergeNodes(tree[2 * node + 1], tree[2 * node + 2], tree[node]);
            }
        }
        std::pair<long long, long long> query(int node, int start, int end, int l, int r, int median) {
            if (r < start || end < l) {
                return {0, 0};
            }
            if (l <= start && end <= r) {
                const NODE &currNode = tree[node];
                int lessCount = std::upper_bound(currNode.vals.begin(), currNode.vals.end(), median) - currNode.vals.begin();
                long long lessSum = (lessCount > 0) ? currNode.prefixSums[lessCount - 1] : 0;
                return {lessCount, lessSum};
            }
            int mid = start + (end - start) / 2;
            auto leftResult = query(2 * node + 1, start, mid, l, r, median);
            auto rightResult = query(2 * node + 2, mid + 1, end, l, r, median);
            return {leftResult.first + rightResult.first, leftResult.second + rightResult.second};
        }
    };
public:
    vector<long long> minOperations(vector<int>& nums, int k, vector<vector<int>>& queries) {
        // refer to https://leetcode.com/problems/minimum-operations-to-equalize-subarrays/solutions/7382847/mos-algorithm-sliding-median-two-multise-0bex/
        int n = nums.size();
        int qSize = queries.size();
        std::vector<long long> ans(qSize, 0);

        std::vector<int> right2LeftMatch(n);
        right2LeftMatch[n - 1] = n - 1;
        for (int i = n - 2; i >= 0; i--) {
            if (nums[i] % k == nums[i + 1] % k) {
                right2LeftMatch[i] = right2LeftMatch[i + 1];
            } else {
                right2LeftMatch[i] = i;
            }
        }
        std::vector<long long> prefixSums(n);
        prefixSums[0] = nums[0];
        for (int i = 1; i < n; i++) {
            prefixSums[i] = prefixSums[i - 1] + nums[i];
        }
        SegmentTree segmentTree(n);
        segmentTree.build(nums, 0, 0, n - 1);
        for (int i = 0; i < qSize; i++) {
            int l = queries[i][0], r = queries[i][1];
            if (right2LeftMatch[l] < r) {
                ans[i] = -1;
                continue;
            }
            int totalCount = (r -l + 1);
            int cntLess = (totalCount + 1) / 2;
            long long median = 0;
            std::pair<long long, long long> queryAns;
            long long start = 1, end = 1e9;
            while (start <= end) {
                long long mid = start + (end - start) / 2;
                auto lessResult = segmentTree.query(0, 0, n - 1, l, r, mid);
                #ifdef LESS_FIRST
                    if (lessResult.first < cntLess) {
                        start = mid + 1;
                        #ifdef __DEBUG__
                        std::cout << "update median to " << median << ", start <- mid + 1: " << start << std::endl;
                        #endif
                    } else {
                        median = mid;
                        queryAns = lessResult;
                        end = mid - 1;
                    }
                #else
                    if (lessResult.first >= cntLess) {
                        median = mid;
                        queryAns = lessResult;
                        end = mid - 1;
                        #ifdef __DEBUG__
                        std::cout << "update median to " << median << ", end <- mid - 1: " << end << std::endl;
                        #endif
                    } else {
                        start = mid + 1;
                    }
                #endif
                #ifdef __DEBUG__
                std::cout << "result:" << " mid: " << median << ", lessCnt: " << lessResult.first << ", PreSum: " << lessResult.second << std::endl;
                #endif
            }
            long long totalSum = prefixSums[r] - (l > 0 ? prefixSums[l - 1] : 0);
            long long lessCount = queryAns.first;
            long long lessSum = queryAns.second;
            long long totalOps = (1LL * lessCount * median - lessSum
                              + (totalSum - lessSum) - 1LL * (totalCount - lessCount) * median) / k;
            ans[i] = totalOps;
        }
        return ans;
    }

};