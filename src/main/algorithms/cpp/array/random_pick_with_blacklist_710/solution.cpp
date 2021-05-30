#include "../../head.h"


class Solution {
public:
    Solution(int const N, std::vector<int> const & blacklist) {
        // plagiarizing from https://leetcode.com/problems/random-pick-with-blacklist/discuss/144624/Java-O(B)-O(1)-HashMap and
        // https://leetcode.com/problems/random-pick-with-blacklist/discuss/146356/C%2B%2B-DO-NOT-use-rand()-after-C%2B%2B11-! and
        // https://isocpp.org/files/papers/n3551.pdf and
        // https://www.cplusplus.com/reference/random/uniform_int_distribution/uniform_int_distribution/

        for (int const blackNum : blacklist) {
            if (blackNum < N) {
                blacks[blackNum] = -1;
            }
        }
        int const maxEleLen = N - blacks.size();
        assert(maxEleLen > 0);
        int initMaxLen = N;
        for (int const blackNum : blacklist) {
            if (blackNum < maxEleLen) {
                while (blacks.find(--initMaxLen) != blacks.end()) {
                    // find the first maximum element which is not blocked
                    ;
                }
            }
            blacks[blackNum] = initMaxLen;
        }
        std::random_device rd;
        gen = std::mt19937(rd());
        dis = std::uniform_int_distribution<int>(0, maxEleLen - 1);
    }

    int pick() {
        int rnd = dis(gen);
        if (blacks.find(rnd) != blacks.end()) {
            return blacks[rnd];
        }
        return rnd;
    }

private:
    std::mt19937 gen;
    std::uniform_int_distribution<int> dis;
    std::unordered_map<int, int> blacks;
};

class Solution {
public:
    Solution(int Num, std::vector<int> const & blist) {
        N = Num;
        blacklist = blist; // .assign(blist.begin(), blist.end());
        size = blacklist.size();
        if (size > 0) {
            std::sort(blacklist.begin(), blacklist.end());
        }
    }

    int pick() {
        /*
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        std::mt19937_64 gen(seed);
        std::uniform_int_distribution<int> dist(0, N - size - 1);

        int r = dist(gen);*/

        int r = rand() % (N - size);

        if (size == 0) {
            return r;
        }

        int s = blacklist.front();
        int t = blacklist.back();
        int ans = 0;
        if (r < s) {
            ans = r;
        } else if (r > t - size) {
            ans = r + size;
        } else {
            int low = 0;
            int high = size - 1;
            while (low < high) {
                int mid = (low + high + 1) / 2;
                if (blacklist[mid] - mid > r) {
                    high = mid - 1;
                } else {
                    low = mid;
                }
            }
            if (low == high && blacklist[low] - low <= r) {
                ans = r + low + 1;
            } else {
                ans = r;
            }
        }
        return ans;

    }
private:
    std::vector<int> blacklist;
    int size = 0;
    int N = 0;
};
