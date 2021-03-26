#include "../../head.h"


class Solution {
public:
    std::vector<int> advantageCount(std::vector<int> & A, std::vector<int> const & B) {
        // plagiarizing idea from https://youtu.be/fY310tCXS_E
        if (A.empty() || B.empty()) {
            return {};
        }
        int const ASize = A.size();
        int const BSize = B.size();
        std::vector<int> BIdx(BSize, 0);
        std::iota(BIdx.begin(), BIdx.end(), 0);
        std::sort(A.begin(), A.end());
        std::sort(BIdx.begin(), BIdx.end(), [&] (int left, int right) {
                return B[left] <= B[right];
                });
        std::vector<int> ans(ASize);
        for (int left = 0, right = ASize - 1, idxB = BSize - 1; left <= right; idxB--) {
            if (A[right] > B[BIdx[idxB]]) {
                ans[BIdx[idxB]] = A[right--];
            } else {
                ans[BIdx[idxB]] = A[left++];
            }
        }
        return ans;
    }
};

class Solution {
public:
    std::vector<int> advantageCount(std::vector<int> & A, std::vector<int> const & B) {
        int n = A.size();
        if (n < 2) {
            return A;
        }

        std::sort(A.begin(), A.end());
        std::vector<std::pair<int,int>> C;
        for(int i=0; i<n; ++i) {
            C.push_back(std::make_pair(B[i], i));
        }
        std::sort(C.begin(), C.end());

        int l = 0, r = n-1;
        std::vector<int> D(n);
        for (int i = n-1; i >=0; i--) {
            if (A[r] <= C[i].first) {
                D[C[i].second] = A[l++];
            } else {
                D[C[i].second] = A[r--];
            }
        }
        return D;
    }
};
