#include "../../head.h"


class Solution {
public:
    std::vector<std::string> letterCombinations(std::string const & digits) {
        std::vector<std::string> ans;
        if (digits.empty()) {
            return ans;
        }
        static bool initFlag = (init(), true);
        std::string curAns;
        dfs(digits, 0, curAns, ans);
        return ans;
    }

private:
    void dfs(std::string const & digits, int start, std::string & curAns, std::vector<std::string> & ans) {
        int const digitsSize = digits.size();
        if (start == digitsSize) {
            ans.emplace_back(curAns);
            return;
        }
        int idx = digits[start] - START_DIGIT;
        for (char c : digit2letters[idx]) {
            curAns.push_back(c);
            dfs(digits, start + 1, curAns, ans);
            curAns.pop_back();
        }
    }

    void init() {
        char begin = START_LETTER;
        for (int digit = 0; digit < DIGIT_LEN; digit++) {
            int mapLen = DIGIT_MAP_LEN;
            // the digit 8 has 3 letters not 4
            if (digit < DIGIT_LEN - DIGIT_MAP_FOUR_LEN || 6 == digit) {
                mapLen--;
                digit2letters[digit].pop_back();
            }
            for (int mapIdx = 0; mapIdx < mapLen; mapIdx++) {
                digit2letters[digit][mapIdx] = begin++;
            }
        }
    }
private:
    static int const DIGIT_LEN = 8;
    static int const DIGIT_MAP_LEN = 4;
    static int const DIGIT_MAP_FOUR_LEN = 3;
    static char const START_DIGIT = '2';
    static char const START_LETTER = 'a';
    static std::vector<std::vector<char>> digit2letters;
};
std::vector<std::vector<char>> Solution::digit2letters = std::vector<std::vector<char>>(DIGIT_LEN,
                                                            std::vector<char>(DIGIT_MAP_LEN));

class Solution {
public:

    void generateCombinations(std::string const & digits, int start, int n,
            std::string str, std::unordered_map<char, std::string> const & hashmap,
            std::vector<std::string> &ans) {
        if (start == n) {
            ans.push_back(str);
        }

        for (int i=0; i < hashmap[digits[start]].size(); i++) {
            //str = str+hashmap[digits[start]][i];
            generateCombinations(digits, start + 1, n, str + hashmap[digits[start]][i], hashmap, ans);
        }
    }

    std::vector<std::string> letterCombinations(std::string const & digits) {
        std::vector<std::string> ans;
        int n = digits.size();

        if (n == 0) {
            return ans;
        }

        std::unordered_map<char, std::string> hashmap;
        hashmap['2'] = "abc";
        hashmap['3'] = "def";
        hashmap['4'] = "ghi";
        hashmap['5'] = "jkl";
        hashmap['6'] = "mno";
        hashmap['7'] = "pqrs";
        hashmap['8'] = "tuv";
        hashmap['9'] = "wxyz";

        generateCombinations(digits, 0, n, "", hashmap, ans);

        return ans;
    }
};
