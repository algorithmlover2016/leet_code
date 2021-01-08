#include "../../head.h"


class Solution {
public:
    int maxUncrossedLines(std::vector<int> const & A, vector<int> const & B) {
        // plagiarizing idea from https://www.youtube.com/watch?v=Gwp8hL2F6c0
        // the longest common subsequence
        int const ASize = A.size();
        int const BSize = B.size();
        if (JUST_EMPTY == ASize || JUST_EMPTY == BSize) {
            return 0;
        }
        std::vector<std::vector<int>> dpMemo(ASize + 1,
                std::vector<int>(BSize + 1, 0));
        for (int idxA = 1; idxA < dpMemo.size(); idxA++) {
            for (int idxB = 1; idxB < dpMemo[idxA].size(); idxB++) {
                if (B[idxB - 1] == A[idxA - 1]) {
                    dpMemo[idxA][idxB] = 1 + dpMemo[idxA - 1][idxB - 1];
                } else {
                    dpMemo[idxA][idxB] = std::max(dpMemo[idxA - 1][idxB],
                                                  dpMemo[idxA][idxB - 1]);
                }
            }
        }

        return dpMemo[ASize][BSize];
    }
    private:
    static int const JUST_EMPTY = 0;
};
