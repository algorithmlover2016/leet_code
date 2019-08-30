class Solution {
public:
    TreeNode* recoverFromPreorder(std::string S) {
        if (S.size() == 0) {
            return nullptr;
        }
        std::vector<TreeNode*> stack;
        stack.emplace_back(new TreeNode(0));
        for (size_t index = 0; index < S.size(); ) {
            int level = findDashes(S, index)  + 1;
            while(stack.size() > level) {
                stack.pop_back();
            }
            TreeNode* node = new TreeNode(getNum(S, index));
            if (nullptr == stack.back()->left) {
                stack_back->left = node;
            } else {
                stack_back->right = node;
            }
        }
        return stack[0]->left;
    }

    int findDashes(std::string const & s, size_t & start) {
        int num = 0;
        while (start < s.size() && '-' == s[start]) {
            num++;
            start++;
        }
        return num;
    }

    int getNum(std::string const & s, size_t & start) {
        int num = 0;
        while (start < s.size() && isdigit(s[start])) {
            num = num * 10 + (s[start++] - '0');
        }
        return num;
    }

};

class Solution_recursion {
public:
    TreeNode* recoverFromPreorder(std::string S) {
        std::vector<int> vec = proc(S);
        int i=0;
        return helper(vec, i, 0);
    }

    // parse the string to <level, val> pair
    sted::vector<int> proc(std::string s) {
        std::vector<int> res;
        int i = 0;
        int dcount = 0;
        int num = 0;
        while (i < s.length()) {
            if (s[i] == '-') {
                if (s[i-1] != '-') {
                    res.push_back(num);
                    num=0;
                }
                dcount++;
            } else {
                if (i == 0 || s[i-1] == '-') {
                    res.push_back(dcount);
                    dcount=0;
                }
                num = 10 * num + (s[i] - '0');
            }
            i++;
        }
        res.push_back(num);
        return res;
    }
    TreeNode* helper(std::vector<int> const & vec, int & i, int lvl) {
        if (i >= vec.size() || lvl != vec[i]) {
            return NULL;
        }
        int num = vec[++i++];
        TreeNode* root = new TreeNode(num);
        root->left = helper(vec, i, lvl + 1);
        root->right = helper(vec, i, lvl + 1);
        return root;
    }
};
