#include "../../head.h"

#define TEST_MAIN
class DNode {
    public:
        int val;
        DNode* next;
        DNode* pre;
        DNode(int val_ = -1, DNode* next_ = nullptr, DNode* pre_ = nullptr) :
            val(val_), next(next_), pre(pre_) {
            }
};

class Solution {
public:
    Solution () {
        head = new DNode(-1); //dumpy node
        tail = new DNode(-1); // dumpy node
        head->next = tail;
        tail->pre = head;
    }

    ~Solution() {
        DNode* cur = head;
        while (nullptr != cur) {
            DNode* tmp = cur;
            cur = cur->next;
            delete tmp;
            tmp = nullptr;
        }
    }

    bool add(int val) {
        DNode* newNode = new DNode(val);
        if (nullptr == newNode) {
            return false;
        }
        return insert(newNode, tail);
    }

    bool erase(int val) {
        DNode* it = search(val);
        if (nullptr == it) {
            return false;
        }
        return erase(it);
    }

    DNode* search(int val) {
        DNode* cur = head->next;
        while (cur != tail) {
            if (val == cur->val) {
                return cur;
            } else {
                cur = cur->next;
            }
        }
        return nullptr;
    }

private:
    bool erase(DNode* pos) {
        if (pos == head || pos == tail) {
            return false;
        }
        pos->pre->next = pos->next;
        pos->next->pre = pos->pre;
        delete pos;
        pos = nullptr;
        return true;
    }

    bool insert(DNode* newNode, DNode* pos) {
        if (nullptr == pos) {
            return false;
        }

        newNode->next = pos;
        newNode->pre = pos->pre;
        pos->pre->next = newNode;
        pos->pre = newNode;

        return true;
    }
private:
    DNode* head = nullptr;
    DNode* tail = nullptr;
};

#ifdef TEST_MAIN
int main() {
    Solution obj;
    assert(true == obj.add(5));
    assert(true == obj.add(6));
    assert(true == obj.add(1));
    assert(true == obj.add(8));
    assert(true == obj.add(9));
    assert(true == obj.add(10));
    assert(true == obj.add(11));
    assert(true == obj.add(2));
    assert(true == obj.add(4));
    assert(nullptr != obj.search(8));
    assert(8 == obj.search(8)->val);
    assert(nullptr == obj.search(7));
    assert(true == obj.erase(10));
    assert(false == obj.erase(15));
    std::cout << "TEST SUCCESSFULLY" << std::endl;
    return 0;
}
#endif
