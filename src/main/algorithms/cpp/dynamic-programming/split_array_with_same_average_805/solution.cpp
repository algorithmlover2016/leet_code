#include "../../head.h"


// #define TEST

// #ifdef TEST
// #define TEST_SCREEN_OUTPUT
// #endif
class SolutionWrongAnswer {
public:
    bool splitArraySameAverage(std::vector<int> const & A) {
        int const ASize = A.size();
        if (JUST_RETURN >= ASize) {
            return JUST_RETURN != ASize;
        }
        int sum = std::accumulate(A.begin(), A.end(), 0);
        if (1 & sum) {
            return false;
        }
        int target = sum >> 1;
        // can't be unordered_map default-delete constructor error
        std::map<std::pair<int, int>, int> targetIdx2ValMap;
        for (int idx = 0; idx < ASize; idx++) {
            if (dfs(A, target, targetIdx2ValMap, idx)) {
                return true;
            }
        }
        return false;
    }
    bool dfs(std::vector<int> const & nums,
            int target,
            std::map<std::pair<int, int>, int> & targetIdx2ValMap,
            int idx) {
        if (0 == target) {
            return true;
        }

        if (idx >= nums.size()) {
            return false;
        }
        std::pair<int, int> key = std::make_pair(target, idx);

        bool ans = dfs(nums, target, targetIdx2ValMap, idx + 1);
        if (ans)  {
            return targetIdx2ValMap[key] = true;
        }

        ans |= dfs(nums, target - nums[idx], targetIdx2ValMap, idx + 1);
        return targetIdx2ValMap[key] = ans;
    }
private:
    static int const JUST_RETURN = 1;
};

class SolutionTLE {
public:
    bool splitArraySameAverage(std::vector<int> const & A) {
        int const ASize = A.size();
        if (JUST_RETURN >= ASize) {
            return JUST_RETURN != ASize;
        }
        int sum = std::accumulate(A.begin(), A.end(), 0);
        double target = sum * 1.0 / ASize; ;
        for (int idx = 0; idx < ASize; idx++) {
            if (dfs(A, target, idx, A[idx], 1)) {
                return true;
            }
        }
        return false;
    }
    bool dfs(std::vector<int> const & nums,
            double target,
            int idx,
            double sum,
            int cnt) {
        int const numsSize = nums.size();
        if (numsSize <= cnt || numsSize <= idx) {
            return false;
        }
        double quotient = sum / cnt;
        if (EQUAL_ABS > std::abs(quotient - target)) {
            return true;
        }


        bool ans = dfs(nums, target,idx + 1, sum, cnt);
        if (ans)  {
            return true;
        }

        ans |= dfs(nums, target, idx + 1, sum + nums[idx], cnt + 1);
        return ans;
    }
private:
    static int const JUST_RETURN = 1;
    static double const EQUAL_ABS;
};
double const Solution::EQUAL_ABS = 1e-6;

#ifdef TEST
int main() {
    Solution obj;
    std::vector<int> nums{{1, 6, 1}};
#ifdef DEBUG
    std::cout << "call function\n";
#endif
    bool ans = obj.splitArraySameAverage(nums);
#ifdef TEST_SCREEN_OUTPUT
    std::cout << std::boolalpha << ans << "\n";
#endif
    assert(ans == false);
    return 0;

}
#endif

class SolutionTLEAGAIN {
public:
    bool splitArraySameAverage(std::vector<int> const & A) {
        int const ASize = A.size();
        if (JUST_RETURN >= ASize) {
            return JUST_RETURN != ASize;
        }
        int sum = std::accumulate(A.begin(), A.end(), 0);
        double target = sum * 1.0 / ASize; ;
        std::unordered_map<long long, int> dpMemo;
        for (int idx = 0; idx < ASize; idx++) {
            if (dfs(A, target, dpMemo, idx, A[idx], 1)) {
                return true;
            }
        }
        return false;
    }
    bool dfs(std::vector<int> const & nums,
             double target,
             std::unordered_map<long long, int> & dpMemo,
             int idx,
             int sum,
             int cnt) {
        long long code = ((long long)idx << 48) | ((long long)cnt << 32) | sum;
        if (dpMemo.find(code) != dpMemo.end()) {
            return dpMemo[code];
        }
        int const numsSize = nums.size();
        if (cnt >= numsSize || idx >= numsSize) {
            return dpMemo[code] = false;
        }
        double quotient = static_cast<double>(sum) / cnt;
        if (EQUAL_ABS > std::abs(quotient - target)) {
            return dpMemo[code] = true;
        }


        bool ans = dfs(nums, target, dpMemo, idx + 1, sum, cnt);
        if (ans)  {
            return dpMemo[code] = true;
        }

        ans |= dfs(nums, target, dpMemo, idx + 1, sum + nums[idx], cnt + 1);
        return dpMemo[code] = ans;
    }
private:
    static int const JUST_RETURN = 1;
    static double const EQUAL_ABS;
};
double const Solution::EQUAL_ABS = 1e-6;


class Solution {
public:
    bool splitArraySameAverage(std::vector<int> const & A) {
        // plagiarizing idea from https://leetcode.com/problems/split-array-with-same-average/discuss/120667/C%2B%2B-Solution-with-explanation-early-termination-(Updated-for-new-test-case)
        // sum(A) / ASize = sum(partB) / len(partB) = sum(partC) / len(partC);
        // => sum(A) * len(partB) / ASize = sum(partB) who is integer. assume len(B) <= len(C)
        int const ASize = A.size();
        if (JUST_RETURN >= ASize) {
            return JUST_RETURN != ASize;
        }
        int const sum = std::accumulate(A.begin(), A.end(), 0);
        int const smallerMaxLen = ASize / 2;
        bool isPossible = false;
        for (int idx = 1; idx <= ASize && !isPossible; idx++) {
            if (MOD_ZERO == sum * idx % ASize) {
                isPossible = true;
            }
        }
        if (!isPossible) {
            return false;
        }

        std::vector<std::unordered_set<int>> smallerLenSumSet(smallerMaxLen + 1);
        smallerLenSumSet[0].insert(0);
        // must first traverse A and then the len and then the preSmallerLenSumSet
        // traverse A with index, means using from 0 to index(include), how many combination we can get
        for (int const num : A) {
            // because we dependens on its previous, and
            // the smallerLenSumSet means the last traversal,
            // which means smallerLenSumSet[index - 1][len - 1]
            for (int len = smallerMaxLen; len > 0; len--) {
                for (auto const ele : smallerLenSumSet[len - 1]) {
                    smallerLenSumSet[len].insert(ele + num);
                }
            }
        }
        for (int len = 1; len <= smallerMaxLen; len++) {
            if (MOD_ZERO == sum * len % ASize &&
                smallerLenSumSet[len].find(sum * len / ASize) != smallerLenSumSet[len].end()) {
                return true;
            }
        }
        return false;
    }
    private:
    static int const JUST_RETURN = 1;
    static int const MOD_ZERO = 0;
};


/*
class Solution:
 def splitArraySameAverage(self, A: List[int]) -> bool:
     # plagiarizing from https://leetcode.com/problems/split-array-with-same-average/discuss/120741/Python-Easy-and-Concise-Solution
     @functools.lru_cache()
     def find(target, k, i):
         if k == 0: return target == 0
         if target < 0 or k + i > n: return False
         return find(target - A[i], k - 1, i + 1) or find(target, k, i + 1)
     n, s = len(A), sum(A)
     return any(find(s * k // n, k, 0) for k in range(1, n // 2 + 1) if s * k % n == 0)
*/
class SolutionFromUpperPythonOfLee {
public:
    bool splitArraySameAverage(std::vector<int> const & A) {
        int const ASize = A.size();
        if (JUST_RETURN >= ASize) {
            return JUST_RETURN != ASize;
        }
        int sum = std::accumulate(A.begin(), A.end(), 0);
        std::unordered_map<long long, int> dpMemo;
        int smallerPartMaxLen = ASize >> 1;

        for (int len = 1; len <= smallerPartMaxLen; len++) {
            int multi = sum * len;
            int mod = multi % ASize;
            int quotient = multi / ASize;
            if (MOD_ZERO == mod) {
                if (dfs(A, quotient, dpMemo, 0, len)) {
                    return true;
                }
            }
        }
        return false;
    }
    bool dfs(std::vector<int> const & nums,
            int target,
            std::unordered_map<long long, int> & dpMemo,
            int idx,
            int cnt) {
        long long code = ((long long)idx << 48) | ((long long)cnt << 32) | target;
        if (dpMemo.find(code) != dpMemo.end()) {
            return dpMemo[code];
        }
        int const numsSize = nums.size();
        if (target < ZERO_VAL || numsSize < cnt + idx) {
            return dpMemo[code] = false;
        }
        if (ZERO_VAL == cnt) {
            return dpMemo[code] = (ZERO_VAL == target);
        }

        if (dfs(nums, target, dpMemo, idx + 1, cnt))  {
            return dpMemo[code] = true;
        }
        return  dpMemo[code] = dfs(nums, target - nums[idx], dpMemo, idx + 1, cnt - 1);
    }
private:
    static int const JUST_RETURN = 1;
    static int const MOD_ZERO = 0;
    static int const ZERO_VAL = 0;
};
