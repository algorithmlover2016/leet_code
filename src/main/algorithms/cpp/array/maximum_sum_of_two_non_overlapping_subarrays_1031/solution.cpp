#include "../../head.h"


// #define DEBUG
class SolutionMyIdea {
public:
    int maxSumTwoNoOverlap(std::vector<int> const & A, int L, int M) {
        // dp problem
        int const ASize = A.size();
        std::vector<int> preSum(ASize + 1, 0);
        for (int idx = 0; idx < ASize; idx++) {
            preSum[idx + 1] = preSum[idx] + A[idx];
        }
        std::vector<int> maxSumInLToIdx(ASize, 0);
        std::vector<int> maxSumInMToIdx(ASize, 0);
        std::vector<int> maxSumInLFromIdx(ASize, 0);
        std::vector<int> maxSumInMFromIdx(ASize, 0);
        int ans = 0;
        maxSumInLFromIdx[ASize - L] = preSum[ASize] - preSum[ASize - L];
        #ifdef DEBUG
        std::cout << "LFROMIDX\n";
        #endif
        for (int idx = ASize - 1 - L; idx > EXCLUDE_MOST_LEFT_IDX; idx--) {
            maxSumInLFromIdx[idx] = std::max(maxSumInLFromIdx[idx + 1], preSum[idx + L] - preSum[idx]);
            #ifdef DEBUG
            std::cout << idx << "," << maxSumInLFromIdx[idx] << "\t";
            #endif

        }
        #ifdef DEBUG
        std::cout << "\nMFROMIDX\n";
        #endif
        maxSumInMFromIdx[ASize - M] = preSum[ASize] - preSum[ASize - M];
        for (int idx = ASize -1 - M; idx > EXCLUDE_MOST_LEFT_IDX; idx--) {
            maxSumInMFromIdx[idx] = std::max(maxSumInMFromIdx[idx + 1], preSum[idx + M] - preSum[idx]);
            #ifdef DEBUG
            std::cout << idx << "," << maxSumInMFromIdx[idx] << "\t";
            #endif
        }
        #ifdef DEBUG
        std::cout << "\nLTOIDX\n";
        #endif
        maxSumInLToIdx[L - 1] = preSum[L - 1];
        for (int idx = L; idx < ASize; idx++) {
            maxSumInLToIdx[idx] = std::max(maxSumInLToIdx[idx - 1], preSum[idx] - preSum[idx - L]);
            #ifdef DEBUG
            std::cout << idx << "," << maxSumInLToIdx[idx] << "\t";
            #endif
        }
        #ifdef DEBUG
        std::cout << "\nMTOIDX\n";
        #endif
        maxSumInMToIdx[M - 1] = preSum[M - 1];
        for (int idx = M; idx < ASize; idx++) {
            maxSumInMToIdx[idx] = std::max(maxSumInMToIdx[idx - 1], preSum[idx] - preSum[idx - M]);
            #ifdef DEBUG
            std::cout << idx << "," << maxSumInMToIdx[idx] << "\t";
            #endif
        }
        #ifdef DEBUG
        std::cout << "\nANS\n";
        #endif
        for (int idx = L - 1; idx <= ASize - M; idx++) {
            ans = std::max(ans, maxSumInLToIdx[idx] + maxSumInMFromIdx[idx]);
            // ans = std::max(ans, maxSumInLToIdx[idx + 1] + maxSumInMFromIdx[idx + 1]);
            #ifdef DEBUG
            std::cout << idx << ", " << ans << "\t";
            #endif
        }
        #ifdef DEBUG
        std::cout << "\nANS\n";
        #endif

        for (int idx = M - 1; idx <= ASize - L; idx++) {
            ans = std::max(ans, maxSumInMToIdx[idx] + maxSumInLFromIdx[idx]);
            // ans = std::max(ans, maxSumInMToIdx[idx + 1] + maxSumInLFromIdx[idx + 1]);
            #ifdef DEBUG
            std::cout << idx << ", " << ans << "\t";
            #endif
        }

        return ans;
    }
private:
    static int const EXCLUDE_MOST_LEFT_IDX = -1;
};

class Solution {
public:
    int findMax(std::vector<int> const & A, int L, int M) {
        int result = 0;
        std::vector<int> L_max(A.size(),0), M_max(A.size(),0);
        int l_sum = A[0];
        L_max[0] = A[0];
        for(int i = 1;i < L_max.size(); i++) {
            l_sum += (A[i] - (i >= L ? A[i-L]:0));
            L_max[i] = std::max(L_max[i-1], l_sum);
        }

        int r_sum = 0;
        M_max[A.size() - 1] = 0;
        for(int j = A.size() - 2; j >= 0; j--) {
            r_sum += (A[j + 1] - (j + M + 1 < A.size() ? A[j + M + 1]:0));
            // exuclude A[j];
            M_max[j] = std::max(M_max[j + 1], r_sum);
        }

        for (int i=0; i < A.size(); i++) {
            result = std::max(result, L_max[i] + M_max[i]);
        }
        return result;
    }

    int maxSumTwoNoOverlap(std::vector<int> const & A, int L, int M) {
        return std::max(findMax(A, L, M), findMax(A, M, L));
    }
};
