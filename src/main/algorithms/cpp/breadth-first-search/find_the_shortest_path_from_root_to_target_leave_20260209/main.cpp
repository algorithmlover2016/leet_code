#include <string>
#include <vector>
#include "solution.cpp"
#include <iostream>

void printTestCaseResult(int steps, int expected, int caseNumber) {
    if (steps != expected) {
        std::cout << "Test case " << caseNumber << " failed: expected " << expected << ", got " << steps << std::endl;
    } else {
        std::cout << "Test case " << caseNumber << " passed." << std::endl;
    }
}

int main() {
    Solution solution;
    std::string begin = "hit";
    std::string target = "cog";
    std::vector<std::string> wordlist = {"hot", "dot", "dog", "lot", "log", "cog"};
    int steps = solution.findShortestSteps(begin, target, wordlist);
    std::cout << "Minimum steps from " << begin << " to " << target << ": " << steps << std::endl;
    printTestCaseResult(steps, 5, 1);

    begin = "cat";
    target = "dog";
    wordlist = {"cot", "cog", "dog"};
    steps = solution.findShortestSteps(begin, target, wordlist);
    std::cout << "Minimum steps from " << begin << " to " << target << ": " << steps << std::endl;
    printTestCaseResult(steps, 4, 2);

    begin = "sand";
    target = "gold";
    wordlist = {"sand", "send", "sold", "cold"};
    steps = solution.findShortestSteps(begin, target, wordlist);
    std::cout << "Minimum steps from " << begin << " to " << target << ": " << steps << std::endl;
    printTestCaseResult(steps, 0, 3);

    begin = "apple";
    target = "pleas";
    wordlist = {"ample", "apply", "pears"};
    steps = solution.findShortestSteps(begin, target, wordlist);
    std::cout << "Minimum steps from " << begin << " to " << target << ": " << steps << std::endl;
    printTestCaseResult(steps, 0, 4);
    begin = "hello";
    target = "hello";
    wordlist = {"hello", "hallo", "hollo"};
    steps = solution.findShortestSteps(begin, target, wordlist);
    std::cout << "Minimum steps from " << begin << " to " << target << ": " << steps << std::endl;
    printTestCaseResult(steps, 1, 5);
    return 0;
}