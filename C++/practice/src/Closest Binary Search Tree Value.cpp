http://www.cnblogs.com/grandyang/p/5237170.html
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int closestValue(TreeNode* root, double target) {
        // 利用BST的性质 小的往左，大的往右
        // 法1是用循环的方法 用root迭代就好了
        int res = root->val;
        while(root)
        {
            // 更新返回值
            if(abs(res - target) >= abs(root->val - target))
            {
                res = root->val;
            }
            // 小的往左，大的往右
            root = root->val > target ? root->left : root->right;
        }
        return res;
    }
};


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int closestValue(TreeNode* root, double target) {
        // 法2 递归的解法
        int a = root->val;
        TreeNode* t = target < a ? root->left : root->right;
        
        // 递归的返回条件，到叶子节点
        if(!t) return a;
        // 递归，找出子树中的最近的值
        int b = closestValue(t, target);
        // 比较当前node与其子node关系返回点，谁更小就返回谁
        return abs(a-target) < abs(b-target) ? a : b; 
    }
};
