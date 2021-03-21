#include "../../head.h"


class Solution {
public:
    int atMostNGivenDigitSet(std::vector<std::string> const & digits, int n) {
        std::string nstr = std::to_string(n);
        int nn = nstr.size(), nd = digits.size(), res = 0;
        
        for (int i = 1; i < nn; ++i)
            res += std::pow(nd, i);
        
        for (int i = 0; i < nn; ++i) {
            bool same_num = false;
            for (std::string & digit : digits) {
                // the digit start from smaller than nstr[i], equal to nstr[i], and then bigger than nstr[i].
                // if there is no digit = nstr[i], which means we have compute all the smaller elements, and no need go on
                if (digit[0] < nstr[i]) {
                    res += std::pow(nd, nn - i - 1);
                } else if (digit[0] == nstr[i]) {
                    // 
                    same_num = true;
                } else {
                    break;
                }
            }
            
            if (!same_num)
                return res;
        }
        return res + 1;
    }
};
