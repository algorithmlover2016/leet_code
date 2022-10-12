#include "../../head.h"

// #define DEBUG
// #define ADD_ONE_ON_NUM // refer to https://leetcode.com/problems/count-special-integers/solutions/2425271/java-python-math/
class Solution {
public:
    int countSpecialNumbers(int n) {
        #ifdef ADD_ONE_ON_NUM
        std::string nStr = std::to_string(n + 1);
        #else
        std::string nStr = std::to_string(n);
        #endif
        int ans = 0;
        int nStrSize = nStr.size();
        if (nStrSize > 1) {
            for (int len = nStrSize - 1; len > 0; len--) {
                int mul = 9;
                for (int i = 1; i < len; i++) {
                    mul *= (10 - i);
                }
                ans += mul;
                #ifdef DEBUG
                std::cout << "without the first letter, ans: " << ans << "\n";
                #endif
            }
        }

        {
            int mul = (nStr[0] - OFFSET - 1);
            for (int idx = 1; idx < nStrSize; idx++) {
                mul *= (10 - idx);
            }
            ans += mul;
            #ifdef DEBUG
            std::cout << "with the first letter, ans: " << ans << "\n";
            #endif
            if (1 == nStrSize) {
                #ifndef ADD_ONE_ON_NUM
                ans += 1; // nStr[0] - OFFSET
                #endif
                return ans;
            }
        }

        if (nStrSize > 1) {
            std::set<int> visited;
            visited.insert(nStr[0] - OFFSET);
            for (int idx = 1; idx < nStr.size(); idx++) {
                int cur = nStr[idx] - OFFSET;
                auto it = std::lower_bound(std::begin(visited), std::end(visited), cur);
                int needIg = std::distance(std::begin(visited), it);
                #ifdef DEBUG
                std::cout << "curIdx: " << idx << ", " << cur << "; Need delete: " << needIg << ";\t";
                #endif

                int mul = cur - needIg;
                for (int i = idx + 1; i < nStr.size(); i++) {
                    mul *= (10 - i);
                }
                ans += mul;
                #ifdef DEBUG
                std::cout <<  "cur idx: " << ans << "\n";
                #endif
                if (*it == cur) {
                    break;
                }
                #ifndef ADD_ONE_ON_NUM
                ans += (idx == nStrSize - 1 ? 1 : 0);
                #endif
                visited.insert(cur);
            }
        }
        return ans;
    }
private:
    char constexpr static OFFSET = '0';
};


class SolutionPERM {
public:
    int countSpecialNumbers(int n) {
        // plagiarizing from https://leetcode.com/problems/count-special-integers/solutions/2425271/java-python-math/
        std::string nStr = std::to_string(n + 1);
        std::set<int> visited;
        int ans = 0;
        for (int len = 1; len < nStr.size(); len++) {
            ans += 9 * A(9, len - 1);
        }
        for (int idx = 0; idx < nStr.size(); idx++) {
            for (int j = (idx == 0 ? 1 : 0); j < nStr[idx] - OFFSET; j++) {
                if (visited.find(j) == visited.end()) {
                    ans += A(9 - idx, nStr.size() - idx - 1); // from idx + 1 (included) to nStr.size() (excluded)
                }
            }
            if (visited.find(nStr[idx] - OFFSET) != visited.end()) {
                break;
            }
            visited.insert(nStr[idx] - OFFSET);
        }
        return ans;
    }
private:
    int A(int m, int n) {
        // m >= n
        return 0 == n ? 1 : (A(m, n - 1) * (m - n + 1));
    }
private:
    char constexpr static OFFSET = '0';
};


// #define DEBUG
// #define ADD_ONE
class SolutionDFS {
public:
    int countSpecialNumbers(int n) {
        //plagiarizing from https://leetcode.com/problems/count-special-integers/solutions/2422436/counting-dfs/
        #ifdef ADD_ONE
        std::string nStr = std::to_string(n + 1); // because in dfs, we return 1 when idx == s.size()
        #else
        std::string nStr = std::to_string(n); // because in dfs, we return 1 when idx == s.size()
        #endif
        int ans = dfs(nStr, 0, 0);
        #ifdef DEBUG
        std::cout << "with same len ans: " << ans << "\n";
        #endif
        for (int len = 1; len < nStr.size(); len++) {
            ans += 9 * A(9, len - 1); // we can select one from 1 - 9 for the left most pos, and the others pos can select from 0 - 9 except the left most one.
        }
        return ans;
    }
private:
    int dfs(std::string const & s, int idx, int mask) {
        if (idx == s.size()) {
            #ifdef ADD_ONE
            return 0;
            #else
            return 1;
            #endif
        }
        int cur = s[idx] - OFFSET;
        int ans = 0;
        for (int num = (0 == idx ? 1 : 0 /* it measn it's the left most pos, can not be zero*/); num < cur; num++) {
            if ((mask & (1 << num) /* it means the num has been used in the left pos. */)) {
                continue;
            }
            ans += A(9 - idx, s.size() - 1 - idx);
            #ifdef DEBUG
            std::cout << "idx: " << idx << ", num: " << num << ": " << A(9 - idx, s.size() - 1 - idx) << "\n";
            #endif
        }
        return ans + ((mask & (1 << cur)) ? 0 : dfs(s, idx + 1, mask | (1 << cur)));
    }
    int A(int m, int n) {
        // m >= n
        return 0 == n ? 1 : (A(m, n - 1) * (m - n + 1));
    }
private:
    char constexpr static OFFSET = '0';
};

class Solution {
public:
    int countSpecialNumbers(int n) {
        // plagiarizing from https://leetcode.com/problems/count-special-integers/solutions/2422090/c-with-explanation-digit-dynamic-programming/
        std::vector<std::vector<std::vector<int>>> dpMemo(MAX_DIGITS, 
                                                            std::vector<std::vector<int>>(TIGHT + 1,
                                                                                            std::vector<int>((1 << MASK_BITS), INIT_VAL)));
        std::string nStr = std::to_string(n);
        return dfs(nStr, 0, 1, 0, dpMemo);
    }

private:
    int dfs(std::string const & s, int idx, int tight, int mask, std::vector<std::vector<std::vector<int>>> & dpMemo) {
        if (idx == s.size()) {
            return 0 != mask; // mask is zero, which is 0, which should not be counted.
        }
        if (INIT_VAL != dpMemo[idx][tight][mask]) {
            return dpMemo[idx][tight][mask];
        }
        int ans = 0;
        if (tight) {
            int cur = s[idx] - OFFSET;
            for (int num = 0; num <= cur; num++) {
                if (mask & (1 << num)) {
                    continue;
                }
                int newMask = ((0 == mask && 0 == num) ? mask /* 0 */ : mask | (1 << num));
                if (num == cur) {
                    ans += dfs(s, idx + 1, tight, newMask, dpMemo);
                } else {
                    ans += dfs(s, idx + 1, NOT_TIGHT, newMask, dpMemo);
                }
            }
        } else {
            for (int num = 0; num <= 9; num++) {
                if (mask & (1 << num)) {
                    continue;
                }
                int newMask = ((0 == mask && 0 == num) ? mask /* 0 */ : mask | (1 << num));
                ans += dfs(s, idx + 1, NOT_TIGHT, newMask, dpMemo);
            }
        }
        return dpMemo[idx][tight][mask] = ans;
    }
private:
    char constexpr static OFFSET = '0';
    int constexpr static MAX_DIGITS = 10; // because n <= 2 * 1e9 which is 2,000, 000, 000 whose length is 10
    int constexpr static TIGHT = 1;
    int constexpr static NOT_TIGHT = 0;
    int constexpr static MASK_BITS = 10; // length is 10 ,which will lead to 2 ^ 10 combination.
    int constexpr static INIT_VAL = -1;
};
int constexpr Solution::INIT_VAL;