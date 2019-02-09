/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;

    Node() {}

    Node(int _val, Node* _next) {
        val = _val;
        next = _next;
    }
};
*/
class Solution {
public:
    Node* insert(Node* head, int insertVal) {
        // 边界检查，空节点
        if(!head)
        {
            // Node headNode(insertVal, nullptr);
            // head = &headNode;
            head = new Node(insertVal, nullptr);
            head->next = head;
            return head;
        }
        
        Node *pre = head, *cur = pre->next;
        while(cur != head)
        {
            // [a<= insertVal <=b] 且
            if(pre->val <=insertVal && cur->val >= insertVal) break;
            // 到了转折点， 比最大的大，或者比最小的小 
            // insertVal<=[a  或  b]<= insertVal 
            if(pre->val > cur->val && (pre->val <= insertVal || cur->val >= insertVal)) break;
            pre = pre->next;
            cur = cur->next;
        }
        pre->next = new Node(insertVal, cur);
        return head;
        
    }
};
