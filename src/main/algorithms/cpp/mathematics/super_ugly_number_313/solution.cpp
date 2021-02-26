#include "../../head.h"


// #define DEBUG
class Solution {
    protected:
    class Compare {
    public:
        Compare(bool reverse_ = false) : reverse(reverse_) {
        }
        bool operator()(int const left, int const right) {
            if (left <= right) {
                return !reverse;
            } else {
                return reverse;
            }
        }
    private:
        bool reverse = false;
    };
public:
    int nthSuperUglyNumber(int n, std::vector<int> const & primes) {
        typedef std::priority_queue<long, std::vector<long>, Compare> MaxHeap;
        MaxHeap minHeap(Compare(true));
        std::unordered_set<long> seen;
        
        minHeap.emplace(1);
        seen.insert(1);
        
        while (1 < n--) {
            long long cur = minHeap.top(); minHeap.pop();
            #ifdef DEBUG
            std::cout << cur << '\t';
            #endif
            for (int const prime : primes) {
                long long next = cur * prime;
                if (INT_MAX < next) {
                    continue;
                }
                if (seen.insert(next).second) {
                    minHeap.emplace(next);
                }
            }
        }
        return minHeap.top();
    }
};
