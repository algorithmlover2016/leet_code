#include "../../head.h"


class SmallestInfiniteSet {
public:
    SmallestInfiniteSet() {
    }
    
    int popSmallest() {
        if (!added.empty()) {
            int ans = *added.begin();
            added.erase(added.begin());
            return ans;
        } else {
            return cur++;
        }
        
    }
    
    void addBack(int num) {
        if (num < cur) {
            added.insert(num);
        }
    }
private:
    int cur = 1;
    std::set<int> added;
};

/**
 * Your SmallestInfiniteSet object will be instantiated and called as such:
 * SmallestInfiniteSet* obj = new SmallestInfiniteSet();
 * int param_1 = obj->popSmallest();
 * obj->addBack(num);
 */