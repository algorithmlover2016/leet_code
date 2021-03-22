#include "../../head.h"


// #define DEBUG
// #define USINT_STD__SET_INTERSECTION
class Solution {
public:
    int rotatedDigits(int N) {
        int ans = 0;
        for (int num = 1; num <= N; num++) {
            if (valid(num)) {
                ans++;
            }
        }
        return ans;
    }
private:
    bool valid(int num) {
        // plagiarizing idea from https://leetcode.com/problems/rotated-digits/discuss/116547/Easily-Understood-Java-Solution
        std::string numStr(std::to_string(num));
#ifdef USINT_STD__SET_INTERSECTION
        static std::set<int> canRotate{{1, 8, 0, 2, 5, 6, 9}};

        static std::set<int> rotateNoChage{{1, 8, 0}};

        std::set<int> curNum;
        for (int idx = 0; idx < numStr.size(); idx++) {
            curNum.insert(numStr[idx] - '0');
        }

        std::vector<int> allCanRotate(10);
        std::vector<int> notAllRotateNoChange(10);
        std::vector<int>::iterator it;
        it = std::set_intersection(curNum.begin(), curNum.end(), canRotate.begin(), canRotate.end(), allCanRotate.begin());
        allCanRotate.resize(it - allCanRotate.begin());

        #ifdef DEBUG
        std::cout << "all can rotated: ";
        for (int num : allCanRotate) {
            std::cout << num << "\t";

        }
        std::cout << "\n";
        #endif

        if (allCanRotate.size() != curNum.size()) {
            return false;
        }

        it = std::set_difference(curNum.begin(), curNum.end(), rotateNoChage.begin(), rotateNoChage.end(),
                notAllRotateNoChange.begin());

        notAllRotateNoChange.resize(it - notAllRotateNoChange.begin());

        #ifdef DEBUG
        std::cout << "not all are rotated no change: ";
        for (int num : notAllRotateNoChange) {
            std::cout << num << "\t";

        }
        std::cout << "\n";
        #endif

        return !notAllRotateNoChange.empty();

#else
        bool canChangeRorate = false;
        for (int idx = 0; idx < numStr.size(); idx++) {
            switch (numStr[idx] - '0') {
                case 2:
                case 5:
                case 6:
                case 9:
                    canChangeRorate = true;
                    break;
                case 1:
                case 8:
                case 0:
                    break;
                default: return false; break;
            }
        }
        return canChangeRorate;
#endif
    }

};

class Solution {
public:
    int rotatedDigits(int N) {
        // just traverse all number from 1 to N;
        // maybe we can compute with compute;
        // the number whose length is smaller than N; lenght means the number of digits
        // 4 * (7 ** (len - 1)) the first chose from 2, 5, 6, 9. and then the left chose from 1, 8, 0, 2, 5, 6, 9
        // 2 * ((len - 1) * 4) * (7 ** (len - 2)) the first can be 1, 8, the left: first chose one pos set (2, 5, 6, 9)
        //                                        and the left chose from 1, 8, 0, 2, 5, 6, 9
        // same length
        // set each digit. the condition is too much.
        // reference to numbers_at_most_n_given_digit_set_902 and numbers_with_repeated_digits_1012
        //     and largest_multiple_of_three_1363 and k_th_smallest_in_lexicographical_order_440
        // plagiarizing idea from https://leetcode.com/problems/rotated-digits/discuss/116530/JavaPython-O(logN)-Time-O(1)-Space

        static std::unordered_set<int> canRotate{{1, 8, 0, 2, 5, 6, 9}};
        static std::set<int> rotateNoChage{{1, 8, 0}};

        int ans = 0;
        std::string NStr = std::to_string(N);
        int const NStrSize = NStr.size();
        std::set<int> digits;
        for (int idx = 0; idx < NStr.size(); idx++) {
            int digit = NStr[idx] - '0';
            bool isSub = isSubSet(rotateNoChage, digits);
            for (int d = 0; d < digit; d++) {
                // when d = 0, we will compute the smaller number whose length is less than NStrSize;
                if (canRotate.find(d) != canRotate.end()) {
                    ans += std::pow(7, NStrSize - 1 - idx);
                }
                if (isSub && rotateNoChage.find(d) != rotateNoChage.end()) {
                    ans -= std::pow(3, NStrSize - 1 - idx);
                }
            }
            digits.insert(digit);
            if (canRotate.find(digit) == canRotate.end()) {
                return ans;
            }
        }
        return ans + (isSubSet(rotateNoChage, digits) ? 0 : 1);
    }

private:
    bool isSubSet(std::set<int> const & left, std::set<int> const & subSet) {
        if (subSet.empty()) {
            return true;
        }
        if (left.empty()) {
            return false;
        }
        int const leftSize = left.size();
        int const subSetSize = subSet.size();
        std::vector<int> ans(std::min(leftSize, subSetSize));
        auto it = std::set_intersection(left.begin(), left.end(), subSet.begin(), subSet.end(), ans.begin());
        return subSet.size() == it - ans.begin();
    }
};

class Solution {
public:
    int rotatedDigits(int N) {
        // just traverse all number from 1 to N;
        // maybe we can compute with compute;
        // the number whose length is smaller than N; lenght means the number of digits
        // 4 * (7 ** (len - 1)) the first chose from 2, 5, 6, 9. and then the left chose from 1, 8, 0, 2, 5, 6, 9
        // 2 * ((len - 1) * 4) * (7 ** (len - 2)) the first can be 1, 8, the left: first chose one pos set (2, 5, 6, 9)
        //                                        and the left chose from 1, 8, 0, 2, 5, 6, 9
        // same length
        // set each digit. the condition is too much.
        // reference to numbers_at_most_n_given_digit_set_902 and numbers_with_repeated_digits_1012
        //     and largest_multiple_of_three_1363 and k_th_smallest_in_lexicographical_order_440
        // plagiarizing idea from https://leetcode.com/problems/rotated-digits/discuss/116530/JavaPython-O(logN)-Time-O(1)-Space

        static std::unordered_set<int> canRotate{{1, 8, 0, 2, 5, 6, 9}};
        static std::unordered_set<int> rotateNoChage{{1, 8, 0}};

        int ans = 0;
        std::string NStr = std::to_string(N);
        int const NStrSize = NStr.size();
        bool isSub = true;
        for (int idx = 0; idx < NStr.size(); idx++) {
            int digit = NStr[idx] - '0';
            for (int d = 0; d < digit; d++) {
                // when d = 0, we will compute the smaller number whose length is less than NStrSize;
                if (canRotate.find(d) != canRotate.end()) {
                    ans += std::pow(7, NStrSize - 1 - idx);
                }
                if (isSub && rotateNoChage.find(d) != rotateNoChage.end()) {
                    ans -= std::pow(3, NStrSize - 1 - idx);
                }
            }
            if (rotateNoChage.find(digit) == rotateNoChage.end()) {
                isSub = false;
            }
            if (canRotate.find(digit) == canRotate.end()) {
                return ans;
            }
        }
        return ans + (isSub ? 0 : 1);
    }
};

class Solution {
public:
    int rotatedDigits(int N) {
        // plagiarizing from https://leetcode.com/problems/rotated-digits/discuss/117975/Java-dp-solution-9ms
        int ans = 0;
        std::vector<int> dpMemo(N + 1, 0);
        for (int idx = 0; idx <= N; idx++) {
            if (10 > idx) {
                switch(idx) {
                    case 0:
                    case 1:
                    case 8:
                        dpMemo[idx] = 1;
                        break;
                    case 2:
                    case 5:
                    case 6:
                    case 9:
                        dpMemo[idx] = 2;
                        ans++;
                    default:
                        /*it means 3, 4, 7 can't be rotatoed*/
                        break;
                }
            } else {
                int high = dpMemo[idx / 10];
                int low = dpMemo[idx % 10];
                if (1 == high && 1 == low) {
                    // after rotated, it is no change
                    dpMemo[idx] = 1;
                } else if (1 <= high && 1 <= low) {
                    // at least one of high or low is 2
                    dpMemo[idx] = 2;
                    ans++;
                }
            }
        }
        return ans;
    }

};
