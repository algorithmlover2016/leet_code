#include "../../head.h"
#include <string>
#include <cstring>
#include <vector>

class SolutionTLE {
public:
    long long totalWaviness(long long num1, long long num2) {
        long long wavinessSum = 0;
        for (int num = num1; num <= num2; ++num) {
            if (num < 100) {
                continue;
            }
            wavinessSum += computeWaviness(std::to_string(num));
        }
        return wavinessSum;
    }
private:
    long long computeWaviness(std::string const & numStr) {
        long long waviness = 0;
        for (size_t idx = 1; idx < numStr.size() - 1; ++idx) {
            if ((numStr[idx] > numStr[idx - 1] && numStr[idx] > numStr[idx + 1]) ||
                (numStr[idx] < numStr[idx - 1] && numStr[idx] < numStr[idx + 1])) {
                waviness += 1;
            }
        }
        return waviness;
    }
};

class Solution {
public:
    long long totalWaviness(long long num1, long long num2) {
        return solve(num2) - solve(num1 - 1);
    }

private:
    static const int LEAST_NUM = 100;
    static const int MAX_DIGITS_CNT = 16; // since 10^15 (1 000, 000, 000, 000, 000) < 2^64 < 10^16
    class Result {
    public:
        long long count;
        long long totalVal;
    };

    Result memo[MAX_DIGITS_CNT][11][11][2][2];
    bool visited[MAX_DIGITS_CNT][11][11][2][2];
    std::string s;

    long long solve(long long n) {
        if (n < LEAST_NUM) return 0;
        s = std::to_string(n);
        std::memset(visited, 0, sizeof(visited));
        return dfs(0, 10, 10, true, true).totalVal;
    }

    Result dfs(int pos, int pp, int p, bool tight, bool leadZero) {
        if (pos == s.size()) {
            return {1, 0};
        }
        if (visited[pos][pp][p][tight][leadZero]) {
            return memo[pos][pp][p][tight][leadZero];
        }

        long long count = 0;
        long long totalVal = 0;
        int limit = tight ? (s[pos] - '0') : 9;

        for (int d = 0; d <= limit; ++d) {
            bool nextTight = tight && (d == limit);
            bool nextLeadZero = leadZero && (d == 0);

            int next_pp = pp;
            int next_p = p;

            if (!nextLeadZero) {
                next_pp = p;
                next_p = d;
            }

            // Check if placing 'd' creates a peak or valley at 'p'
            int isWave = 0;
            // We need a valid previous-previous (pp) and previous (p) to check for a wave at p.
            // If leadZero was true, pp and p are 10, so this block won't execute, which is correct.
            if (pp != 10) { // == (!leadZero && pp != 10 && p != 10)
                if ((p > pp && p > d) || (p < pp && p < d)) {
                    isWave = 1;
                }
            }

            Result sub = dfs(pos + 1, next_pp, next_p, nextTight, nextLeadZero);
            
            count += sub.count;
            // The waviness added here (isWave) applies to all valid number completions (sub.count)
            // Plus the waviness accumulated from the sub-problems (sub.totalVal)
            totalVal += sub.totalVal + (isWave * sub.count);
        }

        visited[pos][pp][p][tight][leadZero] = true;
        memo[pos][pp][p][tight][leadZero] = {count, totalVal};
        return {count, totalVal};
    }
};