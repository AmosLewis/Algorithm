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


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

//O(n)
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        if(!root) return true;
        
        // 设置一个全局变量，在递归的过程中设置它
        bool balanced = true;
        
        int height_all = height(root, &balanced);
        
        return balanced;
    }
    
    int height(TreeNode* node, bool* balanced)
    {
        if(!node) return 0;
        // 递归求高度
        int height_left = height(node->left, balanced);
        int height_right = height(node->right, balanced);
        if(abs(height_left - height_right) > 1)
        {
            // 在递归的过程中设置全局变量
            *balanced = false;
            // 一旦发现不满足条件， 立马返回
            return -1;
        }
        // 高度定义 左右子树最大值+1
        return max(height_left, height_right) + 1;
    }
    
};
