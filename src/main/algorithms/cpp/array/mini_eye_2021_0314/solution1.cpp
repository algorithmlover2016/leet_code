#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <forward_list>
#include <array>
#include <deque>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <tuple>

#include <algorithm>
#include <cassert>
#include <cctype>
#include <chrono>
#include <ctime>
#include <functional>
#include <iterator>
#include <limits>
#include <locale>
#include <random>
#include <regex>
#include <utility>

#define DEBUG

int main() {
    int N = 0;
    
    std::cin >> N;
    std::string ss;
    std::vector<int> nums(N / 2);
    int sum = 0;
    for (int idx = 0; idx < nums.size(); idx++) {
        std::cin >> nums[idx];
        sum += nums[idx];
    }
    std::sort(nums.begin(), nums.end());
    int oddSum = 0;
    int evenSum = 0;
    int oddRight = N - 1;
    int evenRight = N;

    for (int idx = nums.size() - 1; idx >= 0; idx--) {
        oddSum += std::abs(oddRight - nums[idx]);
        evenSum += std::abs(evenRight - nums[idx]);
        oddRight -= 2;
        evenRight -= 2;
    }

#ifdef DEBUG
    std::cout << sum << "\t" << oddSum << "\t" << evenSum << "\n";
#endif
    std::cout << std::min(oddSum, evenSum) << std::endl;
    return 0;
}
