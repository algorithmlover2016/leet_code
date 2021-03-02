#include "../../head.h"


// #define DEBUG
class Solution {
public:
    int minimumDistance(std::string const & word) {
        // plagiarizing from https://leetcode.com/problems/minimum-distance-to-type-a-word-using-two-fingers/discuss/477652/JavaC%2B%2BPython-1D-DP-O(1)-Space
        std::unordered_map<int, int> dpMemo;
        dpMemo[0] = 0;
        for (char const c : word) {
            // if add 1, from 1 to 6, they should be in a row, but the distance() will get wrong answer
            // int cNum = c - BASIC_OFFSET + 1;
            int cNum = c - BASIC_OFFSET + ROW_SIZE; // cNum start from 6 which is a n * ROW_SIZE, 1 <= n <= 18

#ifdef DEBUG
            std::cout << "\ncur Letter: " << c << "\t";
#endif
            std::unordered_map<int, int> nextDpStatus;
            for (auto const & [coded, minDis] : dpMemo) {
                int finger1Pos = 0, finger2Pos = 0;
                decode(coded, finger1Pos, finger2Pos);
#ifdef DEBUG
                std::cout << "cur Finger: " << finger1Pos << ",\t" << finger2Pos << ";\t";
#endif
                // from figner1 to cNum, finger1Pos now is at cNum, after this move
                int finger1Move = encode(cNum, finger2Pos);
                if (nextDpStatus.find(finger1Move) == nextDpStatus.end()) {
                    nextDpStatus[finger1Move] = minDis + distance(finger1Pos, cNum);
                } else {
                    nextDpStatus[finger1Move] = std::min(nextDpStatus[finger1Move], minDis + distance(finger1Pos, cNum));
                }

                // from finger2 to cNum
                int finger2Move = encode(finger1Pos, cNum);
                if (nextDpStatus.find(finger2Move) == nextDpStatus.end()) {
                    nextDpStatus[finger2Move] = minDis + distance(finger2Pos, cNum);
                } else {
                    nextDpStatus[finger2Move] = std::min(nextDpStatus[finger2Move], minDis + distance(finger2Pos, cNum));
                }

            }
            std::swap(dpMemo, nextDpStatus);
        }
        int ans = INT_MAX;
        for (auto const & [key, minDis] : dpMemo) {
            ans = std::min(ans, minDis);
        }
        return ans;

    }

private:
    int encode(int finger1Pos, int finger2Pos) {
        return ((finger1Pos & FINGER_CODE_RESET) << FINGER_CODE_OFFSET) | (finger2Pos & FINGER_CODE_RESET);
    }
    void decode(int coded, int & finger1Pos, int & finger2Pos) {
        finger2Pos = (coded & FINGER_CODE_RESET);
        finger1Pos = (coded >> FINGER_CODE_OFFSET) & FINGER_CODE_RESET;
    }
    int distance(int a, int b) {
        if (JUST_ZERO == a) {
            // if a is zero, which means finger is at any position, so it can be initialized at b
            return a;
        }
        return (std::abs(a / ROW_SIZE - b / ROW_SIZE) + std::abs(a % ROW_SIZE - b % ROW_SIZE));
    }
private:
    static int const JUST_ZERO = 0;
    static int const ROW_SIZE = 6;
    // static int const LETTER_ROW_OFFSET = ROW_SIZE - 1;
    static char const BASIC_OFFSET = 'A';
    static int const FINGER_CODE_OFFSET = 8;
    static int const FINGER_CODE_RESET = 0xFF;

};

class Solution {
public:
    int minimumDistance(std::string const & word) {
        // plagiarizing from https://leetcode.com/problems/minimum-distance-to-type-a-word-using-two-fingers/discuss/477652/JavaC++Python-1D-DP-O(1)-Space/426597

        if (JUST_TWO >= word.size()) {
            return 0;
        }

        std::vector<int> dpMemo(UPPER_LETTERS_WITH_INIT_NUM, INIT_MAX);
        dpMemo[UPPER_LETTERS_NUM] = 0;
        for (int idx = 1; idx < word.size(); idx++) {
            int oneFinger = word[idx - 1] - BASIC_OFFSET;
            int needType = word[idx] - BASIC_OFFSET;
            std::vector<int> nextDpStatus(UPPER_LETTERS_WITH_INIT_NUM, INIT_MAX);

            //  the other finger can be at any location. only if we record the status
            for (int otherFinger = 0; otherFinger <= UPPER_LETTERS_NUM; otherFinger++) {
                // from oneFinger jump to needType
                nextDpStatus[otherFinger] = std::min(nextDpStatus[otherFinger],
                        dpMemo[otherFinger] + distance(oneFinger, needType));
                // from the other finger jump to needType
                nextDpStatus[oneFinger] = std::min(nextDpStatus[oneFinger],
                        dpMemo[otherFinger] + distance(otherFinger, needType));
            }
            std::swap(dpMemo, nextDpStatus);
        }
        return *std::min_element(dpMemo.begin(), dpMemo.end());
    }
private:
    int distance(int from, int to) {
        if (UPPER_LETTERS_NUM == from) {
            return 0;
        }
        return std::abs(from / ROW_SIZE  - to / ROW_SIZE) + std::abs(from % ROW_SIZE  - to % ROW_SIZE);
    }

private:
    static int const UPPER_LETTERS_NUM = 26;
    static int const UPPER_LETTERS_WITH_INIT_NUM = UPPER_LETTERS_NUM + 1;
    static int const JUST_TWO = 2;
    static char const BASIC_OFFSET = 'A';
    static int const ROW_SIZE = 6;
    int const INIT_MAX = INT_MAX - UPPER_LETTERS_WITH_INIT_NUM;
};


class Solution {
public:
    int minimumDistance(std::string const & word) {
        // plagiarizing from https://leetcode.com/problems/minimum-distance-to-type-a-word-using-two-fingers/discuss/477652/JavaC%2B%2BPython-1D-DP-O(1)-Space

        if (JUST_TWO >= word.size()) {
            return 0;
        }
        std::vector<int> dpMemo(UPPER_LETTERS_NUM, 0);
        int save = 0;
        int oneFingerAns = 0;
        for (int idx = 0; idx + 1 < word.size(); idx++) {
            int curFinger = word[idx] - BASIC_OFFSET;
            int nextType = word[idx + 1] - BASIC_OFFSET;
            for (int otherFinger = 0; otherFinger < UPPER_LETTERS_NUM; otherFinger++) {
                dpMemo[curFinger] = std::max(dpMemo[curFinger],
                        dpMemo[otherFinger] + distance(curFinger, nextType) - distance(otherFinger, nextType));
            }
            save = std::max(save, dpMemo[curFinger]);
            oneFingerAns += distance(curFinger, nextType);
        }
        return oneFingerAns - save;
    }

private:
    int distance(int from, int to) {
        return std::abs(from / ROW_SIZE  - to / ROW_SIZE) + std::abs(from % ROW_SIZE  - to % ROW_SIZE);
    }

private:
    static int const UPPER_LETTERS_NUM = 26;
    static int const JUST_TWO = 2;
    static char const BASIC_OFFSET = 'A';
    static int const ROW_SIZE = 6;
};


