#include "../../head.h"


class Solution {
public:
    std::string encode(std::string const & str) {
        if (str.empty()) {
            return "";
        }
        int const strSize = str.size();
        std::vector<std::vector<std::string>> dp(strSize,
                std::vector<std::string>(strSize)); // initialize to ""
        for (int idxLeft = strSize - 1; idxLeft > -1; idxLeft--) {
            for (int idxRight = idxLeft; idxRight < strSize; idxRight++) {
                std::string curLeftRight = str.substr(idxLeft, idxRight - idxLeft + 1);
                dp[idxLeft][idxRight] = curLeftRight;
                if (dp[idxLeft][idxRight].size() > MINI_LEN) {
                    for (int idx = idxLeft; idx < idxRight; idx++) {
                        // must split the idx from idxLeft to idx(include), and from idx + 1 to idxRight
                        if (dp[idxLeft][idx].size() + dp[idx + 1][idxRight].size() <
                                dp[idxLeft][idxRight].size()) {
                            dp[idxLeft][idxRight] = dp[idxLeft][idx] + dp[idx + 1][idxRight];
                        }
                    // }
                    // for (int idx = idxLeft; idx < idxRight; idx++) {
                        std::string pattern = str.substr(idxLeft, idx - idxLeft + 1);
                        if (0 == curLeftRight.size() % pattern.size() &&
                                "" == replaceAll(curLeftRight, pattern, "")) {
                            std::string patternAns = std::to_string(curLeftRight.size() / pattern.size()) + 
                                "[" + dp[idxLeft][idx] + "]";
                            // std::cout << "patternAns: " << patternAns << "\t";
                            // dp[idxLeft][idxRight] = patternAns;
                            if (patternAns.size() < dp[idxLeft][idxRight].size()) {
                                dp[idxLeft][idxRight] = patternAns;
                            }
                        }
                    }
                }
            }
        }
        return dp[0][strSize - 1];
    }

private:
    std::string replaceAll(std::string const & str,
            std::string const & search,
            std::string const & rep = "") {
        std::string ans(str);
        size_t const repSize = rep.size();
        size_t pos = 0;
        while ((pos = ans.find(search, pos)) != std::string::npos) {
            ans.replace(pos, search.size(), rep);
            pos += repSize;
        }
        return ans;
    }

private:
    static int const MINI_LEN = 4;

};

int main() {
    Solution s;
    std::string input("aaa");

    std::cout << "input " << input << ": " << "\t" << s.encode(input) << "\n";
    input = "aaaaa";
    std::cout << "input " << input << ": " << "\t" << s.encode(input) << "\n";
    input = "aaaaaaaaaa";
    std::cout << "input " << input << ": " << "\t" << s.encode(input) << "\n";
    input = "aabcaabcd";
    std::cout << "input " << input << ": " << "\t" << s.encode(input) << "\n";
    input = "abbbabbbcabbbabbbc";
    std::cout << "input " << input << ": " << "\t" << s.encode(input) << "\n";
    return 0;
}
