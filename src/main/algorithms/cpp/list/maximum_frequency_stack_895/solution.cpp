#include "../../head.h"


class FreqStack {
    // plagiarizing from https://leetcode.com/problems/maximum-frequency-stack/discuss/163410/C%2B%2BJavaPython-O(1)
public:
    FreqStack() :maxFreq(0) {
    }
    
    void push(int x) {
        maxFreq = std::max(maxFreq, ++freqs[x]);
        mStores[freqs[x]].emplace(x);
    }
    
    int pop() {
        int val = mStores[maxFreq].top(); mStores[maxFreq].pop();
#ifdef EASY_TO_UNDERSTAND
        freqs[val]--;
        if (mStores[maxFreq].empty()) {
            maxFreq--;
        }
#else
        if (mStores[freqs[val]--].empty()) {
            maxFreq--;
        }
#endif
        return val;
        
    }
private:
    typedef int KEY_TYPE;
    std::unordered_map<KEY_TYPE, int> freqs;
    std::unordered_map<int, std::stack<KEY_TYPE>> mStores;
    int maxFreq;
};
