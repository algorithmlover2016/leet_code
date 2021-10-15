#include "../../head.h"


class Solution {
public:
    int numberOfArithmeticSlices(std::vector<int> const & nums) {
        // plagiarizing from https://www.youtube.com/watch?v=tVByevGUxbU
        int numsSize = nums.size();
        if (MIN_SIZE > numsSize) {
            return 0;
        }
        int ans = 0;
        std::vector<std::unordered_map<long, int>> dpMemo(numsSize);
        for (int right = 1; right < numsSize; right++) {
            for (int left = 0; left < right; left++) {
                long diff = (long)nums[right] - nums[left];
                // the meaning of dpMemo[left][diff] means that at current time,
                // how many combinations match the left with diff, and the at least three elements will be nums[left],
                // nums[right] and the previous combinations with diff difference.
                ans += dpMemo[left][diff];
                // the 1 means the left can be a new combination for right with the diff difference
                dpMemo[right][diff] += dpMemo[left][diff] + 1;
            }
        }
        return ans;
    }
private:
    static int const MIN_SIZE = 3;
};

class index_map {
    static constexpr int SZ = 4096;
    vector<vector<pair<int, int>>> data {SZ};
    int sz = 0;

public:
    int add(int v) {
        auto &d = data[v & (SZ-1)];
        for (auto [w, i] : d) if (w == v) return i;
        d.push_back({v, sz});
        return sz++;
    }

    int operator[](int v) {
        for (auto [w, i] : data[v & (SZ-1)]) if (w == v) return i;
        return -1;
    }

    int size() { return sz; }
};

class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        index_map nids;
        vector<int> pids; pids.reserve(nums.size());
        for (int n : nums) pids.push_back(nids.add(n));

        vector<int> dp(nums.size() * nids.size());
        int res = 0;
        for (int i = 1; i < size(nums); ++i) {
            int ni = nums[i], idxBase = i * nids.size();
            for (int j = 0; j < i; ++j) {
                int idx = idxBase + pids[j];
                ++dp[idx];

                int id;
                long long nk = nums[j] * 2LL - ni;
                if (nk < INT_MIN || nk > INT_MAX || (id = nids[nk]) < 0) continue;
                int cnt = dp[j * nids.size() + id];
                dp[idx] += cnt;
                res += cnt;
            }
        }
        return res;
    }
};

class Solution {
public:
    int numberOfArithmeticSlices(std::vector<int> const & nums) {
        const int n = nums.size();
        int result = 0;
        std::unordered_map<int, std::vector<int>> histogram;
        int dp[n][n];
        std::memset(dp, 0, sizeof(dp));
        for (int i = 0; i < n; ++i) {
            histogram[nums[i]].push_back(i);
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                long next = 2l * nums[j] - nums[i];
                if (next < std::numeric_limits<int>::lowest() || next > std::numeric_limits<int>::max()) {
                    continue;
                }
                if (auto it = histogram.find(next); it != end(histogram)) {
                    for (int k : it->second) {
                        if (k >= j) {
                            break;
                        }
                        dp[i][j] += dp[j][k] + 1;
                    }
                }
                result += dp[i][j];
            }
        }
        return result;
    }
};
