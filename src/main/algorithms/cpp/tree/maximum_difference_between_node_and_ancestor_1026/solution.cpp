class Solution {
public:
    int maxAncestorDiff(TreeNode* root) {
        dfsPostOrderTraversal(root);
        return res;
    }
    std::pair<int, int> dfsPostOrderTraversal(TreeNode * root) {
        if (nullptr == root) {
            // first is min, and second is max
            return std::make_pair(INT_MAX, INT_MIN);
        }
        std::pair<int, int> left = dfsPostOrderTraversal(root->left);
        std::pair<int, int> right = dfsPostOrderTraversal(root->right);
        int minEle = std::min(left.first, right.first);
        if (INT_MAX == minEle) {
            minEle = root->val;
        }
        int maxEle = std::max(left.second, right.second);
        if (INT_MIN == maxEle) {
            maxEle = root->val;
        }
        int diff = int(std::max(std::abs(root->val - minEle), std::abs(root->val - maxEle)));
        if (diff > res) {
            res = diff;
        }
        return {std::min(minEle, root->val), std::max(maxEle, root->val)};
    }
private:
    int res = INT_MIN;
};

class Solution_0ms {
public:
    int maxAncestorDiff(TreeNode* root) {
        return helper(root, root->val, root->val);
    }

    int helper(TreeNode* root, int l, int h) {
        // from top to buttom
        l = std::min(l, root->val);
        h = std::max(h, root->val);
        if (!root->left && !root->right) return h-l;
        int left = (root->left) ? helper(root->left, l, h) : 0;
        int right = (root->right) ? helper(root->right, l, h) : 0;
        return std::max(left, right);
    }
};

class solution_oneline {
public:
    int maxAncestorDiff(TreeNode* r, int mn = 100000, int mx = 0) {
        return r ? max(maxAncestorDiff(r->left, min(mn, r->val), max(mx, r->val)),
        maxAncestorDiff(r->right, min(mn, r->val), max(mx, r->val))) : mx - mn;
    }
};
