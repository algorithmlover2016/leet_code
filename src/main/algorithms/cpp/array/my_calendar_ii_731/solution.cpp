#include "../../head.h"

#define TEST_MAIN

/*
class MyCalendarTwo {
private:
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

public:
    // plagiarizing idea from https://leetcode.com/problems/my-calendar-ii/discuss/109519/JavaC%2B%2B-Clean-Code-with-Explanation
    MyCalendarTwo() {
    }

    bool book(int start, int end) {
        MyCalendar myCal;
        for (auto const & bookEle : booked) {
            int internalStart = std::max(start, bookEle.first);
            int internalEnd = std::min(end, bookEle.second);

            if (internalStart < internalEnd) {
                // have repeat once
                if (!myCal.book(internalStart, internalEnd)) {
                    return false;
                }
            }
        }
        booked.emplace_back(std::make_pair(start, end));
        return true;
    }
private:
    std::vector<std::pair<int, int>> booked;
};

class MyCalendarTwo {
public:
    // plagiarizing from https://leetcode.com/problems/my-calendar-ii/discuss/109530/N2-Python-Short-and-Elegant
    MyCalendarTwo() {
    }

    bool book(int start, int end) {
        for (auto const & overLap : overLapBookeds) {
            int intervalStart = std::max(start, overLap.first);
            int intervalEnd = std::min(end, overLap.second);
            if (intervalStart < intervalEnd) {
                return false;
            }
        }
        for (auto const & book : booked) {
            int intervalStart = std::max(start, book.first);
            int intervalEnd = std::min(end, book.second);
            if (intervalStart < intervalEnd) {
                overLapBookeds.emplace_back(std::make_pair(intervalStart, intervalEnd));
            }
        }
        booked.emplace_back(std::make_pair(start, end));
        return true;
    }

private:
    std::vector<std::pair<int, int>> booked;
    std::vector<std::pair<int, int>> overLapBookeds;
};
*/

class MyCalendarTwo {
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
    // plagiarizing from https://leetcode.com/problems/my-calendar-ii/discuss/109530/N2-Python-Short-and-Elegant
    MyCalendarTwo() {
    }

    bool book(int start, int end) {
        for (auto const & book : booked) {
            int intervalStart = std::max(start, book.first);
            int intervalEnd = std::min(end, book.second);
            if (intervalStart < intervalEnd) {
                Node * newNode = new Node(intervalStart, intervalEnd);
                if (!dfs(newNode, root)) {
                    return false;
                }
            }
        }
        booked.emplace_back(std::make_pair(start, end));
        return true;
    }
private:
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
    struct Node * root;
    std::vector<std::pair<int, int>> booked;
};

#ifdef TEST_MAIN
#define PRINT_SCREEN
int main() {
    MyCalendarTwo obj;
    assert(true == obj.book(10, 20));
    assert(true == obj.book(50, 60));
    assert(true == obj.book(10, 40));
    assert(false == obj.book(5, 15));
    assert(true == obj.book(5, 10));
    assert(true == obj.book(25, 55));
#ifdef PRINT_SCREEN
    std::cout << "Test Successfully" << std::endl;
#endif
    return 0;
}
#endif
