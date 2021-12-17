#include "../../head.h"
#include "../tree.h"


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

// #define DEBUG
class Solution {
public:
    TreeNode* canMerge(std::vector<TreeNode*> const & trees) {
        // plagiarizing from https://leetcode.com/problems/merge-bsts-to-create-single-bst/discuss/1330387/Just-do-what-it-says
        std::unordered_map<int, TreeNode*> val2Nodes;
        std::unordered_map<int, int> valCnts;
        for (auto const & it : trees) {
            // The value of each element is distinct, so there is no need to check conflict when inserted into val2Nodes
            val2Nodes[it->val] = it;

            // record the occuring time of leafs; because of unordered_map in std::c++11 will be initialized with zero value
            ++valCnts[it->val];
            if (nullptr != it->left) {
                ++valCnts[it->left->val];
            }
            if (nullptr != it->right) {
                ++valCnts[it->right->val];
            }
        }
        for (auto & it : trees) {
            if (UNIQUE_ROOT == valCnts[it->val]) {
                // the root only appears once and can be treated as root
                #ifdef DEBUG
                std::cout << "root: " << it->val << "\n";
                #endif
                val2Nodes.erase(it->val);
                return (traverse(it, val2Nodes, INT_MIN, INT_MAX) && val2Nodes.empty())? it : nullptr;
            }
        }
        return nullptr;
    }
private:
    bool traverse(TreeNode* root, std::unordered_map<int, TreeNode*> & val2Nodes, int const leftMax, int const rightMin) {
        if (nullptr == root) {
            return true;
        }
        if (root->val >= rightMin || root->val <= leftMax) {
            // because it is strict bst, so root->val > max(leftSubTree->vals) and root->val < min(rightSubTree->vals)
            return false;
        }
        #ifdef DEBUG
        std::cout << "cur: " << root->val << "\n";
        #endif
        if (root->left == root->right) {
            /*root it a leaf, then we can merge other root nodes into this leaf if meeting requirements*/
            auto it = val2Nodes.find(root->val);
            if (it != val2Nodes.end()) {
                #ifdef DEBUG
                std::cout << "leaf add: " << root->val << "\n";
                #endif
                root->left = it->second->left;
                root->right = it->second->right;
                #ifdef DEBUG
                std::cout << "before erase: " << val2Nodes.size() << '\n';
                #endif
                val2Nodes.erase(it);
                #ifdef DEBUG
                std::cout << "after erase: " << val2Nodes.size() << '\n';
                #endif
            }
        }
        return traverse(root->left, val2Nodes, leftMax, root->val) && traverse(root->right, val2Nodes, root->val, rightMin);
    }
private:
    static int const UNIQUE_ROOT = 1;
};

// #define DEBUG
class Solution {
public:
    TreeNode* canMerge(std::vector<TreeNode*> const & trees) {
        // plagiarizing from https://leetcode.com/problems/merge-bsts-to-create-single-bst/discuss/1330387/Just-do-what-it-says
        for (auto const & it : trees) {
            // The value of each element is distinct, so there is no need to check conflict when inserted into val2Nodes
            val2Nodes[it->val] = it;
        }

        for (auto const & it : trees) {
            totalUniqueNodes.insert(it->val);
            addLeafs(it->left);
            addLeafs(it->right);
        }
        for (auto subTreeRoot : root2Leafs) {
            auto it = val2Nodes.find(subTreeRoot->val);
            if (it == val2Nodes.end()) {
                return nullptr;
            }
            subTreeRoot->left = it->second->left;
            subTreeRoot->right = it->second->right;
            val2Nodes.erase(it);
        }
        return (UNIQUE_ROOT == val2Nodes.size() && totalUniqueNodes.size() == validBST(std::begin(val2Nodes)->second)) ? std::begin(val2Nodes)->second : nullptr;
    }
private:
    void addLeafs(TreeNode* node) {
        if (nullptr != node) {
            totalUniqueNodes.insert(node->val);
            if (val2Nodes.find(node->val) != val2Nodes.end()) {
                // this leaf node should be treated as internal to join other tree
                root2Leafs.emplace_back(node);
            }
        }
    }
    int validBST(TreeNode* root,  int const leftMax = INT_MIN, int const rightMin = INT_MAX) {
        if (nullptr == root || root->val >= rightMin || root->val <= leftMax) {
            return 0;
        }
        return 1 + validBST(root->left, leftMax, root->val) + validBST(root->right, root->val, rightMin);
    }
private:
    static int const UNIQUE_ROOT = 1;
    std::unordered_map<int, TreeNode*> val2Nodes;
    std::unordered_set<int> totalUniqueNodes;
    std::vector<TreeNode*> root2Leafs;
};