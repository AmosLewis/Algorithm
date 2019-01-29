/*
Given a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.

Example:

Input: [1,2,3,null,5,null,4]
Output: [1, 3, 4]
Explanation:

   1            <---
 /   \
2     3         <---
 \     \
  5     4       <---
/*
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
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
    vector<int> rightSideView(TreeNode* root) {
        // 要宽搜二叉树，并且用一个数组记录下二叉树没一行最后一个节点
        // 这个数组可以是一个vector<pair<int, int>>对每个节点定义一个pair对，对应其行数
        // 优化空间复杂度后，只用一个vector<int> 记录，层数是ID，值是内容
        // 并对每一层的节点迭代更新这个数组
        // 如何用对同一层反复更新同一个值？用那一层的层ID作为vector的索引
        // 如何判断是开辟新空间还是反复更新旧值?判断depth与vector.size的大小
        if(!root) return {};
        vector<int> view;
        
        queue<pair<TreeNode*, int>> Q;
        
        if(root)
        {
            Q.push(make_pair(root, 0));
        }
        
        while(!Q.empty())
        {
            TreeNode* tmp_node = Q.front().first;
            int depth = Q.front().second;
            Q.pop();
            
            // 后面要建立新pair的时候，对depth+1，depth 和返回数组比较大小
            // 相等说明还没push过， 
            if(depth == view.size()) 
            {
                view.push_back(tmp_node->val);
            }else
            {
                // 不等说明已经push过，可以在同一个位子更新,
                // 用depth索引，可以循环对这一层对应的vector ID多次更新
                view[depth] = tmp_node->val;  
            }  
            
            // 插入新节点,先左后右
            if(tmp_node->left)
            {
                Q.push(make_pair(tmp_node->left, depth + 1));
            }
            if(tmp_node->right)
            {
                Q.push(make_pair(tmp_node->right, depth + 1));
            }
        }
        
         return view;     
    }
    
};
