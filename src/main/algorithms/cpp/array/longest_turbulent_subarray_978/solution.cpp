#include "../../head.h"


// #define DEBUG
class Solution {
public:
    int maxTurbulenceSize(std::vector<int> const & arr) {
        int const arrSize = arr.size();
        if (JUST_TWO > arrSize) {
            return arrSize;
        }
        int ans = std::max(firstLess(arr), firstLess(arr, true));
        return ans;
    }

private:
    int firstLess(std::vector<int> const & arr, bool initFlag = false) {
        #ifdef DEBUG
        std::cout << typeid(*this).name() << "::" << __func__ << "\n";
        #endif
        int const arrSize = arr.size();
        int preIdx = 0, endIdx = 0;
        int ans = 0;
        bool needLess = initFlag;
        for (int idx = 1; idx < arrSize; idx++) {
            if (needLess) {
                if (arr[idx] < arr[idx - 1]) {
                    #ifdef DEBUG
                    std::cout << arr[idx] << ", ";
                    #endif
                    endIdx = idx;
                    needLess = false;
                } else if (arr[idx] > arr[idx - 1]) {
                    #ifdef DEBUG
                    std::cout << "need break at: " <<  arr[idx - 1] << ", " << arr[idx] << ", ";
                    #endif
                    ans = std::max(ans, endIdx - preIdx + 1);
                    preIdx = idx - 1;
                    endIdx = idx;
                } else {
                    #ifdef DEBUG
                    std::cout << "need break because equal at: " <<  arr[idx] << ", ";
                    #endif
                    ans = std::max(ans, endIdx - preIdx + 1);
                    preIdx = endIdx = idx;
                    needLess = initFlag;
                }
            } else {
                if (arr[idx] > arr[idx - 1]) {
                    #ifdef DEBUG
                    std::cout << arr[idx] << ", ";
                    #endif
                    endIdx = idx;
                    needLess = true;
                } else if (arr[idx] < arr[idx - 1]) {
                    #ifdef DEBUG
                    std::cout << "need break at: " <<  arr[idx - 1] << ", " << arr[idx] << ", ";
                    #endif
                    ans = std::max(ans, endIdx - preIdx + 1);
                    preIdx = idx - 1;
                    endIdx = idx;
                } else {
                    #ifdef DEBUG
                    std::cout << "need break because equal at: " <<  arr[idx] << ", ";
                    #endif
                    ans = std::max(ans, endIdx - preIdx + 1);
                    preIdx = endIdx = idx;
                    needLess = initFlag;
                }
            }
        }
        ans = std::max(ans, endIdx - preIdx + 1);
        return ans;
    }
private:
    static int const JUST_TWO = 2;
};

class Solution {
public:
    //length of longest subarray with alternate elements
    int maxTurbulenceSize(std::vector<int> const & arr) {
        int res = INT_MIN, n = arr.size(), linc = 1, ldec = 1;
        if(2 > n) {
            return n;
        }
        for (int i = 1; i < n; i++) {
            if (arr[i - 1] > arr[i]) {
                ldec = linc + 1;
                linc = 1; //reset to 1
            } else if(arr[i - 1] < arr[i]) {
                linc = ldec + 1;
                ldec = 1; //reset to 1
            } else if(arr[i] == arr[i - 1]) {
                linc = 1, ldec = 1;
            }
            res = std::max(res, std::max(linc, ldec));
        }
        return res;
    }
};
