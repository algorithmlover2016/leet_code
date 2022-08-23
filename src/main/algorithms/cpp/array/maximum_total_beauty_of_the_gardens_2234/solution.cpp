#include "../../head.h"


// #define DEBUG
// #define INNER_LOOP
class Solution {
public:
    long long maximumBeauty(std::vector<int> flowers, long long newFlowers, int target, int full, int partial) {
        // plagiarizing from https://leetcode.com/problems/maximum-total-beauty-of-the-gardens/discuss/1934318/Two-Pointers

        // sort the vector of flowers with non-increasing order, from largest to smallest.
        std::sort(std::begin(flowers), std::end(flowers), std::greater<int>());
        long long p1 = 0, flowersSize = flowers.size();
        while (p1 < flowersSize) {
            if (target - flowers[p1] > newFlowers) {
                // we can not get enough flowers to plant in any garden.
                break;
            }
            newFlowers -= std::max(0, (target - flowers[p1++]));
        }
        #ifdef DEBUG
        for (int flower : flowers) {
            std::cout << flower << ", ";
        }
        std::cout << "\np1: " << p1 << ", newFlowers: " << newFlowers << "\n";
        #endif
        // after the upper loop, we know there are at most idx completed graden.
        if (p1 == flowersSize) {
            // all the graden can be planted as completed graden
            return (flowersSize - 1) * full  + std::max((long long) (full) /* all the graden are completed*/,
                                                        (flowers.back() < target) ? ((long long)(target - 1) * partial /*we can set one graden with uncompleted garden*/) :
                                                                                     (long long)(full));
        }

        long long ans = 0;
        // Not all the graden can be planted to complete
        long long minF = 0, p2 = 0, plantedNum = 0;
        for (minF = flowers.back(), p2 = flowersSize - 1; minF < target;) {
            while (p2 >= p1 && flowers[p2] <= minF) {
                plantedNum += flowers[p2--];
            }
            int needFlowers = (flowersSize - p2 - 1) * minF - plantedNum;
            #ifdef DEBUG
            std::cout << "p2: " << p2 << ", plantedNum: " << plantedNum << ", needPlanted: " << needFlowers << ", minF: " << minF << "\n";
            #endif
            
            #ifdef INNER_LOOP
            while (needFlowers > newFlowers && 0 < p1) {
                newFlowers += std::max(0, target - flowers[--p1]);
                #ifdef DEBUG
                std::cout << "p1: " << p1 << ", newFlowers: " << newFlowers << "\n";
                #endif
            }
            // we can not use the judgement that 0 == p1, because if do like that, we may ignore a case that needFloweers <= newFlowers and 0 == p1
            // which means we will not plant a completed garden. but we can find a maximum with minF * partial
            if (needFlowers <= newFlowers) {
                ans = std::max(ans, p1 * full + minF * partial);
                #ifdef DEBUG
                std::cout << "ans: " << ans << '\n';
                #endif
                minF++;
            } else {
                break;
            }
            
            #else
            
            if (needFlowers > newFlowers) {
                if (0 <  p1) {
                    newFlowers += std::max(0, target - flowers[--p1]);
                } else {
                    break;
                }
                #ifdef DEBUG
                std::cout << "p1: " << p1 << ", newFlowers: " << newFlowers << "\n";
                #endif
            } else {
                ans = std::max(ans, p1 * full + minF * partial);
                #ifdef DEBUG
                std::cout << "ans: " << ans << '\n';
                #endif
                minF++;
            }
            #endif
                
        }
        return ans;
    }
};