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

#define EACH_PRIME_COMPUTE_MIN
// #define DEBUG
class Solution {
public:
    int nthSuperUglyNumber(int n, std::vector<int> const & primes) {
        if (n == 1) {
            return 1;
        }

        std::vector<int> dp(n + 1, INT_MAX);
        dp[1] = 1;

        int m = primes.size();
        // record the primes[i] using times;
        std::vector<int> indexj(m, 1);
        // record the next used element
        std::vector<int> nexts(m, 1);

        for (int i=2; i<=n; i++) {
            for (int p=0; p<m; p++) {
                #ifdef DEBUG
                std::cout << p << ",\t" << dp[i - 1] << ",\t" << indexj[p] << ",\t" << nexts[p] << "\t";
                #endif
                if (nexts[p] == dp[i-1]) {
                    // nexts[p] need update, it should become bigger.
                    // all the elements come from nexts
                    // the last element that use primes[p] is indexj[p]
                    // or the primes[p] create indexj[p] elements, and it need create a new one

                    nexts[p] = dp[indexj[p]] * primes[p];
                    indexj[p]++;
                }
                #ifdef DEBUG
                std::cout << "\n";
                #endif
#ifdef EACH_PRIME_COMPUTE_MIN
                dp[i] = std::min(dp[i], nexts[p]);
#endif
            }

#ifndef EACH_PRIME_COMPUTE_MIN
            dp[i] = *std::min_element(nexts.begin(), nexts.end());
#endif
        }

        return dp[n];
    }
};
