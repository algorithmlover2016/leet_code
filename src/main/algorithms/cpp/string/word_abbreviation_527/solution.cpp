#include "../../head.h"

#define TEST
#define OUTPUT_TO_SCREEN
class Solution {
public:
    std::vector<std::string> wordsAbbreviation(std::vector<std::string> const & dict) {
        // plagiarizing idea from https://www.youtube.com/watch?v=lI1GGOBgmfc
        int const dictSize = dict.size();
        std::vector<std::string> ans(dictSize);
        std::vector<int> prefixIdx(dictSize, 0);
        std::unordered_map<std::string, std::vector<int>> abbr2IdxMap;
        for (int idx = 0; idx < dictSize; idx++) {
            std::string curAbbrStr = abbr(dict[idx]);
            ans[idx] = curAbbrStr;
            abbr2IdxMap[curAbbrStr].emplace_back(idx);
        }

        for (auto & [key, val] : abbr2IdxMap) {
            int const valSize = val.size();
            if (ONLY_ONE == valSize) {
                continue;
            }
            std::unordered_map<std::string, std::vector<int>> dulps;
            dulps[key] = val;
            while (!dulps.empty()) {
                std::unordered_map<std::string, std::vector<int>> nextDulps;
                for (auto & [innerKey, innerVal] : dulps) {
                    if (ONLY_ONE == innerVal.size()) {
                        continue;
                    }
                    for (const auto idx : innerVal) {
                        prefixIdx[idx] += 1;
                        ans[idx] = abbr(dict[idx], prefixIdx[idx]);
                        nextDulps[ans[idx]].emplace_back(idx);
                    }
                }
                std::swap(dulps, nextDulps);
            }
        }
        return ans;
    }

    std::string abbr(std::string const & str, int prefix = 0) {
        // prefix will not be abbreviated
        int const strSize = str.size();
        if (MIN_LEN >= strSize - prefix) {
            return str;
        }
        return std::string(str.substr(0, prefix + 1) + // the prefix
                std::to_string(strSize - 2 - prefix) + // the number of abbreviated characters
                str[strSize - 1]); // the last character
    }
private:
    static int const MIN_LEN = 3;
    static int const ONLY_ONE = 1;
};

#ifdef TEST
int main() {
    Solution obj;
    std::vector<std::string> dict{{"like", "god", "internal", "me", "internet", "interval",
                                    "intension", "face", "intrusion"}};
    
    std::vector<std::string> ans{{"l2e", "god", "internal", "me", "i6t", "interval", "inte4n",
                                    "f2e", "intr4n"}};


    std::vector<std::string> computeAns = obj.wordsAbbreviation(dict);

#ifdef OUTPUT_TO_SCREEN
    std::cout << "\n";
    for (auto const & ele : computeAns) {
        std::cout << ele << "\t";
    }
    std::cout << "\n";
#endif
    assert(ans == computeAns);
    return 0;
}
#endif
