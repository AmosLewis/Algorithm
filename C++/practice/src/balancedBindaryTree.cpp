/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// O(nlogn)
// 左右子树高度差<=1
// 两次递归
// 先用递归求出树的高度，
// 再递归调用求子树是否balanced
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        if(!root) return true;
        // 先用递归求出树的高度，
        int height_left = height(root->left);
        int height_right = height(root->right);
        
        // 左右子树高度差<=1
        // 再递归调用求子树是否balanced
        return ( abs(height_left-height_right) <= 1) && isBalanced(root->left)
            && isBalanced(root->right);
    }
    
    int height(TreeNode* node)
    {
        if(!node) return 0;
        // 先用递归求出树的高度
        return max(height(node->left),height(node->right)) + 1;
    }
    
};
