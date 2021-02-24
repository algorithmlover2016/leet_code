#include "../../head.h"


class SolutionTLE {
public:
    int subarraysWithKDistinct(std::vector<int> const & A, int K) {
        int ASize = A.size();
        if (ASize < K) {
            return 0;
        }
        int res = 0;
        for (int index = 0; index <= ASize - K; index++) {
            std::set<int> visited;
            for (int start = index; start < ASize; start++) {
                visited.emplace(A[start]);
                int visitedSize = visited.size();
                if (visitedSize == K) {
                    res++;
                } else if (visitedSize > K) {
                    break;
                }
            }
        }
        return res;

    }
};

class Solution {
public:
    /*
       This problem will be a very typical sliding window,
       if it asks the number of subarrays with at most K distinct elements.
       Just need one more step to reach the folloing equation:
       exactly(K) = atMost(K) - atMost(K-1)
     */
    int subarraysWithKDistinct(std::vector<int> const & A, int K) {
        // plagiarizing from https://leetcode.com/problems/subarrays-with-k-different-integers/discuss/523136/JavaC%2B%2BPython-Sliding-Window
        return atMost(A, K) - atMost(A, K - 1) ;
    }
    int atMost(std::vector<int> const & A, int K) {
        int res = 0, start = 0;
        std::unordered_map<int, int> visited;
        for (int index = 0; index < A.size(); index++) {
            if (0 == visited[A[index]]++) {
                K--; // insert into a new element
            }
            while (K < 0) {
                if (0 == --visited[A[start++]]) {
                    K++;
                }
                // start++; // remove a element from the start
            }
            res += index - start + 1; // the 1 means its self;
        }
        return res;
    }

};

class Solution {
public:
    int subarraysWithKDistinct(std::vector<int> const & A, int K) {
        // plagiarizing from https://leetcode.com/problems/subarrays-with-k-different-integers/discuss/235235/C%2B%2BJava-with-picture-prefixed-sliding-window
        std::unordered_map<int, int> visited;
        int res = 0;
        int cnt = 0, prefix = 0, start = 0;
        for (int index = 0; index < A.size(); index++) {
            // std::cout << "\nele: " << A[index] << "\t";
            if (0 == visited[A[index]]++) {
                // std::cout << "add: " << A[index] << "\t";
                cnt++;
            }
            if (cnt > K) {
                // std::cout << "remove: " << A[start] << "\t";
                visited[A[start++]]--;
                cnt--;
                prefix = 0;
            }
            while (visited[A[start]] > 1) {
                // to make sure there is only one element A[start] in visited,
                // so that when need remove it, just need A[start]--, which means removing an distinct element
                // std::cout << "make start distinct: " << visited[A[start]] << "\t";
                visited[A[start++]]--;
                prefix++;
            }
            if (cnt == K) {
                // std::cout << "loop ADD: " << prefix + 1 << "\n";
                res += prefix + 1;
            }
        }
        return res;
    }
};
