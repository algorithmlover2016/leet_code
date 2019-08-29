class Solution {
  
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* re=nullptr;
        dfs(root,p,q,re);
        return re;
    }
    int dfs(TreeNode* root, TreeNode* p, TreeNode* q,TreeNode*& re){
        if(!root) return 0;
        if(re) return 0;
        int count=0;
        if(root==p || root==q) count++;
        count += dfs(root->left,p,q,re);
        count += dfs(root->right,p,q,re);
        if(count==2 && re == nullptr) re = root;
        return count;
    }
};
