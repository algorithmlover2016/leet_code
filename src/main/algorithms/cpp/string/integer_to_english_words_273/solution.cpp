#include "../../head.h"


class Solution {
public:
    std::string numberToWords(int num) {
        if (0 == num) {
            return "Zero";
        }
        int interval = 0;
        std::string ans;
        while (0 < num) {
            int last = num % THOUSAND;
            std::string curAns;
            int hundredBit = last / HUNDRED;
            if (0 < hundredBit) {
                curAns += NUMBER_STR[hundredBit] + " Hundred";
            }
            int leftBit = last % HUNDRED;
            if (0 < leftBit) {
                if (20 > leftBit) {
                    curAns += (curAns.empty() ? "" : " ") + NUMBER_STR[leftBit];
                } else {
                    int tenBit = leftBit / TEN;
                    curAns += (curAns.empty() ? "" : " ") + TY_STR[tenBit];
                    int bit = leftBit % TEN;
                    if (0 < bit) {
                        curAns += (curAns.empty() ? "" : " ") + NUMBER_STR[bit];
                    }
                }
            }

            if (0 != interval && !curAns.empty()) {
                curAns += " " + INTERVAL[interval] + " ";
            }
            num /= THOUSAND;
            interval++;
            ans = curAns + ans;
        }
        while (!ans.empty() && ' ' == ans.back()) {
            ans.pop_back();
        }
        return ans;
    }

private:
    static std::vector<std::string> const INTERVAL;
    static std::vector<std::string> const NUMBER_STR;
    static std::vector<std::string> const TY_STR;
    static int const THOUSAND = 1000;
    static int const HUNDRED = 100;
    static int const TEN = 10;
};
std::vector<std::string> const Solution::INTERVAL{{"", "Thousand", "Million", "Billion"}};
std::vector<std::string> const Solution::NUMBER_STR{{"",
    "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten",
    "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen",
}};

std::vector<std::string> const Solution::TY_STR{{
    "", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"
}};
