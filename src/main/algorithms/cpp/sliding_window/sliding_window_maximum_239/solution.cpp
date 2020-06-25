#include "../../head.h"


class Solution {
public:
    std::vector<int> maxSlidingWindow(std::vector<int> const & nums, int K) {
        std::vector<int> res;
        int start = 0;
        int maxEle = INT_MIN, cnt = 0;
        for (int inner = 0; inner < nums.size(); inner++) {
            // std::cout << "\ninner: " << inner << "\t";
            if (maxEle < nums[inner]) {
                maxEle = nums[inner];
            }
            if (++cnt < K) {
                continue;
            }
            if (cnt > K) {
                if (maxEle == nums[start++]) {
                    maxEle = *std::max_element(nums.begin() + start, nums.begin() + inner + 1);
                }
                cnt--;
            }
            if (cnt == K) {
                // std::cout << "ele: " << maxEle << "\t";
                res.emplace_back(maxEle);
            }
        }
        return res;

    }
};

class SolutionRecordIncreasing {
public:
    std::vector<int> maxSlidingWindow(std::vector<int> const & A, int k) {
        std::ios_base::sync_with_stdio(false);
        cin.tie(0);

        std::deque<int> dq(k);
        int i;
        std::vector<int> res;

        int firstK = std::min(k, A.size());
        for (i = 0; i < firstK; i++) {
            while (dq.size() && A[i] >= A[dq.back()]) {
                dq.pop_back();
            }
            dq.push_back(i);
        }

        for (; i < A.size(); i++) {
            res.push_back(A[dq.front()]);
            while (dq.size() && dq.front() <= i-k) {
                dq.pop_front();
            }

            while (dq.size() && A[i] >= A[dq.back()]) {
                dq.pop_back();
            }

            dq.push_back(i);
        }

        res.push_back(A[dq.front()]);

        return res;
    }
};
