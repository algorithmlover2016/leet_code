#include "../../head.h"


// #define DEBUG
// #define EASY_UNDERSTANDING
class Solution {
public:
    std::string smallestSubsequence(std::string const & s, int k, char letter, int repetition) {
        // plagiarizing from https://www.youtube.com/watch?v=IUbWew2HH0s
        std::string ans;
        if (k < repetition) {
            return ans;
        }
        int cnts = std::count(s.begin(), s.end(), letter);
        if (cnts < repetition) {
            return ans;
        }
        int sSize = s.size();
        if (sSize < k) {
            return ans;
        }
        for (int idx = 0; idx < sSize; idx++) {
            while (!ans.empty() && (
                #ifndef EASY_UNDERSTANDING
                ((sSize - idx > k - ans.size()) && (ans.back() > s[idx]) && (ans.back() != letter || cnts > repetition)) ||
                (repetition > k - int(ans.size()))
                #else
                ((sSize - idx > k - ans.size() /*there are left enough characters*/) &&
                 (ans.back() != letter || cnts > repetition /*no pop back letter target, or check out there are left enough letter characters*/) &&
                 (ans.back() > s[idx] || (repetition > k - int(ans.size())) /*obey lexicographical order unless lack of letter characters */))
                #endif
            )) {
                if (ans.back() == letter) {
                    repetition++;
                }
                ans.pop_back();
                #ifdef DEBUG
                std::cout << "ans: " << ans << "\n";
                #endif
            }
            if (ans.size() < k) {
                ans.append(1, s[idx]);
                if (s[idx] == letter) {
                    repetition--;
                }
            }
            if (letter == s[idx]) {
                cnts--;
            }
            #ifdef DEBUG
            std::cout << "cur ans: " << ans << "\n";
            #endif
        }
        return ans;
    }
};

#define DEBUG
class Solution {
public:
    std::string smallestSubsequence(std::string const & s, int k, char letter, int repetition) {
        int sz = std::size(s), lpos = sz, ql = 0, qr = -1, sp = 0;
        #ifdef DEBUG
        std::cout << sz << ", " << lpos << ", " << s.size() << ", " << s[sz] << "a\n";
        #endif
        for (int r = repetition; r; --lpos) {
            if (s[lpos] == letter) {
                --r;
            }
        }
        ++lpos;

        std::string res;
        res.reserve(k);
        while(k > repetition) {
            while (sp <= lpos && sp <= sz-k) {
                while (qr >= ql && s[sp] < q[qr]) {
                    --qr;
                }
                q[++qr] = s[sp++];
            }
            res.push_back(q[ql]); --k;
            if (q[ql++] == letter && repetition) {
                if (--repetition) {
                    while (s[++lpos] != letter) ;
                } else {
                    lpos = sz-1;
                }
            }
        }
        res.append(k, letter);
        return res;
    }
private:
    char q[50000];
};
