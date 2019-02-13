
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
            if(abs(res - target) >= abs(root->val - target))
            {
                res = root->val;
            }
            root = root->val > target ? root->left : root->right;
        }
        return res;
    }
};
