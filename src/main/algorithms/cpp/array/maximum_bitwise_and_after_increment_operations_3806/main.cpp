#include <iostream>
#include <string>
#include <vector>
#include "solution.cpp"

int main() {
    Solution sol;
    
    // std::vector<std::string> test_cases = {"3902", "34789"}; 
    // You can add more test cases here
    std::vector<int> input = {1,2,3};
    int k = 8;
    int m = 2;
    int result = sol.maximumAND(input, k, m);
    std::cout << "Result: " << result << std::endl;

    return 0;
}