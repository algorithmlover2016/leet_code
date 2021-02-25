#include "../../head.h"


class MyCalendar {
public:
    MyCalendar() {
    }

    bool book(int start, int end) {
        for (auto const & bookEle : booked) {
            if (start >= bookEle.second || end <= bookEle.first) {
                continue;
            }
            return false;
        }
        booked.emplace_back(std::make_pair(start, end));
        return true;
    }
    /*
    bool book(int start, int end) {
        for (auto const & bookEle : booked) {
            if (start < bookEle.second && end > bookEle.first) {
                return false;
            }
        }
        booked.emplace_back(std::make_pair(start, end));
        return true;
    }
    */
private:
    std::vector<std::pair<int, int>> booked;
};

class MyCalendar {
private:
    struct Node {
        int start;
        int end;
        Node *left = nullptr;
        Node *right = nullptr;
        Node(int start_ = 0, int end_ = 0, Node *left_ = nullptr, Node *right_ = nullptr) :
            start(start_), end(end_), left(left_), right(right_) {
        }
    };
public:
    MyCalendar() {
    }

    bool book(int start, int end) {
        // plagiarizing idea from https://youtu.be/YZdIwAEtgIY
        Node * newNode = new Node(start, end);
        return dfs(newNode, root);
    }

    bool dfs(struct Node * node, struct Node * & root) {
        if (nullptr == root) {
            root = node;
            return true;
        }
        if (node->end <= root->start) {
            // left
            if (nullptr == root->left) {
                root->left = node;
                return true;
            } else {
                return dfs(node, root->left);
            }
        } else if (node->start >= root->end) {
            // right
            if (nullptr == root->right) {
                root->right = node;
                return true;
            } else {
                return dfs(node, root->right);
            }
        } else {
            return false;
        }
    }
private:
    struct Node * root = nullptr;
};
