// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if (!l1) {
            return l2;
        }
        
        if (!l2) {
            return l1;
        }
        
        ListNode dummy(0);
        ListNode* cur = &dummy;
        int carry = 0;
        while (l1 || l2 || carry > 0) {
            int val = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + carry;
            ListNode* node = new ListNode(val % 10);
            cur->next = node;
            cur = cur->next;
            carry = val / 10;
            l1 = (l1 ? l1->next : l1);
            l2 = (l2 ? l2->next : l2);
        }
        
        return dummy.next;
    }
};