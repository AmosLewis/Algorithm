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
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        return helper(inorder, 0, inorder.size() - 1, postorder, 0, postorder.size() - 1);
    }
    
    TreeNode* helper(vector<int>& inorder, int iLeft, int iRight,
                    vector<int>& postorder, int pLeft, int pRight)
    {
        if(iRight < iLeft || pRight < pLeft )
        {
            return nullptr;
        }
        TreeNode *curRoot = new TreeNode(postorder[pRight]);
        int iRoot = 0;
        for(iRoot = iLeft; iRoot <= iRight; iRoot++)
        {
            if(postorder[pRight] == inorder[iRoot])
            {
                break;
            }
        }
        
        curRoot->left = helper(inorder, iLeft, iRoot - 1, postorder, pLeft, pRight - (iRight - iRoot) - 1);
        curRoot->right = helper(inorder, iRoot + 1, iRight, postorder, pRight - (iRight - iRoot), pRight - 1);
        
        return curRoot;
    }
};

// inorder =   [9,    |3|,    15,    20,     7]
//            iLeft   iRoot                   iRight
// postorder = [9,   |15,      7,    20,|    3]
//              pLeft                        pRight
//                                           pRoot
