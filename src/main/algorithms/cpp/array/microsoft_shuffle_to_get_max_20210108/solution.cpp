#include "../../head.h"

#define TEST
#define TEST_OUTPUT_TO_SCREEN
class Solution {
public:
    std::vector<int> shuffle(std::vector<int> const & A,
                             std::vector<int> const & B) {
        int const ASize = A.size();
        int const BSize = B.size();
        if (JUST_RETURN >= ASize || ASize != BSize) {
            return A;
        }
        std::multiset<int> sortedA;
        for (auto const num : A) {
            sortedA.insert(num);
        }
        std::vector<int> ans(ASize, 0);
        for (int idx = 0; idx < BSize; idx++) {
            auto it = sortedA.upper_bound(B[idx]);
            if (it == sortedA.end()) {
                it = sortedA.begin();
            }
            ans[idx] =*it;
            sortedA.erase(it);
        }
        return ans;
    }
private:
    static int const JUST_RETURN = 1;

};

#ifdef TEST
int main() {
    Solution obj;
    std::vector<int> A{{2,  8,   4,  6}};
    std::vector<int> B{{7,  9,  11 , 5}};
    std::vector<int> ans = obj.shuffle(A, B);
#ifdef TEST_OUTPUT_TO_SCREEN
    std::cout << "\nTEST OUTPUT\n";
    for (auto num : ans) {
        std::cout << num << "\t";
    }
    std::cout << "\n";
#endif


}
#endif
