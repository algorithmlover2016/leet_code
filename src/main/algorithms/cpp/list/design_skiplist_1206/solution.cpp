#include "../../head.h"


// #define DEBUG
// #define REMOVE_ALL_ELEMENTS_EQUALS_TO_TARGET
class Skiplist {
protected:
    class Node {
    public:
        int val;
        std::vector<Node*> levels;

        Node() : val(0) {
        }

        Node(int val_, int const levels_) : val(val_), levels(std::vector<Node*>(levels_)) {
        }
    };
public:
    Skiplist() {
        head = new Node(DUMMY_NODE_VAL, MAX_LEVELS + 1);
    }

    ~Skiplist() {
        if (nullptr != head) {
            delete head;
            head = nullptr;
        }
    }

    bool search(int const target) {
        #ifdef DEBUG
        std::cout << __func__ << ", " << __LINE__ << ": " << target << "\n";
        #endif
        std::vector<std::pair<Node*, int>> ans = iterator(target); // ans at least add the head node, which means ans will not be empty
        auto & buttomLevelNode = ans.back();
        Node* pre = buttomLevelNode.first;
        int level = buttomLevelNode.second; // which means level = 0;
        Node* cur = pre->levels[level]; // Node* cur = buttomLevelNode.first.levels[buttomLevelNode.second];
        return nullptr != cur && cur->val == target;
    }

    void add(int const num) {
        
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine generator(seed);
        std::uniform_int_distribution<int> distribution(MIN_LEVELS, MAX_LEVELS);
        int curLevel = distribution(generator) + 1;
        
        #ifdef DEBUG
        std::cout << __func__ << ", " << __LINE__ << ": "  << num << ", " << curLevel << "\n";
        #endif
        
        Node * newNode = new Node(num, curLevel);
        std::vector<std::pair<Node*, int>> preNode = iterator(num);
        for (auto const & ele : preNode) {
            Node* pre = ele.first;
            int level = ele.second;
            if (level < newNode->levels.size()) {
                // to avoid out of range
                newNode->levels[level] = pre->levels[level];
                pre->levels[level] = newNode;
            }
        }
    }

    bool erase(int const num, bool recursive = false) {
        
        #ifdef DEBUG
        std::cout << __func__ << ", " << __LINE__ << ": " << num << "\t";
        #endif
        std::vector<std::pair<Node*, int>> preNode = iterator(num);
        bool ret = false;
        for (auto const & ele : preNode) {
            Node* pre = ele.first;
            int level = ele.second;
            Node* forwardNode = pre->levels[level]; // the cur level next node
            if (nullptr != forwardNode && forwardNode->val == num) {
                ret = true;
                pre->levels[level] = forwardNode->levels[level];
                #ifdef DEBUG
                std::cout << forwardNode->val << "\t";
                #endif
                if (MIN_LEVELS == level) {
                    delete forwardNode;
                    forwardNode = nullptr;
                }
            }
        }
        #ifndef REMOVE_ALL_ELEMENTS_EQUALS_TO_TARGET
        return ret;
        #else
        if (!ret) {
            #ifdef DEBUG
            std::cout << "no found " << num << "\n";
            #endif
            return ret;
        }
        while (ret) {
            ret = erase(num, true);
        }
        return recursive ? ret : true;
        #endif
    }

private:
    std::vector<std::pair<Node*, int>> iterator(int const num) {
        std::vector<std::pair<Node*, int>> ans;
        Node* cur = head;
        for (int level = MAX_LEVELS; level >= MIN_LEVELS; level--) {
            while (true) {
                // find at the level level, the last node whose val is less than num, which means its next node.val >= num
                Node * forwardNode = cur->levels[level];
                if (nullptr != forwardNode && forwardNode->val < num) {
                    cur = forwardNode;
                } else {
                    break;
                }
            }
            ans.emplace_back(std::make_pair(cur, level));
        }
        return ans;
    }
private:
    Node * head = nullptr;
    static int const DUMMY_NODE_VAL = INT_MIN;
    static int const MAX_LEVELS = 16; // included, so the total level will be MAX_LEVELS + 1
    static int const MIN_LEVELS = 0;
};

class Skiplist {
protected:
    const int kMaxLevelNum = 12;
    struct Node {
        int value_;
        Node *next_[kMaxLevelNum];
    };
public:
    Skiplist() {
        head_ = new Node();
        head_->value_ = -1;
        auto *tail = new Node();
        tail->value_ = 1;
        memset(tail->next_, 0, kMaxLevelNum * sizeof(void *));
        for (int i = 0; i < kMaxLevelNum; i++) {
            head_->next_[i] = tail;
        }
    }

    bool search(int target) {
        Node *prev[kMaxLevelNum];
        return DoSearch(target, prev) != nullptr;
    }

    void add(int num) {
        Node *prev[kMaxLevelNum];
        Node *ge_node = FindGreaterOrEqual(num, prev);
        Node *node = new Node();
        node->value_ = num;

        int height = RandomHeight();
        for (int i = 0; i < height; i++)
        {
            node->next_[i] = prev[i]->next_[i];
            prev[i]->next_[i] = node;
        }
    }

    bool erase(int num) {
        Node *prev[kMaxLevelNum];
        auto *ge_node = DoSearch(num, prev);
        if (ge_node == nullptr) {
            return false;
        }

        for (int i = 0; i < kMaxLevelNum; i++) {
            if (ge_node->next_[i] == nullptr) {
                break;
            }
            prev[i]->next_[i] = ge_node->next_[i];
            ge_node->next_[i] = prev[i];
        }
        delete ge_node;
        return true;
    }

    void PrintAll() {
        auto* cur_node = head_->next_[0];

        int counter = 1;
        std::vector<Node*> node_list;

        std::string debug_str[kMaxLevelNum];
        for (int i=0; i<kMaxLevelNum; i++) {
            debug_str[i] += "|";
        }

        printf("%p, ",head_);
        while (cur_node->next_[0] != nullptr) {
            char buf[100];
            sprintf(buf, "%-2d", cur_node->value_);
            debug_str[0] += " -> ";
            debug_str[0] += buf;
            node_list.emplace_back(cur_node);
            printf("%p, ",cur_node);
            cur_node = cur_node->next_[0];
        }
        printf("%p, ",cur_node);
        printf("\n");
        debug_str[0] += "-> |";

        cur_node = head_;
        for (int i=1; i<kMaxLevelNum; i++) {
            debug_str[i] = "|";
            auto* cur_left_node = head_;
            for (auto* node: node_list) {
                printf("node: %p, left: %p, left->next[i]: %p\n", node, cur_left_node, cur_left_node->next_[i]);
                printf("node: %d, left: %d\n", node->value_, cur_left_node->next_[i]->value_);
                if (node == cur_left_node->next_[i]) {
                    printf("true\n");
                    char buf[100];
                    sprintf(buf, "%-2d", node->value_);
                    debug_str[i] += " -> ";
                    debug_str[i] += buf;
                    cur_left_node = node;
                } else {
                    printf("false\n");
                    debug_str[i] += "------";
                }
            }
            debug_str[i] += "-> |";
        }
        for (int i = kMaxLevelNum - 1; i >= 0; i--) {
            printf("level: %d: %s\n", i, debug_str[i].c_str());
        }
        printf("\n");
    }

private:
    Node *head_;
    int cur_max_level_ = 0;

    int RandomHeight() {
        static std::mt19937 mt_rand(0);
        int height = 1;
        while (height < kMaxLevelNum and mt_rand() & 0x1) {
            height++;
        }
        return height;
    }

    Node *DoSearch(int target, Node **prev) {
        Node *ge_node = FindGreaterOrEqual(target, prev);
        if (ge_node->next_[0] != nullptr and ge_node->value_ == target) {
            return ge_node;
        } else {
            return nullptr;
        }
    }

    //返回值应当是比key大的最小的数，prev是一个长度为kMaxHeight的数组，保存每层比key小的数的指针。最后是要利用这个指针把当前的key嵌入进去的。
    Node *FindGreaterOrEqual(int target, Node **prev) {
        int level = kMaxLevelNum - 1;
        Node *cur_node = head_;
        while (true) {
            auto *next = cur_node->next_[level];
            if (next == nullptr) { // right edge
                return cur_node;
            } else if (next->next_[level] == nullptr or next->value_ >= target) {
                //right node is right edge or is larger
                if (level == 0) {
                    prev[level] = cur_node;
                    return next;
                } else {
                    prev[level] = cur_node;
                    level--;
                }
            } else { //(next->value_ < target)
                cur_node = next;
            }
        }
    }
};

const int MAX_LEVEL = 20;

struct Node {
    Node* go[MAX_LEVEL];
    int val;
    int cnt;

    Node(int v): val(v), cnt(1) {
        fill(go, go + MAX_LEVEL, nullptr);
    }
};

int get_level() {
    int res = 0;
    while (res + 1 < MAX_LEVEL && rand() % 2 == 0) {
        res++;
    }
    return res;
}

class Skiplist {
public:
    bool search(int target) {
        Node* cur = head;
        int level = MAX_LEVEL - 1;
        for (;;) {
            if (cur->val == target) {
                return cur->cnt != 0;
            }
            if (cur->go[level] == nullptr || cur->go[level]->val > target) {
                level--;
            } else {
                cur = cur->go[level];
            }
            if (level < 0) {
                break;
            }
        }
        return false;
    }

    void add(int num) {
        Node* cur = head;
        int level = MAX_LEVEL - 1;
        Node* at_level[MAX_LEVEL];
        for (;;) {
            if (cur->val == num) {
                cur->cnt++;
                // print();
                return;
            }
            at_level[level] = cur;
            if (cur->go[level] == nullptr || cur->go[level]->val > num) {
                level--;
            } else {
                cur = cur->go[level];
            }
            if (level < 0) {
                break;
            }
        }
        Node* v = new Node(num);
        int lvl = get_level();
        for (int i = 0; i <= lvl; i++) {
            v->go[i] = at_level[i]->go[i];
            at_level[i]->go[i] = v;
        }
        // print();
    }

    bool erase(int num) {
        Node* cur = head;
        int level = MAX_LEVEL - 1;
        for (;;) {
            if (cur->val == num) {
                if (cur->cnt == 0) {
                    return false;
                }
                cur->cnt--;
                return true;
            }
            if (cur->go[level] == nullptr || cur->go[level]->val > num) {
                level--;
            } else {
                cur = cur->go[level];
            }
            if (level < 0) {
                break;
            }
        }
        return false;
    }
private:
    Node* head = new Node(-1);

    void print() {
        for (auto v = head; v != nullptr; v = v->go[0]) {
            cout << v->val << " " << v->cnt << endl;
            for (int i = 0; i < MAX_LEVEL; i++) {
                cout << (v->go[i] == nullptr ? -1 : v->go[i]->val) << " ";
            }
            cout << endl;
        }
        cout << "_____________" << endl;
    }
};

struct Node {
    Node *right, *down;
    int val;
    Node(Node *right, Node *down, int val): right(right), down(down), val(val) {}
};

class Skiplist {
    // plagiarizing from https://leetcode.com/problems/design-skiplist/discuss/400028/C%2B%2B-SkipList.-2-pointer-for-each-node.-64ms.
    Node* head;

public:
    Skiplist(): { head = new Node(NULL, NULL, 0); }

    bool search(int num) {
        Node *p = head;
        while(p) {
            while(p->right and p->right->val < num) p = p->right;
            if(!p->right or p->right->val > num) p = p->down;
            else return true;
        }
        return false;
    }

    void add(int num) {
        insertPoints.clear();
        Node *p = head;
        while(p) {
            while(p->right and p->right->val < num) p = p->right;
            insertPoints.push_back(p);
            p = p->down;
        }

        Node* downNode = NULL;
        bool insertUp = true;
        while(insertUp and insertPoints.size()) {
            Node *ins = insertPoints.back();
            insertPoints.pop_back();

            ins->right = new Node(ins->right, downNode, num);
            downNode = ins->right;

            insertUp = (rand() & 1) == 0;
        }
        if(insertUp) {
            head = new Node(new Node(NULL, downNode, num), head, 0);
        }
    }
    vector<Node*> insertPoints;

    bool erase(int num) {
        Node *p = head;
        bool seen = false;
        while(p) {
            while(p->right and p->right->val < num) p = p->right;
            if(!p->right or p->right->val > num) p = p->down;
            else {
                seen = true;
                p->right = p->right->right;
                p = p->down;
            }
        }
        return seen;
    }
};

struct Node {
    Node* next;
    Node* son;
    int data;
    Node(int data = -1, Node* next = NULL, Node* son = NULL): data(data), next(next), son(son) {};
};

class Skiplist {
public:
    Node* head;
    vector<Node*> preStack;
    Skiplist() {
        this->head = new Node();
    }

    bool search(int target) {
        Node* pre = head;
        while (pre) {
            while (pre->next) {
                if (pre->next->data == target) {
                    return true;
                } else if (pre->next->data < target) {
                    pre = pre->next;
                } else {
                    break;
                }
            }
            pre = pre->son;
        }
        return false;
    }

    void add(int num) {
        preStack.clear();
        Node* pre = head;
        while (pre) {
            while (pre->next) {
                if (pre->next->data >= num) {
                    preStack.push_back(pre);
                    break;
                } else {
                    pre = pre->next;
                }
            }
            pre = pre->son;
        }
        bool insertUp = true;
        Node* newNode = NULL;
        while (insertUp && preStack.size()) {
            Node *pre = preStack.back();
            preStack.pop_back();
            newNode = new Node(num, pre->next, newNode);
            pre->next = newNode;

            insertUp = (rand() & 4) == 0;
        }
        if (insertUp) {
            head = new Node(-1, new Node(num, NULL, newNode), head);
        }
    }

    bool erase(int num) {
        Node* pre = head;
        Node* preHead = NULL;
        Node* preFather = NULL;
        bool result = false;
        while (pre) {
            while (pre->next) {
                if (pre->next->data == num) {
                    if (preFather == NULL) {
                        preHead = preFather = pre->next;
                        pre->next = pre->next->next;
                        result = true;
                        break;
                    } else if(preFather->son != pre->next) {
                        pre = pre->next;
                    } else {
                        preFather = pre->next;
                        pre->next = pre->next->next;
                        result = true;
                        break;
                    }
                } else if (pre->next->data < num) {
                    pre = pre->next;
                } else {
                    break;
                }
            }
            pre = pre->son;
        }
        return result;
    }
};
