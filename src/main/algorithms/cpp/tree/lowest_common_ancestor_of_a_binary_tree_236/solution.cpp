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

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // plagiarizing idea from https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/solution/er-cha-shu-de-zui-jin-gong-gong-zu-xian-by-leetc-2/
        TreeNode* ans = nullptr;
        dfs(root, p, q, ans);
        return ans;
    }

    bool dfs(TreeNode* root, TreeNode* p, TreeNode* q, TreeNode* & ans) {
        if (nullptr == root) {
            return false;
        }

        if (nullptr != ans) {
            // have find the lowest common anccessor
            return false;
        }
        bool fLSon = dfs(root->left, p, q, ans);
        bool fRSon = dfs(root->right, p, q, ans);

        bool curEqual = false;
        if (root->val == p->val || root->val == q->val) {
            curEqual = true;
        }

        if ((fLSon && fRSon) || (curEqual && (fLSon || fRSon))) {
            ans = root;
        }

        return fLSon || fRSon || curEqual;
    }
};

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // plagiarizing idea from https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/solution/er-cha-shu-de-zui-jin-gong-gong-zu-xian-by-leetc-2/
        std::unordered_map<int, TreeNode*> val2Node;
        std::unordered_map<int, bool> visited;
        if (nullptr == root) {
            return nullptr;
        }
        val2Node[root->val] = nullptr;
        dfs(root, val2Node);

        while (nullptr != p) {
            visited[p->val] = true;
            p = val2Node[p->val];
        }

        while (nullptr != q) {
            if (visited[q->val]) {
                return q;
            }
            q = val2Node[q->val];
        }
        return nullptr;
    }

    void dfs(TreeNode* root,
            std::unordered_map<int, TreeNode*> & val2Node) {
        if (nullptr == root) {
            return;
        }

        if (nullptr != root->left) {
            val2Node[root->left->val] = root;
            dfs(root->left, val2Node);
        }

        if (nullptr != root->right) {
            val2Node[root->right->val] = root;
            dfs(root->right, val2Node);
        }
    }
};
