#include "../../head.h"
#include "../tree.h"


#define DEBUG
#define TEST_MAIN
class Solution {
public:
    TreeNode* str2tree(std::string const & str) {
        if (str.empty()) {
            return nullptr;
        }
        int num = 0;
        int idx = 0;
        int negFlag = 1;
        while (idx < str.size()) {
            if (0 == idx && ('-' == str[idx])) {
                idx++;
                negFlag = -1;
            } else if (std::isdigit(str[idx])) {
                num = num * 10 + str[idx++] - OFFSET;
            } else {
                break;
            }
        }
        num *= negFlag;
        TreeNode* root = new TreeNode(num);
        if (idx == str.size() || '(' != str[idx]) {
            return root;
        }

        int startIdx = idx; // skip the ( char
        int parentTheseCnt = 0;
        bool setLeft = false;
        for (; idx < str.size(); idx++) {
            if ('(' == str[idx]) {
                parentTheseCnt++;
            } else if (')' == str[idx]) {
                parentTheseCnt--;
            }
            if (0 == parentTheseCnt) {
                // we find a subtree
                if (!setLeft) {
                    root->left = str2tree(str.substr(startIdx + 1, idx - startIdx - 1));
                    setLeft = true;
                    startIdx = idx + 1; // the next character is (, we need skip the next character
                    parentTheseCnt = 0;
                } else {
                    root->right = str2tree(str.substr(startIdx + 1, idx - startIdx - 1));
                }
            }
        }
        return root;
    }
private:
    static int const OFFSET = '0';
};

class SolutionStack {
public:
    TreeNode* str2tree(std::string const & str) {
        if (str.empty()) {
            return nullptr;
        }
        std::vector<TreeNode*> parentsNode;
        int idx = 0;
        int const strSize = str.size();
        TreeNode* dummyNode = new TreeNode(INT_MIN);
        while (idx < strSize) {
            if ('-' == str[idx]) {
                // meet a negative number
                idx++;
                int num = 0;
                while (idx < strSize && std::isdigit(str[idx])) {
                    num = num * 10 + str[idx] - OFFSET;
                    idx++;
                }
                parentsNode.emplace_back(new TreeNode(-num));
                idx--;
            } else if (std::isdigit(str[idx])) {
                // meet a positive number
                int num = 0;
                while (idx < strSize && std::isdigit(str[idx])) {
                    num = num * 10 + str[idx] - OFFSET;
                    idx++;
                }
                parentsNode.emplace_back(new TreeNode(num));
                idx--;
            } else if (')' == str[idx]) {
                if (idx > 0 && '(' == str[idx - 1]) {
                    parentsNode.emplace_back(dummyNode);
                }
                TreeNode* cur = parentsNode.back();
                parentsNode.pop_back();
                if (!parentsNode.empty()) {
                    TreeNode* parent = parentsNode.back();
                    if (nullptr == parent->left) {
                        parent->left = cur;
                    } else {
                        parent->right = cur;
                    }
                }
            }
            idx++;
        }
        TreeNode* root = parentsNode.back();
#ifdef DEBUG
        if (nullptr != root) {
            std::cout << root->val << " root\n";
        }
#endif
        if (nullptr == root || root == dummyNode) {
            root = nullptr;
        }
        adjust(root, dummyNode);
        delete dummyNode;
        dummyNode = nullptr;

        return root;
    }
private:
    void adjust(TreeNode* root, TreeNode* dummyNode) {
        if (nullptr == root) {
            return;
        }
        if (root->left == dummyNode) {
            root->left = nullptr;
        }
        if (root->right == dummyNode) {
            root->right = nullptr;
        }
        adjust(root->left, dummyNode);
        adjust(root->right, dummyNode);
    }

private:
    static int const OFFSET = '0';
};

#ifdef TEST_MAIN
void printTree(TreeNode* root) {
    if (nullptr == root) {
        return;
    }
    std::cout << root->val << ", ";
    printTree(root->left);
    printTree(root->right);
}
#define PRINT_TO_SCREEN
#define TEST_STACK_SOLUTION
int main() {
#ifdef TEST_STACK_SOLUTION
    SolutionStack obj;
#else
    Solution obj;
#endif

    std::string str("4(2(3)(1))(6(5))");
    TreeNode* root = obj.str2tree(str);
#ifdef PRINT_TO_SCREEN
    printTree(root);
    std::cout << "\n" << str << " done\n";
#endif

    str = "4(2(3)(1))(6(5)(7))";
    root = obj.str2tree(str);
#ifdef PRINT_TO_SCREEN
    printTree(root);
    std::cout << "\n" << str << " done\n";
#endif

    str = "-4(-2(3)(-1))(6(-5)(7))";
    root = obj.str2tree(str);
#ifdef PRINT_TO_SCREEN
    printTree(root);
    std::cout << "\n" << str << " done\n";
#endif

    str = "-4(-2(3)())(6(-5)(7))";
    root = obj.str2tree(str);
#ifdef PRINT_TO_SCREEN
    printTree(root);
    std::cout << "\n" << str << " done\n";
#endif

    // std::cout << "TEST SUCCESSFULLY" << std::endl;
    return 0;
}
#endif
