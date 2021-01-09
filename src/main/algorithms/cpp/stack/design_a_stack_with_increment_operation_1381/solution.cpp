#include "../../head.h"


// #define DEBUG
class CustomStack {
public:
    CustomStack(int maxSize) : _cStackSize(maxSize) {
        _cStack.clear();
    }

    void push(int x) {
        if (_cStackSize <= _cStack.size()) {
            return;
        }
        #ifdef DEBUG
        std::cout << "push: " << x << "\n";
        #endif
        _cStack.emplace_back(x);
    }

    int pop() {
        if (_cStack.empty()) {
            return -1;
        }
        int last = _cStack.back();

        #ifdef DEBUG
        std::cout << "pop: " << last << "\n";
        #endif
        _cStack.pop_back();
        return last;
    }

    void increment(int k, int val) {
        int incSize = k;
        if (_cStack.size() < k) {
            incSize = _cStack.size();
        }
        for (int idx = 0; idx < incSize; idx++) {
            _cStack[idx] += val;
        }
    }
private:
    int const _cStackSize;
    std::vector<int> _cStack;
};
