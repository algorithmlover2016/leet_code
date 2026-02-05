#include <iostream>
#include <vector>
#include <stack>
#include <climits> 

using namespace std;

// 递归版本 - O(N^2)
class SolutionRecursive {
public:
    bool verifyPreorder(vector<int>& preorder) {
        if (preorder.empty()) return true;
        return help(preorder, 0, preorder.size() - 1);
    }

private:
    bool help(const vector<int>& preorder, int start, int end) {
        if (start >= end) {
            return true;
        }

        int rootVal = preorder[start];
        
        // 1. 找到第一个大于根节点的值的位置，作为左右子树的分界点
        int i = start + 1;
        while (i <= end && preorder[i] < rootVal) {
            i++;
        }
        
        int splitIndex = i;

        // 2. 检查右子树部分（splitIndex 到 end）是否所有值都大于根节点
        while (i <= end) {
            if (preorder[i] < rootVal) {
                return false;
            }
            i++;
        }

        // 3. 递归检查左右子树
        return help(preorder, start + 1, splitIndex - 1) && 
               help(preorder, splitIndex, end);
    }
};

// 栈版本 - O(N) - 推荐解法
class SolutionStack {
public:
    bool verifyPreorder(vector<int>& preorder) {
        stack<int> stk;
        int lower_bound = INT_MIN;

        for (int val : preorder) {
            if (val < lower_bound) {
                return false;
            }

            while (!stk.empty() && val > stk.top()) {
                lower_bound = stk.top();
                stk.pop();
            }

            stk.push(val);
        }

        return true;
    }
};

