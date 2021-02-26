#include "../../head.h"


class Solution {
public:
    bool checkPartitioning(std::string const & s) {
        // plagiarizing from https://youtu.be/K5RzCGYLYLk
        int const sSize = s.size();
        if (3 > sSize) {
            return false;
        }
        std::vector<std::vector<bool>> dpMemo(sSize, std::vector<bool>(sSize, false));
        for (int len = 1; len <= sSize; len++) {
            for (int idx = 0; idx + len - 1 < sSize; idx++) {
                int end = idx + len - 1; // idx and end are all included
                if (s[idx] == s[end]) {
                    dpMemo[idx][end] = end - idx < 2 || dpMemo[idx + 1][end - 1];
                }
            }
        }
        for (int idx = 0; idx < sSize - 2 /*at least left two elements*/; idx++) {
            if (dpMemo[0][idx]) {
                for (int sec = idx + 1; sec < sSize - 1; sec++) {
                    if (dpMemo[idx + 1][sec] && dpMemo[sec + 1][sSize - 1]) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
};

class Solution {
    bool isPalindromic(const std::string & s, int i, int j) {
        while (i < j && s[i] == s[j])
            ++i, --j;
        return i >= j;
    }

public:
    bool checkPartitioning(std::string const & s) {
        const int N = s.length();
        // s[0...left[i]] is palindromic
        std::vector<int> left{0};
        for (int i = 1; i < N - 2; ++i) {
            if (isPalindromic(s, 0, i)) {
                left.push_back(i);
            }
        }

        // s[right[i]...N-1] is palindromic
        std::vector<int> right{N - 1};
        for (int i = N - 2; i > 1; --i) {
            if (isPalindromic(s, i, N - 1)) {
                right.push_back(i);
            }
        }

        std::reverse(std::begin(right), std::end(right));

        int j = 0;
        for (int l : left) {
            while (j < right.size() && l + 2 > right[j]) {
                ++j;
            }
            if (j >= right.size()) {
                // can't get three group
                break;
            }
            int r = right[j];
            // cout << s.substr(0, l + 1) << " " << s.substr(r) << endl;
            if (isPalindromic(s, l + 1, r - 1)) {
                return true;
            }
        }
        return false;
    }
};
