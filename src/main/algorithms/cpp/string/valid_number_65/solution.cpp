#include "../../head.h"

class Solution {
public:
    bool isNumber(std::string const & s) {
        size_t sSize = s.size();
        if (sSize == 0) {
            return false;
        }
        size_t index = 0;
        size_t beginFlag = 0;
        bool dotFlag = false;
        while((index < sSize) && (' ' == s[index])) {
            index++;
        }
        if (index == sSize) {
            return false;
        }
        if ((index < sSize) && (('-' == s[index]) || ('+' == s[index]))) {
            index++;
        }
        beginFlag = index;
        while((index < sSize) && isdigit(s[index])) {
            index++;
        }
        if ((index < sSize) && ('.' == s[index])) {
            index++;
            while((index < sSize) && isdigit(s[index])) {
                index++;
            }
            if (beginFlag + 1 == index) {
                return false;
            }
            dotFlag = true;
        }
        if ((index < sSize) && ('e' == s[index])) {
            // there must be number before e; if there is no dot before e, number should not be 0-prefix unless there is only a 0 before e
            if ((beginFlag == index) || (('0' == s[beginFlag]) && (!dotFlag) && (beginFlag + 1 != index))) {
            // if (beginFlag == index) {
                return false;
            }
            index++;
            if ((index < sSize) && (('-' == s[index]) || ('+' == s[index]))) {
                index++;
            }
            beginFlag = index;
            while((index < sSize) && isdigit(s[index])) {
                index++;
            }
            // if there is no number after e[-+], false
            if (beginFlag == index) {
                return false;
            }
        }
        while((index < sSize) && (' ' == s[index])) {
            index++;
        }
        return index == sSize;
    }
};
