#include "../../head.h"


// #define DEBUG
class Solution {
public:
    int numDupDigitsAtMostN(int N) {
        // plagiarizing from https://leetcode.com/problems/numbers-with-repeated-digits/discuss/256725/JavaPython-Count-the-Number-Without-Repeated-Digit
        int maxN = N + 1; // excluded
        std::string maxNStr = std::to_string(maxN);
        int const maxNStrSize = maxNStr.size();
        // get each digit on the pos
        std::vector<int> digits(maxNStrSize, 0);
        for (int idx = 0; idx < maxNStrSize; idx++) {
            digits[idx] = maxNStr[idx] - '0';
        }
        std::string().swap(maxNStr);

        int noRepeatAns = 0;
        for (int smallerLen = 1; smallerLen < digits.size(); smallerLen++) {
            // the length who is smaller than maxNStrSize; for example maxNStrSize = 8;
            // we compute all elements that smaller than 8;
            // the first element can only be chosed from 1 - 9; the left are chose from 0 - 9 and remove the first one
            noRepeatAns += 9 /* the first element chosed from 1 - 9 */ *
                (/*from 9 elements chose smallerLen - 1 elements*/
                 A(9 /*the left elements can be selected from 0 - 9, and remove the first, which means we have 9 choice*/,
                   smallerLen - 1 /*excluded the first element, there are smallerLen - 1 elements left*/)
                 );
        }
        #ifdef DEBUG
        std::cout << noRepeatAns << "smaller one digit \n";
        #endif
        std::vector<bool> allDigits(ALL_DIGITS_LEN, false);
        // deal with number that has same length with N
        for (int idx = 0; idx < digits.size(); idx++) {
            for (int start = (idx > 0 /*the pos is not the first*/ ? 0 : 1); start < digits[idx]; start++) {
                // for the cur position, we can chose from start to digits[idx](excluded)
                if (!allDigits[start]) {
                    // we have not use this digit before
                    noRepeatAns += A(9 - idx
                            /*from idx + 1 to maxNStrSize(excluded), we have use idx + 1 elements, there are total 10 digits*/,
                            maxNStrSize - idx - 1);
                }
            }
            if (allDigits[digits[idx]]) {
                // we have used this digit before, then all the noRepeat has been computed
                break;
            }
            allDigits[digits[idx]] = true; // the digits[idx] has been used, we move to right
        }
        #ifdef DEBUG
        std::cout << noRepeatAns << "digit \n";
        #endif
        return N - noRepeatAns;
    }
private:
    int A(int m, int n) {
        // from m elements select n elements. the elements are different, which means the order matters
        assert(m >= n);
        return n == 0 ? 1 : (A(m, n - 1) * (m - n + 1));
    }
private:
    static int const ALL_DIGITS_LEN = 10;
};



// #define DEBUG
class Solution {
public:
    int numDupDigitsAtMostN(int N) {
        // plagiarizing from https://leetcode.com/problems/numbers-with-repeated-digits/discuss/258212/Share-my-O(logN)-C%2B%2B-DP-solution-with-proof-and-explanation
        std::string NStr = std::to_string(N);
        int const NStrSize = NStr.size();
        // get each digit on the pos
        std::vector<int> digits(NStrSize, 0);
        for (int idx = 0; idx < NStrSize; idx++) {
            digits[idx] = NStr[idx] - '0';
        }
        std::string().swap(NStr);

        int noRepeatAns = 0;
        std::vector<int> noRepeatSmaller(NStrSize, 0);
        for (int smallerLen = 1; smallerLen < NStrSize; smallerLen++) {
            // each time, we can add one element from 10 - (smallerLen - 1) digits to the former (smallerLen - 1);
            noRepeatSmaller[smallerLen] = (1 == smallerLen) ? 9 : noRepeatSmaller[smallerLen - 1] * (10 - (smallerLen - 1));
            noRepeatAns += noRepeatSmaller[smallerLen];
        }
        #ifdef DEBUG
        std::cout << noRepeatAns << "digit \n";
        #endif

        bool isDuplicate = false;
        std::vector<int> digitsCnt(ALL_DIGITS_LEN, 0);
        std::vector<int> noRepeatSameLen(NStrSize, 0);

        for (int idx = 0; idx < NStrSize; idx++) {
            // we just compute the noRepeat combination
            // if there is a duplicate, then the left digits can take all the range from 0 - 9 except appear before
            noRepeatSameLen[idx] = (0 == idx) ? 9 : (noRepeatSameLen[idx - 1] * (10 - idx));
            if (!isDuplicate) {
                int diff = 0;
                for (int upper = digits[idx] + 1; upper < 10; upper++) {
                    // because noRepeatSameLen[idx] don't accumulate the repeat situation, so we should exclude repeat
                    diff += (0 == digitsCnt[upper]);
                }
                noRepeatSameLen[idx] -= diff;
                digitsCnt[digits[idx]]++;
                if (digitsCnt[digits[idx]] > 1) {
                    isDuplicate = true;
                }
            }
        }
        return N - noRepeatAns - noRepeatSameLen[NStrSize - 1];
    }
private:
    static int const ALL_DIGITS_LEN = 10;
};
