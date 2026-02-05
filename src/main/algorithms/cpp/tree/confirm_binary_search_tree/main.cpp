#include "../../header.h"
#include "./solution.cpp"

int main() {
    SolutionRecursive solRec;
    SolutionStack solStack;
    
    // 测试用例
    vector<int> test1 = {5, 2, 1, 3, 4, 7, 6}; // True
    vector<int> test2 = {5, 2, 6, 1, 3};       // False

    cout << "--- Recursive Solution (O(N^2)) ---" << endl;
    cout << "Test 1: " << (solRec.verifyPreorder(test1) ? "true" : "false") << endl;
    cout << "Test 2: " << (solRec.verifyPreorder(test2) ? "true" : "false") << endl;

    cout << "\n--- Stack Solution (O(N)) ---" << endl;
    cout << "Test 1: " << (solStack.verifyPreorder(test1) ? "true" : "false") << endl;
    cout << "Test 2: " << (solStack.verifyPreorder(test2) ? "true" : "false") << endl;

    return 0;
}
