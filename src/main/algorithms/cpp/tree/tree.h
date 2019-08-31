#ifndef LEETCODE_TREE_TREENODE_H
#define LEETCODE_TREE_TREENODE_H
/**
 * Definition for a binary tree node.
 */
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };
#endif
