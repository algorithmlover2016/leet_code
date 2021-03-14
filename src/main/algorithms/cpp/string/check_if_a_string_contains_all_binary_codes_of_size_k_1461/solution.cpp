#include "../../head.h"


// #define DEBUG
// https://blog.csdn.net/MOU_IT/article/details/89060249
class Solution {
public:
    bool hasAllCodes(std::string const & s, int k) {
        int const len = 1 << k;
        std::bitset<MAX_K> bInt;
        std::set<int> combs;

        for (int idx = 0; idx + k <= s.size(); idx++) {
            int num = std::stoi(s.substr(idx, k), nullptr, 2);
            #ifdef DEBUG
            std::cout << s.substr(idx, k) << ", " << num << "\n";
            #endif
            combs.insert(num);
        }
        return combs.size() == len;

    }
private:
    static int const MAX_K = 20;
};

class Solution {
public:
    bool hasAllCodes(std::string const & s, int k) {
        // plagiarizing idea from https://youtu.be/_gL9Q0_sCQs
        int const len = 1 << k;
        std::set<int> combs;

        int curNum = 0; // because max(k) <= 20
        for (int idx = 0; idx < s.size(); idx++) {
            curNum = (curNum << 1) & (len - 1) | (s[idx] - '0');

            if (idx >= k - 1) {
                combs.insert(curNum);
            }
        }
        return combs.size() == len;

    }
};

class Solution {
public:
    bool hasAllCodes(std::string const & s, int k) {
        if (s.length() < k) {
            return false;
        }
        int const len = 1 << k;
        std::vector<bool> binary(1 << k);
        int bc = 0;
        int cnt = 0;
        for (int i = 0; i < k - 1; i++) {
            bc |= s[i] - '0';
            bc <<= 1;
        }
        for (int i = k - 1, mask = len - 1; i < s.length(); i++) {
            bc |= s[i] - '0';
            cnt += 1 - binary[bc];
            binary[bc] = true;
            bc <<= 1;
            bc &= mask;
        }
        return cnt == len;
    }
};
