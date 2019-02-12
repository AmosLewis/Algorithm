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
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        int data = p->val;
        // 找到这个值所在的节点O(h)
        TreeNode* current = Find(root, data);
        if(current == NULL) return nullptr;
        // case1 : Node 有右子树
        if(current->right != nullptr)
        {
            TreeNode* temp = current->right;
            // 找到右节点的最左节点 O(h)
            while(temp->left != nullptr) temp = temp->left;
            return temp;
        }else
        {
            // case2: Node 没有右子树 O(h)
            // 两根指针，一前一后向下找
            TreeNode* successor = nullptr;
            TreeNode* ancestor = root;
            // ancestor 最终落到current上
            while(ancestor != current)
            {
                // ancestor太大，向左边走，让它变小，
                // 并用第二根指针记录此时的最深的successor
                if(ancestor->val > current->val)
                {
                    successor = ancestor;
                    ancestor = ancestor->left;
                }
                else
                {
                    // ancestor 太小，向右走让他变大
                    ancestor = ancestor->right;
                }
            }
            return successor;
        }  
    }
    
    TreeNode* Find(TreeNode* node, int data)
    {
        if(node->val == data)
        {
           return node; 
        }else if(node->val > data)
        {
            return Find(node->left, data);
        }else
        {
            return Find(node->right, data);
        }
        
    }
    
    
};
