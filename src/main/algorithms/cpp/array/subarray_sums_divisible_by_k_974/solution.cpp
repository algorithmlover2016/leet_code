#include "../../head.h"


// #define DEBUG
class Solution {
public:
    int subarraysDivByK(std::vector<int> const & A, int K) {
        // plagiarizing idea from https://youtu.be/p2UDld3rM_Q
        std::unordered_map<int, int> redundantMap;
        redundantMap[0] = 1;
        
        int preSum = 0, ans = 0;
        for (int const num : A) {
            preSum += num;
            int redundant = preSum % K;
            if (JUST_ZERO > redundant) {
                redundant += K;
            }
            
            #ifdef DEBUG
            std::cout << "\n" << redundant << "\t";
            #endif
            
            if (redundantMap.find(redundant) != redundantMap.end()) {
                #ifdef DEBUG
                std::cout << redundantMap[redundant] << "\t";
                #endif
                ans += redundantMap[redundant]++;
            } else {
                redundantMap[redundant] = 1;
            }
        }
        return ans;

    }
private:
    static int const JUST_ZERO = 0;
};
