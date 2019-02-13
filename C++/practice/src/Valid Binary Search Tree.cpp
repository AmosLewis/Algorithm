// https://www.youtube.com/watch?v=Jq0Wk9xeQ0U
// easy
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
    bool isValidBST(TreeNode* root) {
        return isValidBST(root, nullptr, nullptr);
    }
    
    bool isValidBST(TreeNode* root, int* min_val, int* max_val) {
        if(!root) return true;
        if((min_val && root->val <= *min_val) ||
          (max_val && *max_val <= root->val)) return false;
        
        return isValidBST(root->left, min_val, &root->val) &&
            isValidBST(root->right, &root->val, max_val);
    }
};
