#include "../../head.h"


// #define DEBUG
class Solution {
public:
    int largestVariance(std::string const & s) {
        // plagiarizing from https://leetcode.com/problems/substring-with-largest-variance/solutions/2039178/weird-kadane/
        if (s.size() < 2) {
            return 0;
        }
        std::unordered_set<char> letters(s.begin(), s.end());

        int ans = 0;
        for (auto it = letters.cbegin(); it != letters.cend(); it++) {
            for (auto another = letters.cbegin(); another != letters.cend(); another++) {
                if ((*it) == (*another)) {
                    continue;
                }
                #ifdef DEBUG
                std::cout << "count " << *it << ", " << *another << "\n";
                #endif
                int cnt = 0;
                bool encounter_another = false;
                bool first_encounter = false;
                for (const char e : s) {
                    if ((*it) == e) {
                        #ifdef DEBUG
                        std::cout << "encounter an inc letter\n";
                        #endif
                        cnt++;
                    } else if ((*another) == e) {
                        encounter_another = true;
                        if (first_encounter && cnt >= 0) {
                            #ifdef DEBUG
                            std::cout << "change the fist dec letter\n";
                            #endif
                            first_encounter = false;
                        } else {
                            // if (cnt-- <= 0)
                            if (--cnt < 0)
                            {
                                #ifdef DEBUG
                                std::cout << "need reset\n";
                                #endif
                                first_encounter = true;
                                cnt = -1;
                            }
                        }
                    }
                    #ifdef DEBUG
                    std::cout << "cur var: " << cnt << "\n";
                    #endif
                    ans = std::max(ans, (encounter_another ? cnt : 0));
                }
            }
        }
        return ans;
    }
};