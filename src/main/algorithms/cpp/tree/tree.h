#ifndef LEETCODE_TREE_TREENODE_H
#define LEETCODE_TREE_TREENODE_H
/**
 * Definition for a binary tree node.
 */
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

 struct PTreeNode {
     int val;
     PTreeNode *left;
     PTreeNode *right;
     PTreeNode *parent;
     PTreeNode() : val(0), left(nullptr), right(nullptr), parent(nullptr) {}
     PTreeNode(int x) : val(x), left(nullptr), right(nullptr), parent(nullptr) {}
     PTreeNode(int x, PTreeNode *left, PTreeNode *right, PTreeNode* parent_)
         : val(x), left(left), right(right), parent(parent_) {}
 };
#endif
