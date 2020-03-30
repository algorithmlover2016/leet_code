#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

class Solution {
public:
    int findPeakElement(std::vector<int>& nums) {
        int size = nums.size();
        if (size < 2) {
            return size - 1;
        }
        int pre = INT_MIN;
        for (int index = 0; index < size; index++) {
            if (index + 1 == size) {
                if (nums[index] > pre) {
                    return index;
                }
            } else {
                if ((nums[index] > pre) && (nums[index] > nums[index + 1])) {
                    return index;
                }
                pre = nums[index];
            }
        }
        return INT_MAX;
    }
};

class class Solution_BSR {
public:
    int findPeakElement(const vector<int> &num) {
        return Helper(num, 0, num.size()-1);
    }
    int Helper(const vector<int> &num, int low, int high) {
        if(low == high) {
            return low;
        }
        else {
            int mid1 = (low+high)/2;
            int mid2 = mid1+1;
            if(num[mid1] > num[mid2]) {
                return Helper(num, low, mid1);
            }
            else {
                return Helper(num, mid2, high);
            }
        }
    }
};

class Solution_BSI {
public:
    int findPeakElement(const vector<int> &num) {
        int low = 0;
        int high = num.size()-1;

        while(low < high) {
            int mid1 = (low+high)/2;
            int mid2 = mid1+1;
            if(num[mid1] < num[mid2]) {
                low = mid2;
            }
            else {
                high = mid1;
            }
        }
        return low;
    }
};

// other thinking
// copy from https://leetcode.com/problems/find-peak-element/discuss/50232/Find-the-maximum-by-binary-search-(recursion-and-iteration)
class Solution_less_before {
    public:
        int findPeakElement(const std::vector<int> &num) {
            for(int i = 1; i < num.size(); i ++) {
                if(num[i] < num[i-1]) {
                    // <
                    return i-1;
                }
            }
            return num.size()-1;
        }
};

int main() {
    Solution var;
    std::vector<int> dominoes = {1, 1, 1, 3, 5, 6, 4};
    std::cout << var.findPeakElement(dominoes) << std::endl;
    Solution_less_before var_1;
    std::cout << var_1.findPeakElement(dominoes) << std::endl;
    return 0;

}
// g++ -std=c++11  -o main solution.cpp
//  g++-9 -std=c++11 solution.cpp -o main
