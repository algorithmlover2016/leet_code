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

