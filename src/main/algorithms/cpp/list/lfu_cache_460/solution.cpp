#include "../../head.h"
#include "../dlinked_node.h"

class LFUCache {
public:
    LFUCache(int capacity) {
        this->used = 0;
        this->capacity = capacity;
        head = new DLinkedNode(-1, -1);
        tail = new DLinkedNode(-2, -2);
        head->next = tail;
        tail->pre = head;
    }

    int get(int key) {
        node_const_iterator getIterator = keyAddress.find(key);
        if (keyAddress.end() == getIterator) {
            return -1;
        }
        // std::cout << "get key " << key  << "\t" << getIterator->second->value << std::endl;
        reOrderDList(getIterator->second, false);
        return getIterator->second->value;
    }

    void put(int key, int value) {
        if (0 == capacity) {
            return;
        }
        DLinkedNode * node = nullptr;
        node_iterator it = keyAddress.find(key);
        if (keyAddress.end() == it) {
            // std::cout << "put key v " << key << "\t" << value << std::endl;
            node = new DLinkedNode(key, value);
            keyAddress[key] = node;
            used++;
            if (used > capacity) {
                DLinkedNode * delNode = popTail();
                // std::cout << "delNode " << delNode << "\t" << delNode->key << "\t" << delNode->value << std::endl;
                keyAddress.erase(delNode->key);
                int cnt = keyCnt[delNode->key];
                node_iterator cntAddressIterator = cntAddress.find(cnt);
                while (cntAddress.end() != cntAddressIterator && cntAddressIterator->second == delNode) {
                    cntAddressIterator->second = delNode->next;
                    cntAddressIterator = cntAddress.find(++cnt);
                }
                keyCnt.erase(delNode->key);
                used--;
                delete delNode;
                delNode = nullptr;
            }
        } else {
            it->second->value = value;
            node = it->second;
        }
        // std::cout << "call reorder by put" << std::endl;
        reOrderDList(node, true);
    }

private:
    void preAddNode(DLinkedNode * node) {
        node->next = head->next;
        node->pre = head;
        head->next->pre = node;
        head->next = node;
    }

    void insertNode(DLinkedNode* node, DLinkedNode* pos) {
        node->pre = pos->pre;
        pos->pre->next = node;
        pos->pre = node;
        node->next = pos;
    }

    // insertNode(node, tail);
    void postAddNode(DLinkedNode* node) {
        node->pre = tail->pre;
        tail->pre->next = node;
        tail->pre = node;
        node->next = tail;
    }

    void removeNode(DLinkedNode* node) {
        node->next->pre = node->pre;
        node->pre->next = node->next;
    }

    void reOrderDList(DLinkedNode * node, bool reset) {
        // std::cout << "reorder list" << std::endl;
        if (false == reset) {
            // get model
            integer_iterator it = keyCnt.find(node->key);
            int cnt = it->second;
            node_iterator node_iter = cntAddress.find(cnt);
            while (cntAddress.end() != node_iter && node_iter->second == node) {
                node_iter->second = node->next;
                node_iter = cntAddress.find(++cnt);
            }
            removeNode(node);
            it->second++;
            node_iterator new_node_iter = cntAddress.find(it->second);
            if (cntAddress.end() == new_node_iter) {
                insertNode(node, head->next);
            } else {
                insertNode(node, new_node_iter->second);
            }
            cntAddress[it->second] = node;
        } else {
            // put model
            integer_iterator it = keyCnt.find(node->key);
            if (keyCnt.end() == it) {
                keyCnt[node->key] = 1;
                it = keyCnt.find(node->key);
            } else {
                int cnt = it->second;
                node_iterator node_iter = cntAddress.find(cnt);
                while (cntAddress.end() != node_iter && node_iter->second == node) {
                    node_iter->second = node->next;
                    node_iter = cntAddress.find(++cnt);
                }
                removeNode(node);
                it->second++;
            }

            node_iterator node_iter = cntAddress.find(it->second);
            
            if (cntAddress.end() == node_iter) {
                // std::cout << "insert from head" << std::endl;
                insertNode(node, head->next);
            } else {
                // std::cout << "insert from somewhere" << std::endl;
                insertNode(node, node_iter->second);
            }
            cntAddress[it->second] = node;
        }
    }

    DLinkedNode* popTail() {
        DLinkedNode * node = tail->pre;
        if (head == node) {
            return nullptr;
        }
        tail->pre = node->pre;
        node->pre->next = tail;
        return node;
    }

private:
    typedef typename std::unordered_map<int, int>::const_iterator integer_const_iterator;
    typedef typename std::unordered_map<int, int>::iterator integer_iterator;

    typedef typename std::unordered_map<int, DLinkedNode*>::const_iterator node_const_iterator;
    typedef typename std::unordered_map<int, DLinkedNode*>::iterator node_iterator;

    DLinkedNode * head = nullptr;
    DLinkedNode * tail = nullptr;
    int used;
    int capacity;
    std::unordered_map<int, int> keyCnt;
    std::unordered_map<int, DLinkedNode*> keyAddress;
    std::unordered_map<int, DLinkedNode*> cntAddress;
};

class LFUCache_104ms {
public:
    struct Node {
        int key;
        int value;
        int count;
        list<int>::iterator it;

    };

    LFUCache(int capacity) {
        _capacity = capacity;
    }

    //user case:
    //get value when query with exising key and increase the count of the key and move the key to the end of the elements with same count;
    // insert a non existing key, remove the element which has smallest count number if cache is full and insert new to the beginning of list and update cache.
    // insert a existing key, inrease the count of the key and move the key to the end of the elements with same count.
    int get(int key) {
        //cout<<"get "<<key<<endl;
        //check if key exists in map
        //if it exists, move it to the back of list
        if(dic.count(key)) {
            auto & p = dic[key];
            touch(p);
            //cout<<"return "<<_list.back().value<<endl;
            return p.value;
        }
        //cout<<"return -1"<<endl;
        return -1;
    }

    void put(int key, int value) {
        //check if is full
        // if key exists, updae key's value and move it to the back of list
        //if key doesnot exists,
        //remove the head element of the list and from the map
        //insert the new element to the end of list and insert it to the map
        //cout<<"put "<<key<<" "<<value<<" "<<_capacity<<endl;

        if(dic.count(key)) {
            dic[key].value = value;
            touch(dic[key]);
            return;
        }

        if(_capacity == 0) {
            return;
        }

        //cout<<"still put"<<endl;
        if(dic.size() == _capacity) {
            auto k = indexDic[min_freq].back();
            auto p = dic[k];
            indexDic[p.count].erase(p.it);
            if(indexDic[p.count].size() == 0) {
                indexDic.erase(p.count);
            }
            dic.erase(k);
        }

        indexDic[1].push_front(key);
        //_list.push_front({key, value, 1, indexDic[1].begin()});
        dic[key] = {key, value, 1, indexDic[1].begin()};
        min_freq = 1;
    }

    void touch(Node& node) {
        int prevCount = node.count;
        int count = ++node.count;
        indexDic[prevCount].erase(node.it);
        if(indexDic[prevCount].size() == 0) {
            indexDic.erase(prevCount);
            if(prevCount == min_freq)
                min_freq++;
        }
        indexDic[count].push_front(node.key);
        node.it = indexDic[count].begin();
    }

    //key is just key of every element, and value is the corresponding list node
    std::unordered_map<int, Node> dic;
    //key is visiting count, start and end node of the elements which have same visiting count.
    std::unordered_map<int, list<int>> indexDic;
    //list<Node> _list;
    int _capacity;
    int min_freq;

};

class LFUCache_100ms {
    public:
        struct node {
            int key;
            int val;
            int freq;
            node(int k, int v, int f): key(k), val(v), freq(f){}
        };

        LFUCache(int capacity) {
            cap = capacity;
        }

        int get(int key) {
            if (iter.count(key) == 0) {
                return -1;
            }

            int value = iter[key]->val;
            // note, the minFreq may change
            int frequence = iter[key]->freq;

            freq[frequence].erase(iter[key]);
            if (freq[minFreq].size() == 0) {
                minFreq++;
            }
            // if (freq[frequence].size() == 0) {
            //     freq.erase(frequence);
            //     if (minFreq == frequence) minFreq += 1;
            // }

            freq[frequence + 1].push_back(node(key, value, frequence + 1));
            iter[key] = --freq[frequence + 1].end();

            return value;
        }

        void put(int key, int value) {
            if (cap <= 0) return;
            if (get(key) != -1) {
                iter[key]->val = value;
                return;
            }

            // wei: this check must be put before adding new node!!!
            // if oversize, delete least frequently used node
            if (iter.size() >= cap) {
                int k = freq[minFreq].begin()->key;
                freq[minFreq].pop_front();
                iter.erase(k);
            }

            // add new node
            minFreq = 1;
            freq[1].push_back(node(key, value, 1));
            iter[key] = --freq[1].end();
        }


    private:
        // 0. 实时统计
        int cap, minFreq;
        // 1. 资料库
        // std::unordered_map<int, pair<int, int>> m;    // key, pair<val, freq>
        // 2. 功能单元
        std::unordered_map<int, list<node>> freq;      // freq, list of keys
        // 3. 辅助单元
        std::unordered_map<int, list<node>::iterator> iter; // key, this key's iterator/position in the list

};


/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
