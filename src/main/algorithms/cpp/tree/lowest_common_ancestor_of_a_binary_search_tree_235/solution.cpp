/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
#include "../../head.h"
#include "../tree.h"

class Solution_my_stupid {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        one = p;
        another = q;
        dfsPostOrderTraversal(root);
        return ancestor;
    }
    bool dfsPostOrderTraversal(TreeNode* root) {
        if (nullptr == root) {
            return false;
        }
        if (nullptr != ancestor) {
            return false;
        }
        bool left = dfsPostOrderTraversal(root->left);
        bool right = dfsPostOrderTraversal(root->right);
        bool ro = false;
        if (root->val == one->val) {
            findOne = true;
            ro = true;
        } else if (root->val == another->val) {
            findAnother = true;
            ro = true;
        }
        if (((left & right) | (ro & left) | (ro & right)) & findOne & findAnother) {
            ancestor = root;
        }
        return ro | left | right;

    }
    TreeNode* ancestor = nullptr;
    TreeNode* one = nullptr;
    TreeNode* another = nullptr;
    bool findOne = false;
    bool findAnother = false;
};

class solution_24ms {
    public:
        TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || !p || !q) {
            return NULL;
        }

        if (p->val > q->val) {
            std::swap(p, q);
        }

        while (root->val != p->val && root->val != q->val && (root->val < p->val || root->val > q->val)) {
            if (root->val > q->val) {
                root = root->left;
            } else {
                root = root->right;
            }
        }
        return root;
    }
}
class Solution_10ms {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if((p->val <= root->val && q->val >= root->val) || (q->val <= root->val && p->val >= root->val))
            return root;
        if(p->val < root->val && q->val < root->val)
            return lowestCommonAncestor(root->left, p, q);
        return lowestCommonAncestor(root->right, p, q);
    }
};
