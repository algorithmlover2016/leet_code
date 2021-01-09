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

const static int _ = []() {
	cin.tie(0);
	cout.tie(0);
	ios_base::sync_with_stdio(false);
	return 0;
}();

class CustomStack {
public:

    int *stack,*lazy;
    int ptr, maxSize;

    CustomStack(int maxSize):ptr(0),maxSize(maxSize) {
        stack = (int*)calloc((maxSize+7),sizeof(int));
        lazy = (int*)calloc((maxSize+7),sizeof(int));
        //memset(lazy,0,1007*sizeof(int));
        //memset(stack,0,1007*sizeof(int));
    }
    inline void push(int x) {
        if(ptr+1>maxSize) return;
        stack[ptr++]=x;
    }

    inline int pop() {
        if(ptr==0) return -1;
        int x = stack[ptr-1]+lazy[ptr-1];
        if(ptr-2>=0) {
            lazy[ptr-2]+=lazy[ptr-1];
            lazy[ptr-1]=0;
        } else {
            lazy[0]=0;
        }
        ptr--;
        return x;
    }
    inline
    void increment(int k, int val) {
        if(ptr>0) lazy[min(ptr-1,k-1)]+=val;
    }
};
