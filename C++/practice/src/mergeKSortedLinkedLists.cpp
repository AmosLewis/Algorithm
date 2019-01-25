/**
Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.

Example:

Input:
[
  1->4->5,
  1->3->4,
  2->6
]
Output: 1->1->2->3->4->4->5->6
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // 递归返回条件
        if(lists.size() == 0) return nullptr;
        if(lists.size() == 1) return lists[0];
        if(lists.size() == 2) return mergeTwoLists(lists[0], lists[1]);
        
        // 从中间拆分该lists成两个
        int mid = lists.size() / 2;
        vector<ListNode*> sub_lists1(lists.begin(), lists.begin() + mid); // 注意这里 [ ),mid 不会被拿到
        vector<ListNode*> sub_lists2(lists.begin() + mid, lists.end());// 注意这里 [ )，end() 指向最后一个item的下一个位置
        
        // 对左右两边分别递归调用该函数
        ListNode* l1 = mergeKLists(sub_lists1);
        ListNode* l2 = mergeKLists(sub_lists2);
        
        // 调用2 lists 函数
        return mergeTwoLists(l1, l2);
    }
    
    ListNode* mergeTwoLists(ListNode* l1,ListNode* l2)
    {
        ListNode tmp_head(0); // 创建零时头节点类，用于保存返回的头指针，也用于下一行获取迭代用指针
        ListNode* pre = &tmp_head; // 头节点指针， 后面添加新节点始终移动这个指针
        while(l1 && l2)  // 当任意一个List没有遍历完
        {
            if(l1->val < l2->val)
            {
                pre->next = l1;// 头节点指向小的数l1
                l1 = l1->next;// l1 向前移动一步
            }
            else
            {
                pre->next = l2; // l2小，头节点指向l2
                l2 = l2->next;
            }
            pre = pre->next; // 头节点自己向前移动一步，每次pre都是当前已经构建好的list的尾部
        }
        if(l1) // l1 此时已经是原来l1剩余部分的头节点
        {
            pre->next = l1; // l1更长一点，剩余部分直接接在pre 后面
        }
        
        if(l2) // l2 此时已经是原来l2剩余部分的头节点
        {
            pre->next = l2; // l1更长一点，剩余部分直接接在pre 后面
        }
        
        return tmp_head.next;
    }
};
