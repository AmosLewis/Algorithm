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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if(preorder.size() != inorder.size() || preorder.empty() || inorder.empty())
        {
            return nullptr;
        }
        return helper(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
    }
    TreeNode* helper(vector<int>& preorder, // 当前子树根是preorder[ps]
                     int ps, int pe,        // 当前子树在preorder 当前左右边界
                     vector<int>& inorder,  
                     int is, int ie)        // 当前子树 inoder 当前左右边界
    {
        if(is > ie || ps > pe )
        {
            return nullptr;
        }
        int ir = 0; // current root id in inoder
        // 找到该根在inorder中的位置
        for(ir = is; ir <= ie; ir++)
        {
            if(inorder[ir] == preorder[ps])
            {
                break;
            }
        }
        // 新建这个根
        TreeNode* curRoot = new TreeNode(preorder[ps]);
        // 分别递归新建左子树和右子树
        curRoot->left = helper(preorder, ps + 1, ps + ir - is, inorder, is, ir - 1);
        curRoot->right = helper(preorder, ps + ir - is + 1, pe, inorder, ir + 1, ie);
        // 返回已经建立好的子树
        return curRoot;
    }
};
//              3
//          /       \
//          4         5
//       /   \     /   \
//     6      7    8    9
//
// preorder: 3 | 4 6 7  | 5 8 9
//           ps               pe
//                           pspe
//              
// inorder:  6   4 7 3    8 5 9
//           is      ir       ie
//           s . ir e
//          es/ir
//                        s ir e
//                           isirie
//                             ie is
//





