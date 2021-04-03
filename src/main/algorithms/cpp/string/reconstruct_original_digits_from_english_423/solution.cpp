#include "../../head.h"


// #define CNT_THREE_WITH_H
class Solution {
public:
    std::string originalDigits(std::string const & s) {
        // zero one two three four five six seven eight nine
        // 0 -> z
        // 2 -> w
        // 4 -> u
        // 6 -> x
        // 8 -> g
        // 1 -> o, if excluded zero and two and four
        // 3 -> t, if excluded two and eight or 3 -> h, if excluded eight
        // 5 -> f, if excluded four
        // 7 -> s, if exlcluded six
        // 9 -> i, if excluded five six and eight

        // plagiarizing from https://leetcode.com/problems/reconstruct-original-digits-from-english/discuss/91207/one-pass-O(n)-JAVA-Solution-Simple-and-Clear
        // and https://leetcode.com/problems/reconstruct-original-digits-from-english/discuss/91210/Fun-fact

        std::vector<int> digitsCnt(DIGIT_SIZE, 0);
        for (char const c : s) {
            switch (c) {
                case 'z' :
                    digitsCnt[0]++;
                    break;
                case 'w' :
                    digitsCnt[2]++;
                    break;
                case 'u' :
                    digitsCnt[4]++;
                    break;
                case 'x' :
                    digitsCnt[6]++;
                    break;
                case 'g' :
                    digitsCnt[8]++;
                    break;
                case 'o' :
                    digitsCnt[1]++;
                    break;
               #ifdef CNT_THREE_WITH_H
                case 'h' :
               #else
                case 't' :
               #endif
                    digitsCnt[3]++;
                    break;
                case 'f' :
                    digitsCnt[5]++;
                    break;
                case 's' :
                    digitsCnt[7]++;
                    break;
                case 'i' :
                    digitsCnt[9]++;
                    break;
                default:
                    break;
            }
        }

        digitsCnt[1] -= digitsCnt[0] + digitsCnt[2] + digitsCnt[4];
        #ifdef CNT_THREE_WITH_H
        digitsCnt[3] -= digitsCnt[8];
        #else
        digitsCnt[3] -= digitsCnt[2] + digitsCnt[8];
        #endif
        digitsCnt[5] -= digitsCnt[4];
        digitsCnt[7] -= digitsCnt[6];
        digitsCnt[9] -= digitsCnt[5] + digitsCnt[6] + digitsCnt[8];

        std::string ans;
        for (int digit = 0; digit < DIGIT_SIZE; digit++) {
            for (int cnt = 0; cnt < digitsCnt[digit]; cnt++) {
                ans += std::to_string(digit);
            }
        }
        return ans;
    }
private:
    static int const  DIGIT_SIZE = 10;
};

class Solution {
public:
    std::string originalDigits(std::string const & s) {
        // zero one two three four five six seven eight nine
        // 0 -> z
        // 2 -> w
        // 4 -> u
        // 6 -> x
        // 8 -> g
        // 1 -> o, if excluded zero and two and four
        // 3 -> t, if excluded two and eight or 3 -> h, if excluded eight
        // 5 -> f, if excluded four
        // 7 -> s, if exlcluded six
        // 9 -> i, if excluded five six and eight

        // plagiarizing from https://leetcode.com/problems/reconstruct-original-digits-from-english/discuss/91207/one-pass-O(n)-JAVA-Solution-Simple-and-Clear
        // and https://leetcode.com/problems/reconstruct-original-digits-from-english/discuss/91210/Fun-fact
        static std::vector<std::string> digitsLetter{{"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"}};
        static std::vector<char> recognize{{'z', 'o', 'w', 'h', 'u', 'f', 'x', 's', 'g', 'i'}};
        static std::vector<int> orderedDigits{{0, 2, 4, 6, 8, 1, 3, 5, 7, 9}};

        static std::vector<int> digitsCnt(DIGIT_SIZE, 0);
        static std::vector<int> lettersCnt(LETTER_SIZE, 0);
        for (char const c : s) {
            lettersCnt[c - OFFSET]++;
        }

        for (int orderDigit : orderedDigits) {
            digitsCnt[orderDigit] = lettersCnt[recognize[orderDigit] - OFFSET];
            for (char c : digitsLetter[orderDigit]) {
                lettersCnt[c - OFFSET] -= digitsCnt[orderDigit];
            }
        }

        std::string ans;
        for (int digit = 0; digit < DIGIT_SIZE; digit++) {
            for (int cnt = 0; cnt < digitsCnt[digit]; cnt++) {
                ans += std::to_string(digit);
            }
        }
        return ans;
    }
private:
    static int const DIGIT_SIZE = 10;
    static int const LETTER_SIZE = 26;
    static char const OFFSET = 'a';

};
