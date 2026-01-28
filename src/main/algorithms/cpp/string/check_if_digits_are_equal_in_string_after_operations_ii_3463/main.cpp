#include <iostream>
#include <string>
#include <vector>
#include "solution.cpp"

int main() {
    Solution sol;
    
    // std::vector<std::string> test_cases = {"3902", "34789"}; 
    // You can add more test cases here
    std::string input;
    std::cout << "Enter a string of digits: ";
    if (std::cin >> input) {
        bool result = sol.hasSameDigits(input);
        std::cout << "Result for " << input << ": " << (result ? "true" : "false") << std::endl;
    }

    return 0;
}