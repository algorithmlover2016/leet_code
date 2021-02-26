#include "../../head.h"


#define TEST_MAIN
class Solution {
public:
    int lengthOfLongestSubstringKDistinct(std::string const s, int const k) {
        std::unordered_map<char, int> cnt;
        int ans = 0;
        int i = 0, j = 0;
        for (; j < s.size(); j++) {
            cnt[s[j]]++;
            // the j is included
            if (cnt.size() > k) {
                if(0 == --cnt[s[i]]) {
                    cnt.erase(s[i]);
                }
                i++;
            }
        }
        // the j is s.size(), which is not included
        return j - i;

    }
};

#ifdef TEST_MAIN
#define PRINT_TO_SCREEN
int main() {
    Solution obj;
    std::string s("eceba");
    assert(3 == obj.lengthOfLongestSubstringKDistinct(s, 2));

    assert(2 == obj.lengthOfLongestSubstringKDistinct("aa", 1));

#ifdef PRINT_TO_SCREEN
    std::cout << "Test Successfully" << std::endl;
#endif

    return 0;
}
#endif
