#include "../../head.h"

class SolutionLamda {
public:
    std::string toGoatLatin(std::string const & S) {
        function<bool(char)> isVowel = [](char i) -> bool {
            switch(tolower(i)) {
                case 'a':
                case 'e':
                case 'i':
                case 'o':
                case 'u':
                    return true;
            }
            return false;
        };
        std::string ans = "", cur = "", suff = "ma";
        for(int i = 0; i <= S.size(); ++i) {
            if (i == S.size() || S[i] == ' ') {
                if (cur.size() == 0) {
                    continue;
                }
                suff += "a";
                if (isVowel(cur[0])) {
                    cur += suff;
                } else {
                    cur += (cur[0] + suff);
                    cur.erase(cur.begin());
                }
                // the first word, there is no need to add " " at begining
                if (suff.size() > 3) {
                    ans+=" ";
                }
                ans += cur;
                cur = "";
            } else {
                cur+=S[i];
            }
        }
        return ans;
    }
};

class Solution {
public:
    std::string toGoatLatinLowUper(std::string const & S) {
        if (S.length() == 0) {
            return "";
        }
        std::string word{""}, letter{""}, aStr{"a"}, resStr{""};
        char vowelArray[] = {'a', 'A', 'e', 'E', 'i', 'I', 'o', 'O', 'u', 'U'};
        std::set<char> vowel(vowelArray, vowelArray + 10);
        if (vowel.find(S[0]) != vowel.end()) {
            word = S[0];
        } else {
            letter = S[0];
        }
        for (size_t index = 1; index < S.size(); index++) {
            if (' ' == S[index]) {
                resStr += word + letter + "ma" + aStr + " ";
                word = "";
                letter = "";
                aStr += 'a';
                if ( ++index < S.size()) {
                    if (vowel.find(S[index]) != vowel.end()) {
                        word = S[index];
                    } else {
                        letter = S[index];
                    }
                }
            } else {
                word += S[index];
            }
        }
        resStr += word + letter + "ma" + aStr;
        return resStr;
    }

    std::string toGoatLatin(std::string const & S) {
        if (S.length() == 0) {
            return "";
        }
        std::string word{""}, letter{""}, aStr{"a"}, resStr{""};
        char vowelArray[] = {'a', 'e', 'i', 'o', 'u'};
        std::set<char> vowel(vowelArray, vowelArray + 5);
        if (vowel.find(std::tolower(S[0])) != vowel.end()) {
            word = S[0];
        } else {
            letter = S[0];
        }
        for (size_t index = 1; index < S.size(); index++) {
            if (' ' == S[index]) {
                resStr += word + letter + "ma" + aStr + " ";
                word = "";
                letter = "";
                aStr += 'a';
                if ( ++index < S.size()) {
                    if (vowel.find(tolower(S[index])) != vowel.end()) {
                        word = S[index];
                    } else {
                        letter = S[index];
                    }
                }
            } else {
                word += S[index];
            }
        }
        resStr += word + letter + "ma" + aStr;
        return resStr;
    }
};
int main() {
    std::string input{"G UxjR"};
    Solution a;
    std::cout << "result : " << a.toGoatLatin(input) << std::endl;
    std::cout << "result : " << a.toGoatLatinLowUper(input) << std::endl;
    return 0;
}
