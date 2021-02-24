#include "../../head.h"


class Solution__O_N {
public:
    Node* connect(Node* root) {
        if (nullptr == root) {
            return root;
        }
        std::queue<Node*> que;
        que.push(root);
        int size = 0;
        while (JUST_ZERO != (size = que.size())) {
            Node* pre = nullptr;
            while (size--) {
                Node* cur = que.front(); que.pop();
                if (nullptr != pre) {
                    pre->next = cur;
                }
                if (nullptr != cur->left) {
                    que.push(cur->left);
                }
                
                if (nullptr != cur->right) {
                    que.push(cur->right);
                }
                pre = cur;
            }
        }
        return root;
    }
private:
    static int const JUST_ZERO = 0;
};
// #define DEBUG
class Solution {
public:
    Node* connect(Node* root) {
        // plagiarizing idea from https://youtu.be/68RmOoq-OSs
        if (nullptr == root) {
            return root;
        }
        Node *leftMost = root;
        Node *pre = nullptr, *cur = nullptr;
        while (leftMost) {

            #ifdef DEBUG
            if (leftMost) {
                std::cout << "leftMost: " << leftMost->val << "\n";
            }
            #endif
            
            cur = leftMost;
            leftMost = nullptr;
            pre = nullptr;

            while (cur) {
                if (cur->left) {
                    if (nullptr == leftMost) {
                        leftMost = cur->left;
                    }
                    if (pre) {
                        pre->next = cur->left;
                    }
                    pre = cur->left;
                }

                if (cur->right) {
                    if (nullptr == leftMost) {
                        leftMost = cur->right;
                    }
                    if (pre) {
                        pre->next = cur->right;
                    }
                    pre = cur->right;
                }
                cur = cur->next;
            }
        }

        return root;
    }
};
