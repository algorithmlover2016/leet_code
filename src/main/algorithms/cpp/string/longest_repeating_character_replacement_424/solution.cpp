#include "../../head.h"


class Solution {
public:
    int characterReplacement(std::string const & s, int k) {
        std::vector<int> cnt(UPPER_LETTERS_NUM, 0);
        int ans = 0;
        for ( int i = 0, j = 0; j < s.size(); j++) {
            cnt[s[j] - UPPER_LETTER_OFFSET]++;
            while (j - i + 1 - *std::max_element(cnt.begin(), cnt.end()) > k) {
                cnt[s[i++] - UPPER_LETTER_OFFSET]--;
            }
            ans = std::max(ans, j - i + 1);
        }
        return ans;
    }
private:
    static int const UPPER_LETTERS_NUM = 26;
    static char const UPPER_LETTER_OFFSET = 'A';
};

class Solution {
public:
    int characterReplacement(std::string const & s, int k) {
        std::vector<int> cnt(UPPER_LETTERS_NUM, 0);
        int ans = 0;
        int i = 0, j = 0;
        for (; j < s.size(); j++) {
            cnt[s[j] - UPPER_LETTER_OFFSET]++;
            // the j is included
            if (j - i + 1 - *std::max_element(cnt.begin(), cnt.end()) > k) {
                cnt[s[i++] - UPPER_LETTER_OFFSET]--;
            }
        }
        // the j is s.size(), which is not included
        return j - i;
    }
private:
    static int const UPPER_LETTERS_NUM = 26;
    static char const UPPER_LETTER_OFFSET = 'A';
};
