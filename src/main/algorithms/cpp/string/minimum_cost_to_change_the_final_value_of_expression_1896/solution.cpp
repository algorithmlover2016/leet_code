#include "../../head.h"


// #define DEBUG
#define USE_LAMDA
class Solution {
public:
    int minOperationsToFlip(std::string const & expression) {
        // plagiarizing from https://leetcode.com/problems/minimum-cost-to-change-the-final-value-of-expression/discuss/1267304/Python-Recursion-dfs-solution-explained
        std::unordered_map<int, int> closeToOpenMatchIndex;
        findPairMatchIndex(expression, closeToOpenMatchIndex);
        #ifdef DEBUG
        std::cout << "get pair match\n";
        #endif
        auto [val, change] = dfs(expression, closeToOpenMatchIndex, 0, expression.size() - 1);
        return change;
    }
private:
    void findPairMatchIndex(std::string const & str, std::unordered_map<int, int> & closeToOpenMatchIndex) {
        std::vector<int> openParentheses;

        for (int idx = 0; idx < str.size(); idx++) {
            char cur = str[idx];
            if (OpenParenthese == cur) {
                openParentheses.emplace_back(idx);
            } else if (CloseParenthese == cur) {
                int openIdx = openParentheses.back();
                openParentheses.pop_back();
                closeToOpenMatchIndex[idx] = openIdx;
                #ifdef DEBUG
                std::cout << "pair :(" << openIdx << "," << idx << ")\n";
                #endif
            }
        }
    }
    std::tuple<int, int> dfs(std::string const & str, std::unordered_map<int, int> const & closeToOpenMatchIndex, int begin, int end) {
        if (begin == end) {
            return std::make_tuple(static_cast<int>(str[begin] - OffsetChar), 1);
        }
        int matchEndIdx = (closeToOpenMatchIndex.find(end) != closeToOpenMatchIndex.end() ? closeToOpenMatchIndex.at(end) : end);
        if (matchEndIdx == begin) {
            // encounter an () pair
            return dfs(str, closeToOpenMatchIndex, begin + 1, end - 1);
        }
        auto [valLeft, changeLeft] = dfs(str, closeToOpenMatchIndex, begin, matchEndIdx - 2);
        auto [valRight, changeRight] = dfs(str, closeToOpenMatchIndex, matchEndIdx, end);
        char curOp = str[matchEndIdx - 1];
        #ifdef DEBUG
        std::cout << "valLeft, changeLeft: " << valLeft << ", " << changeLeft << ";"
            << "valRight, changeRight: " << valRight << ", " << changeRight << "\n";
        #endif

        int change = ((valLeft + valRight == 1) ? 1 : (std::min(changeLeft, changeRight) + (valLeft ^ (curOp == AndOpChar))));

        #ifdef USE_LAMDA
        auto andOp = [](int x, int y) -> bool {
            return static_cast<bool>(x && y);
        };
        
        auto orOp = [](int x, int y) -> bool {
            return static_cast<bool>(x || y);
        };
        #endif


        if (AndOpChar == curOp) {
            #ifdef USE_LAMDA
                return std::make_tuple(andOp(valLeft, valRight), change);
            #else
                return std::make_tuple((valLeft && valRight), change);
            #endif
        } else {
            #ifdef USE_LAMDA
                return std::make_tuple(orOp(valLeft, valRight), change);
            #else
                return std::make_tuple((valLeft || valRight), change);
            #endif
        }
    }

private:
    char const OpenParenthese = '(';
    char const CloseParenthese = ')';
    char const AndOpChar = '&';
    char const OrOpChar = '|';
    char const OffsetChar = '0';
};