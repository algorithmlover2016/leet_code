#include "../../head.h"

class SolutionCheckNumber {
public:
    bool isNumber(string s) {
        int begin = 0;
        int end = s.size();
        while (begin < end && s[begin] == ' ') begin++;
        while (begin < end && s[end - 1] == ' ') end--;
        return isTrimmedNumber(s.substr(begin, end - begin));
    }
    
    bool isTrimmedNumber(string s) {
        if (s.empty()) return false;
        int e = s.find('e');
        if (e == string::npos) {
            return isDecimalNum(s);   
        } else {
            return isDecimalNum(s.substr(0, e)) &&
                isIntegerNum(s.substr(e + 1), true, false);
        }
    }
    
    bool isDecimalNum(string s) {
        if (s.empty()) return false;
        int sep = s.find('.');
        if (sep == string::npos) {
            return isIntegerNum(s, true, false);
        } else {
            string l = s.substr(0, sep);
            string r = s.substr(sep + 1);
                        
            return (isIntegerNum(l, true, true) && // [+]1.[0]
                    isIntegerNum(r, false, false))
                || (isIntegerNum(l, true, false) && // [0].1
                    isIntegerNum(r, false, true));
                
        }
    }
    
    bool isIntegerNum(string s, bool is_signed, bool can_be_empty) {
        if (is_signed && !s.empty() && (s[0] == '-' || s[0] == '+')) {
            s = s.substr(1);
//            can_be_empty = false;
        }
        
        if (s.empty()) return can_be_empty;
        for (char c : s) if (!isdigit(c)) return false;
        return true;
    }
};

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
