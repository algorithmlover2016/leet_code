#include <iostream>
#include <vector>
using namespace std;

#define DEBUG
int main() {
    std::string ss;
    std::getline(cin, ss);
    std::vector<int> nums;
    int i = 0;
    int cur = 0;
    for (int idx = 0; idx < ss.size(); idx++) {
        if (ss[idx] >= '0' && ss[idx] <= '9') {
            cur = cur * 10 + ss[idx] - '0';
        } else if (ss[idx] == 'Y') {
            nums.emplace_back(cur);
            cur = 0;
        } else if (ss[idx] == 'S') {
            cur *= 7;
            nums.emplace_back(cur);
            cur = 0;
        } else {
            cur = 0;
        }
    }

#ifdef DEBUG
    for (int idx = 0; idx < nums.size(); idx++) {
        std::cout << nums[idx] << "\t";
    }
    std::cout << "\n";
    
#endif

    int ans = 0;
    int minNum = nums[0];
    int maxNum = nums[0];
    for (int idx = 1; idx < nums.size(); idx++) {
        if (nums[idx] >= nums[idx - 1]) {
            maxNum = nums[idx];
        } else {
            ans += maxNum - minNum;
            maxNum = minNum = nums[idx];
        }
#ifdef DEBUG
        std::cout << minNum << ",\t" << maxNum << "\n";
#endif
    }
    ans += maxNum - minNum;
    std::cout << ans << std::endl;
    return 0;
}
