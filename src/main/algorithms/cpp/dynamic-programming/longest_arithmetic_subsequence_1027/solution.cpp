#include "../../head.h"


class Solution {
public:
    int longestArithSeqLength(std::vector<int> const & A) {
        // plagiairizing from https://youtu.be/-NIlLdVKBFs
        if (A.empty()) {
            return 0;
        }
        int const ASize = A.size();
        std::vector<std::unordered_map<int, int>> dpMemo(ASize);

        int ans = 0;
        for (int idx = 0; idx < ASize; idx++) {
            for (int prev = 0; prev < idx; prev++) {
                int diff = A[idx] - A[prev];
                if (dpMemo[prev].find(diff) == dpMemo[prev].end()) {
                    dpMemo[idx][diff] = 2;
                } else {
                    dpMemo[idx][diff] = dpMemo[prev][diff] + 1;
                }
                ans = std::max(ans, dpMemo[idx][diff]);
            }
        }
        return ans;
    }
};

class SolutionTLE {
public:
    int longestArithSeqLength(std::vector<int> const & A) {
        // plagiairizing from https://youtu.be/-NIlLdVKBFs
        if (A.empty()) {
            return 0;
        }
        int const ASize = A.size();
        std::vector<std::unordered_map<int, int>> dpMemo(ASize);

        int ans = 0;
        for (int idx = 0; idx < ASize; idx++) {
            for (int prev = 0; prev < idx; prev++) {
                int diff = A[idx] - A[prev];
                ans = std::max(ans, dpMemo[idx][diff] = dpMemo[prev][diff] + 1);
            }
        }
        return ans + 1;
    }
};

class Solution {
public:
    int longestArithSeqLength(std::vector<int> const & A) {
        // plagiairizing from https://youtu.be/-NIlLdVKBFs
        if (A.empty()) {
            return 0;
        }
        int const ASize = A.size();
        static int const BASIC_OFFSET = 500;
        std::vector<std::vector<int>> dpMemo(ASize, std::vector<int>(BASIC_OFFSET * 2 + 1, 0));

        int ans = 0;
        for (int idx = 0; idx < ASize; idx++) {
            for (int prev = 0; prev < idx; prev++) {
                int diff = A[idx] - A[prev] + BASIC_OFFSET;
                ans = std::max(ans, dpMemo[idx][diff] = dpMemo[prev][diff] + 1);
            }
        }
        return ans + 1;
    }
};

class Solution {
public:
    int longestArithSeqLength(std::vector<int> const & A) {
         int dp[A.size()][1001];
         std::memset(dp, 0, sizeof(dp));

        int ans = 1;
        const int BASIC_OFFSET = 500;
        for (int i = 1; i < A.size(); i++) {
            for (int j = 0; j < i; j++) {
                int d = A[i] - A[j];
                ans = std::max(dp[i][d + BASIC_OFFSET] = dp[j][d + BASIC_OFFSET] + 1, ans);
            }
        }

        return ans + 1;
    }
};
