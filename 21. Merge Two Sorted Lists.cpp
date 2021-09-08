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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        // uses dummy.next to return
        ListNode dummy(0);
        // uses tail to concat ListNodes
        ListNode* tail = &dummy;
        while (l1 && l2) {
            // swaps the pointers so that the pointer l1 always points to the smaller node
            if (l1->val > l2->val) swap(l1, l2);
            tail->next = l1;
            tail = tail->next;
            // always moves forward the smaller pointer
            l1 = l1->next;
        }
        
        if (l1) tail->next = l1;
        if (l2) tail->next = l2;
        
        return dummy.next;
    }
    
    void swap(ListNode* l1, ListNode* l2) {
        ListNode tmp = *l1;
        *l1 = *l2;
        *l2 = tmp;
        return;
    }
};