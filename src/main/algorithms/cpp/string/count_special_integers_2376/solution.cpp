#include "../../head.h"


// #define DEBUG
class Solution {
public:
    int countSpecialNumbers(int n) {
        std::string nStr = std::to_string(n);
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
                ans += 1; // nStr[0] - OFFSET
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
                ans += (idx == nStrSize - 1 ? 1 : 0);
                visited.insert(cur);
            }
        }
        return ans;
    }
private:
    char constexpr static OFFSET = '0';
};