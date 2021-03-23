#include "../../head.h"


// #define DEBUG
class Solution {
public:
    int longestMountain(std::vector<int> arr) {
        arr.emplace_back(INT_MAX);
        int const arrSize = arr.size();
        if (JUST_RETURN > arrSize) {
            return 0;
        }

        int ans = 0;

        bool inc = true;
        int start = 0;
        int maxVal = arr[0];

        for (int idx = 1; idx < arrSize; idx++) {
            #ifdef DEBUG
            std::cout << std::boolalpha << inc << "\t";
            #endif
            if (inc) {
                if (arr[idx] > arr[idx - 1]) {
                    maxVal = std::max(maxVal, arr[idx]);
                    continue;
                } else if (arr[idx] == arr[idx - 1]) {
                    start = idx;
                } else {
                    inc = false;
                    if (maxVal == arr[start]) {
                        maxVal = arr[idx];
                        start = idx;
                        inc = true;
                    }
                }
            } else {
                if (arr[idx] < arr[idx - 1]) {
                    continue;
                } else {
                    #ifdef DEBUG
                    std::cout << "start, idx: " << start << ",\t" << idx << "\n";
                    #endif
                    if (maxVal != arr[start]) {
                        ans = std::max(ans, idx - start);
                    }
                    start = idx - 1;
                    if (arr[idx] == arr[idx - 1]) {
                        start = idx;
                    }
                    inc = true;
                }
            }
        }
        return ans;
    }
private:
    static int const JUST_RETURN = 4;
};

class Solution {
public:
    int longestMountain(std::vector<int> const & arr) {
        int res = 0, c = 0, n = 0, safe = 0, m = 0;

        n = arr.size() - 1;
        if (n < 2) {
            return 0;
        }
        for(int i = 0; i < n;) {
            c = i;
            while (c < n && arr[c + 1] > arr[c]) {
                c++;
            }
            safe = c;
            if (c > i) {
                while (c < n && arr[c + 1] < arr[c]) {
                    c++;
                }
                if (c > safe) {
                    m = std::max(m, c - i + 1);
                }
                i = c - 1;
            }
            i++;
        }
        return m;
    }
};

class Solution {
public:
    int longestMountain(std::vector<int> const & a) {
        int n = (int) a.size();
        int ans = 0, start = 0;
        while (start < n) {
            int end = start;

            if (end + 1 < n and a[end] < a[end + 1]){
                while (end + 1 < n and a[end] < a[end + 1]) {
                    end++;
                }
                if (end + 1 < n and a[end] > a[end + 1]) {
                    while(end + 1 < n and a[end] > a[end + 1]) {
                        end++;
                    }
                    ans = std::max(ans, end - start + 1);
                }
            }
            start = std::max(end, start + 1);
        }
        return ans;
    }
};
