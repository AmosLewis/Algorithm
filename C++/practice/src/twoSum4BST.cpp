/*
Given a Binary Search Tree and a target number, return true if there exist two elements in the BST such that their sum is equal to the given target.

Example 1:
Input: 
    5
   / \
  3   6
 / \   \
2   4   7

Target = 9

Output: True
Example 2:
Input: 
    5
   / \
  3   6
 / \   \
2   4   7

Target = 28

Output: False
*/

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
    bool findTarget(TreeNode* root, int k) {
        if(!root) return false;
        // hash表查找，把树中的所有对值放入unordered_set
        // 为什么不用unordered_map 因为返回bool，不用记录ID
        unordered_set<int> my_set;
        
        return dfs_tree(root, k, my_set);
    }
    
    bool dfs_tree(TreeNode* node, int target, unordered_set<int>& my_set)
    {
        // 每个节点都要边界检查
        if(!node) return false;
        // 要先查找， 再插入，避免找到自己
        int tmp = target - node->val;
        if(my_set.count(tmp)) return true;
        
        my_set.insert(node->val);
        
        return dfs_tree(node->left, target, my_set) || dfs_tree(node->right, target, my_set);
    }
};
