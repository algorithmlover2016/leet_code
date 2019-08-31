// #include "../../head.h"
// #include "../dlinked_node.h"

class LRUCache {
public:
    struct DLinkedNode {
        int key;
        int value;
        DLinkedNode* pre;
        DLinkedNode* next;
        DLinkedNode() : key(0), value(0), pre(nullptr), next(nullptr) {}
        DLinkedNode(int key, int value) : key(key), value(value), pre(nullptr), next(nullptr) {}
    };
    LRUCache(int capacity) {
        this->capacity = capacity;
        this->used = 0;
        this->head = new DLinkedNode(-1, -1);
        this->tail = new DLinkedNode(-2, -2);
        head->next = tail;
        tail->pre = head;
    }

    int get(int key) {
        std::cout << "get key " << "\t" << key << std::endl;
        const_iterator it = cache.find(key);
        if (cache.end() == it) {
            return -1;
        }
        std::cout << "call move to head with get " << it->second->key << "\t" << it->second->value << std::endl;
        moveToHead(it->second);
        return it->second->value;
    }

    void put(int key, int value) {
        std::cout << "call put " << key << "\t" << value << std::endl;
        iterator it = cache.find(key);
        if (cache.end() != it) {
            std::cout << "find exist key " << it->second->key << "\t" << it->second->value << std::endl;
            it->second->value = value;
            moveToHead(it->second);
        } else {
            DLinkedNode * node = new DLinkedNode(key, value);
            addNode(node);
            // cache.insert({key, node});
            cache[key] = node;
            if (++used > capacity) {
                DLinkedNode * node = popTail();
                cache.erase(node->key);
                used--;
                // free node
                delete node;
                node = nullptr;
            }
        }

    }
private:
    void addNode(DLinkedNode* node) {
        // creating node by caller
        std::cout << "add Node "<< node->key << "\t" << node->value << std::endl;
        node->pre = head;
        node->next = head->next;
        head->next->pre = node;
        head->next = node;
    }

    void removeNode(DLinkedNode* node) {
        std::cout << "remove Node "<< node->key << "\t" << node->value << std::endl;
        node->next->pre = node->pre;
        node->pre->next = node->next;
    }

    void moveToHead(DLinkedNode* node) {
        // creating node by caller;
        std::cout << "move to head" << std::endl;
        this->removeNode(node);
        this->addNode(node);
    }

    DLinkedNode* popTail() {
        // freeing node by caller
        std::cout << "pop Tail" << std::endl;
        DLinkedNode * node = tail->pre;
        this->removeNode(node);
        return node;
    }


private:
    typedef typename std::unordered_map<int, DLinkedNode*>::const_iterator const_iterator;
    typedef typename std::unordered_map<int, DLinkedNode*>::iterator iterator;
    std::unordered_map<int, DLinkedNode*> cache;
    DLinkedNode * head = nullptr;
    DLinkedNode * tail = nullptr;
    int used;
    int capacity;
};

struct biDirectionList {
    int val;
    biDirectionList* next;
    biDirectionList* pre;
    biDirectionList(int val_ = 0, biDirectionList* next_ = nullptr, biDirectionList* pre_ = nullptr):
        val(val_), next(next_), pre(pre_) {}
};

class LRUCacheTwoMap {
public:
    LRUCache(int capacity) : cap(capacity), head(nullptr), end(nullptr), used(0) {
    }

    int get(int key) {
        std::unordered_map<int, int>::const_iterator gotIter = keyValMap_.find(key);
        if (gotIter == keyValMap_.end()) {
            return -1;
        }
        reOrderList(key);
        return gotIter->second;
    }

    void put(int key, int value) {
        std::unordered_map<int, int>::iterator gotIter = keyValMap_.find(key);
        if (gotIter != keyValMap_.end()) {
            gotIter->second = value;
            reOrderList(key);
            return;
        }
        if (cap == 0) {
            return;
        }

        biDirectionList* cur = nullptr;
        if (head == nullptr) {
            cur = new biDirectionList(key);
            head = end = cur;
            used++;
        } else {
            if (used < cap) {
                cur = new biDirectionList(key);
                end->next = cur;
                cur->pre = end;
                used++;
            } else {
                cur = head;
                if (head != end) {
                    head = head->next;
                    head->pre = nullptr;
                    end->next = cur;
                    cur->pre = end;
                }
                keyValMap_.erase(cur->val);
                keyAddressMap_.erase(cur->val);
                cur->val = key;
            }
            cur->next = nullptr;
            end = cur;
        }
        keyValMap_[key] = value;
        keyAddressMap_[key] = cur;
    }

    void reOrderList(int key) {
        std::unordered_map<int, biDirectionList*>::const_iterator gotIter = keyAddressMap_.find(key);
        biDirectionList* cur = gotIter->second;
        if (cur == end) {
            return;
        }

        if (cur == head) {
            head = head->next;
            head->pre = nullptr;
        } else {
            cur->next->pre = cur->pre;
            cur->pre->next = cur->next;
        }

        end->next = cur;
        cur->pre = end;
        cur->next = nullptr;
        end = cur;
        return;
    }
    void printList() {
        biDirectionList* cur = head;
        while(cur != nullptr) {
            std::cout << cur->val << "\t";
            cur = cur->next;
        }
        std::cout << std::endl;
    }

private:
    unordered_map<int, int> keyValMap_;
    unordered_map<int, biDirectionList*> keyAddressMap_;
    int cap;
    int used;
    biDirectionList* head;
    biDirectionList* end;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
