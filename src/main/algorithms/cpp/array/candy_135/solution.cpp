#include "../../head.h"


// #define DEBUG
class Solution {
public:
    int candy(std::vector<int> const & ratings) {
        // maybe we just traverse the array named ratings twice
        int ratingsSize = ratings.size();
        if (JUST_TWO > ratingsSize) {
            return ratingsSize;
        }
        std::vector<int> needCandys(ratingsSize, 1);
        int ans = ratingsSize;
        for (int idx = 1; idx < ratingsSize; idx++) {
            if (ratings[idx] > ratings[idx - 1]) {
                int delta = std::max(0, needCandys[idx - 1] + 1 - needCandys[idx]);
                ans += delta;
                needCandys[idx] += delta;
            }
                #ifdef DEBUG
                std::cout << idx << ", " << needCandys[idx] << '\t';
                #endif
        }
        #ifdef DEBUG
        std::cout << '\n';
        #endif
        for (int idx = ratingsSize - 2; idx > MOST_LEFT_IDX_EXCLUDE; idx--) {
            if (ratings[idx] > ratings[idx + 1]) {
                int delta = std::max(0, needCandys[idx + 1] + 1 - needCandys[idx]);
                ans += delta;
                needCandys[idx] += delta;
            }
            #ifdef DEBUG
            std::cout << idx << ", " << needCandys[idx] << '\t';
            #endif
        }
        #ifdef DEBUG
        std::cout << '\n';
        #endif
        return ans;
    }

private:
    static int const JUST_TWO = 2;
    static int const MOST_LEFT_IDX_EXCLUDE = -1;
};

class Solution {
public:
    int candy(std::vector<int> const & A) {
        int n = A.size();
        if (JUST_TWO > n) {
            return n;
        }
        int ans = 0;
        std::vector<int> left(n, 1);
        std::vector<int> right(n, 1);
        for (int i = 1; i < n; i++) {
            if (A[i] > A[i - 1]) {
                left[i] = left[i - 1] + 1;
            }
        }
        for (int i = n - 2; i >= 0; i--) {
            if (A[i] > A[i + 1]) {
                right[i]  = right[i + 1] + 1;
            }
        }
        for (int i = 0; i < n; i++) {
            ans += std::max(left[i], right[i]);
        }
        return ans;
    }
private:
    static int const JUST_TWO = 2;
};

class Solution {
public:
    int candy(std::vector<int> const & ratings) {
        int d = 0, s = ratings.size(), ans = s;
        if (JUST_TWO > s) {
            return s;
        }
        for (int i = 1; i < s;) {
            if (ratings[i - 1] == ratings[i]) {
                ++i;
            }
            // find the increasing order sub-array
            for (d = 0; i < s && ratings[i - 1] < ratings[i]; ans += ++d, ++i);
            int sd = d;
            // find the descreasing order sub-array
            for (d = 0; i < s && ratings[i - 1] > ratings[i]; ans += ++d, ++i);
            // if we look at the descreasing sub-array from right to left, we add twice in the middle maximum position
            // which means when dealing with increasing order, we add a sd;
            // and dealing with descreasing order, we add a d. we should just add a maximum(sd, d), but we add sd and d
            // so we need minus the smaller one
            ans -= std::min(d, sd);
        }
        return ans;
    }
private:
    static int const JUST_TWO = 2;
};
